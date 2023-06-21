# Grepfa SDK for esp-idf

esp-idf 기반의 grepfa controller 컴포넌트 모음집 입니다.

## 구성
- grepfa_connector - 외부 네트워크 연결 구현 컴포넌트
- grepfa_error - 에러 구현 컴포넌트
- grepfa_lora - lora 연결 구현 컴포넌트
  - rak3172 (RUI3 AT command base), sx317x (direct control)
- grepfa_mqtt - mqtt 연결 구현 컴포넌트
- grepfa_http - http 연결 구현 컴포넌트
- grepfa_payload - payload 메세지 구현 컴포넌트
- grepfa_type - 컴포넌트 공통 타입, 상수, 열거형 컴폰넌트 
- grepfa_config - 컴포넌트 공통 KConfig 설정 컴포넌트
- grepfa_uuid - UUIDv4 구현체




## 설계 제약사항
- C23, C++23 을 사용합니다.
- C++ 기반으로 개발합니다.
- POSIX Thread, C++ Thread, POSIX Socket, C++ Socket 을 금합니다.
  - Thread -> FreeRTOS Task 를 사용하세요.
  - Socket -> netif, mqtt, http 등의 esp-idf 네트워크 상위 구현체를 사용하세요
- 모든 힙 할당 개체는 스마트 포인터로 메모리 누수 방지가 필수입니다.
  - 단, cJSON 등의 C API 개체는 필요시 RAW Pointer 를 사용합니다.
- JSON 파싱 라이브러리는 cJSON을 사용합니다.
- `virtual` 을 제외한 RTTI 구문 사용을 금합니다.
  - 'virtual' 대신 CRTP + type erasure 도입 고려 필요
- 예외 구문 사용을 금합니다. std::expected 로 대체 합니다.
- 4중 이상의 상속을 금합니다.
- 헤더파일에 주석을 강제하지 않지만, 컴포넌트 별로 readme.md 설명서를 작성해 주세요.
- 증복 include 방지를 꼭 해주세요


### 참고
- https://learn.microsoft.com/ko-kr/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-170