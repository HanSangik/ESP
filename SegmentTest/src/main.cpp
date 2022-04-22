#include <Arduino.h>

int position_pin[] = {1,2,3,4};               //4자리 결정 핀
int segment_pin[] = {5,6,7,8,9,10,11,12};     //세그먼트 제어 핀
const int delayTime = 5;                      //일시정지 시간
void show(int a, int b);
void show2(int a, int b);
void alpa();
void count();
void myDelay(unsigned long a);
unsigned long before = millis();
//0 ~ 9를 표현하는 세그먼트 값
byte data[] = {0xFD, 0x61, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE5, 0xFF, 0xE7};
byte data2[] = {0xEE, 0x3E, 0X9C, 0x7A, 0x9E, 0x8E, 0xF6, 0x6E, 0x60, 0x70, 0x5E, 0x1C, 0xF2, 0x2A, 0xFC,
                0xCE, 0xDE, 0x0A, 0XB6, 0X1E, 0x7C, 0x38, 0x9E, 0x6E, 0x66, 0x4A};

void setup() {
  //4자리 결정 핀 출력용으로 설정
  for(int i = 0; i < 4; i++) {
     pinMode(position_pin[i], OUTPUT);
  }

  //세그먼트 제어 핀 출력용으로 설정
  for(int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
}

void loop() {
  // show(1,1);                //첫 번째 자리, 1출력
  // myDelay(delayTime);         //0.005초 일시정지
  // show(2,2);                //두 번째 자리, 2출력
  // myDelay(delayTime);         //0.005초 일시정지
  // show(3,3);                //세 번째 자리, 3출력
  // myDelay(delayTime);         //0.005초 일시정지
  // show(4,4);                //네 번째 자리, 4출력
  // myDelay(delayTime);
  alpa();
  //count();                //count함수 호출, count 함수 실행시 주석 해제(//를 지우면 됩니다.)
}

void show(int position, int number) {
  //4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == position){
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  //8개 세그먼트를 제어해서 원하는 숫자 출력
  for(int i = 0; i < 8; i++){
     byte segment = (data[number] & (0x01 << i)) >> i;
     if(segment == 1){
       digitalWrite(segment_pin[7 - i], HIGH);
     } else {
       digitalWrite(segment_pin[7 - i], LOW);
     }
  }
}

/*
 0001부터 하나씩 카운트하는 함수
*/
void count() {
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      for(int k = 0; k < 10; k++) {
        for(int l = 0; l < 10; l++) {
          show(1,i);
          myDelay(delayTime);
          show(2,j);
          myDelay(delayTime);
          show(3,k);
          myDelay(delayTime);
          show(4,l);
          myDelay(delayTime);
        }
      }
    }
  }
  myDelay(1000);
}

void myDelay(unsigned long a){
  unsigned long after;
  while(1){
    after = millis();
    if(after - before >= a){
      before = after;
      break;
    }
  }
}

void show2(int position, int number) {
  //4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == position){
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  //8개 세그먼트를 제어해서 원하는 숫자 출력
  for(int i = 0; i < 8; i++){
     byte segment = (data2[number] & (0x01 << i)) >> i;
     if(segment == 1){
       digitalWrite(segment_pin[7 - i], HIGH);
     } else {
       digitalWrite(segment_pin[7 - i], LOW);
     }
  }
}

void alpa() {
  for(int i = 0; i < 26; i++) {
    for(int j = 0; j < 26; j++) {
      for(int k = 0; k < 26; k++) {
        for(int l = 0; l < 26; l++) {
          show2(1,i);
          myDelay(delayTime);
          show2(2,j);
          myDelay(delayTime);
          show2(3,k);
          myDelay(delayTime);
          show2(4,l);
          myDelay(delayTime);
        }
      }
    }
  }
  myDelay(1000);
}