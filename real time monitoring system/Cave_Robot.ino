#define BLYNK_TEMPLATE_ID "TMPL3cANPicXL"
#define BLYNK_TEMPLATE_NAME "Image Processing in Harsh Environment"
#define BLYNK_AUTH_TOKEN "p_qt1kDmF7YMB6M_A8Ggvg9LddOfAtv9"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "caverobot";
char pass[] = "123456789";

#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 13



DHT dht(dht_dpin, DHTTYPE); 

#define IN_1  5          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  4         // L298N in2 motors Right           GPIO13(D7)
#define IN_3  0           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  2          // L298N in4 motors Left            GPIO0(D3)

float gas_vol=0;

int speedCar = 40;  


void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
     

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

  void stopRobot()
  {  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      
 }

 BLYNK_WRITE(V0) 
 {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving forward");
    goAhead();
  }
  else {
    Serial.println("Stop");
   stopRobot();
  }
}

BLYNK_WRITE(V1) 
 {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving backward");
    goBack();
  }
  else {
    Serial.println("Stop");
    stopRobot();
  }
}


BLYNK_WRITE(V3) 
 {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving Left");
    goLeft();
  }
  else {
    Serial.println("Stop");
    stopRobot();
  }
}


void setup() 
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    stopRobot();
    dht.begin();
 }

void loop() 
{
  Blynk.run();
  gas_vol=analogRead(A0)/10;
  Serial.print("O2_Value:");
  Serial.println(gas_vol,2);
  Blynk.virtualWrite(V2,gas_vol);
  float h = dht.readHumidity();
  float t = dht.readTemperature();     
  Blynk.virtualWrite(V4,t);
  //Blynk.virtualWrite(V5,h);
  delay(500);
}



