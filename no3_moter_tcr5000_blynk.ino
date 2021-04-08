#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>;
char auth[] = "aZuwkXj1j4WS3uXaZlDhBFLM_tTTMlci";
char ssid[] = "vivo 88";
char pass[] = "08112541";

int enableA = D8;
int pinA1 = D2;
int pinA2 = D1;

int enableB = D7;
int pinB1 = D4;
int pinB2 = D3;
int sensor[3] = {0, 0, 0};

void setup()
{
  //Serial.begin (9600) ;
  pinMode(enableA,OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
 
  Blynk.begin(auth, ssid, pass);
}


BLYNK_WRITE(V2){
  
  int pinValue =param.asInt();
  Serial.print("pinValue: ");
  Serial.println(pinValue);
 
  if(pinValue==1){
     analogWrite(enableA,550);
     analogWrite(enableB,550);
     
  }else if(pinValue==0){
     analogWrite(enableA,0);
     analogWrite(enableB,0);
     
 }
}

void loop()
{


  sensor[0] = digitalRead(D5);
  sensor[1] = digitalRead(D6);
  sensor[2] = digitalRead(D0);

  if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) )
    forward(1);
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) )
    turnRight(1);
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) )
    turnRight(4);
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0)  )
    turnLeft(1);
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) )
    turnLeft(4);
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) )
    coast(10);


  else
    forward(1);

    Blynk.run();
}

void forward(int time)
{
  motorAForward();
  motorBForward();
  delay(time);
}

void backward(int time)
{
  motorABackward();
  motorBBackward();
  delay(time);
}

void turnLeft(int time)
{
  motorABackward();
  motorBForward();
  delay(time);
}

void turnRight(int time)
{
  motorAForward();
  motorBBackward();
  delay(time);
}

void coast(int time)
{
  motorACoast();
  motorBCoast();
  delay(time);
}

void brake(int time)
{
  motorABrake();
  motorBBrake();
  delay(time);
}

void motorAOn()
{
  digitalWrite(enableA, HIGH);
 // analogWrite(enableA,460);
  
}

void motorBOn()
{
  digitalWrite(enableB, HIGH);
  //analogWrite(enableB, 460);
}

void motorAOff()
{
  digitalWrite(enableB, LOW);
  //analogWrite(enableA,0);
 
}

void motorBOff()
{
  digitalWrite(enableA, LOW);
 // analogWrite(enableB, 0);
}

void motorAForward()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
}

void motorABackward()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
}

void motorBForward()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
}

void motorACoast()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
}

void motorABrake()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
}
