#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h> 
Servo myservo;  
#include <NewPing.h>
const char* ssid = "vivo 88";
const char* password = "08112541";
const char* mqtt_server = "35.240.143.198";

#define TRIGGER_PIN  D7 
#define ECHO_PIN     D8  
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
//int value = 0;
int PE = 4;
int digitalPin = 0;
int val = 0;
void setup_wifi() {

  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

if (strcmp(topic,"ser")==0){
  digitalWrite(PE,HIGH);
      myservo.write(180); 
      delay(5000);

    } 

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("ser");
   
    
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  
  myservo.attach(5);
  pinMode(digitalPin, INPUT);
  pinMode(PE, OUTPUT);
  Serial.begin(9600);
  
 setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    Serial.print(sonar.ping_cm());
  Serial.println("cm");
  val = digitalRead(digitalPin);
  if ((val == 1)&&(sonar.ping_cm()<20)) { 
    myservo.write(180);
  digitalWrite(PE,HIGH);
  delay(3000);
  }else if ((val == 0)&&(sonar.ping_cm()<20)) { 
    myservo.write(180);
  digitalWrite(PE,HIGH);
  delay(3000);
  }else if ((val == 0)&&(sonar.ping_cm()>20)) { 
  myservo.write(180);
  digitalWrite(PE,HIGH);
  delay(3000);
  }else if ((val == 1)&&(sonar.ping_cm()>20)) {
  myservo.write(0);
  digitalWrite(PE,LOW);
  delay(500);         
}
 Serial.print("val = "); 
  Serial.println(val); 
}
