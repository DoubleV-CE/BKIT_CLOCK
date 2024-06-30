#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char* ssid = "";
const char* password = "";

//setup Adafruit
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//fill your username                   
#define AIO_USERNAME    ""
//fill your key
#define AIO_KEY         ""

#define LED_PIN 2

//setup MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//setup publish
Adafruit_MQTT_Publish sch_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sche");
Adafruit_MQTT_Publish led_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/led");

//setup subcribe
Adafruit_MQTT_Subscribe sch_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/sche", MQTT_QOS_1);
Adafruit_MQTT_Subscribe led_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led", MQTT_QOS_1);

void schcallback(char* value, uint16_t len) {
  // Chuyển payload thành chuỗi (string)
  // for (int i = 0; i < len; i++) {
  //   message += value[i];
  // }
  // String message = value;
  Serial.println('A');
  Serial.println('h', len);
  Serial.println('Z');
  // if(value[0] == '0') Serial.print('a');
  // if(value[0] == '1') Serial.print('A'); 
  // digitalWrite(LED_PIN, 1);
}  

void lightcallback(char* value, uint16_t len){
  if(value[0] == '0') Serial.print('b');
  if(value[0] == '1') Serial.print('B');
}

int counter = 20;
int led_status = 0;


void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
  led_status = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.println("Đang kết nối Wi-Fi...");
  }

  sch_sub.setCallback(schcallback);
  mqtt.subscribe(&sch_sub);


  led_sub.setCallback(lightcallback);
  mqtt.subscribe(&led_sub);

    //connect MQTT
  while (mqtt.connect() != 0){ 
    mqtt.disconnect();
    delay(500);
  }

  // Serial.println("Đã kết nối Wi-Fi");
  digitalWrite(LED_PIN, 0);
  led_status = 0;
}

void loop() {

  mqtt.processPackets(1);

  if (Serial.available()){
  //   Serial.println("Vao....");
    int msg = Serial.read();
    // if (msg == 'a'){
    //   Serial.println(message);
    //   Serial.println('Z');
    // }
    if (msg == 't'){
      Serial.println('S');
      //lấy dữ liệu giờ quốc tế ngay khi chạy set up (lấy 1 lần duy nhất).
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(client, "http://worldtimeapi.org/api/timezone/Asia/Ho_Chi_Minh"); // Thay đổi URL nếu cần

        int httpCode = http.GET();

        if (httpCode > 0) {
          String payload = http.getString();
          //Serial.println(payload);

          // Parse JSON
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);
          const char* datetime = doc["datetime"]; 
          Serial.println(datetime);
          Serial.println('E');
          led_pub.publish("led", 1);
        } else {
          Serial.println("Lỗi HTTP");
        }
        http.end();
      }
    }
  }
  if (counter <= 0){
    counter = 20;
    if (led_status == 1){
      digitalWrite(LED_PIN, 0);
      led_status = 0;
    }
    else {
      digitalWrite(LED_PIN, 1);
      led_status = 1;
    }
  }
  else {
    counter--;
  }
  delay(50); // Lấy thời gian mỗi phút
}