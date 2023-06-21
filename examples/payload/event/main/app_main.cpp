#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cstdio>

#include <grepfa_type.h>
#include <grepfa_payload.h>
#include <memory>

void LogPayloadTest() {
    auto p =grepfa::LogPayload::builder(grepfa::LogLevel::LOG, "hello");

    p->setAProtocol(grepfa::ConnectionProtocol::MQTT);
    p->setNetwork(grepfa::NetworkType::WIFI);

    auto str = p->toJSON();
    if (str) {
        printf("%s\n", str.value().c_str());
    } else {
        printf("%s\n", grepfa::GetErrorString(str.error()).c_str());
    }
}


void EventPayloadTest() {
    auto p = grepfa::EventPayload::builder();
    p->add(grepfa::PayloadValue::builder("id", "value", 18));
    p->add(grepfa::PayloadValue::builder("id", "value", 18.5));
    p->add(grepfa::PayloadValue::builder("id", "value", "18"));

    std::unique_ptr<grepfa::IPayload> x = std::move(p);
    auto str = x->toJSON();

    printf("%s\n", str->c_str());
}

extern "C" void app_main(void)
{
    while (1){
        EventPayloadTest();
        LogPayloadTest();
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}