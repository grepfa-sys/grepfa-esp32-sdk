//
// Created by vl0011 on 23. 6. 21.
//

#include <grepfa_payload.h>
#include <ArduinoJson.hpp>
#include <grepfa_type_key_name.h>
#include <sstream>
#include <utility>

std::unique_ptr<grepfa::EventPayload> grepfa::EventPayload::builder() {
    auto payload = new EventPayload;

    std::unique_ptr<EventPayload> ret(payload);
    return ret;
}

std::expected<std::unique_ptr<grepfa::EventPayload>, grepfa::ErrorType>
grepfa::EventPayload::fromJSON(const ArduinoJson::JsonVariantConst doc) {
        auto ret = std::make_unique<EventPayload>();
    auto err = ret->setFromJSONObj2(doc);

    if (err != ErrorType::OK) {
        return std::unexpected<ErrorType>{err};
    }

    ret->values = doc["values"].as<std::vector<PayloadValue>>();

    return ret;
}

std::expected<std::string, grepfa::ErrorType> grepfa::EventPayload::toJSON() noexcept {

    ArduinoJson::DynamicJsonDocument doc(2048);
    auto base = baseJSON2(doc);

    if (!base) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }

    base["values"].set<std::vector<PayloadValue>>(this->values);

    std::stringstream ss;

    ArduinoJson::serializeJson(doc, ss);

    return ss.str();
}


grepfa::EventPayload::EventPayload() :IPayload(MessageType::EVENT) {}

grepfa::EventPayload *grepfa::EventPayload::add(const grepfa::PayloadValue& value) {
    this->values.push_back(value);
    return this;
}

grepfa::EventPayload::EventPayload(
        std::string payloadId,
        time_t timestamp,
        grepfa::NetworkType network,
        grepfa::ConnectionProtocol aProtocol
        ):IPayload(std::move(payloadId), timestamp, network, aProtocol, MessageType::EVENT) {}

grepfa::EventPayload::~EventPayload() = default;

// class EventValue

