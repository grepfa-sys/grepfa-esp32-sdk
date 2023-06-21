//
// Created by vl0011 on 23. 6. 21.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_TYPE_KEY_NAME_H
#define GREPFA_ESP_COMPONENTS_GREPFA_TYPE_KEY_NAME_H

#define NETWORK_TYPE_UNKNOWN_KEY     "unknown"
#define NETWORK_TYPE_WIFI_KEY        "wifi"
#define NETWORK_TYPE_ETHERNET_KEY    "ethernet"
#define NETWORK_TYPE_LORA_KEY        "lora"

#define CONNECTION_PROTOCOL_UNKNOWN_KEY    "unknown"
#define CONNECTION_PROTOCOL_MQTT_KEY       "mqtt"
#define CONNECTION_PROTOCOL_HTTP_KEY       "http"
#define CONNECTION_PROTOCOL_LORAWAN_KEY    "lorawan"

#define VALUE_TYPE_UNKNOWN_KEY  "unknown"
#define VALUE_TYPE_FLOAT_KEY    "float"
#define VALUE_TYPE_INTEGER_KEY  "integer"
#define VALUE_TYPE_STRING_KEY   "string"
#define VALUE_TYPE_BOOLEAN_KEY  "boolean"

#define MESSAGE_TYPE_UNKNOWN_KEY    "unknown"
#define MESSAGE_TYPE_LOG_KEY        "log"
#define MESSAGE_TYPE_SYSTEM_KEY     "system"
#define MESSAGE_TYPE_CONTROL_KEY    "control"
#define MESSAGE_TYPE_EVENT_KEY      "event"

#define LOG_LEVEL_UNKNOWN_KEY   "unknown"
#define LOG_LEVEL_DEVELOP_KEY   "develop"
#define LOG_LEVEL_INFO_KEY      "info"
#define LOG_LEVEL_ALERT_KEY     "alert"
#define LOG_LEVEL_WARNING_KEY   "warning"
#define LOG_LEVEL_ERROR_KEY     "error"
#define LOG_LEVEL_FATAL_KEY     "fatal"

#define JSON_KEY_PHYSICAL_DEVICE_ID "things_id"
#define JSON_KEY_PAYLOAD_ID         "payload_id"
#define JSON_KEY_TIME               "time"
#define JSON_KEY_NETWORK            "network"
#define JSON_KEY_PROTOCOL           "protocol"
#define JSON_KEY_MESSAGE_TYPE       "message_type"

#endif //GREPFA_ESP_COMPONENTS_GREPFA_TYPE_KEY_NAME_H
