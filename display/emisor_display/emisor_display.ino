


int decenas;
int unidades;


void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
}

void loop()
{
  if (Serial.available()>0)
  {
    decenas=Serial.read();
    
    while(Serial.available()==0)
    {}
    
    unidades=Serial.read();
    decenas=decenas-48;
    unidades=unidades-48;
    Serial1.print(decenas);
    Serial1.print(unidades);
    Serial.println(decenas);
    Serial.println(unidades);
    
  }
}
    




