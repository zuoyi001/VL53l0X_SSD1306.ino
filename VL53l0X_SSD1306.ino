

#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup()
{
  Serial.begin(9600);
    
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
  display.display();
  delay(1000);
    
  
  Wire.begin();

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop()
{
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4) {  
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(1,1);
      display.print("RxTx");
      display.setTextSize(2);
      display.setCursor(5  ,12);
      display.print((measure.RangeMilliMeter*0.1)-2);
      display.print("cm");
      display.display();
      Serial.println();
      delay(100);
  } else {
    display.display();
    display.clearDisplay();
    return;
  }
}
