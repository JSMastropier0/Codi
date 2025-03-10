#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN  33
#define VRY_PIN  35 
#define SW_PIN   25
#define SERR_PIN 15
#define RD_PIN    4
#define RE_PIN    5


#define LED_PIN  19

int xValue = 0;
int yValue = 0;

int bSerra=0; 
int rotaD = 0;
int rotaE = 0;

// REPLACE WITH YOUR RECEIVER MAC Address
// cotxeAntic (ESP32) {0x30,0xAE,0xA4,0x1B,0x78,0x20};
// cotxeNou (ESP32C3) {0xEC,0xDA,0x3B,0xBF,0x72,0xB8};
// cotxeNou (ESP32C3) placa 2 {0xEC,0xDA,0x3B,0xBF,0x74,0x00};
uint8_t broadcastAddress[] = {0xEC,0xDA,0x3B,0xBF,0x72,0xB8};  

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char dir;
  char bRota;
  int bSerra;
} struct_message;

// Create a struct_message called myData & peer
struct_message myData;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  status == ESP_NOW_SEND_SUCCESS ? digitalWrite(LED_PIN, HIGH) : digitalWrite(LED_PIN, LOW);
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  //pinMode(VRX_PIN, INPUT);
  //pinMode(VRY_PIN, INPUT);
  //pinMode(SW_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  // Butons
  pinMode(SERR_PIN, INPUT_PULLUP);
  pinMode(RD_PIN, INPUT_PULLUP);
  pinMode(RE_PIN, INPUT_PULLUP);
  
}
 
void loop() {
  
  //llegir butons
  bSerra = !digitalRead(SERR_PIN);
  rotaD = !digitalRead(RD_PIN);
  rotaE = !digitalRead(RE_PIN);
  
  // read analog X and Y analog values
  xValue = map (analogRead(VRX_PIN),0,4095,0,255);
  yValue = map (analogRead(VRY_PIN),0,4095,0,255);

  if (rotaD ==1) {
    myData.dir='G';}
  else if (rotaE==1){
    myData.dir='F';}
  else if (xValue > 100 and xValue <140 and yValue >140) {
    myData.dir='W';}
  else if (xValue > 100 and xValue <140 and yValue <100) {
    myData.dir='S';}
  else if (xValue > 140 and yValue <140 and yValue >100) {
    myData.dir='D';}
  else if (xValue < 100 and yValue <140 and yValue >100) {
    myData.dir='A';}
  else if (xValue >140 and yValue >140) {
    myData.dir='E';}
  else if (xValue < 100 and yValue >140) {
    myData.dir='Q';}
  else if (xValue > 140 and yValue <100) {
    myData.dir='C';}
  else if (xValue < 100 and yValue <100) {
    myData.dir='Z';}
  else if (xValue > 100 and xValue <140 and yValue >100 and yValue < 140) {
    myData.dir='X';}
    
  
  myData.bRota='E';
  myData.bSerra=bSerra;


  

Serial.print(myData.dir);Serial.print("  ");Serial.print("valor serra= ");;Serial.println(myData.bSerra);
//Serial.println("");
  
 


  Serial.print(xValue);
  Serial.print
  ("   ");
  Serial.println(yValue);
  
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(20);

}
