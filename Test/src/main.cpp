#include <Arduino.h>
#include <stdio.h>

void setup() {
  Serial.begin(9600);
}
unsigned long before = millis();
unsigned long before1 = millis();
unsigned long before2 = millis();
int a = 0, b = 0, c = 0;
int flag = 0;
void loop() {
  // put your main code here, to run repeatedly:
 
  // unsigned long after = millis();
  // if(flag == 0){
  //   if((after)%1000 == 0){
  //     Serial.print(after);
  //     Serial.print("(a b c) (a = ");
  //     Serial.print(++a);
  //     b += 1;
  //     c += 1;
  //   }
  //   if((after)%2000 == 0){
  //     Serial.print(" ,b = ");
  //     Serial.print(b);
  //   }
  //   if((after)%3000 == 0){
  //     Serial.print(" ,c = ");
  //     Serial.print(c);
  //   }
  //   if((after)%1000 == 0){
  //     Serial.print(")");
  //     Serial.println();
  //   }

  unsigned long after = millis();
  
    if((after - before) >= 1000){
      before = after;
      Serial.print(" a = ");
      Serial.print(++a);
    
    }
    if((after - before1)>= 2000){
      before1 = after;
      Serial.print(" b = ");
      Serial.print(++b);
    }
    if((after - before2)>= 3000){
      before2 = after;
      Serial.print(" c = ");
      Serial.print(++c);
    }

    before = after;
 
}