#include <TimerOne.h>
int t_dec = 35;
int t_uni =34;
byte display[10] = {63, 06, 91, 79, 102, 109, 125, 07, 127, 103};
int decenas;
int unidades;
int start = 37;
int P1= 31;
int P2= 30;
int vcarro= 22;
int acarro= 23;
int rcarro = 24;
int vpeaton = 25;
int rpeaton = 26;
int cont,primero;
int seg, tilt,marca;

void reloj()
{
  if (tilt==1)
  {
     
  if (marca==0)
  {
    marca=1;
    seg=seg-1;
  }
  else
  {
  marca=0;
  seg=seg-1;
  }
  }
  else
  {
  seg=seg-1;
  Serial.println("aca");
  }
}

void setup() 
{
   pinMode(t_uni, OUTPUT);     
  pinMode(t_dec, OUTPUT);     
  pinMode(43, OUTPUT);        
  pinMode(44, OUTPUT);       
  pinMode(45, OUTPUT);       
  pinMode(46, OUTPUT);       
  pinMode(47, OUTPUT);      
  pinMode(48, OUTPUT);      
  pinMode(49, OUTPUT);  
 pinMode(P1,INPUT);
 pinMode(P2,INPUT);
 pinMode(start,INPUT);
 pinMode(vcarro,OUTPUT);
 pinMode(acarro,OUTPUT);
 pinMode(rcarro,OUTPUT);
 pinMode(vpeaton,OUTPUT);
 pinMode(rpeaton,OUTPUT);
 digitalWrite(vcarro,LOW);
 digitalWrite(acarro,LOW);
 digitalWrite(rcarro,LOW);
 digitalWrite(vpeaton,LOW);
 digitalWrite(rpeaton,LOW);
 Serial.begin(9600);
 seg=0;
 cont=0;
 Timer1.initialize(500000);
 Timer1.attachInterrupt(reloj);
  seg=42;
  tilt=0;
  marca=1;
  primero=1;
}

void loop() 
{
  cont=0;
  Timer1.detachInterrupt();
  
  if(digitalRead(start)==HIGH)
  {
    
    while (seg>10)
    {
       //Serial.println("man");
      decenas=(seg/2)/10;
      unidades=(seg/2)%10;
      Serial.println(seg);
    digitalWrite(rcarro,HIGH);
    digitalWrite(vpeaton,HIGH);
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
    while(11>seg && seg>0)
    {
      tilt=1;
      
      if(marca==1)
      {
     Timer1.attachInterrupt(reloj);
     decenas=(seg/2)/10;
     unidades=(seg/2)%10;
     Serial.println(seg);
    digitalWrite(rcarro,HIGH);
    digitalWrite(vpeaton,HIGH);
    digitalWrite(t_dec, LOW);   
    digitalWrite(t_uni, HIGH);
    PORTL=(display[unidades]);
   delay(1);
   digitalWrite(t_uni, LOW);   
   digitalWrite(t_dec, HIGH);   
    PORTL = (display[decenas]);	     
    delay(1); 
    } 
    if(marca==0)
    {
     decenas=(seg/2)/10;
     unidades=(seg/2)%10;
     Serial.println(seg);
     Serial.println("davidddddddddd");
    digitalWrite(rcarro,HIGH);
    digitalWrite(vpeaton,LOW);
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
    }
    
  digitalWrite(vpeaton,LOW);
  digitalWrite(rcarro,LOW);
  Serial.println("ojholknfofgfdhgfg");
  seg=40;
  tilt=0;
  
   while (seg>10)
    {
    decenas=(seg/2)/10;
    unidades=(seg/2)%10;
    Serial.println(seg);
    digitalWrite(rpeaton,HIGH);
    digitalWrite(vcarro,HIGH);
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
    while(11>seg && seg>0)
    {
      tilt=1;
      Timer1.attachInterrupt(reloj);
      if(marca==1)
      {
     decenas=(seg/2)/10;
     unidades=(seg/2)%10;
     Serial.println(seg);
    digitalWrite(rpeaton,HIGH);
    digitalWrite(vcarro,HIGH);
    digitalWrite(t_dec, LOW);   
    digitalWrite(t_uni, HIGH);
    PORTL=(display[unidades]);
   delay(1);
   digitalWrite(t_uni, LOW);   
   digitalWrite(t_dec, HIGH);   
    PORTL = (display[decenas]);	     
    delay(1); 
    }
    if(marca==0)
    {
     decenas=(seg/2)/10;
     unidades=(seg/2)%10;
     Serial.println(seg);
    digitalWrite(rpeaton,HIGH);
    digitalWrite(vcarro,LOW);
    digitalWrite(t_dec, LOW);   
    digitalWrite(t_uni, HIGH);
    PORTL=(display[unidades]);
   delay(1);
   digitalWrite(t_uni, LOW);   
   digitalWrite(t_dec, HIGH);   
    PORTL = (display[decenas]);	     
    delay(1); 
    }
    }
  digitalWrite(vcarro,LOW);
  digitalWrite(rpeaton,LOW);
  seg=2;
  tilt=0;
  while (seg>0)
  {
  Timer1.attachInterrupt(reloj);
  digitalWrite(acarro,HIGH);
  digitalWrite(rpeaton,HIGH);
  digitalWrite(t_uni, LOW);   
  digitalWrite(t_dec, LOW);
  }
  digitalWrite(acarro,LOW);
  digitalWrite(rpeaton,LOW);  
  seg=40;
    
    
    
  
    
    

