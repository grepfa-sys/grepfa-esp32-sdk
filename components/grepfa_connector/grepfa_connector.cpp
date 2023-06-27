//
// Created by vl0011 on 23. 6. 20.
//
#include <grepfa_connector.h>

#include <utility>


grepfa::Connector::Connector(const std::string&  id, grepfa::IConnectorCallback *callback): connectorId(id), callback(callback) {
}
