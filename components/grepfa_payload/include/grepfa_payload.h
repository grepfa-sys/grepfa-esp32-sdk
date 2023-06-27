//
// Created by vl0011 on 23. 6. 20.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_PAYLOAD_H
#define GREPFA_ESP_COMPONENTS_GREPFA_PAYLOAD_H

#include <memory>
#include <string>
#include <vector>
#include <expected>

#include <grepfa_type.h>
#include <grepfa_error.h>
#include <grepfa_uuid.h>

namespace grepfa {
    class LogPayload final : public IPayload{
    private:
        std::string message;
        LogLevel level;

    public:
        LogPayload();
        ~LogPayload() override;

        static std::unique_ptr<IPayload> builder(LogLevel level, const std::string& message) noexcept;

        static std::unique_ptr<IPayload> dev(const std::string& message)   noexcept { return builder(LogLevel::DEVELOP, message);}
        static std::unique_ptr<IPayload> info(const std::string& message)  noexcept { return builder(LogLevel::INFO, message);}
        static std::unique_ptr<IPayload> alert(const std::string& message) noexcept { return builder(LogLevel::ALERT, message);}
        static std::unique_ptr<IPayload> warn(const std::string& message)  noexcept { return builder(LogLevel::WARNING, message);}
        static std::unique_ptr<IPayload> err(const std::string& message)   noexcept { return builder(LogLevel::ERROR, message);}
        static std::unique_ptr<IPayload> fatal(const std::string& message) noexcept { return builder(LogLevel::FATAL, message);}

        std::expected<std::string, grepfa::ErrorType> toJSON() noexcept override;
    };

    class PayloadValue {

    private:
        int channel;
        std::string id;
        std::string value;
        std::string type;
        ValueType valueType;
    public:
        [[nodiscard]] int getChannel() const;
        [[nodiscard]] const std::string &getId() const;
        [[nodiscard]] const std::string &getValue() const;
        [[nodiscard]] const std::string &getType() const;
        [[nodiscard]] ValueType getValueType() const;

        PayloadValue(int channel, std::string id, std::string value, std::string type, ValueType valueType);

        static PayloadValue builder(int channel, const std::string& id, const std::string& type, const std::string& value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, int value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, double value) noexcept;
//      static PayloadValue builder(int channel, const std::string& id, const std::string& type, float value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, bool value) noexcept;

    };

    class EventPayload : public IPayload {
    private:
        std::vector<PayloadValue> values;
    public:
        EventPayload();
        EventPayload(std::string payloadId, time_t timestamp, grepfa::NetworkType network,
                     grepfa::ConnectionProtocol aProtocol);
        ~EventPayload() override;

        static std::unique_ptr<EventPayload> builder();
        static std::expected<std::unique_ptr<EventPayload>, ErrorType> fromJSON(const ArduinoJson::JsonVariantConst doc);
        EventPayload *add(const PayloadValue& value);

        std::expected<std::string, grepfa::ErrorType> toJSON() noexcept override;
    };

    class ControlPayload : public IPayload {

    };

}

namespace ArduinoJson {
    template <>
    struct Converter<grepfa::PayloadValue> {
        static void toJson(const grepfa::PayloadValue& src, JsonVariant dst) {
            dst["value"] = src.getValue();
            dst["type"] = src.getType();
            dst["valueType"] = src.getValueType();
            dst["id"] = src.getId();
            dst["channel"] = src.getChannel();
        }

        static grepfa::PayloadValue fromJson(JsonVariantConst src) {
            return {
                    src["channel"],
                    src["id"],
                    src["value"],
                    src["type"],
                    src["valueType"]
                    };
        }

        static bool checkJson(JsonVariantConst src) {
            return
            src.containsKey("channel") &&
            src.containsKey("id") &&
            src.containsKey("value") &&
            src.containsKey("type") &&
            src.containsKey("valueType");
        }
    };
}

#endif //GREPFA_ESP_COMPONENTS_GREPFA_PAYLOAD_H
