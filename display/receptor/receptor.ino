#include <TimerOne.h>
int t_dec = 23;
int t_uni =22;
byte display[10] = {63, 06, 91, 79, 102, 109, 125, 07, 127, 103};
int decenas;
int unidades;
int temp;
int disp;


void reloj()
{
  if (disp==1)
  {
    disp=0;
    Serial.println("relojrejorlñsjkdfopias djfoijdfgoidfhgñoidfasf");
    temp++;
  }
  else
  {
    disp=1;
    temp++;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(t_uni, OUTPUT);     
  pinMode(t_dec, OUTPUT);     
  pinMode(43, OUTPUT);        
  pinMode(44, OUTPUT);       
  pinMode(45, OUTPUT);       
  pinMode(46, OUTPUT);       
  pinMode(47, OUTPUT);      
  pinMode(48, OUTPUT);      
  pinMode(49, OUTPUT);    
 temp=0; 
 Timer1.initialize(500000);
 Timer1.attachInterrupt(reloj);
 disp=1;
}
void loop()
{
  Timer1.detachInterrupt();
  temp=0;
  if (Serial1.available()>0)
  {
    temp=0;
    decenas=Serial1.read();
    decenas=decenas-48;
    
    while(Serial1.available()==0)
    {}
    
    unidades=Serial1.read();
    
    unidades=unidades-48;
  
  while(temp<6)
  {
  if (disp==1)
  {
  digitalWrite(t_dec, LOW);   
  digitalWrite(t_uni, HIGH);
   PORTL=(display[unidades]);
   delay(1);
  digitalWrite(t_uni, LOW);  
  digitalWrite(t_dec, HIGH);   
  PORTL = (display[decenas]);	     
  delay(1); 
  Timer1.attachInterrupt(reloj);
  }
  else
  {
  digitalWrite(t_dec, LOW);   
  digitalWrite(t_uni, LOW);
  Timer1.attachInterrupt(reloj);
  }
  }
  }
   while(Serial1.available()==0)
    {
   digitalWrite(t_dec, LOW);   
  digitalWrite(t_uni, HIGH);
  
   PORTL=(display[unidades]);
   delay(1);
  digitalWrite(t_uni, LOW);   
  digitalWrite(t_dec, HIGH);   
  PORTL = (display[decenas]);	     
  delay(1); 
  Timer1.detachInterrupt();
    } 
}
    

