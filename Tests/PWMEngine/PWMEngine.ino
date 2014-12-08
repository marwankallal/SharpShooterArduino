

void setup(){
  pinMode(9, OUTPUT);
  
  //writes x/255 * 5 volts to pin 9
  analogWrite(9, 42.3);  
}

void loop()
{
}
