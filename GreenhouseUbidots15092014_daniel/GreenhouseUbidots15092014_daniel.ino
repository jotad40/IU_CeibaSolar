#include <Ubidots.h>
#include <SPI.h>
#include <WiFi.h>


char ssid[] = "AIREAFIT";
char pass[] = "abierta-al-mundo";

String api = "f5828e44156ec32eba10c832f2b979ae27d6256f";

String TempIdVar = "5568cb287625420cc24a81c3";
String HumIdVar = "";
String SoilIdVar = "";
String LightIdVar = "";
String HighHumIdVar = "";
String LowHumIdVar = "";
String IrrigationIdVar = "";

int TempHumSensorPin = 5;
int SoilSensorPin = A2;
int LightSensorPin = A1;

int  HumSensorValue = 0;
int  TempSensorValue = 0;
int  SoilSensorValue = 0;
int  LightSensorValue = 0;

float Adc5V10Bits = 0.0049;

float IdealSoilSensorValue = 50;      //dato arbitrario
float IdealHumSensorValue = 60;      //dato extraido de una web sobre cultivo en invernaderos
float IdealTempSensorValue = 25;     //dato extraido de una web sobre cultivo en invernaderos
float IdealLightSensorValue = 75;     //dato arbitrario

boolean HighHumidity = false;
boolean LowHumidity = false;
boolean ManualIrrigation = false;

int NumeroEnvios = 0;
unsigned long TiempoUltimoEnvio = 0;
unsigned long TiempoActual = 0;
unsigned long Intervalo = 500;

//dht11 DHT11;


Ubidots ubiclient(api);

void setup()
{
  boolean response;                                                                 
  
  int status = WL_IDLE_STATUS;
  Serial.begin(9600);
  
  //this function is to connect to your wifi network
  response = ubiclient.WifiCon(ssid, pass, status, api);                              
  Serial.println(response); 
}

void loop()
{
 
      delay(200);
            
      LightSensorValue = analogRead(LightSensorPin);
      LightSensorValue = LightSensorValue * Adc5V10Bits;
      LightSensorValue = (-21 * LightSensorValue) + 100;
          if (LightSensorValue < 0)
     {
        LightSensorValue = 0;
      }
      
      delay(200);

      
TiempoActual = millis();
if(TiempoActual - TiempoUltimoEnvio >= Intervalo){
	TiempoUltimoEnvio = TiempoActual;
	++NumeroEnvios;
	if(NumeroEnvios == 1199){
		TiempoUltimoEnvio = 0;
		NumeroEnvios = 0;
	}
}
        Serial.println(TempSensorValue);
        Serial.println(HumSensorValue);
        Serial.println(SoilSensorValue);
        Serial.println(LightSensorValue);
        Serial.println("--------");

        
        ubiclient.save_value(TempIdVar, String(TempSensorValue));
        
        ubiclient.save_value(HumIdVar, String(HumSensorValue));
                
        ubiclient.save_value(SoilIdVar, String(SoilSensorValue));
        
        ubiclient.save_value(LightIdVar, String(LightSensorValue));
        
      

     if (SoilSensorValue > IdealSoilSensorValue && HumSensorValue > IdealHumSensorValue){
      HighHumidity = true;
        Serial.println("Highly humid ambient");
        Serial.println(HighHumidity);
        Serial.println("..............");
//        ubiclient.save_value(HighHumIdVar, String(HighHumidity));
//        delay(200);
}
       }




