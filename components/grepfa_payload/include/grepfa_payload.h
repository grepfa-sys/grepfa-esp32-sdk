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
        std::string name;
        std::string value;
        std::string type;
        ValueType valueType;
    public:
        PayloadValue(int channel, std::string id, std::string value, std::string type, ValueType valueType);

        static PayloadValue builder(int channel, const std::string& id, const std::string& type, const std::string& value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, int value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, double value) noexcept;
//      static PayloadValue builder(int channel, const std::string& id, const std::string& type, float value) noexcept;
        static PayloadValue builder(int channel, const std::string& id, const std::string& type, bool value) noexcept;

        static std::expected<PayloadValue, ErrorType> buildWithJSONObj(cJSON* obj);

        std::expected<cJSON*, grepfa::ErrorType> baseJSON() noexcept;
    };

    class EventPayload : public IPayload {
    private:
        std::vector<PayloadValue> values;
    public:
        EventPayload();
        ~EventPayload() override;

        static std::unique_ptr<EventPayload> builder();
        static std::expected<std::unique_ptr<EventPayload>, ErrorType> fromJSON(const std::string &jsonStr);

        EventPayload *add(const PayloadValue& value);
        std::expected<std::string, grepfa::ErrorType> toJSON() noexcept override;
    };

    class ControlPayload : public IPayload {

    };
}

namespace ArduinoJson {
//    template <>
//    struct Converter<grepfa::PayloadValue> {
//        static void toJson(const std::vector<T>& src, JsonVariant dst) {
//            JsonArray array = dst.to<JsonArray>();
//            for (T item : src)
//                array.add(item);
//        }
//
//        static std::vector<T> fromJson(JsonVariantConst src) {
//            std::vector<T> dst;
//            for (T item : src.as<JsonArrayConst>())
//                dst.push_back(item);
//            return dst;
//        }
//
//        static bool checkJson(JsonVariantConst src) {
//            JsonArrayConst array = src;
//            bool result = array;
//            for (JsonVariantConst item : array)
//                result &= item.is<T>();
//            return result;
//        }
//    };
}

#endif //GREPFA_ESP_COMPONENTS_GREPFA_PAYLOAD_H
