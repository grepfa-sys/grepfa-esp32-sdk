//
// Created by vl0011 on 23. 6. 20.
//

#ifndef GREPFA_ESP_COMPONENTS_GREPFA_CONNECTOR_H
#define GREPFA_ESP_COMPONENTS_GREPFA_CONNECTOR_H

#include <functional>

#include <grepfa_error.h>
#include <grepfa_connector.h>
#include <grepfa_type.h>


namespace grepfa{
    class IConnectorCallback {
        virtual void connected() = 0;
        virtual void received(IPayload payload) = 0;
        virtual void disconnected() = 0;
    };

    class Connector {
    private:
        std::string connectorId;
    protected:
        IConnectorCallback* callback;
    public:
        virtual ~Connector() = default;
        virtual ErrorType sendPayload(std::unique_ptr<grepfa::IPayload> payload) = 0;
        Connector(const std::string&  id, IConnectorCallback* callback);
//        ErrorType subscribe();
    };


}

#endif //GREPFA_ESP_COMPONENTS_GREPFA_CONNECTOR_H
