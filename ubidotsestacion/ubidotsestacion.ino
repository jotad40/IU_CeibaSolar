#include <Ubidots.h>
#include <SPI.h>
#include <WiFi.h>



//float R1 = 15540.0; // 
//float R2 = 1009.0; // 
//float R3 = 10150.0; // 
//float R4 = 1990.0; // 

//char ssid[] = "Private";
//char pass[] = "eafit123*";

//char ssid[] = "Davidphone";
//char pass[] = "davidred";

char ssid[] = "AIREAFIT";
char pass[] = "abierta-al-mundo";

String api = "c20fbd735a5dac7b3ebce19ba0f640a923d89bc9";
String Voltaje_panelesIdVar = "5565f6ba76254206023d45bd";
String Voltaje_BateriaIdVar = "5566388c7625420f1b2e16d3";
String Corriente_PanelesIdVar = "556639d87625421292a9cc65";
String Corriente_ControladorIdVar = "55663a677625421007d98078";
String Corriente_AcIdVar = "55663bf67625421695b3a67e";
String Potencia_consumidaIdVar= "556625687625426a5e7b36ed";
//String TemperaturaIdVar="5567406576254274d14e192b";

String Energia_EntradaIdVar="556624ad762542695588f95d";
String Energia_SalidaIdVar="556625687625426a5e7b36ed";
//String LowVoltaje_BateriaIdVar = "";
//String IrrigationIdVar = "";

int Voltaje_panelesSensorPin = A0;
int Voltaje_bateriaSensorPin = A1;
int Corriente_panelesSensorPin = A3;
int Corriente_ControladorSensorPin = A4;
int Corriente_ACSensorPin = A2;
//int TemperaturaPin=A5;
//

float  voltajePanelesSensorValue = 0;
float  voltajeBateriaSensorValue = 0;
float  CorrientePanelesSensorValue = 0;
float  CorrienteControladorSensorValue = 0;
float  CorrienteACSensorValue=0;
//float  TemperaturaValue=0;
float  Energia_EntradaValue=0;
float  Energia_SalidaValue=0;


//int NumeroEnvios = 0;
//unsigned long TiempoUltimoEnvio = 0;
//unsigned long TiempoActual = 0;
//const unsigned long Intervalo = 500;

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
  voltajePanelesSensorValue = analogRead(Voltaje_panelesSensorPin);
  
  voltajeBateriaSensorValue = analogRead(Voltaje_bateriaSensorPin);
 //CorrientePanelesSensorValue = analogRead(Corriente_panelesSensorPin);
 // CorrienteControladorSensorValue = analogRead(Corriente_ControladorSensorPin);
 // CorrienteACSensorValue=analogRead(Corriente_ACSensorPin);
  //TemperaturaValue=analogRead(TemperaturaPin);
  
  //voltajePanelesSensorValue=Voltimetro(R1,R2,Voltaje_panelesSensorPin)+0.12;
  //voltajeBateriaSensorValue=Voltimetro(R3,R4,Voltaje_bateriaSensorPin);
  
  
  //Cálculos
  //TemperaturaValue=(5*TemperaturaValue*100)/1024-273;
  //TemperatureValue=TemperaturaValue/9.31
  
  //CorrientePanelesSensorValue=30/512*(0.004883*CorrientePanelesSensorValue);
  
  //CorrienteControladorSensorValue=30/512*(0.00488*CorrienteControladorSensorValue);
  
 // CorrienteACSensorValue=(CorrienteACSensorValue-510)*0.42/17;
  
  //voltajePanelesSensorValue = (voltajePanelesSensorValue*0.004883)/ (R2/(R1+R2));
  
  //voltajeBateriaSensorValue = (voltajeBateriaSensorValue*0.004883)/ (R4/(R3+R4));
  
 
  
 // Energia_EntradaValue=(CorrientePanelesSensorValue*voltajePanelesSensorValue*3600)/1000;               //Se calcula la energía producida por los paneles en kWh
  
  //Energia_SalidaValue=(((120*CorrienteACSensorValue)/(12*0.92))*voltajeBateriaSensorValue*3600)/1000;   //Se calcula la energía de salida en kWh por medio de la eficiencia del inversor
  //Fin de los cálculos
  
// TiempoActual = millis();
//if (TiempoActual - TiempoUltimoEnvio >= Intervalo) 
   // TiempoUltimoEnvio = millis();
   // ++NumeroEnvios;
    Serial.println("Voltaje bateria");
    Serial.println(voltajeBateriaSensorValue);
    Serial.println("Voltaje paneles");
   // Serial.println(voltajePanelesSensorValue);
  //  Serial.println("Corriente Paneles");
   // Serial.println(CorrientePanelesSensorValue);
   // Serial.println("Corriente controlador");
  //  Serial.println(CorrienteControladorSensorValue);
 //   Serial.println("Temperatura");
 //   Serial.println(TemperaturaValue);
   // Serial.println("--------");
    
   ubiclient.save_value(Voltaje_panelesIdVar, String(voltajePanelesSensorValue));
    
    ubiclient.save_value(Voltaje_BateriaIdVar, String(voltajeBateriaSensorValue));
//    
//    ubiclient.save_value(Corriente_PanelesIdVar, String(CorrientePanelesSensorValue));
//    
//    ubiclient.save_value(Corriente_ControladorIdVar, String(CorrienteControladorSensorValue));
//    
//    ubiclient.save_value(Corriente_AcIdVar, String(CorrienteACSensorValue));
//    
//    ubiclient.save_value(TemperaturaIdVar, String(TemperaturaValue));
//    
//    ubiclient.save_value(Energia_EntradaIdVar, String(Energia_EntradaValue));
//    
//    ubiclient.save_value(Energia_SalidaIdVar, String(Energia_SalidaValue));
    
   
//    ubiclient.save_value(Corriente_AcIdVar, String(HighHumidity));

   // if (NumeroEnvios == 1199) 
    //  TiempoUltimoEnvio = 0;
    //  NumeroEnvios = 0;
     
}




//float Voltimetro(float R11, float R22, int pin)
//{
//int value = 0;
//float voutBat = 0.0;
//float vinBat = 0.0;
//value = analogRead(pin);
//voutBat = (value * 0.004883); // 
//vinBat = voutBat / (R22/(R11+R22));
//if (vinBat<0.21) {
//vinBat=-0.2;// LIMPIEZA
//   }
//return vinBat;
//}



