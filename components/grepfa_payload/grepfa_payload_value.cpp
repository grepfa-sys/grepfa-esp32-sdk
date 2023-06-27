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

int grepfa::PayloadValue::getChannel() const {
    return channel;
}

const std::string &grepfa::PayloadValue::getId() const {
    return id;
}

//const std::string &grepfa::PayloadValue::getName() const {
//    return name;
//}

const std::string &grepfa::PayloadValue::getValue() const {
    return value;
}

const std::string &grepfa::PayloadValue::getType() const {
    return type;
}

grepfa::ValueType grepfa::PayloadValue::getValueType() const {
    return valueType;
}

