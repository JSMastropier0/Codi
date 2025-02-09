// ESP-NOW  receiver + motor

#include <esp_now.h>
#include <WiFi.h>

//motor
#define A1 1    //blue
#define A2 0    //orange
#define B1 2    //green
#define B2 3    //brown
unsigned int delaytime = 10;

typedef struct struct_message {
  int xVal;
  int yVal;
  char bRota;
  int bSerra;
} struct_message;

struct_message myData;


const int DEBOUNCE_DELAY = 50;   // the debounce time; increase if the output flickers

// button debounce
int lastSteadyState = LOW;
int lastState = LOW;
unsigned long lastDebounceTime = 0;
int flag = 0;


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  commands();
}
 
void setup() {
     
  //motor
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);

  
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Iniciem el sistema");
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}


void loop() {
   
}

void commands() {
  Serial.print ("X: "); Serial.print (myData.xVal);Serial.print(" Y: ");Serial.println (myData.yVal);
  if ((myData.xVal < 130)&&(myData.yVal < 5)) (Serial.println("<-- left"));
  if ((myData.xVal < 130)&&(myData.yVal > 240)) (Serial.println("         right-->"));
  if ((myData.xVal < 5)&& (myData.yVal > 110)){
    Serial.println("   v back v");
    cclockwise1(5);
  }
  if ((myData.xVal > 240)&&(myData.yVal > 110)){
    Serial.println("  ^ forward ^");
    clockwise1(5);
    
  }

  //debounce subfunction
  if (myData.bSerra != lastState) {
    lastDebounceTime = millis();
    lastState = myData.bSerra;
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (lastSteadyState == HIGH && myData.bSerra == LOW)
      if (flag == 0) {
        Serial.println("Motor on");
        flag = 1;
      }
      else if (flag == 1) {
        Serial.println("Motor off");
        flag = 0;
      }

    lastSteadyState = myData.bSerra;
  }

}






void step11(){
   digitalWrite(A1, 1);
   digitalWrite(A2, 0);
   digitalWrite(B1, 1);
   digitalWrite(B2, 0);
   delay(delaytime);
}

void step12(){
   digitalWrite(A1, 1);
   digitalWrite(A2, 0);
   digitalWrite(B1, 0);
   digitalWrite(B2, 1);
   delay(delaytime);
}

void step13(){
   digitalWrite(A1, 0);
   digitalWrite(A2, 1);
   digitalWrite(B1, 0);
   digitalWrite(B2, 1);
   delay(delaytime);
}

void step14(){
   digitalWrite(A1, 0);
   digitalWrite(A2, 1);
   digitalWrite(B1, 1);
   digitalWrite(B2, 0);
   delay(delaytime);
}


void clockwise1(long steps){  //turn right
 long p = 1;
 while( p < steps ){
   step11();
   step12();
   step13();
   step14();
   p++;
 }
}

void cclockwise1(long steps){  //turn left
 long p = 1;
 while( p < steps ){
   step14();
   step13();
   step12();
   step11();
   p++;
 }
}
