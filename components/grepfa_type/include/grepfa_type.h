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
        LOG,
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

    std::string ConnectionProtocolToString(NetworkType type);
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
        std::expected<std::unique_ptr<ArduinoJson::DynamicJsonDocument>, grepfa::ErrorType> baseJSON2() noexcept;
        grepfa::ErrorType setFromJSONObj(cJSON*) noexcept;

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

#endif //GREPFA_ESP_COMPONENTS_GREPFA_TYPE_H
