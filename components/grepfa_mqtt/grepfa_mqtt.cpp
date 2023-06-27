//
// Created by vl0011 on 23. 6. 17.
//

static const char * TAG = "mqtt";

#include <esp_log.h>

#include <mqtt_client.h>
#include <grepfa_mqtt.h>
#include <grepfa_type.h>
#include <grepfa_type_key_name.h>

int grepfa::MqttConnector::initMqtt(int qos, bool wait) {
    this-> qos = qos;
    const esp_mqtt_client_config_t mqtt_cfg{
        .broker = {
                .address = { .uri = endpoint.c_str() },
                .verification = { .certificate = Global::getRootCa() }
        },
        .credentials = {
                .authentication = {
                        .certificate = Global::getClientCrt(),
                        .key = Global::getClientKey()
                }
        }
    };

    ESP_LOGI(TAG, "start mqtt connector");
    ESP_LOGI(TAG, "endpoint: %s", endpoint.c_str());
    ESP_LOGI(TAG, "qos: %d", qos);


    handler = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(handler, MQTT_EVENT_ANY , evRouter, this);
    esp_mqtt_client_start(handler);

    if (wait){
        ESP_LOGI(TAG, "waiting mqtt broker server connect...");
        useWait = true;
        connect_sem = xSemaphoreCreateBinary();
        xSemaphoreTake(connect_sem, portMAX_DELAY);
    }

    return 0;
}

grepfa::MqttConnector::~MqttConnector() {
    esp_mqtt_client_destroy(handler);
    if (connect_sem) {
        vSemaphoreDelete(connect_sem);
    }
}

void grepfa::MqttConnector::evRouter(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,
                                     void *event_data) {
    ESP_LOGI(TAG, "event occurs");
    auto it = (MqttConnector*) event_handler_arg;
    it->eventFunc(event_base, event_id, event_data);
}

void grepfa::MqttConnector::unlockConnect() {
    if (useWait && connect_sem) {
        xSemaphoreGive(connect_sem);
    }
}

void grepfa::MqttConnector::disconnected() {
    if (connect_sem) {
        vSemaphoreDelete(connect_sem);
        connect_sem = nullptr;
    }
}


void grepfa::MqttConnector::eventFunc(esp_event_base_t base, int32_t event_id, void *data) {
    esp_mqtt_event_handle_t event;
    switch ((esp_mqtt_event_id_t) event_id) {

        case MQTT_EVENT_ERROR:
            event = static_cast<esp_mqtt_event_handle_t>(data);
            ESP_LOGI(TAG, "mqtt error %d", event->error_handle->error_type);
            break;
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "mqtt broker server connected");
            this->unlockConnect();
            sendPayload(grepfa::LogPayload::info("connected"));
            break;
        case MQTT_EVENT_DISCONNECTED:
            disconnected();
            break;
        case MQTT_EVENT_DATA:
            event = static_cast<esp_mqtt_event_handle_t>(data);
            this->data(event);
            break;
        default:
            break;
    }
}


grepfa::ErrorType grepfa::MqttConnector::sendPayload(std::unique_ptr<grepfa::IPayload> payload) {
    payload->setProtocol(grepfa::ConnectionProtocol::MQTT);
    payload->setNetwork(grepfa::NetworkType::WIFI);
    auto value = payload->toJSON();
    auto topic = MQTT_TOPIC_HEADER + payload->getThingsId() + "/" + grepfa::MessageTypeToString(payload->getType());
    esp_mqtt_client_publish(handler, topic.c_str(), value->c_str(), value->length(), qos, 0);

    return grepfa::ErrorType::OK;
}

void grepfa::MqttConnector::data(esp_mqtt_event_handle_t msg) {
    ESP_LOGI(TAG, "data received");
    std::string topic = msg->topic;

    ArduinoJson::DynamicJsonDocument doc(2048);
    ArduinoJson::deserializeJson(doc, msg->data);

}

grepfa::MqttConnector::MqttConnector(const std::string& id, IConnectorCallback* callback, const std::string& endpoint) : Connector(id, callback) {
    this->endpoint = endpoint;
}

