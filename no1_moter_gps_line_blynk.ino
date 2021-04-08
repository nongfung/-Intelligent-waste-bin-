#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TridentTD_LineNotify.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = D8, TXPin = D7;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
#define BLYNK_PRINT Serial

#define pin1 D1
#define pin2 D2  // D3 <-> IN2
#define pin3 D3  // D2 <-> IN3
#define pin4 D4  // D4 <-> IN4
char auth[] = "aZuwkXj1j4WS3uXaZlDhBFLM_tTTMlci";
char ssid[] = "vivo 88";
char pass[] = "08112541";

#define SSID "vivo 88"
#define PASSWORD "08112541"
#define LINE_TOKEN "HtxhSod2qu5NKPVDFhRlDYYQxuxFLj9tiR2U1EuPWq3"

//void Line_Notify(String message) ;
String message = "https://www.google.co.th/maps/place/";
String la = "7.012919" ;
String lon = "100.473209" ;
String dated = "00/00/00";
String timed ="0";

void setup()
{
 //Serial.begin(9600);

 
 pinMode(pin1, OUTPUT);
 pinMode(pin2, OUTPUT);
 pinMode(pin3, OUTPUT);
 pinMode(pin4, OUTPUT);
 ss.begin(GPSBaud);
 Serial.println("start");
 Serial.begin(115200); Serial.println();
 Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  Blynk.begin(auth, ssid, pass);
  LINE.setToken(LINE_TOKEN);
}
BLYNK_WRITE(V3){
  
  int pinValue =param.asInt();
  Serial.print("pinValue: ");
  Serial.println(pinValue);
   gps_sen();
   la = String(gps.location.lat(),6); 
   lon =  String(gps.location.lng(),6) ;
   dated=  String(gps.date.value());
   timed=String(gps.time.value());
   message +=la + "+" + lon+"/@"+la+"@"+lon+"13z";
  if(pinValue==1){
        Serial.println("Enter !");
        LINE.notify("ตำแหน่งปัจจุบันคือ : "+message);
}
}

//หน้า
 BLYNK_WRITE(V6){
  
  int pinValue =param.asInt();
  if(pinValue==1){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}else  if(pinValue==0){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
}
//หลัง
BLYNK_WRITE(V7){
  
  int pinValue =param.asInt();
  if(pinValue==1){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}else  if(pinValue==0){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
}
//ซ้าย
BLYNK_WRITE(V8){
  
  int pinValue =param.asInt();
  if(pinValue==1){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}else  if(pinValue==0){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
}
//ขวา
BLYNK_WRITE(V9){
  
  int pinValue =param.asInt();
  if(pinValue==1){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}else  if(pinValue==0){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
}
void loop()
{
 gps_sen();
 Blynk.run();
}
void gps_sen(){
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      la = String(gps.location.lat(),6); 
      lon =  String(gps.location.lng(),6) ;
      Serial.print("Latitude= "); 
      Serial.print(la);
      Serial.print(" Longitude= "); 
      Serial.println(lon);
      Serial.print("Raw date DDMMYY = ");
      Serial.println(gps.date.value());
      Serial.print("Raw time in HHMMSSCC = ");
      Serial.println(gps.time.value());

    }
  } 
}
