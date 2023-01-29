
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

LiquidCrystal_I2C lcd(0x20,16,2);

int ledGreen = 13;
int ledRed = 12;
int btn = 10;


int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button
  

// HX711 scale;

void setup() {
  // Initilizing the LCD 
          lcd.init();                    
          lcd.backlight();

  //  Setting UP VCC
          pinMode(9, OUTPUT);
          digitalWrite(9, HIGH); // USED AS VCC
 
  //  Setting UP LED lights
          pinMode(btn, INPUT_PULLUP);
          pinMode(ledRed, OUTPUT);
          pinMode(ledGreen, OUTPUT);

          //  Setting Initial State of LED LIGHTS
          digitalWrite(ledGreen, LOW);
          digitalWrite(ledRed, HIGH);

          // CURRENT BUTTON STATE
          currentButtonState = digitalRead(btn);
}

  

void loop() {
  // Displaying TOTAL ITEMS
        lcd.setCursor(0,0);
        lcd.print("Items: 0");


  // CONTROLLING LED LIGHTS
        lastButtonState = currentButtonState;  // SAVING THE LAST STATE OF BTN
        currentButtonState = digitalRead(btn); // READING THE NEW STATE OF BTN

        if(lastButtonState == HIGH && currentButtonState == LOW) {
        
          // REVERSING THE STATE OF LED LIGHTS
          digitalWrite(ledRed, !digitalRead(ledRed)); 
          digitalWrite(ledGreen, !digitalRead(ledGreen));
        }

  
}
