

/*
 * 
 * Made By: Sadman Sakib Jisan
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void invalidAlarm(){
  digitalWrite(7,HIGH);
  delay(500);
  digitalWrite(7,LOW);
  delay(500);
}

void invalidEntry(){
  digitalWrite(7,HIGH);
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(7,LOW);
  digitalWrite(12,LOW);
  delay(500);
}

void setup() 
{
  pinMode(12,OUTPUT); //Buzzer (With RDR) Pin
  pinMode(5,INPUT); // Light Sensor Pin
  pinMode(7, OUTPUT); //Buzzer (With Laser) Pin 
  pinMode(3, OUTPUT); // Laser Pin
  pinMode(A4, OUTPUT); // Yellow Light
  pinMode(A7, OUTPUT); // Green Light
  pinMode(A3, OUTPUT); // Red Light Beside Laser Light
  pinMode(A6, OUTPUT); // Red Light Beside Laser Sensor
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Wave Your Card Near The Reader...");
  Serial.println();
  delay(500);

}
void loop() 
{
  
  
  digitalWrite(A4, HIGH);
  digitalWrite(3, HIGH);
  // Look for new cards
  if(digitalRead(5) == HIGH){
    digitalWrite(A4, LOW);
    digitalWrite(A6, HIGH);
    digitalWrite(A3, HIGH);
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    invalidEntry();
    digitalWrite(A6, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "A3 32 A1 1A" && digitalRead(7) == LOW) //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A7, HIGH);
    Serial.println();
    delay(10000);
    digitalWrite(3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A7, LOW);
    delay(3000);
    
  }else if (content.substring(1) != "A3 32 A1 1A" && digitalRead(7) == LOW)   {
    digitalWrite(A4, LOW);
    digitalWrite(A3, HIGH);
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();
    invalidAlarm();

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);
  }
  
  
} 
