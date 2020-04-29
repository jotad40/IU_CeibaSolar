
//int analogInput = 0;
int analogInputUno = 0;
float vout = 0.0;
float vin = 0.0;
float voutBat = 0.0;
float vinBat = 0.0;
float R1 = 180000.0; // 
float R2 = 10000.0; // 
float R3 = 1000.0; // 
float R4 = 2000.0; // 
int valor = 0;
int valorUno = 0;
int contador = 1;

void setup(){
//pinMode(analogInput, INPUT);   
pinMode(analogInputUno, INPUT);
Serial.begin(9600);

//setTime(10,30,0,5,22,15); // set time to Saturday 10:30:00am May 22 2011

Serial.println("VOLTIMETRO DC");
}
void loop(){
//  digitalClockDisplay();
  
// LEE EL VALOR DE LA ENTRADA ANALOGA PANELES
//   valor = analogRead(analogInput);
//   vout = (valor * 0.004883); // 
//   vin = vout / (R2/(R1+R2)); 
//   
//   if (vin<0.09) {
//   vin=0.0;// LIMPIEZA
//} 

// LEE EL VALOR DE LA ENTRADA ANALOGA BATERIA
   valorUno = analogRead(analogInputUno);
   voutBat = (valorUno * 0.004883); // 
   vinBat = voutBat / (R3/(R3+R4)); 
   
   if (vin<0.09) {
   vin=0.0;// LIMPIEZA
} 

// IMPRIME EN MONITOR SERIAL
//Serial.print(contador);
//Serial.print(" Voltaje Paneles= ");
//Serial.print(vin);
Serial.print("  Voltaje Bateria= ");
Serial.print(vinBat);
Serial.print("  resolucion:");
Serial.println(valorUno);
delay(3000);
contador = contador+1;

//IMPRIME XBEE



contador = contador+1;


}

//void digitalClockDisplay()
//{
//  // digital clock display of the time
//  Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.println(); 
//}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

