#include <sdkconfig.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cstdio>

#include <esp_log.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include <grepfa_type.h>
#include <grepfa_payload.h>
#include <memory>
#include <string>
#include <esp_log.h>
#include <grepfa_connector.h>
#include <grepfa_mqtt.h>
#include <grepfa_wifi.h>
#include <grepfa_sntp.h>
#include <grepfa_neopixel.h>
#include <esp_wifi_types.h>
#include <networking_util.h>

#include <rak3172.h>
#include <esp_task_wdt.h>

static const char * TAG = "app";

//extern "C" void app_main(void)
//{
//
//    esp_err_t ret = nvs_flash_init();
//    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//        /* NVS partition was truncated
//         * and needs to be erased */
//        ESP_ERROR_CHECK(nvs_flash_erase());
//
//        /* Retry nvs_flash_init */
//        ESP_ERROR_CHECK(nvs_flash_init());
//    }
//    ESP_ERROR_CHECK(esp_netif_init());
//    ESP_ERROR_CHECK(esp_event_loop_create_default());
//
//    vTaskDelay(100/portTICK_PERIOD_MS);
//
//
//    GrepfaNeoPixelInit();
//
//    GrepfaNeoPixelOn(100, 0, 0);
//    GrepfaWiFiInit();
//    GrepfaWiFiSTA();
//
//    GrepfaNeoPixelOn(0, 100, 0);
//
//    GrepfaWiFiStartScan(true, false, true);
//    wifi_ap_record_t records[16];
//    uint16_t scanned;
//    GrepfaWiFiGetScanRecord(16, &scanned, records);
//    GrepfaWiFiStopScan();
//    for (int i = 0; i < scanned; ++i) {
//        ESP_LOGI(TAG, "wifi %d ->", i);
//        ESP_LOGI(TAG, "SSID: %s", records[i].ssid);
//        ESP_LOGI(TAG, "AUTH: %s", auth_mode_str(records[i].authmode));
//        puts("=================");
//    }
//
//    GrepfaNeoPixelOn(0, 0, 100);
//    GrepfaWiFiConnectSTA("sys2.4G", "shin0114", true, 15);
//
//    GrepfaNeoPixelOn(0, 100, 100);
//    GrepfaSntpObtainTime();
//
//    std::string endpoint = "mqtts://a2bp9adt6od3cn-ats.iot.ap-northeast-2.amazonaws.com";
//    ESP_LOGI(TAG, "hello");
//
//    auto conn = std::make_unique<grepfa::MqttConnector>(grepfa::Global::getPhysicalId(), nullptr, endpoint);
//    conn->initMqtt(1, true);
//
//    while (1) {
//        conn->sendPayload(grepfa::LogPayload::info("hello world"));
//        vTaskDelay(1000/portTICK_PERIOD_MS);
//    }
//
//}

#define LORAWAN_JOIN_ATTEMPTS           5
#define LORAWAN_MAX_JOIN_INTERVAL_S     15
#define LORAWAN_TX_ATTEMPTS             5

void lora() {
    const char Payload[]                     = {'{', '}'};

    // 5E9D1E0857CF25F1
    const uint8_t APPEUI[8] = { 0x5e, 0x9d, 0x1e, 0x08, 0x57, 0xcf, 0x25, 0xf1 };

    // 5E 9D 1E 08 57 CF 25 F1
    const uint8_t DEVEUI[8] = { 0x5e, 0x9d, 0x1e, 0x08, 0x57, 0xcf, 0x25, 0xf1 };

    // F921D50CD7D02EE3C5E6142154F274B2
    //
    // 0xF9,
    // 0x21,
    // 0xD5,
    // 0x0C,
    // 0xD7,
    // 0xD0,
    // 0x2E,
    // 0xE3,
    // 0xC5,
    // 0xE6,
    // 0x14,
    // 0x21,
    // 0x54,
    // 0xF2,
    // 0x74,
    // 0xB2,
    const uint8_t APPKEY[16] = { 0xF9,
                                 0x21,
                                 0xD5,
                                 0x0C,
                                 0xD7,
                                 0xD0,
                                 0x2E,
                                 0xE3,
                                 0xC5,
                                 0xE6,
                                 0x14,
                                 0x21,
                                 0x54,
                                 0xF2,
                                 0x74,
                                 0xB2 };

    RAK3172_t dev                        = RAK3172_DEFAULT_CONFIG(2, 12, 14, 115200);

    RAK3172_Error_t Error;
    RAK3172_Info_t Info;

    dev.Info = &Info;

    Error = RAK3172_Init(dev);
    if(Error != RAK3172_ERR_OK)
    {
        ESP_LOGE(TAG, "Cannot initialize RAK3172! Error: 0x%04X", static_cast<unsigned int>(Error));
    }

    ESP_LOGI(TAG, "Firmware: %s", Info.Firmware.c_str());
    ESP_LOGI(TAG, "Serial number: %s", Info.Serial.c_str());
    ESP_LOGI(TAG, "Current mode: %u", dev.Mode);

    Error = RAK3172_LoRaWAN_Init(dev, 10, RAK_JOIN_OTAA, DEVEUI, APPEUI, APPKEY, RAK_CLASS_A, RAK_BAND_KR920, RAK_SUB_BAND_NONE);
    if(Error != RAK3172_ERR_OK)
    {
        ESP_LOGE(TAG, "Cannot initialize RAK3172 LoRaWAN! Error: 0x%04X", static_cast<unsigned int>(Error));
    }

    if(!RAK3172_LoRaWAN_isJoined(dev))
    {
        ESP_LOGI(TAG, "Not joined. Rejoin...");

        Error = RAK3172_LoRaWAN_StartJoin(dev, LORAWAN_JOIN_ATTEMPTS, RAK3172_NO_TIMEOUT, true, false, LORAWAN_MAX_JOIN_INTERVAL_S, NULL);
        if(Error != RAK3172_ERR_OK)
        {
            ESP_LOGE(TAG, "Cannot join network! Error: 0x%04X", static_cast<unsigned int>(Error));
        }
    }
    else
    {
        ESP_LOGI(TAG, "Joined...");
    }


    while(true)
    {

        auto ep = grepfa::EventPayload::builder();
        std::string a = "test uuid";
        std::string b = "sensor";
        ep->add(grepfa::PayloadValue::builder(1, a, b, (int)time(NULL)));

        auto payload = ep->toJSON();
        ESP_LOGI(TAG, "%d", payload->length());
        Error = RAK3172_LoRaWAN_Transmit(dev, 3, payload->c_str(), payload->length(), 3, false, nullptr);

        if(Error != RAK3172_ERR_OK)
        {
            ESP_LOGE(TAG, "Cannot transmit message! Error: 0x%04X", static_cast<unsigned int>(Error));
        }

        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main() {
    lora();
}