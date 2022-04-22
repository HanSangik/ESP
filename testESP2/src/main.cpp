#include <Arduino.h>
#include <String>
#include <iostream>

int a = 12;
int b = 13;
int c = 27;
int d = 15;
int e = 32;
int f = 22;
int g = 18;

#define _0 { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}
#define _1 { LOW, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _2 { HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}
#define _3 { HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH}
#define _4 { LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH}
#define _5 { HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}
#define _6 { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _7 { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW}
#define _8 { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
#define _9 { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}
int num_bit[10][7] = { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9 };


void putString();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
 

 pinMode(a, OUTPUT);
 pinMode(b, OUTPUT);
 pinMode(c, OUTPUT);
 pinMode(d, OUTPUT);
 pinMode(e, OUTPUT);
 pinMode(f, OUTPUT);
 pinMode(g, OUTPUT);


}
unsigned long before = millis();
void pickNumber(int n);
int num = 0;


void loop() {
  // put your main code here, to run repeatedly:
  //putString();
  unsigned long after = millis();

  if (after - before >= 1000)
  {
  before = after;
  pickNumber(num++);
  if(num == 10)
    num = 0;
  
  }
}
void putString(){
  Serial.println("**METHOD START**");
  while(1){
    if(Serial.available()){
     
      String inString = Serial.readStringUntil('\n');
      Serial.println(inString);
      Serial.println(strcmp(inString.c_str(), "END"));
      if(inString == "END\r"){ //carriage return의 존재
        Serial.println("**METHOD END**");
        break;
      }
      
    }
  }
}

void pickNumber(int n) 
{
 digitalWrite(a, num_bit[n][0]);
 digitalWrite(b, num_bit[n][1]);
 digitalWrite(c, num_bit[n][2]);
 digitalWrite(d, num_bit[n][3]);
 digitalWrite(e, num_bit[n][4]);
 digitalWrite(f, num_bit[n][5]);
 digitalWrite(g, num_bit[n][6]);
}

