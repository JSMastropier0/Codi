#include "Arduino.h"
#include <esp_now.h>
#include <WiFi.h>

const int M1enable = 4; //M1 motor esquerre
const int M2enable = 5; //M2 motor dret
const int M1Fwd=2;
const int M1Bkd=1;
const int M2Fwd=6;
const int M2Bkd=7;
const int Srr=3; //serra
const char nn='W'; //endavant
const char ss='S'; //endarrere
const char oo='A'; //esquerra
const char ee='D'; //dreta
const char st='X'; //para
const char ne='E'; //Nordest
const char se='C'; //Sudest
const char so='Z'; //Sudoest
const char no='Q';//Nordoest
const char rd='G';//rota Dreta (horari)
const char re='F';//rota Esquerra (antihorari)


//velocitat

int lent=128;
int rap=255;
int zero=0;
int previ=0;

//Estructura de dades

typedef struct struct_message {
  char dir;
  char bRota;
  int bSerra=0;
} struct_message;

struct_message myData;

//recepció de dades

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
}


void nord (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, rap);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Bkd, zero);
  analogWrite(M2Fwd, rap);
  digitalWrite(M2enable, HIGH);
}

void sud (){
  analogWrite(M1Fwd, zero);
  analogWrite(M1Bkd, rap);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, zero);
  analogWrite(M2Bkd, rap);
  digitalWrite(M2enable, HIGH);
}

void est (){
  analogWrite(M1Fwd, rap);
  analogWrite(M1Bkd, zero);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Bkd, zero);
  analogWrite(M2Fwd, zero);
  digitalWrite(M2enable, LOW);
}

void oest (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, zero);
  digitalWrite(M1enable, LOW);
  analogWrite(M2Fwd, rap);
  analogWrite(M2Bkd, zero);
  digitalWrite(M2enable, HIGH);
}

void nordest (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, rap);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, lent);
  analogWrite(M2Bkd, zero);
  digitalWrite(M2enable, HIGH);
}

void nordoest (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, lent);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, rap);
  analogWrite(M2Bkd, zero);
  digitalWrite(M2enable, HIGH);
}

void sudest (){
  analogWrite(M1Bkd, rap);
  analogWrite(M1Fwd, zero);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, zero);
  analogWrite(M2Bkd, lent);
  digitalWrite(M2enable, HIGH);
}

void sudoest (){
  analogWrite(M1Bkd, lent);
  analogWrite(M1Fwd, zero);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, zero);
  analogWrite(M2Bkd, rap);
  digitalWrite(M2enable, HIGH);
}


void atura (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, zero);
  digitalWrite(M1enable, LOW);
  analogWrite(M2Fwd, zero);
  analogWrite(M2Bkd, zero);
  digitalWrite(M2enable, LOW);
}

void rotaDreta (){
  analogWrite(M1Bkd, rap);
  analogWrite(M1Fwd, zero);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, rap);
  analogWrite(M2Bkd, zero);
  digitalWrite(M2enable, HIGH);
}

void rotaEsquerra (){
  analogWrite(M1Bkd, zero);
  analogWrite(M1Fwd, rap);
  digitalWrite(M1enable, HIGH);
  analogWrite(M2Fwd, zero);
  analogWrite(M2Bkd, rap);
  digitalWrite(M2enable, HIGH);
}


  

void setup() {
  Serial.begin(115200);
 // while(!Serial);
  Serial.println("Consola activada.");
  Serial.println("Funcionant, esperant dades");
  pinMode(M1Fwd,OUTPUT);
  pinMode(M1Bkd,OUTPUT);
  pinMode(M2Fwd,OUTPUT);
  pinMode(M2Bkd,OUTPUT);
  pinMode(M1enable,OUTPUT);
  pinMode(M2enable,OUTPUT);
  pinMode(Srr,OUTPUT);
  digitalWrite(M1Bkd, LOW);
  digitalWrite(M1Fwd, LOW);
  digitalWrite(M1enable, LOW);
  digitalWrite(M2Fwd, LOW);
  digitalWrite(M2Bkd, LOW);
  digitalWrite(M2enable, LOW);
  digitalWrite(Srr, LOW);
// analog write
  analogWriteResolution(8);
  analogWriteFrequency(5000);
  
  WiFi.mode(WIFI_STA);
 // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}


void loop() {
  
  
    switch (myData.dir){ 
      case rd: 
        rotaDreta();
        Serial.write("Rota Dreta");
        Serial.write("\n");
        break;   
      case re: 
        rotaEsquerra();
        Serial.write("Rota Esquerra");
        Serial.write("\n");
        break;         
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
      case oo: 
        oest();
        Serial.write("esquerra");
        Serial.write("\n");
        break;
      case ee: 
        est();
        Serial.write("dreta");
        Serial.write("\n");
        break;
      case ne: 
        nordest ();
        Serial.write("nordest");
        Serial.write("\n");
        break;
      case se: 
        sudest();
        Serial.write("sudest");
        Serial.write("\n");
        break;
      case so: 
        sudoest();
        Serial.write("sudoest");
        Serial.write("\n");
        break;
      case no: 
        nordoest();
        Serial.write("nordoest");
        Serial.write("\n");
        break;
      case st: 
        atura();
        //Serial.write("atura");
        //Serial.write("\n");
        break;
    
    }
    if (myData.bSerra ==1 ){
      if (previ !=1){
        digitalWrite(Srr,HIGH);
        Serial.write("Activem Serra");
        Serial.write("\n");
      }
      previ=1;
    }
    else if (myData.bSerra==0 ){
      if (previ !=0) {
        digitalWrite(Srr,LOW);
        Serial.write("Aturem Serra");
        Serial.write("\n");
      }      
      previ=0;
    }
  
  delay(20);
}
