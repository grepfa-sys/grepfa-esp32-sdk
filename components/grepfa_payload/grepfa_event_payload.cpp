//
// Created by vl0011 on 23. 6. 21.
//

#include <grepfa_payload.h>
#include <ArduinoJson.hpp>
#include <grepfa_type_key_name.h>

std::unique_ptr<grepfa::EventPayload> grepfa::EventPayload::builder() {
    auto payload = new EventPayload;

    std::unique_ptr<EventPayload> ret(payload);
    return ret;
}

std::expected<std::unique_ptr<grepfa::EventPayload>, grepfa::ErrorType> grepfa::EventPayload::fromJSON(const std::string& jsonStr) {
    cJSON* obj = cJSON_ParseWithLength(jsonStr.c_str(), jsonStr.length());
    if (obj == nullptr) {
        return std::unexpected<ErrorType>{ErrorType::ERR_JSON};
    }
    auto ep = std::make_unique<EventPayload>();
    auto ret = ep->setFromJSONObj(obj);

    if (ret != ErrorType::OK) {
        cJSON_Delete(obj);
        return std::unexpected<ErrorType> {ret};
    }
    cJSON_GetObjectItemCaseSensitive(obj, "values");
    cJSON* valEl;

    cJSON_ArrayForEach(valEl, obj) {
        auto p = PayloadValue::buildWithJSONObj(valEl);
        if (p) {
            ep->values.push_back(p.value());
        } else {
            return std::unexpected<ErrorType>{p.error()};
        }
    }

    return ep;
}

std::expected<std::string, grepfa::ErrorType> grepfa::EventPayload::toJSON() noexcept {
    auto base = baseJSON();

    if (!base) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }

    auto obj = base.value();
    auto arr = cJSON_CreateArray();
    for (auto &el : values) {

        auto oe = el.baseJSON();
        if (!oe) {
            return std::unexpected<ErrorType>{ErrorType::ERR_JSON};
        }
        cJSON_AddItemToArray(arr, oe.value());
    }

    cJSON_AddItemToObject(obj, "values", arr);

    auto raw = cJSON_Print(obj);
    std::string ret = raw;
    cJSON_Delete(obj);
    cJSON_free(raw);

    return ret;
}

//grepfa::EventPayload *grepfa::EventPayload::add(std::unique_ptr<PayloadValue> value) {
//    this->values.push_back(std::move(value));
//    return this;
//}

grepfa::EventPayload::EventPayload() {
    ArduinoJson::DynamicJsonDocument
    this->type = MessageType::EVENT;
}

grepfa::EventPayload *grepfa::EventPayload::add(const grepfa::PayloadValue& value) {
    this->values.push_back(value);
    return this;
}

grepfa::EventPayload::~EventPayload() = default;

// class EventValue

