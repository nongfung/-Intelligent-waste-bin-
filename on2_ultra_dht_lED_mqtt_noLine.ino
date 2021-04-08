#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <NewPing.h>
//#include <Servo.h> 
#include <TridentTD_LineNotify.h>

#define printByte(args)  write(args);
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
#define SSID        "vivo 88"
#define PASSWORD    "08112541"
#define LINE_TOKEN  "HtxhSod2qu5NKPVDFhRlDYYQxuxFLj9tiR2U1EuPWq3"

#include "DHT.h"
#define DHTPIN D4 
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//Servo myservo;  
#define wifi_ssid "vivo 88"
#define wifi_password "08112541"
#define mqtt_server "35.240.143.198"
#define us "sensor/us"
#define humid "sensor/humid"
#define tempc "sensor/tempc"
#define tempf "sensor/tempf"
#define TRIGGER_PIN  D8
#define ECHO_PIN     D6
#define MAX_DISTANCE 400 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);
  dht.begin();

  setup_wifi();
  client.setServer(mqtt_server, 1883);

 Serial.println(LINE.getVersion());
   WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
 
  LINE.setToken(LINE_TOKEN);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Humidity : ");
  lcd.setCursor(0,1);
  lcd.print("quantity : ");
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {

  while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      String clientName;  
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);
      clientName += "-";
      clientName += String(micros() & 0xff, 16);
      Serial.print("Connecting to ");
      Serial.print(mqtt_server);
      Serial.print(" as ");
      Serial.println(clientName);
  if (client.connect((char*) clientName.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(1000);
    }
  }
}


void loop() {

     if (!client.connected()) {
        reconnect();
      }
      client.loop();
      delay(500);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);
      
      if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
      }
          
      lcd.setCursor(10,0);
      lcd.print(String(h).c_str() + String("%"));
      lcd.setCursor(10,1);
      lcd.print(sonar.ping_cm()+ String(" CM "));
      
     
      int cm = sonar.ping_cm();
      Serial.print("ultrasonic:");
      Serial.println(String(cm).c_str());
      client.publish(us, String(cm).c_str(), true);
      delay(1000);
      if (cm < 5 ){
      LINE.notify("ขณะถังขยะถังที่ 2 ใกล้เต็ม กรุณานำขยะไปทิ้ง");
      }
      
      Serial.print("Humidity:");
      Serial.println(String(h).c_str());
      client.publish(humid, String(h).c_str(), true);
      delay(1000);

      
}
