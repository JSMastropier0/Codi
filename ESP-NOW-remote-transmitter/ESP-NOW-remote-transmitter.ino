#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN  33
#define VRY_PIN  35 
#define SW_PIN   25
// & 3.3V    & GND

#define LED_PIN  19

int xValue = 0;
int yValue = 0;
char bRotaValue = ' ';
int bSerraValue=0; 


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30,0xAE,0xA4,0x1B,0x78,0x20};  //34:85:18:26:D7:34   ESP32-C3 Device1
//uint8_t broadcastAddress[] = {0x34,0x85,0x18,0x26,0xC6,0x88};  //34:85:18:26:C6:88   ESP32-C3 Device2

//uint8_t broadcastAddress[] = {0xC8,0xC9,0xA3,0xC9,0x14,0xEC};  //C8:C9:A3:C9:14:EC   ESP32-Wroom


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
}
 
void loop() {

  // read analog X and Y analog values
  xValue = map (analogRead(VRX_PIN),0,4095,0,255);
  yValue = map (analogRead(VRY_PIN),0,4095,0,255);

  if (xValue > 100 and xValue <140 and yValue >140) {
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
  myData.bSerra=0;


  

Serial.print(myData.dir);Serial.print("  ");Serial.print(myData.bRota);;Serial.println(myData.bSerra);
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
