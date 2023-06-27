//
// Created by vl0011 on 23. 6. 17.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H
#define GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H


#include <expected>
#include <grepfa_error.h>
#include <unordered_map>
#include <grepfa_connector.h>
#include <memory>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <grepfa_payload.h>
#include <mqtt_client.h>

namespace grepfa{
    class MqttConnector : public Connector {
    private:
        int qos = 1;
        std::string endpoint;
        esp_mqtt_client_handle_t handler = nullptr;
        SemaphoreHandle_t connect_sem = nullptr;

        bool useWait = false;
        bool connected = false;

        static void evRouter(void* event_handler_arg,
                             esp_event_base_t event_base,
                             int32_t event_id,
                             void* event_data);

        void unlockConnect();
        void disconnected();
        void data(esp_mqtt_event_handle_t msg);
        void eventFunc(esp_event_base_t base, int32_t event_id, void *data);

    public:
        MqttConnector(const std::string& id, IConnectorCallback* callback, const std::string& endpoint);

        int initMqtt(int qos, bool wait);
        ~MqttConnector() override;
        ErrorType sendPayload(std::unique_ptr<grepfa::IPayload> payload) override;
    };
}



#endif //GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H
