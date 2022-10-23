
//---------Libraries -------------
#include <LoRa.h>
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

String LoRaData;
// -------------------setup-----------------------------------------------
void setup() { 
  //---------initialize Serial Monitor-----
  Serial.begin(9500);
  Serial.println("LoRa Receiver Test");

  // ------set up the LCD's number of columns, rows and background:----
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  lcd.setCursor(0, 1);
  lcd.print("LoRa Initializing OK!");
  
}
//-------------------program-----------------------------------------------------
void loop() 
{

  //--try to parse packet (analysere pakken)
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
    {
        //---received a packet
        Serial.print("Received packet ");

        //----read packet-----
        while (LoRa.available()) 
          {
            LoRaData = LoRa.readString();
            Serial.print(LoRaData);
          }

        //----print RSSI of packet  (Received Signal Strength Indicator)
        int rssi = LoRa.packetRssi();
        Serial.print(" with RSSI ");    
        Serial.println(rssi);

      // ---Dsiplay information-------------
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Received packet:");
      lcd.setCursor(0, 1);
      lcd.print(LoRaData);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RSSI:");
      lcd.setCursor(0, 1);
      lcd.print(rssi);
    }
}