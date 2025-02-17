#include "Arduino.h"
#include "BluetoothSerial.h"
#include <esp_now.h>
#include <ESP32Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int Mesq = 25; //M1 motor esquerre
const int Mdrt = 26; //M2 motor dret
const int V = 180; //angle per anar endavant
const int R = 0; //angle per anar endarrere

const char nn='W'; //endavant
const char ss='S'; //endarrere
const char oo='A'; //esquerra
const char ee='D'; //dreta
const char st='X'; //para

//Servo

Servo servoMotorl; // servo esquerre
Servo servoMotorr; // servo dret

void endavant (){
  servoMotorl.write(V);
  servoMotorr.write(R);
}

void endarrere (){
  servoMotorl.write(R);
  servoMotorr.write(V);
}

void dreta (){
  servoMotorl.write(V);
  servoMotorr.write(90);
}

void esquerra (){
  servoMotorl.write(90);
  servoMotorr.write(R);
}

void atura (){
  servoMotorl.write(90);
  servoMotorr.write(90);
}
  

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Consola activada.");
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  servoMotorl.attach(Mesq); 
  servoMotorr.attach(Mdrt); 
 
}

void loop() {
  
  if (SerialBT.available()) {
    char dades=SerialBT.read();
    Serial.write(dades);
    Serial.write("\n");
    switch (dades){ 
      case nn: 
        endavant();
        Serial.write("Endavant");
        Serial.write("\n");
        break;        
      case ss: 
        endarrere();
        Serial.write("endarrere");
        Serial.write("\n");
        break;
      case oo: 
        esquerra();
        Serial.write("esquerra");
        Serial.write("\n");
        break;
      case ee: 
        dreta();
        Serial.write("dreta");
        Serial.write("\n");
        break;
      case st: 
        atura();
        Serial.write("atura");
        Serial.write("\n");
        break;
    
    }
  }
  delay(20);
}
