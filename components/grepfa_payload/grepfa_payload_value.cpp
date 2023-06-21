//
// Created by vl0011 on 23. 6. 21.
//

#include <grepfa_payload.h>
#include <grepfa_type_key_name.h>

grepfa::PayloadValue::PayloadValue(int channel, std::string id, std::string value, std::string type,
                                   grepfa::ValueType valueType) :channel(channel), id(std::move(id)), value(std::move(value)), type(std::move(type)), valueType(valueType) {}


grepfa::PayloadValue grepfa::PayloadValue::builder(
        int channel,
        const std::string& id,
        const std::string& type,
        const std::string& value
) noexcept {
    return {channel, id, value, type, grepfa::ValueType::STRING};
}

grepfa::PayloadValue grepfa::PayloadValue::builder(
        int channel,
        const std::string& id,
        const std::string& type,
        int value
) noexcept {
    return {channel, id, std::to_string(value), type, grepfa::ValueType::INTEGER};
}

grepfa::PayloadValue grepfa::PayloadValue::builder(
        int channel,
        const std::string& id,
        const std::string& type,
        double value
) noexcept {
    return {channel, id, std::to_string(value), type, grepfa::ValueType::FLOAT};
}

//std::unique_ptr<grepfa::EventValue> grepfa::EventValue::builder(
//        const std::string& id,
//        const std::string& type,
//        float value
//) {
//    return std::make_unique<grepfa::EventValue>(id, std::to_string(value), type, grepfa::ValueType::FLOAT);
//}

grepfa::PayloadValue grepfa::PayloadValue::builder(
        int channel,
        const std::string& id,
        const std::string& type,
        bool value
) noexcept {
    return {channel, id, std::to_string(value), type, grepfa::ValueType::BOOLEAN};
}


std::expected<cJSON *, grepfa::ErrorType> grepfa::PayloadValue::baseJSON() noexcept {
    auto ret = cJSON_CreateObject();
    cJSON_AddNumberToObject(ret, "channel", channel);
    cJSON_AddStringToObject(ret, "name", name.c_str());
    cJSON_AddStringToObject(ret, "id",   id.c_str());
    cJSON_AddStringToObject(ret, "valueType", grepfa::ValueTypeToString(valueType).c_str());
    cJSON_AddStringToObject(ret, "type", type.c_str());
    if(cJSON_AddStringToObject(ret, "value", value.c_str()) == nullptr) {
        return std::unexpected<grepfa::ErrorType> {grepfa::ErrorType::ERR_JSON};
    }

    return ret;
}

std::expected<grepfa::PayloadValue, grepfa::ErrorType> grepfa::PayloadValue::buildWithJSONObj(cJSON *obj) {
    if (obj == nullptr) {
        return std::unexpected<ErrorType>{ErrorType::INVALID_ARG};
    }

    cJSON* el;

    printf("1\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "channel");
    if (el == nullptr || !cJSON_IsNumber(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    int channel = cJSON_GetNumberValue(el);
    printf("2\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "id");
    if (el == nullptr || !cJSON_IsString(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    std::string id = cJSON_GetStringValue(el);
    printf("3\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "name");
    if (el == nullptr || !cJSON_IsString(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    std::string name = cJSON_GetStringValue(el);
    printf("4\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "value");
    if (el == nullptr || !cJSON_IsString(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    std::string value = cJSON_GetStringValue(el);
    printf("5\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "type");
    if (el == nullptr || !cJSON_IsString(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    std::string type = cJSON_GetStringValue(el);
    printf("6\n");
    el = cJSON_GetObjectItemCaseSensitive(obj, "valueType");
    if (el == nullptr || !cJSON_IsString(el)) {
        return std::unexpected<ErrorType> {ErrorType::ERR_JSON};
    }
    ValueType vt = ValueTypeFromString(cJSON_GetStringValue(el));

    return PayloadValue(channel, id, value, type, vt);
}

