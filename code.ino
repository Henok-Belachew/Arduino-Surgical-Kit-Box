
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

LiquidCrystal_I2C lcd(0x20,16,2);  //0x20 for simulation and 0x27 for prototype

int totalItems = 0;
int initialDistance = 33;
// int initialDistance_2 = 33;


// GLOBAL VARIABLES FOR LED LIGHTS
      int ledGreen = 13;
      int ledRed = 12;
      int SWH1 = 10;
      int SWH2 = 8;
      int switchState1 = 0;
      int switchState2 = LOW;
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

  // Displaying Initial Status
        lcd.setCursor(0,0);
        lcd.print("BOX Starting ....");
        delay(1000);
        lcd.clear();

  //  Setting UP VCC
          pinMode(9, OUTPUT);
          digitalWrite(9, HIGH); // USED AS VCC
 
  //  Setting UP LED lights
          pinMode(SWH1, INPUT_PULLUP);
          pinMode(SWH2, INPUT_PULLUP);
          pinMode(ledRed, OUTPUT);
          pinMode(ledGreen, OUTPUT);

  int lastSwhState1;    // the previous state of THE SWITCH
  int currentSwhState1; // the current state of THE SWTICH

  int lastSwhState2;    // the previous state of THE SWITCH
  int currentSwhState2; // the current state of THE SWTICH



          //  Setting Initial State of LED LIGHTS
          // digitalWrite(ledGreen, LOW);
          // digitalWrite(ledRed, HIGH);

          // CURRENT BUTTON STATE
          // currentButtonState = digitalRead(btn);

  // Setting Pins for ULTRASONIC SENSORS
          pinMode(trigPin1, OUTPUT);
          pinMode(echoPin1, INPUT);
          pinMode(trigPin2, OUTPUT);
          pinMode(echoPin2, INPUT);
}

  

void loop() {
  // Displaying TOTAL ITEMS
        lcd.setCursor(0,0);
        lcd.print("Items: ");
        lcd.print(totalItems);


  // Displaying mode
        switchState1 = digitalRead(SWH1);
        switchState2 = digitalRead(SWH2);
        lcd.setCursor(0, 1);
        lcd.print("Mode: ");
        
        if (switchState1 == HIGH && switchState2 == LOW) {
          digitalWrite(ledRed, HIGH);
          digitalWrite(ledGreen, LOW);
          lcd.print("Checking");
        }
        else if(switchState1 == LOW && switchState2 == LOW ) {
          digitalWrite(ledRed, LOW);
          digitalWrite(ledGreen, HIGH);
          lcd.print("Counting");
        }

        else if (switchState2 == HIGH) {
          digitalWrite(ledRed, HIGH);
          digitalWrite(ledGreen, HIGH);
          lcd.print("Extracting");
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
            // lcd.setCursor(0,0);
            // lcd.print("Distance1:");
            // lcd.print(distanceCm1);
            // lcd.print(" Cm ");   
  
      // Sensor-2
            digitalWrite(trigPin2, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin2, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin2, LOW);
            duration2 = pulseIn(echoPin2, HIGH);
            distanceCm2= duration2*0.034/2; 

            // DISPLAYING MEASURED DISTANCE-2
           // lcd.setCursor(0,1);
            // lcd.print("Distance2:");
            // lcd.print(distanceCm1);
            // lcd.print(" - ");
            // lcd.print(distanceCm2);
            // lcd.print(" Cm ");  

      // Getting the mode of the machine
      if (digitalRead(ledGreen) == HIGH && switchState2 == LOW) {  //Coutnting Mode

        if(distanceCm1 != initialDistance) {
          totalItems += 1;
          delay(2000);  //time required for the users to handl their out from the box
        }

        if(distanceCm2 != initialDistance) {
          totalItems += 1;
          delay(2000);  //time required for the users to handl their out from the box
        }

      }

      if (digitalRead(ledRed) == HIGH && switchState2 == LOW) {  //Checking Mode

        if(distanceCm1 != initialDistance) {
          totalItems -= 1;
          delay(2000);  //time required for the users to handl their out from the box
        }

        if(distanceCm2 != initialDistance && switchState2 == LOW) {
          totalItems -= 1;
          delay(2000);  //time required for the users to handl their out from the box
        }

      }


      


      // Counting mode
      // if(btn == HIGH){
      //      // Counting total items
      //     if(distanceCm1 != initialDistance) {
      //       totalItems += 1;
      //       delay(2000);  //time required for the users to handl their out from the box
      //     }
      // }
      // else if (btn == LOW){
      //   if(distanceCm1 != initialDistance) {
      //       totalItems -= 1;
      //       delay(2000);  //time required for the users to handl their out from the box
      //     }
      // }

  
}
