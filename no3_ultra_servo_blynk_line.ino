#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <SPI.h>
#include <TridentTD_LineNotify.h>
#define SSID        "vivo 88"
#define PASSWORD    "08112541"
#define LINE_TOKEN  "HtxhSod2qu5NKPVDFhRlDYYQxuxFLj9tiR2U1EuPWq3"
Servo servo;
char auth[] = "aZuwkXj1j4WS3uXaZlDhBFLM_tTTMlci"; 
char ssid[] = "vivo 88";
char pass[] = "08112541";
#include <NewPing.h>
#define TRIGGER_PIN  5
#define ECHO_PIN     4
#define MAX_DISTANCE 100 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
servo.attach(16); 
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);

Serial.println("start");
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
   WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
 
  LINE.setToken(LINE_TOKEN);
}
BLYNK_WRITE(V11)
{
int val =param.asInt();
if (val == 1) { 
servo.write(180); 

}else if (val == 0){
servo.write(0); 

}
//servo.write(param.asInt());

}
void sendSensor()
{
  int cm = sonar.ping_cm();
  Serial.println(cm);
  Blynk.virtualWrite(V5, cm);
  delay(500);
}
void loop() {
   
   sendSensor();
   
  int cm = sonar.ping_cm();
  Serial.print("pinValue: ");
  Serial.println(cm);
  Blynk.run();
  if (cm == 2 ){
  LINE.notify("ขณะนี้พื้นที่ว่างในขยะคงเหลือ 2 cm กรุณานำขยะไปทิ้ง");
  delay(1000);
  }
}
