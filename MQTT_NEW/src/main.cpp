#include <Arduino.h>
#include <WiFi.h>
#include <String>
#include <SimpleDHT.h>
#include <PubSubClient.h>
#include <sstream>      // std::stringstream
#include <vfs_api.h>
 
const char* ssid = "officeFree";
const char* password =  "!@#$1234qwer";
const char* mqttServer = "192.168.98.224";
const int mqttPort = 1883;
const char* mqttUser = "test";
const char* mqttPassword = "1234";
const char* topic_pub = "messagebox";

const char* temp = "Sensor/temp"; //온도
const char* humi = "Sensor/humi"; //습도

const char* topic_sub = "messagebox2";

float tmp = 0;
float hum = 0;

#define UPDATE_INTERVAL 5000L
unsigned long prevUpdateTime = 0L;
unsigned long before = millis();
unsigned long after = millis();

#define DHT_PIN 4

#define STRING(num) #num

SimpleDHT22 dht22(DHT_PIN);

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void DHT();


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic_sub);
 
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
 
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
    }
  }

  mqttClient.subscribe(topic_sub);
  
  mqttClient.publish(topic_pub, "ESP32 logged in");
  prevUpdateTime = millis();
}

void loop() {
  mqttClient.loop();
 
  unsigned long currentTime = millis();
  if(currentTime > prevUpdateTime + UPDATE_INTERVAL) {
    
    // String tmp_str(String(tmp));
    // String hum_str(String(hum));
    int i = random(100);
    std::stringstream st;
    st<<i;
    mqttClient.publish(topic_pub, st.str().c_str());
    DHT();
    
    mqttClient.publish(temp, std::to_string(tmp).c_str());
    mqttClient.publish(humi, std::to_string(hum).c_str());

    prevUpdateTime = currentTime;
  }
}




void DHT(){
  
  

  int err = SimpleDHTErrSuccess;
  after = millis();
    if((after - before)>=2000){
      Serial.println("======================");
      Serial.println("Sample from DHT");
      before = after;
      if((err = dht22.read2(&tmp, &hum, NULL)) != SimpleDHTErrSuccess){
        Serial.print("Read failed, err = ");
        Serial.println(err);
        return;
      }

    Serial.println("Sample OK : ");
    Serial.print((float)tmp);
    Serial.print("*C / ");
    Serial.print((float)hum);
    Serial.println("%");
  }
  
}