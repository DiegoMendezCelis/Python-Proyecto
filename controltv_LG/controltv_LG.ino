#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(4);


const int b1  = 16;  //off/on //D0
const int b2  = 5;  //Volumen +          //D1
const int b3  = 0;  //Volumen -          //D3
const int b4  = 2;  //Canal +            //D4
const int b5  = 15;  //Canal -           //D7


void setup() {
  irsend.begin();
    Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);

}

void loop() {

    if (digitalRead(b1) == LOW) {
      delay(1000);
      irsend.sendNEC(0x20DF10EF, 32); //0xF4BA2988    //0xE0E040BF
      Serial.println("off/on");
    }

    if (digitalRead(b2) == LOW) {
      delay(1000);
      irsend.sendNEC(0x20DF40BF, 32);
       Serial.println("VOL+");
    }

    if (digitalRead(b3) == LOW) {
      delay(1000);
      irsend.sendNEC(0x20DFC03F, 32);
    Serial.println("VOL-");
    }

    if (digitalRead(b4) == LOW) {
      delay(1000);
      irsend.sendNEC(0x20DF00FF, 32);
      Serial.println("CH+");
    }

    if (digitalRead(b5) != LOW) {
      delay(1000);
      irsend.sendNEC(0x20DF807F, 32);
    Serial.println("CH-");
    }

   
}
  
