
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20,16,2);  //0x20 for simulation and 0x27 for prototype

int totalItems = 0;
int initialDistance = 37;


// GLOBAL VARIABLES FOR LED LIGHTS
      int ledGreen = 13;
      int ledRed = 12;
      int SWH1 = 10;
      int SWH2 = 8;
      int switchState1 = 0;
      int switchState2 = 0;
      int buzPin = 7;
      //---------------//

// GLOBAL VARIABLES FOR ULTRASONIC SENSOR

      int distanceInitial = 37;  //Box width

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

 
  //  Setting UP LED lights
          pinMode(SWH1, INPUT_PULLUP);
          pinMode(SWH2, INPUT_PULLUP);
          pinMode(ledRed, OUTPUT);
          pinMode(ledGreen, OUTPUT);

  // Setting Pins for ULTRASONIC SENSORS
          pinMode(trigPin1, OUTPUT);
          pinMode(echoPin1, INPUT);
          pinMode(buzPin, OUTPUT);
          pinMode(trigPin2, OUTPUT);
          pinMode(echoPin2, INPUT);

  // Starting the SERIAL MONITOR for Debugging 
  Serial.begin(9600);
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


            Serial.println(distanceCm1);
             
  
      // Sensor-2
            digitalWrite(trigPin2, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin2, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin2, LOW);
            duration2 = pulseIn(echoPin2, HIGH);
            distanceCm2= duration2*0.034/2; 

            
            Serial.println(distanceCm2);

      // Getting the mode of the machine
      if (digitalRead(ledGreen) == HIGH && switchState2 == LOW) {  //Coutnting Mode

        if(distanceCm1 < initialDistance - 5 || distanceCm1 > initialDistance + 5) {
          
              totalItems += 1;
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(buzPin, LOW);
              delay(2500);
          
         
            //time required for the users to handl their out from the box
        }

        if(distanceCm2 < initialDistance - 25  || distanceCm2 > initialDistance + 25) {
              totalItems += 1;
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(buzPin, LOW);
              delay(2500);
        }

      }

      if (digitalRead(ledRed) == HIGH && switchState2 == LOW) {  //Checking Mode

        if(distanceCm1 < initialDistance - 5 || distanceCm1 > initialDistance + 5) {

          if(totalItems != 0){
              totalItems -= 1;
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(buzPin, LOW);
          }
          
          if (totalItems == 0) {
            for (int i = 0; i < 3; i++) {
              digitalWrite(ledGreen, HIGH);
              digitalWrite(ledRed, HIGH);
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(ledGreen, LOW);
              digitalWrite(ledRed, LOW);
              digitalWrite(buzPin, LOW);
              Serial.println("Buzzered!!");
              delay(500);
            }
            
          }

          if (totalItems == 0) {
            delay(1000);
           
          }
          else {
            delay(3000); //Time required for the users to handl their out from the box
            
          }
            
          
        }


        // Deacrementing using the 2nd sensor
        if(distanceCm2 < initialDistance - 25 || distanceCm2 > initialDistance + 25) {
          if(totalItems != 0){
              totalItems -= 1;
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(buzPin, LOW);
          }
          
          if (totalItems == 0) {
            for (int i = 0; i < 3; i++) {
              digitalWrite(ledGreen, HIGH);
              digitalWrite(ledRed, HIGH);
              digitalWrite(buzPin, HIGH);
              delay(500);
              digitalWrite(ledGreen, LOW);
              digitalWrite(ledRed, LOW);
              digitalWrite(buzPin, LOW);
              Serial.println("Buzzered!!");
              delay(500);
            }
            
          }

          if (totalItems == 0) {
            delay(1000);
           
          }
          else {
            delay(3000); //Time required for the users to handl their out from the box
            
          }
        }
      }

      // Displaying the total number of items on Serial Monitor
      Serial.println(totalItems);
  
}
