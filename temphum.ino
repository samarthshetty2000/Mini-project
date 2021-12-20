// 
// Digital Output on LED 
// Hardware: NodeMCU Blynk Board


#define BLYNK_PRINT Serial

#include<SoftwareSerial.h> 
SoftwareSerial s(3,1);
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"           // including the library of DHT11 temperature and humidity sensor
   //including the library of SimpleTimer
#define DHTTYPE DHT11      // DHT 11

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;
char auth[] = " cr6ilnOxScEFM5VyCNZtNjsZd0V-Uur";            // You should get Auth Token in the Blynk App.
                                           // Go to the Project Settings (nut icon).

char ssid[] = "";    // Your WiFi credentials.
char pass[] = "";  // Set password to "" for open networks.


float t;                                   // Declare the variables 
float h;
String data;
  BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  Serial.print(pinData);
  s.write(pinData);
}

BLYNK_WRITE(V2) //Button Widget is writing to pin V1
{
  int pinData = param.asInt(); 
  
  if(pinData==1)
  pinData=2;
  else
  pinData=3;
  Serial.print(pinData);
  s.write(pinData);
}




void setup()
{
    Serial.begin(9600);// Debug console
    Blynk.begin(auth, ssid, pass);
    dht.begin();
     timer.setInterval(20000, sendUptime);
     timer.setInterval(20000, sendSensor);
     //timer.setInterval(20000, waterlevel);
}

void sendUptime()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  /*Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); */
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  
  
}
void sendSensor()
{
 float value =( 1024-analogRead(A0))*200/1024;
 Blynk.virtualWrite(V3, value); // Humidity for gauge
 /*Serial.print("MOISTURE = ");        //Output distance on arduino serial monitor 
Serial.println(value);*/
Blynk.virtualWrite(V7, value);

}
void waterlevel(){
  //Serial.print("abc");
  Serial.print(data);
   Blynk.virtualWrite(V8,data);
  
}
void loop()
{
  if(Serial.available()>0) // Chek for availablity of data at Serial Port
  { 

     
     data = Serial.readStringUntil('\r');
     //Serial.print(data);
     int data1=data.toInt();
     
     /*Serial.print(data);
      if (data!=" " ){
      Blynk.virtualWrite(V8,data);
      //Serial.println(data);
      }*/
      //Serial.print(data);
      if (data1!=NULL or data1!=0){
      // map(data1, 0, 70, 0, 100);
      /* map(data1,0,100,100,0); 
        //Serial.print(data);*/
        Blynk.virtualWrite(V8,(data1)); 
    
      }
     //Serial.println("us");// Reading Serial Data and saving in data variable
    //Serial.print(data); // Printing the Serial data
  }
   
  Blynk.run();
  timer.run();
}
