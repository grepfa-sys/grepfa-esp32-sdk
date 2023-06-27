//
// Created by vl0011 on 23. 6. 20.
//

#include <grepfa_type_key_name.h>

#include <grepfa_type.h>
#include <grepfa_uuid.h>
#include <ctime>
#include <utility>




static std::unordered_map<grepfa::NetworkType, std::string> NetworkTypeStringMap = {
        {grepfa::NetworkType::UNKNOWN, NETWORK_TYPE_UNKNOWN_KEY},
        {grepfa::NetworkType::WIFI, NETWORK_TYPE_WIFI_KEY},
        {grepfa::NetworkType::ETHERNET, NETWORK_TYPE_ETHERNET_KEY},
        {grepfa::NetworkType::LORA, NETWORK_TYPE_LORA_KEY},
};


static std::unordered_map<grepfa::ConnectionProtocol, std::string> ConnectionProtocolStringMap = {
        {grepfa::ConnectionProtocol::UNKNOWN, CONNECTION_PROTOCOL_UNKNOWN_KEY},
        {grepfa::ConnectionProtocol::MQTT, CONNECTION_PROTOCOL_MQTT_KEY},
        {grepfa::ConnectionProtocol::HTTP, CONNECTION_PROTOCOL_HTTP_KEY},
        {grepfa::ConnectionProtocol::LORAWAN, CONNECTION_PROTOCOL_LORAWAN_KEY},
};


static std::unordered_map<grepfa::ValueType, std::string> ValueTypeStringMap = {
        {grepfa::ValueType::UNKNOWN, VALUE_TYPE_UNKNOWN_KEY},
        {grepfa::ValueType::FLOAT, VALUE_TYPE_FLOAT_KEY},
        {grepfa::ValueType::INTEGER, VALUE_TYPE_INTEGER_KEY},
        {grepfa::ValueType::STRING, VALUE_TYPE_STRING_KEY},
        {grepfa::ValueType::BOOLEAN, VALUE_TYPE_BOOLEAN_KEY},
};



static std::unordered_map<grepfa::MessageType, std::string> MessageTypeStringMap = {
        {grepfa::MessageType::UNKNOWN, MESSAGE_TYPE_UNKNOWN_KEY},
        {grepfa::MessageType::LOG, MESSAGE_TYPE_LOG_KEY},
        {grepfa::MessageType::SYSTEM, MESSAGE_TYPE_SYSTEM_KEY},
        {grepfa::MessageType::EVENT, MESSAGE_TYPE_EVENT_KEY},
        {grepfa::MessageType::CONTROL, MESSAGE_TYPE_CONTROL_KEY},
};



static std::unordered_map<grepfa::LogLevel, std::string> LogLevelStringMap = {
        {grepfa::LogLevel::UNKNOWN, LOG_LEVEL_UNKNOWN_KEY},
        {grepfa::LogLevel::FATAL, LOG_LEVEL_FATAL_KEY},
        {grepfa::LogLevel::ERROR, LOG_LEVEL_ERROR_KEY},
        {grepfa::LogLevel::WARNING, LOG_LEVEL_WARNING_KEY},
        {grepfa::LogLevel::ALERT, LOG_LEVEL_ALERT_KEY},
        {grepfa::LogLevel::INFO, LOG_LEVEL_INFO_KEY},
        {grepfa::LogLevel::DEVELOP, LOG_LEVEL_DEVELOP_KEY},
};

void grepfa::IPayload::setNetwork(grepfa::NetworkType network) noexcept {
    this->network = network;
}

void grepfa::IPayload::setProtocol(grepfa::ConnectionProtocol protocol) noexcept {
    this->protocol = protocol;
}

void grepfa::IPayload::setType(grepfa::MessageType type) noexcept {
    this->type = type;
}


void grepfa::IPayload::renew() {
    timestamp = time(nullptr);
}

grepfa::IPayload::IPayload() {
    thingsId = Global::getPhysicalId();
    char uuid_buf[UUID_STR_LEN];
    random_uuid(uuid_buf);
    payloadId = uuid_buf;
    timestamp = time(nullptr);
}

ArduinoJson::JsonVariant
grepfa::IPayload::baseJSON2(ArduinoJson::JsonVariant doc) noexcept {
    doc[JSON_KEY_TIME] = this->timestamp;
    doc[JSON_KEY_PHYSICAL_DEVICE_ID] = this->thingsId;
//    doc[JSON_KEY_PAYLOAD_ID] = this->payloadId;
//
//    doc[JSON_KEY_NETWORK] = this->network;
//    doc[JSON_KEY_PROTOCOL] = this->protocol;
//    doc[JSON_KEY_MESSAGE_TYPE] = this->type;
    return doc;
}

grepfa::ErrorType grepfa::IPayload::setFromJSONObj2(ArduinoJson::JsonVariantConst doc) noexcept {
    if (!doc.containsKey(JSON_KEY_TIME))
        return ErrorType::ERR_JSON;
    if (!doc.containsKey(JSON_KEY_PHYSICAL_DEVICE_ID))
        return ErrorType::ERR_JSON;
    if (!doc.containsKey(JSON_KEY_PAYLOAD_ID))
        return ErrorType::ERR_JSON;
    if (!doc.containsKey(JSON_KEY_NETWORK))
        return ErrorType::ERR_JSON;
    if (!doc.containsKey(JSON_KEY_PROTOCOL))
        return ErrorType::ERR_JSON;
    if (!doc.containsKey(JSON_KEY_MESSAGE_TYPE))
        return ErrorType::ERR_JSON;

    this->timestamp = doc[JSON_KEY_TIME];
    this->thingsId = doc[JSON_KEY_PHYSICAL_DEVICE_ID].as<ArduinoJson::JsonString>().c_str();
    this->payloadId = doc[JSON_KEY_PAYLOAD_ID].as<ArduinoJson::JsonString>().c_str();

    this->network = doc[JSON_KEY_NETWORK].as<NetworkType>();
    this->protocol = doc[JSON_KEY_PROTOCOL].as<ConnectionProtocol>();
    this->type = doc[JSON_KEY_MESSAGE_TYPE].as<MessageType>();

    return ErrorType::OK;
}

grepfa::IPayload::IPayload(std::string payloadId, time_t timestamp, grepfa::NetworkType network,
                           grepfa::ConnectionProtocol aProtocol, grepfa::MessageType type) : payloadId(std::move(payloadId)),
                                                                                             timestamp(timestamp),
                                                                                             network(network),
                                                                                             protocol(aProtocol),
                                                                                             type(type) {
    thingsId = Global::getPhysicalId();
    char uuid_buf[UUID_STR_LEN];
    random_uuid(uuid_buf);
    payloadId = uuid_buf;
    timestamp = time(nullptr);
}

grepfa::IPayload::IPayload(grepfa::MessageType type) : type(type) {
    thingsId = Global::getPhysicalId();
    char uuid_buf[UUID_STR_LEN];
    random_uuid(uuid_buf);
    payloadId = uuid_buf;
    timestamp = time(nullptr);
}

const std::string &grepfa::IPayload::getThingsId() const {
    return thingsId;
}

const std::string &grepfa::IPayload::getPayloadId() const {
    return payloadId;
}

time_t grepfa::IPayload::getTimestamp() const {
    return timestamp;
}

grepfa::NetworkType grepfa::IPayload::getNetwork() const {
    return network;
}

grepfa::ConnectionProtocol grepfa::IPayload::getAProtocol() const {
    return protocol;
}

grepfa::MessageType grepfa::IPayload::getType() const {
    return type;
}

std::string grepfa::NetworkTypeToString(grepfa::NetworkType type) {
    return NetworkTypeStringMap[type];
}

grepfa::NetworkType grepfa::NetworkTypeFromString(const std::string &type) {
    for (const auto& x: NetworkTypeStringMap) if (x.second == type) return x.first;
    return NetworkType::UNKNOWN;
}

std::string grepfa::ConnectionProtocolToString(grepfa::ConnectionProtocol type) {
    return ConnectionProtocolStringMap[type];
}

grepfa::ConnectionProtocol grepfa::ConnectionProtocolFromString(const std::string &type) {
    for (const auto& x: ConnectionProtocolStringMap) if (x.second == type) return x.first;
    return ConnectionProtocol::UNKNOWN;
}

std::string grepfa::ValueTypeToString(grepfa::ValueType type) {
    return ValueTypeStringMap[type];
}

grepfa::ValueType grepfa::ValueTypeFromString(const std::string &type) {
    for (const auto& x: ValueTypeStringMap) if (x.second == type) return x.first;
    return ValueType::UNKNOWN;
}

std::string grepfa::MessageTypeToString(grepfa::MessageType type) {
    return MessageTypeStringMap[type];
}

grepfa::MessageType grepfa::MessageTypeFromString(const std::string &type) {
    for (const auto& x: MessageTypeStringMap) if (x.second == type) return x.first;
    return MessageType::UNKNOWN;
}

std::string grepfa::LogLevelToString(grepfa::LogLevel level) {
    return LogLevelStringMap[level];
}

grepfa::LogLevel grepfa::LogLevelFromString(const std::string &level) {
    for (const auto& x: LogLevelStringMap) if (x.second == level) return x.first;
    return LogLevel::UNKNOWN;
}

const std::string &grepfa::Global::getPhysicalId() {
    return physicalId;
}

const char* grepfa::Global::getRootCa() {
    return rootCA;
}

const char* grepfa::Global::getClientCrt() {
    return clientCRT;
}

const char* grepfa::Global::getClientKey() {
    return clientKEY;
}