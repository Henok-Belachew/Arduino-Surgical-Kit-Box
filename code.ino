
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

LiquidCrystal_I2C lcd(0x20,16,2);


// GLOBAL VARIABLES FOR LED LIGHTS
      int ledGreen = 13;
      int ledRed = 12;
      int btn = 10;
      //---------------//
      int lastButtonState;    // the previous state of button
      int currentButtonState; // the current state of button
  

// GLOBAL VARIABLES FOR ULTRASONIC SENSOR

      int distanceInitial = 33;  //Box width

      // 1st ULTRASONIC SENSOR
      int trigPin1 = 5;
      int echoPin1 = 6;
      long duration1;
      int distanceCm1;

      // 2nd ULTRASONIC SENSOR
      int trigPin2 = 4;
      int echoPin2 = 3;
      long duration2;
      int distanceCm2;


// ## SETTING UP ## //
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

  // Setting Pins for ULTRASONIC SENSORS
          pinMode(trigPin1, OUTPUT);
          pinMode(echoPin1, INPUT);
          pinMode(trigPin2, OUTPUT);
          pinMode(echoPin2, INPUT);
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

  // Getting measured DISTANCE VALUE

        // Sensor-1
            digitalWrite(trigPin1, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin1, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin1, LOW);
            duration1 = pulseIn(echoPin1, HIGH);
            distanceCm1= duration1*0.034/2; 

            // DISPLAYING MEASURED DISTANCE-1
            lcd.setCursor(0,0);
            lcd.print("Distance1:");
            lcd.print(distanceCm1);
            lcd.print(" Cm ");   
  
      // Sensor-2
            digitalWrite(trigPin2, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin2, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin2, LOW);
            duration2 = pulseIn(echoPin2, HIGH);
            distanceCm2= duration2*0.034/2; 

            // DISPLAYING MEASURED DISTANCE-2
            lcd.setCursor(0,1);
            lcd.print("Distance2:");
            lcd.print(distanceCm2);
            lcd.print(" Cm ");


  
}
