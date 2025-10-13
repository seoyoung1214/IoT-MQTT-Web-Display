# IoT-MQTT-Web-Display
Real-time sensor data (Temp/Humidity) display using ESP32, MQTT, and GitHub Pages.

# 🌡️ IoT-MQTT-Web-Display
(혹은 ESP32-DHT11-MQTT-Web)

## 📌 프로젝트 개요 (Project Overview)

이 프로젝트는 **ESP32** 마이크로컨트롤러와 **DHT11 온습도 센서**를 사용하여 실시간 환경 데이터를 측정하고, **MQTT(Message Queuing Telemetry Transport)** 프로토콜을 이용해 웹 페이지에 실시간으로 표시하는 시스템을 구축합니다.

이는 물리 컴퓨팅(Physical Computing) 수업의 과제로, IoT 기기, 네트워크 통신(MQTT), 웹 기술(HTML/CSS/JavaScript)이 통합된 엔드-투-엔드(End-to-End) 시스템 구현을 목표로 합니다.

## 🛠️ 주요 기술 및 컴포넌트 (Tech Stack & Components)

| 분류 | 컴포넌트/기술 | 역할 |
| :--- | :--- | :--- |
| **IoT H/W** | ESP32 보드 | 온습도 데이터를 측정하고 MQTT 메시지를 발행하는 임베디드 기기 |
| **센서** | DHT11 (온도/습도 센서) | 환경의 온도 및 습도 값을 측정 |
| **통신 프로토콜** | MQTT | 저대역폭, 고지연 환경에 최적화된 메시징 프로토콜 |
| **MQTT Broker** | `damoa.io` | ESP32와 웹 클라이언트 간의 메시지 중개 역할 |
| **데이터 포맷** | JSON | 온도 및 습도 데이터를 구조화하여 전송 (예: `{"temp": 25.5, "humidity": 60.2}`) |
| **Web Frontend**| HTML, JavaScript (Paho MQTT Client) | MQTT Broker를 구독하고 수신한 JSON 데이터를 파싱하여 웹 화면에 실시간 표시 |
| **Web Hosting** | GitHub Pages | 최종 웹 애플리케이션 호스팅 |

---

## 🚀 시스템 작동 흐름 (System Workflow)

1.  **[ESP32]** Wi-Fi 접속 후, DHT11 센서로부터 **3초** 간격으로 온도 및 습도 값을 측정합니다.
2.  **[ESP32]** 측정된 데이터를 **JSON 형식**으로 구성합니다.
3.  **[ESP32]** `damoa.io` 브로커의 **`ewha/본인학번`** 토픽으로 JSON 데이터를 발행(Publish)합니다.
4.  **[Web Page]** GitHub Pages로 호스팅된 웹 페이지는 `ewha/본인학번` 토픽을 구독(Subscribe)합니다.
5.  **[Web Page]** 메시지를 수신하면, JavaScript가 JSON 데이터를 파싱하여 웹 화면의 온도 및 습도 값을 **실시간으로 업데이트**합니다.

---

## 📁 레포지토리 구조 (Repository Structure)
IoT-MQTT-Web-Display/
├── index.html          # 웹페이지 프론트엔드 코드 (MQTT 구독, 데이터 표시)
├── esp32_dht11_mqtt.ino # ESP32 아두이노 코드 (DHT11 측정, JSON 구성, MQTT 발행)
└── README.md           # 현재 문서
---

## 🌐 최종 웹페이지 URL (Final Web Page URL)

프로젝트 결과물은 아래 URL에서 실시간으로 확인할 수 있습니다.

**[여기에 GitHub Pages URL 삽입: 예시: `https://seoyoung1214.github.io/IoT-MQTT-Web-Display/` ]**

---

## 📹 과제 제출 증빙 (Submission Evidence)

본 시스템의 작동 과정을 설명하는 YouTube 영상 URL:

**[여기에 YouTube 영상 URL 삽입]**

---

## 🔑 참고 및 준비 사항 (Prerequisites)

* **MQTT Broker:** `damoa.io`
* **Publish/Subscribe Topic:** `ewha/본인학번`
* **ThingSpeak Account:** [여기에 ThingSpeak 로그인 계정명 삽입]

---
