# grepfa_type
모든 grepfa 컴포넌트에서 공통적으로 사용하는 타입과 열거형 정의 구현체

## `enum class NetworkType`
기기가 외부 네트워크에 어떤 방식으로 연결되어 있는지를 나타낸다.

- UNKNOWN - 정의되지 않음
- WIFI - Wi-Fi
- ETHERNET - 이더넷
- LORA - LoRa

## `enum class ConnectionProtocol`
브로커 혹은 게이트웨이와 어떤 프로토콜로 통신하는지 나타낸다.

- UNKNOWN - 정의되지 않음
- MQTT - MQTT
- HTTP - HTTP
- LORAWAN - LoRaWAN

## `enum class MessageType`
업스트립 메시지의 타입을 나타낸다.

- UNKNOWN - 정의되지 않음
- LOG - 로그 (upstream)
- SYSTEM - 시스템 메세지 (up/downstream)
- EVENT - 이벤트 (upstream)
- CONTROL - 제어 (downstream)

## `enum class LogLevel`
로그 메시지의 레벨을 나타낸다.

- UNKNOWN - 정의되지 않음
- DEVELOP - 개발자용 로그
- LOG - 로그
- INFO - 사용자에게 알릴 필요가 없는 정보성 로그
- ALERT - 사용자에게 알릴 필요가 있는 정보성 로그
- WARNING - 경미한 에러, 경고 메세
- ERROR - 중대한 문제가 있으나 기기 가동에 문제가 없는 에러
- FATAL - 기기 가동 지속에 중대한 문제가 있는 에러

## `enum class ValueType`
메시지의 의도하는 값의 타입을 나타낸다.

- UNKNOWN - 정의되지 않음
- STRING
- FLOAT
- INTEGER
- BOOLEAN

## `class IPayload`
Payload의 원형이 되는 가상 클래스.

