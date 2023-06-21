//
// Created by vl0011 on 23. 6. 17.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H
#define GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H

#include <expected>
#include <grepfa_error.h>
#include <unordered_map>

namespace grepfa{
    class GrepfaConnector{
    private:
        char* rootCA;
        char* clientCRT;
        char* clientKEY;

//        std::unordered_map devices;

        

    public:
        GrepfaConnector(
                const char* CA,
                const char* crt,
                const char* key
        );

        std::expected<void, ErrorType> ConnectBroker(const char* uri);

        ~GrepfaConnector();
    };

}



#endif //GREPFA_ESP_COMPONENTS_GREPFA_MQTT_H
