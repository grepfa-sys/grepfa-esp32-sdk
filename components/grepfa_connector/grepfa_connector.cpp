//
// Created by vl0011 on 23. 6. 20.
//

#include <grepfa_connector.h>
#include <expected>
#include <grepfa_error.h>

namespace grepfa {
    class GrepfaPayload{
        char * payload;
        int size;
        char * type;
    };

    class IGrepfaDevice{
    public:
        virtual ErrorType SendValue(char*, int) = 0;
        virtual void RecvCallback(GrepfaPayload) = 0;
    };
    class IGrepfaConnector{
    public:
        virtual ErrorType AddDevice(IGrepfaDevice) = 0;
        virtual ErrorType DelDevice(IGrepfaDevice) = 0;


    };
}