idf_component_register(SRCS "grepfa_mqtt.cpp"
                    INCLUDE_DIRS "include"
        PRIV_REQUIRES mqtt grepfa_uuid grepfa_error grepfa_connector grepfa_type grepfa_json grepfa_payload)
