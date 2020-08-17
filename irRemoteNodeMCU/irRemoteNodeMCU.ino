#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const int khz =38; //khz for ir leds 
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t tvPower[] = {4350,4650,400,1850,400,1800,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,750,400,700,400,1850,400,700,400,700,400,750,400,700,400,700,400,700,400,1850,400,700,400,1850,400,1850,400,1800,400,1850,400,1800,400,1850,400};
uint16_t tvVolumeUp[] =  {4400,4600,400,1850,400,1800,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,750,400,1800,400,1850,400,1850,400,700,400,700,400,700,400,750,400,700,400,700,400,750,400,700,400,1850,400,1800,400,1850,400,1800,400,1850,400};
uint16_t tvVolumeDown[] =  {4300,4600,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,700,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,700,400,1850,400,1850,400,700,400,1800,400,750,400,700,400,700,400,700,400,750,350,750,400,1800,400,750,400,1800,400,1850,400,1800,400,1850,400};
uint16_t tvChUp[] = {4350,4600,450,1800,400,1850,400,1800,450,700,400,700,400,700,450,700,400,700,400,1800,400,1850,450,1800,400,700,400,700,450,700,400,700,400,700,400,750,400,1800,450,700,400,700,400,1800,400,750,400,700,450,650,450,1800,400,700,400,1850,400,1850,350,750,400,1800,400,1850,450,1800,400};
uint16_t tvChDown[] = {4350,4600,450,1800,400,1850,400,1800,450,650,450,700,400,700,450,650,400,750,400,1800,400,1850,400,1850,400,700,400,700,450,650,450,700,400,700,450,650,450,700,400,700,400,700,450,1800,400,700,400,750,400,700,400,1800,400,1850,400,1850,400,1800,450,700,400,1800,450,1800,400,1800,450};
uint16_t tvSource[] = {4300,4700,350,1850,350,1900,350,1900,350,750,400,750,350,750,350,750,350,800,350,1850,350,1900,350,1850,350,750,400,750,350,750,350,750,400,750,350,1850,400,750,350,750,400,700,450,700,350,750,400,700,400,700,400,750,350,1850,400,1850,350,1900,350,1850,350,1900,400,1800,400,1850,350};
uint16_t tvMute[] = {4300,4650,400,1850,400,1800,400,1850,400,700,450,700,400,700,400,700,400,750,400,1800,450,1800,400,1800,450,700,400,700,450,650,450,700,400,700,450,1800,400,1800,450,1800,450,1800,400,700,400,700,450,650,450,700,400,700,450,650,450,700,400,700,450,1800,400,1800,450,1800,400,1800,450};
uint16_t tvPrevious[] = {4350,4650,400,1850,400,1800,450,1800,400,700,450,700,400,700,400,700,400,700,450,1800,400,1850,400,1800,450,700,400,700,400,700,400,750,400,700,400,1800,400,1850,400,700,400,750,400,1800,400,750,400,700,400,700,400,750,400,700,400,1800,400,1850,400,700,450,1800,400,1850,400,1800,400};
uint16_t tvZero[] =   {4350,4600,400,1850,400,1850,400,1800,400,750,400,700,400,700,400,750,400,700,400,1800,400,1850,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,700,400,700,400,750,400,1800,400,750,400,700,400,700,400,750,400,1800,400,1850,400,1850,400,700,400,1800,400,1850,400,1850,400};
uint16_t tvOne[] = {4350,4650,400,1800,400,1850,400,1850,400,700,400,700,450,650,450,700,400,700,450,1800,400,1800,400,1850,400,700,400,750,350,750,400,700,450,650,450,700,400,700,450,1800,400,700,450,650,450,700,400,700,400,700,450,1800,400,1800,450,700,400,1800,450,1800,450,1800,400,1800,450,1800,400};
uint16_t tvTwo[] = {4300,4650,400,1850,400,1800,400,1850,400,700,400,750,400,700,400,700,400,700,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,750,400,1800,400,700,400,1850,400,700,400,750,400,700,400,700,400,700,400,750,400,1800,400,750,400,1800,400,1850,400,1800,400,1850,400,1850,400};
uint16_t tvThree[] = {4400,4600,450,1800,400,1850,400,1800,450,650,400,750,400,700,400,700,450,700,400,1800,450,1800,400,1850,450,650,400,700,450,650,450,700,400,700,400,700,400,1850,400,1850,400,700,400,700,450,700,400,700,400,700,400,1850,400,700,400,700,450,1800,400,1850,400,1800,450,1800,400,1850,400};
uint16_t tvFour[] = {4350,4650,400,1800,400,1850,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,1800,400,1850,400,700,400,750,400,700,400,700,400,750,400,700,400,700,400,700,450,1800,400,700,400,750,400,700,400,700,400,1850,400,1850,400,1800,400,750,400,1800,400,1850,400,1800,400,1850,400};
uint16_t tvFive[] = {4350,4650,400,1850,400,1800,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,1850,400,1800,400,700,400,750,400,700,400,700,400,750,400,1800,400,750,400,700,400,1850,400,700,400,700,400,700,400,750,400,700,400,1850,400,1800,400,750,400,1800,400,1850,400,1800,400,1850,400};
uint16_t tvSix[] = {4350,4650,400,1800,400,1850,400,1850,400,700,400,700,400,700,400,750,400,700,400,1850,400,1800,400,1850,400,700,400,750,400,700,400,700,400,700,400,750,400,1800,400,750,400,1800,400,750,400,700,400,700,400,750,400,1800,400,700,450,1800,400,700,400,1850,400,1850,400,1800,400,1850,400};
uint16_t tvSeven[] = {4350,4650,400,1850,400,1800,400,1850,400,700,400,700,400,750,400,700,400,700,400,1850,400,1850,400,1800,400,750,400,700,400,700,400,700,450,700,400,700,450,650,400,1850,400,1850,400,700,400,700,400,750,400,700,400,1850,400,1800,400,700,400,750,400,1800,450,1800,450,1800,400,1800,400};
uint16_t tvEight[] =  {4350,4600,400,1850,400,1850,400,1800,400,750,400,700,400,700,400,700,400,750,400,1800,400,1850,450,1800,400,700,400,700,400,750,400,700,400,700,450,1800,400,700,450,1800,400,1800,400,750,400,700,400,700,450,700,400,700,400,1800,400,750,400,700,400,1850,400,1800,400,1850,400,1850,400};     
uint16_t tvNine[] = {4350,4650,350,1850,400,1850,400,1800,400,750,400,700,400,700,400,750,400,700,400,1850,400,1800,400,1850,400,700,400,700,400,750,400,700,400,700,450,700,400,1800,400,1850,400,1850,350,750,400,700,400,700,400,750,400,1800,400,750,400,700,400,700,400,1850,400,1850,350,1850,400,1850,400};
uint16_t fanPower[] = {2100,950,600,1700,600,1750,550,1000,600,950,600,950,550,1000,550,950,600,1000,600,1000,600,950,600,950,600,950,600,950,550,1000,550,950,600};
#define MQTT_SERVER "IP OF MQTT SERVER"
const char* ssid = "NETWORK_SSID";
const char* password = "NETWORK_PASSWORD";

char* remoteTopic = "/remote";
WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int length);

PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);


void setup() {
  delay(1000);
   WiFi.begin(ssid, password);
  //attempt to connect to the WIFI network and then connect to the MQTT server
  reconnect();
  
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
    //reconnect if connection is lost
  if (!client.connected() && WiFi.status() == 3) {reconnect();}

  //maintain MQTT connection
  client.loop();
  
  //MUST delay to allow ESP8266 WIFI functions to run
  delay(10);
 
}

void callback(char* topic, byte* payload, unsigned int length) {
  

  //convert topic to string to make it easier to work with
  String topicStr = topic;
   

  //Print out some debugging info
  Serial.println("Callback update.");
  Serial.print("Topic: ");
  Serial.println(topicStr);

  if(payload[0] == 'P'){
    irsend.sendRaw(tvPower, sizeof(tvPower) / sizeof(tvPower[0]), khz); //Note the approach used to automatically calculate the size of the array.
  }

  if(payload[0] == 'V'){ //volume up
    irsend.sendRaw(tvVolumeUp, sizeof(tvVolumeUp) / sizeof(tvVolumeUp[0]), khz); //Note the approach used to automatically calculate the size of the array.
  }

  if(payload[0] == 'B'){ //volume down
    irsend.sendRaw(tvVolumeDown, sizeof(tvVolumeDown) / sizeof(tvVolumeDown[0]), khz); 
  }

  if(payload[0] == 'C'){ //channel up
    irsend.sendRaw(tvChUp, sizeof(tvChUp) / sizeof(tvChUp[0]), khz); 
  }

  if(payload[0] == 'X'){ //channel down
    irsend.sendRaw(tvChDown, sizeof(tvChDown) / sizeof(tvChDown[0]), khz);
  }

  if(payload[0] == 'S'){ //tv source
    irsend.sendRaw(tvSource, sizeof(tvSource) / sizeof(tvSource[0]), khz); 
  }
  
  if(payload[0] == 'M'){ //mute
    irsend.sendRaw(tvMute, sizeof(tvMute) / sizeof(tvMute[0]), khz);
  }  
  if(payload[0] == 'p'){
    irsend.sendRaw(tvPrevious, sizeof(tvPrevious) / sizeof(tvPrevious[0]), khz); //Note the approach used to automatically calculate the size of the array.
  }

  if(payload[0] == '0'){ //channel up
    irsend.sendRaw(tvZero, sizeof(tvZero) / sizeof(tvZero[0]), khz); 
  }  

  if(payload[0] == '1'){ //channel up
    irsend.sendRaw(tvOne, sizeof(tvOne) / sizeof(tvOne[0]), khz); 
  }  

  if(payload[0] == '2'){ //channel up
    irsend.sendRaw(tvTwo, sizeof(tvTwo) / sizeof(tvTwo[0]), khz); 
  }

  if(payload[0] == '3'){ //channel up
    irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz); 
  }  

  if(payload[0] == '4'){ //channel up
    irsend.sendRaw(tvFour, sizeof(tvFour) / sizeof(tvFour[0]), khz); 
  }
  if(payload[0] == '5'){ //channel up
    irsend.sendRaw(tvFive, sizeof(tvFive) / sizeof(tvFive[0]), khz); 
  }
  if(payload[0] == '6'){ //channel up
    irsend.sendRaw(tvSix, sizeof(tvSix) / sizeof(tvSix[0]), khz); 
  }
  if(payload[0] == '7'){ //channel up
    irsend.sendRaw(tvSeven, sizeof(tvSeven) / sizeof(tvSeven[0]), khz); 
  }
  if(payload[0] == '8'){ //channel up
    irsend.sendRaw(tvEight, sizeof(tvEight) / sizeof(tvEight[0]), khz); 
  }
  if(payload[0] == '9'){ //channel up
    irsend.sendRaw(tvNine, sizeof(tvNine) / sizeof(tvNine[0]), khz); 
  }
  if(payload[0] == 'F'){ //channel up
    irsend.sendRaw(fanPower, sizeof(fanPower) / sizeof(fanPower[0]), khz); 
  }
  if(payload[0] == 'E'){ //channel up
    espn();
  }
  if(payload[0] == 'e'){ //channel up
    espn2();
  }
  
  if(payload[0] == 'f'){ //channel up
    foxSports();
  }
  if(payload[0] == 'x' ){ //channel up
    foxSportsNet();
  }
  if(payload[0] == 'n'){ //channel up
    nbcSports();
  }
  if(payload[0] == 'c'){ //channel up
    comCentral();
  }
  
}

void espn(){
  irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz);
  delay(100);
  irsend.sendRaw(tvFive, sizeof(tvFive) / sizeof(tvFive[0]), khz);
}
void espn2(){
  irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz);
  delay(100);
  irsend.sendRaw(tvSix, sizeof(tvSix) / sizeof(tvSix[0]), khz);
}
void foxSports(){
  irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz);
  delay(100);
  irsend.sendRaw(tvSeven, sizeof(tvSeven) / sizeof(tvSeven[0]), khz);
}
void foxSportsNet(){
  irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz);
  delay(100);
  irsend.sendRaw(tvEight, sizeof(tvEight) / sizeof(tvEight[0]), khz);
}
void nbcSports(){
  irsend.sendRaw(tvFour, sizeof(tvFour) / sizeof(tvFour[0]), khz);
  delay(100);
  irsend.sendRaw(tvThree, sizeof(tvThree) / sizeof(tvThree[0]), khz);
}
void comCentral(){
  irsend.sendRaw(tvNine, sizeof(tvNine) / sizeof(tvNine[0]), khz);
  delay(100);
  irsend.sendRaw(tvFive, sizeof(tvFive) / sizeof(tvFive[0]), khz);
}



void reconnect(){
  //attempt to connect to the wifi if connection is lost
  if(WiFi.status() != WL_CONNECTED){
    //debug printing
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //loop while we wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    //print out some more debug once connected
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  //make sure we are connected to WIFI before attemping to reconnect to MQTT
  if(WiFi.status() == WL_CONNECTED){
  // Loop until we're reconnected to the MQTT server
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");

      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);

      //if connected, subscribe to the topic(s) we want to be notified about
      if (client.connect((char*) clientName.c_str())) {
        Serial.print("\tMTQQ Connected");
        client.subscribe(remoteTopic);
      }

      //otherwise print failed for debugging
      else{Serial.println("\tFailed."); abort();}
    }
  }
}

String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}
