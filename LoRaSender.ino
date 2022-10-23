

//------------Libraries for LoRa-----------

#include <LoRa.h>

//-----------Libraries for LCD Display----
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

//packet counter
int counter = 0;

// -------------------setup-----------------------------------------------
void setup() {
  //------initialize Serial Monitor-----------
  Serial.begin(9500);

  // ------set up the LCD's number of columns and rows:----
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);

  
  Serial.println("LoRa Sender Test");

  if (!LoRa.begin(BAND)) 
    {
      Serial.println("Starting LoRa failed!");
      while (1);
    }
  Serial.println("LoRa Initializing OK!");
  
  delay(2000);
}
//-------------------program-----------------------------------------------------
void loop() {
   
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //------Send LoRa packet to receiver------
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  //--------skriv ut info i LCD display------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LORA SENDER");
  lcd.setCursor(0, 1);
  lcd.print("Counter:");
  lcd.setCursor(10, 1);
  lcd.print(counter); 
      
  // en teller øker med en hver gang en meling blir sendt
  counter++;
  
  delay(10000);
}