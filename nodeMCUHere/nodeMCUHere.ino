#include <ESP8266WiFi.h> 
#include <WebSocketsClient.h> 
 
WebSocketsClient wsc; 
 
const char *ssid = "OrangeDSL-ElDeeb"; 
const char *pass = "Hh2266667"; 
 
#define SERVER "192.168.1.5" 
#define PORT 3000 
#define URL "/" 
 
void websocketEvent(WStype_t type, uint8_t *data, size_t length){ 
  switch(type){ 
    case(WStype_CONNECTED): 
      Serial.printf("connected to server\n"); 
      break; 
    case WStype_DISCONNECTED: 
      Serial.printf("Disconnected!\n"); 
      break; 
    case (WStype_TEXT): 
      int value; 
      if(length == 3){ 
        value = ((data[0]-'0')*100 + (data[1]-'0')*10 + (data[2]-'0')*1); 
        Serial.println(value); 
        analogWrite(D1, value); 
      }else if(length == 2){ 
        value = ((data[0]-'0')*10 + (data[1]-'0')*1); 
        Serial.println(value); 
        analogWrite(D1, value); 
      }else if(length == 1){ 
        value = ((data[0]-'0')*1); 
        Serial.println(value); 
        analogWrite(D1, value); 
      } 
       
      break; 
  }   
} 
 
void setup() { 
  Serial.begin(115200); 
 
  WiFi.begin(ssid, pass); 
 
  while(WiFi.status() != WL_CONNECTED){ 
    Serial.println("Connecting to wifi.."); 
    delay(500); 
  } 
 
  Serial.println(WiFi.SSID()); 
  Serial.println(WiFi.localIP()); 
 
  wsc.begin(SERVER, PORT, URL); 
  wsc.onEvent(websocketEvent); 
  wsc.setReconnectInterval(1000); 
} 
 
// the loop function runs over and over again forever 
void loop() { 
  wsc.loop();
}