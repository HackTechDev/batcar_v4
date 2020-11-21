/*
 * Zumo
 * Gotronic: https://www.gotronic.fr/art-robot-a-chenilles-zumo-2510-24239.htm
 * Library : Zumo Shield Version: 2.1.0 
 * 
 * Seeeduino Lotus Card: https://wiki.seeedstudio.com/Seeeduino_Lotus/
 * Gotronic: https://www.gotronic.fr/art-carte-seeeduino-lotus-1-1-102010168-26688.htm 
 *  
*/
 
// Motor
#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;



// Bluetooth

#include <SoftwareSerial.h>

#define RxD 6  // Plug the Bluetooth on the D6 pin
#define TxD 7

SoftwareSerial blueToothSerial(RxD,TxD);


void setup() {
   
    // Init Servo

    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);

    // Bluetooth
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);  
    setupBlueToothConnection(); 
}

void loop() {

    char recvChar;

    while(1) {

        // Bluetooth
        if (blueToothSerial.available()) {
            recvChar = blueToothSerial.read();
            Serial.print(recvChar);

            if(recvChar == '8') {
                Serial.println("Move forward");
                for (int speed = 0; speed <= 100; speed++){
                    motors.setLeftSpeed(speed);
                    motors.setRightSpeed(speed);
                    delay(2);
                } 
            }

            if(recvChar == '2') {
                Serial.println("Move backward");
                for (int speed = 0; speed >= -100; speed--) {
                    motors.setLeftSpeed(speed);
                    motors.setRightSpeed(speed);
                    delay(2);
                }
            }

            if(recvChar == '7') {
                Serial.println("Move backward right");
                for (int speed = 0; speed <= 100; speed++) {
                    motors.setLeftSpeed(speed);

                    delay(2);
                }
            }

            if(recvChar == '9') {
                Serial.println("Move backward left");
                for (int speed = 0; speed <= 100; speed++) {
                    motors.setRightSpeed(speed);
                    delay(2);
                }
            }

            if(recvChar == '1') {
                Serial.println("Move forward left");
                for (int speed = 0; speed >= -100; speed--) {
                    motors.setLeftSpeed(speed);

                    delay(2);
                }  
            }

            if(recvChar == '3') {
                Serial.println("Move forward right");
                for (int speed = 0; speed >= -100; speed--) {

                    motors.setRightSpeed(speed);
                    delay(2);
                }
            }

            if(recvChar == '5') {
                Serial.println("Move Stop");

                motors.setLeftSpeed(0);
                motors.setRightSpeed(0);
                delay(2);
            }

 

        }
    }
    delay(500);
}


void setupBlueToothConnection() {
    Serial.println("setupBlueToothConnection");
    blueToothSerial.begin(38400);
    blueToothSerial.print("\r\n+STWMOD=0\r\n");
    blueToothSerial.print("\r\n+STNA=Batcar\r\n");
    blueToothSerial.print("\r\n+STPIN=6666\r\n");
    blueToothSerial.print("\r\n+STOAUT=1\r\n");
    blueToothSerial.print("\r\n+STAUTO=0\r\n");
    delay(2000);
    blueToothSerial.print("\r\n+INQ=1\r\n");
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);
    blueToothSerial.flush();
} 
