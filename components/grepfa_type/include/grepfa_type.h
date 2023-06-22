//
// Created by vl0011 on 23. 6. 20.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_TYPE_H
#define GREPFA_ESP_COMPONENTS_GREPFA_TYPE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <expected>

#include <cJSON.h>
#include <grepfa_error.h>
#include <ArduinoJson.hpp>
#include <vector>

namespace grepfa {

    enum class NetworkType : int {
        UNKNOWN = 0,
        WIFI,
        ETHERNET,
        LORA,
    };

    enum class ConnectionProtocol : int {
        UNKNOWN = 0,
        MQTT,
        HTTP,
        LORAWAN,
    };

    enum class LogLevel : int {
        UNKNOWN = 0,
        DEVELOP,
        INFO,
        ALERT,
        WARNING,
        ERROR,
        FATAL,
    };

    enum class MessageType : int {
        UNKNOWN = 0,
        SYSTEM,
        LOG,
        EVENT,
        CONTROL
    };

    enum class ValueType : int {
        UNKNOWN = 0,
        STRING,
        FLOAT,
        INTEGER,
        BOOLEAN,
    };
}

namespace grepfa{

    std::string NetworkTypeToString(NetworkType type);
    NetworkType NetworkTypeFromString(const std::string& type);

    std::string ConnectionProtocolToString(ConnectionProtocol type);
    ConnectionProtocol ConnectionProtocolFromString(const std::string& type);

    std::string ValueTypeToString(ValueType type);
    ValueType ValueTypeFromString(const std::string& type);

    std::string MessageTypeToString(MessageType type);
    MessageType MessageTypeFromString(const std::string& type);

    std::string LogLevelToString(LogLevel level);
    LogLevel LogLevelFromString(const std::string& level);

    class Global {
    private:
        inline const static std::string physicalId = "TODO";
        inline const static std::string rootCA = "TODO";
        inline const static std::string clientCRT = "TODO";
        inline const static std::string clientKEY = "TODO";

        Global() = default;
    public:
        static const std::string &getPhysicalId();
        static const std::string &getRootCa();
        static const std::string &getClientCrt();
        static const std::string &getClientKey();
    };

    class IPayload {
    protected:
        std::string thingsId;
        std::string payloadId;
        time_t timestamp;

        NetworkType network = NetworkType::UNKNOWN;
        ConnectionProtocol protocol = ConnectionProtocol::UNKNOWN;
        MessageType type = MessageType::UNKNOWN;

        std::expected<cJSON*, grepfa::ErrorType> baseJSON() noexcept;

        grepfa::ErrorType setFromJSONObj(cJSON*) noexcept;

        ArduinoJson::JsonVariant baseJSON2(ArduinoJson::JsonVariant doc) noexcept;
        grepfa::ErrorType setFromJSONObj2(ArduinoJson::JsonVariantConst doc) noexcept;

    public:
        IPayload();

        virtual ~IPayload() noexcept = default;
        void renew();
        void setNetwork(NetworkType network) noexcept;
        void setProtocol(ConnectionProtocol protocol) noexcept;
        void setType(MessageType type) noexcept;
        virtual std::expected<std::string, grepfa::ErrorType> toJSON() noexcept = 0 ;
    };

}

namespace ArduinoJson{
    template<>
    struct Converter<grepfa::NetworkType> {
        static void toJson(const grepfa::NetworkType type, JsonVariant dst) {
            dst.set(JsonString(grepfa::NetworkTypeToString(type).c_str(), JsonString::Copied));
        }
        static grepfa::NetworkType fromJson(JsonVariantConst src) {
            auto str = src.as<JsonString>();
            return grepfa::NetworkTypeFromString(str.c_str());
        }
        static bool checkJson(JsonVariantConst src) {
            return true;
        }
    };

    template<>
    struct Converter<grepfa::ConnectionProtocol> {
        static void toJson(const grepfa::ConnectionProtocol type, JsonVariant dst) {
            dst.set(JsonString(grepfa::ConnectionProtocolToString(type).c_str(), JsonString::Copied));
        }
        static grepfa::ConnectionProtocol fromJson(JsonVariantConst src) {
            auto str = src.as<JsonString>();
            return grepfa::ConnectionProtocolFromString(str.c_str());
        }
        static bool checkJson(JsonVariantConst src) {
            return true;
        }
    };

    template<>
    struct Converter<grepfa::ValueType> {
        static void toJson(const grepfa::ValueType type, JsonVariant dst) {
            dst.set(JsonString(grepfa::ValueTypeToString(type).c_str(), JsonString::Copied));
        }
        static grepfa::ValueType fromJson(JsonVariantConst src) {
            auto str = src.as<JsonString>();
            return grepfa::ValueTypeFromString(str.c_str());
        }
        static bool checkJson(JsonVariantConst src) {
            return true;
        }
    };

    template<>
    struct Converter<grepfa::MessageType> {
        static void toJson(const grepfa::MessageType type, JsonVariant dst) {
            dst.set(JsonString(grepfa::MessageTypeToString(type).c_str(), JsonString::Copied));
        }
        static grepfa::MessageType fromJson(JsonVariantConst src) {
            auto str = src.as<JsonString>();
            return grepfa::MessageTypeFromString(str.c_str());
        }
        static bool checkJson(JsonVariantConst src) {
            return true;
        }
    };

    template<>
    struct Converter<grepfa::LogLevel> {
        static void toJson(const grepfa::LogLevel type, JsonVariant dst) {
            dst.set(JsonString(grepfa::LogLevelToString(type).c_str(), JsonString::Copied));
        }
        static grepfa::LogLevel fromJson(JsonVariantConst src) {
            auto str = src.as<JsonString>();
            return grepfa::LogLevelFromString(str.c_str());
        }
        static bool checkJson(JsonVariantConst src) {
            return true;
        }
    };

    template <typename T>
    struct Converter<std::vector<T> > {
        static void toJson(const std::vector<T>& src, JsonVariant dst) {
            JsonArray array = dst.to<JsonArray>();
            for (T item : src)
                array.add(item);
        }

        static std::vector<T> fromJson(JsonVariantConst src) {
            std::vector<T> dst;
            for (T item : src.as<JsonArrayConst>())
                dst.push_back(item);
            return dst;
        }

        static bool checkJson(JsonVariantConst src) {
            JsonArrayConst array = src;
            bool result = array;
            for (JsonVariantConst item : array)
                result &= item.is<T>();
            return result;
        }
    };
}
#endif //GREPFA_ESP_COMPONENTS_GREPFA_TYPE_H
