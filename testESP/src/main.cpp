#include <Arduino.h>
#include <Time.h>
#include <Wire.h>
#include <ESP32Servo.h>
#include <SimpleDHT.h>


#define GAS_PIN A13
#define MOTOR_PIN 2
#define DHT_PIN 4

Servo servo;
int motor = MOTOR_PIN;
int angle = 0;
SimpleDHT22 dht22(DHT_PIN);

void gasDetector(); // 가스측정기
void motorMove(); //모터
void DHT(); //온습도
void setup() {
  // put your setup code here, to run once:
  pinMode(GAS_PIN, INPUT);
  Serial.begin(9600);
  //servo.attach(motor);
  
  
  
}
unsigned long before = millis();
unsigned long after = millis();
int right = 1;
int left = -1;
int flag = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(GAS_PIN));
  gasDetector();
  //motorMove();
  //DHT();
}

void gasDetector(){
 after = millis();
  if((after - before)>=2000){
    Serial.print("time step = ");
    Serial.print((after - before)/2000);
    before = after;
    Serial.print("  result = ");
    Serial.println(analogRead(A13));
   
  }
}
void motorMove(){
  after = millis();
  if((after - before)>=1000){
    before = after;
    if(flag == 0){
    Serial.print("+30 ");
     
      Serial.print("angle : ");
      Serial.println(angle);
      for(int i = 0; i < 30; i++){
        angle = angle + right;
        servo.write(angle);
        if(angle >= 180){
          flag = 1;
          break;
        }
      }
    }else{
      Serial.print("-30 ");
      Serial.print("angle : ");
      Serial.println(angle);
      for(int i = 0; i < 30; i++){
        angle = angle + left;
        servo.write(angle);
        if(angle <= 0){
          flag = 0;
          break;
        }
      }
    }
   
  }
}
void DHT(){
  

  float tmp = 0;
  float hum = 0;
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
    Serial.print("C / ");
    Serial.print((float)hum);
    Serial.println("%");
  }
  
}
