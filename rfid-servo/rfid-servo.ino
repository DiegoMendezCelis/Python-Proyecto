#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h> 
 
Servo microservo9g;

#define SS_PIN 10
#define RST_PIN 9
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

int led_liberado = 5;
int led_negado = 6;

char st[20];

void setup() 
{
  pinMode(led_liberado, OUTPUT);
  pinMode(led_negado, OUTPUT);
 
  microservo9g.attach(3);
 
  microservo9g.write(90);
  
  Serial.begin(9600);
 
  SPI.begin();
  
  mfrc522.PCD_Init(); 
  
  Serial.println("TARJETA RFID");
  Serial.println();
}

void loop() 
{
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  //Serial.print("RFID:SERIAL");
  conteudo.toUpperCase();
  
  if (conteudo.substring(1) == "30 DB 8E 75","F0 C0 95 75")
  {
    Serial.println("tarjeta leida");
    Serial.println();
    
    for (int i= 1; i<5 ; i++)
    {
       microservo9g.write(-90);
      digitalWrite(led_liberado, HIGH);
         digitalWrite(led_negado, LOW);
      delay(500);
      microservo9g.write(90);
       digitalWrite(led_liberado, LOW);
    digitalWrite(led_negado, HIGH);
       }
  delay(250);
  }}
