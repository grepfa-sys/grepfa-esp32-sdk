//
// Created by vl0011 on 23. 6. 20.
//

#include <grepfa_payload.h>
#include <cJSON.h>
#include <sstream>

grepfa::LogPayload::LogPayload() {
    this->type = MessageType::LOG;
    this->level = LogLevel::UNKNOWN;
}

grepfa::LogPayload::~LogPayload() = default;

std::unique_ptr<grepfa::IPayload> grepfa::LogPayload::builder(LogLevel level, const std::string& message) noexcept {
    auto payload = std::make_unique<LogPayload>();
    payload->message = message;
    payload->level = level;
    std::unique_ptr<IPayload> ret = std::move(payload);
    return ret;
}

std::expected<std::string, grepfa::ErrorType> grepfa::LogPayload::toJSON() noexcept {
    ArduinoJson::DynamicJsonDocument doc(2048);

    auto base = baseJSON2(doc);
    if (!base) {
        return std::unexpected<grepfa::ErrorType>{grepfa::ErrorType::ERR_JSON};
    }

    base["log"] = ArduinoJson::JsonString(message.c_str(), ArduinoJson::JsonString::Copied);
    base["level"].set(level);

    std::stringstream ss;
    ArduinoJson::serializeJson(base, ss);

    return ss.str();
}

