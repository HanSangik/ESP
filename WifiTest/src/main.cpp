#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Wire.h>
#include <ESP32Servo.h>

#define MOTOR_PIN 2

Servo servo;
int motor = MOTOR_PIN;
int angle = 0;
int flag = 0;

void motorMove(); //모터

const char* ssid = "officeFree";
const char* password = "!@#$1234qwer";
void myDelay(unsigned long a);
unsigned long before = millis();
unsigned long after;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);

  myDelay(10);

  Serial.println("\n");
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    myDelay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address : ");
  Serial.println(WiFi.localIP());

  server.begin();

  servo.attach(motor);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();

  if(client){
    Serial.println("New Client.");
    String currentLine = "";
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        if(c == '\n'){
          if(currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            client.println();

            break;

          }else{
            Serial.println(currentLine);
            currentLine = "";
          }
        }
        else if(c != '\r'){
            currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          flag = 0;
          angle = 0;
          motorMove();
          Serial.println("HIGH");
          }
        if (currentLine.endsWith("GET /L")) {
          flag = 1;
          angle = 180;
          motorMove();
          Serial.println("LOW");
        }
      }
    }
    // client.stop();
    // Serial.println("Client Disconnected.");
  }
}

void myDelay(unsigned long a){
  
  while(1){
    after = millis();
    if(after - before >= a){
      before = after;
      break;
    }
  }
}

void motorMove(){
  int right = 1;
  int left = -1;
  Serial.println("**********************");
  Serial.print("*This is MotorControl*\n");
  Serial.println("**********************");
  while(1){
  after = millis();
  if((after - before)>=1000){
    before = after;
    if(flag == 0){
    Serial.println("+30 ");
     
      Serial.print("angle : ");
      Serial.println(angle);
      for(int i = 0; i < 30; i++){
        angle = angle + right;
        Serial.print("angle : ");
        Serial.println(angle);
        servo.write(angle);
        if(angle >= 180){
          flag = 1;
          return;
        }
      }
    }else{
      Serial.println("-30 ");
      Serial.print("angle : ");
      Serial.println(angle);
      for(int i = 0; i < 30; i++){
        angle = angle + left;
        Serial.print("angle : ");
        Serial.println(angle);
        servo.write(angle);
        if(angle <= 0){
          flag = 0;
          return;
        }
      }
    }
   
    }
  }
}