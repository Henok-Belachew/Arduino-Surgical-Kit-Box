
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

LiquidCrystal_I2C lcd(0x20,16,2);

int ledGreen = 13;
int ledRed = 12;
int btn = 10;
int LOADCELL_DOUT_PIN = 3;
int LOADCELL_SCK_PIN = 2;

HX711 scale;

void setup() {


  
  // constants won't change
// const int BUTTON_PIN = 7; // btn
// const int LED_PIN    = 3; // ledRed

// variables will change:
int ledStateRed = HIGH;     // the current state of the RED LED LIGHT
int ledStateGreen = LOW;    // the current state of the GREEN LED LIGHT
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button
  ////

   lcd.init();                    
   lcd.backlight();
   pinMode(9, OUTPUT);
   digitalWrite(9, HIGH); // Used as vcc
 
  
   // Displaying 0 weight!
  // scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  // lcd.setCursor(0,1);
  // lcd.print(scale.read_average(15));


  //  Setting UP LED lights
   pinMode(btn, INPUT_PULLUP);
   pinMode(ledRed, OUTPUT);
   pinMode(ledGreen, OUTPUT);
   digitalWrite(ledGreen, LOW);
   digitalWrite(ledRed, HIGH);

  // Current button state
  currentButtonState = digitalRead(btn);
  //  digitalWrite(btn, HIGH);



  // setting up serial monitor for debugging
  // Serial.begin(9600);
}

void loop() {
  lastButtonState = currentButtonState;      // save the last state
  currentButtonState = digitalRead(btn); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    

    // // toggle state of LED
    // ledStateRed = !ledStateRed;
    // ledStateGreen = !ledStateGreen;

    // control LED arccoding to the toggled state
    digitalWrite(ledRed, !digitalRead(ledRed)); 
    digitalWrite(ledGreen, !digitalRead(ledGreen))
  }











  lcd.setCursor(0,0);
  lcd.print("Items: 0");
  

  
  
}
