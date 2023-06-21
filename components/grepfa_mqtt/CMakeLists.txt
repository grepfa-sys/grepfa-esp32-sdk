idf_component_register(SRCS "grepfa_mqtt.cpp"
                    INCLUDE_DIRS "include"
        PRIV_REQUIRES mqtt grepfa_uuid json esp_hw_support grepfa_error)
