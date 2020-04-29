void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
}

void loop ()
{
  if (Serial.available())
  {
    Serial.print(Serial1.read);
  }
}
