#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int M1enable = 23; //M1 motor esquerre
const int M2enable = 15; //M2 motor dret
const int M1Fwd=22;
const int M1Bkd=4;
const int M2Fwd=18;
const int M2Bkd=21;
const char nn='W'; //endavant
const char ss='S'; //endarrere
const char oo='A'; //esquerra
const char ee='D'; //dreta
const char st='X'; //para

void endavant (){
  digitalWrite(M1Bkd, LOW);
  digitalWrite(M1Fwd, HIGH);
  digitalWrite(M1enable, HIGH);
  digitalWrite(M2Bkd, LOW);
  digitalWrite(M2Fwd, HIGH);
  digitalWrite(M2enable, HIGH);
}

void endarrere (){
  digitalWrite(M1Fwd, LOW);
  digitalWrite(M1Bkd, HIGH);
  digitalWrite(M1enable, HIGH);
  digitalWrite(M2Fwd, LOW);
  digitalWrite(M2Bkd, HIGH);
  digitalWrite(M2enable, HIGH);
}

void dreta (){
  digitalWrite(M1Fwd, LOW);
  digitalWrite(M1Bkd, HIGH);
  digitalWrite(M1enable, HIGH);
  digitalWrite(M2Bkd, LOW);
  digitalWrite(M2Fwd, HIGH);
  digitalWrite(M2enable, HIGH);
}

void esquerra (){
  digitalWrite(M1Bkd, LOW);
  digitalWrite(M1Fwd, HIGH);
  digitalWrite(M1enable, HIGH);
  digitalWrite(M2Fwd, LOW);
  digitalWrite(M2Bkd, HIGH);
  digitalWrite(M2enable, HIGH);
}

void atura (){
  digitalWrite(M1Bkd, LOW);
  digitalWrite(M1Fwd, LOW);
  digitalWrite(M1enable, LOW);
  digitalWrite(M2Fwd, LOW);
  digitalWrite(M2Bkd, LOW);
  digitalWrite(M2enable, LOW);
}
  

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Consola activada.");
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(M1Fwd,OUTPUT);
  pinMode(M1Bkd,OUTPUT);
  pinMode(M2Fwd,OUTPUT);
  pinMode(M2Bkd,OUTPUT);
  pinMode(M1enable,OUTPUT);
  pinMode(M2enable,OUTPUT);
  digitalWrite(M1Bkd, LOW);
  digitalWrite(M1Fwd, LOW);
  digitalWrite(M1enable, LOW);
  digitalWrite(M2Fwd, LOW);
  digitalWrite(M2Bkd, LOW);
  digitalWrite(M2enable, LOW);
}

void loop() {
  
  if (SerialBT.available()) {
    char dades=SerialBT.read();
    Serial.write(dades);
    Serial.write("\n");
    switch (dades){ 
      case nn: 
        nord();
        Serial.write("Endavant");
        Serial.write("\n");
        break;        
      case ss: 
        sud();
        Serial.write("endarrere");
        Serial.write("\n");
        break;
      case esq: 
        esquerra();
        Serial.write("esquerra");
        Serial.write("\n");
        break;
      case drt: 
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
