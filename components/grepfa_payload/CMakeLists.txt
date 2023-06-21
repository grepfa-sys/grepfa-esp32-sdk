idf_component_register(SRCS
        "grepfa_log_payload.cpp"
        "grepfa_event_payload.cpp"
        "grepfa_control_payload.cpp"
        "grepfa_payload_value.cpp"
                    INCLUDE_DIRS "include"
        PRIV_REQUIRES grepfa_uuid grepfa_type grepfa_error json grepfa_json)
