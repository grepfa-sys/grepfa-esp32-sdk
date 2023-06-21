//
// Created by vl0011 on 23. 6. 20.
//

#include <grepfa_payload.h>
#include <cJSON.h>

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
    auto base = baseJSON();
    if (!base) {
        return std::unexpected<grepfa::ErrorType>{grepfa::ErrorType::ERR_JSON};
    }

    auto obj = base.value();

    cJSON_AddStringToObject(obj, "log", message.c_str());
    if(cJSON_AddStringToObject(obj, "level", grepfa::LogLevelToString(level).c_str()) == nullptr) {
        return std::unexpected<grepfa::ErrorType>{grepfa::ErrorType::ERR_JSON};
    }
    char* payload = cJSON_PrintUnformatted(obj);
    cJSON_Delete(obj);
    std::string ret = payload;
    cJSON_free(payload);
    return ret;
}

