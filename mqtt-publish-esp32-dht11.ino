#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h> // <--- JSON 라이브러리 추가

// *************** 설정 부분 (본인 정보로 수정) ******************
const char* ssid = "Rhomb_ei_iPhone16";
const char* password = "20021214";
const char* mqtt_server = "damoa.io";

#define DHTPIN 4
#define DHTTYPE DHT11

// MQTT 발행 토픽
const char* publishTopic = "ewha/2277040"; 
// ***************************************************************

WiFiClient espClient;
PubSubClient client(espClient);
DHT_Unified dht(DHTPIN, DHTTYPE);

String clientId; 
unsigned long lastReconnectAttempt = 0;
int cnt = 1;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // 고유한 Client ID 생성 (MAC 주소 기반)
  clientId = "ESP32_" + String((uint32_t)ESP.getEfuseMac(), HEX);
  Serial.println("Client ID: " + clientId);
  
  // WiFi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi 연결됨");
  Serial.println("IP: " + WiFi.localIP().toString());
  
  // MQTT 설정
  client.setServer(mqtt_server, 1883);
  client.setKeepAlive(60); 
  client.setSocketTimeout(30); 
}

boolean reconnect() {
  // 5초마다 재연결 시도
  if (millis() - lastReconnectAttempt < 5000) {
    return false;
  }
  
  lastReconnectAttempt = millis();
  Serial.print("MQTT 재연결 시도...");
  
  // 고유한 Client ID로 연결
  if (client.connect(clientId.c_str())) {
    Serial.println("성공!");
    
    // 💡 과제 3항에 필요한 부분: MQTT 최초 접속 시 checkin 메시지 발행 (ESP32에서)
    client.publish("ewha/checkin", "ESP32_온습도센서_2277040"); // <--- 본인 학번/이름으로 수정
    Serial.println("🚀 checkin 메시지 발행 완료");
    
    return true;
  } else {
    Serial.print("실패, rc=");
    Serial.println(client.state());
    return false;
  }
}

void loop() {
  // MQTT 연결 확인 및 재연결
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop(); // 연결되어 있을 때만 loop 호출
  }
  
  // 3초마다 값 발행
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 3000) {
    publishValue();
    lastTime = millis();
  }
  
  // 짧은 딜레이로 루프 안정화
  delay(10);
}

void publishValue() {
  if (!client.connected()) {
    Serial.println("MQTT 연결 안됨 - 발행 스킵");
    return;
  }
  
  sensors_event_t event;
  float t = 0;
  float h = 0;
  
  // 센서 값 읽기
  dht.temperature().getEvent(&event);
  t = isnan(event.temperature) ? 0.0 : event.temperature;
  
  dht.humidity().getEvent(&event);
  h = isnan(event.relative_humidity) ? 0.0 : event.relative_humidity;
  
  // Serial 모니터 출력
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C | Humidity: "));
  Serial.print(h);
  Serial.println(F("%"));
  
  // ----------------------------------------------------
  // JSON 메시지 생성 (ArduinoJson 사용)
  // ----------------------------------------------------
  const size_t CAPACITY = JSON_OBJECT_SIZE(3); 
  StaticJsonDocument<CAPACITY> doc;

  // JSON 키 이름: "temperature"와 "humidity" 사용
  doc["temperature"] = t; 
  doc["humidity"] = h;
  doc["count"] = cnt; 

  // JSON 객체를 문자열로 직렬화
  char jsonBuffer[100]; 
  serializeJson(doc, jsonBuffer);

  cnt++;

  // MQTT 발행 (ewha/본인학번 토픽)
  if (client.publish(publishTopic, jsonBuffer)) {
    Serial.println("발행 성공: " + String(jsonBuffer));
  } else {
    Serial.println("발행 실패!");
  }
}
