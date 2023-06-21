//
// Created by vl0011 on 23. 6. 17.
//

#include "include/grepfa_error.h"

static std::unordered_map<grepfa::ErrorType, std::string> errStringMap = {
        {grepfa::ErrorType::UNKNOWN, "unknown"},
        {grepfa::ErrorType::ERR_JSON, "invalid json"},
        {grepfa::ErrorType::PAYLOAD_ID_MISMATCH, "payload id mismatch"}
};

std::string grepfa::GetErrorString(grepfa::ErrorType err) {
    if (errStringMap.contains(err))
        return errStringMap[err];
    std::string ret = esp_err_to_name((esp_err_t) err);
    return ret;
}
