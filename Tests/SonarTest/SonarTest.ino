//Analog pin 1 for reading in the analog voltage from the MaxSonar device.
//This variable is a constant because the pin will not change throughout execution of this code.
const int anPin = 1;

//variables needed to store values
long anVolt, inches, cm;
int sum=0;//Create sum variable so it can be averaged
int avgrange=60;//Quantity of values to average (sample size)

void setup() {

  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
}

void loop() {

  //MaxSonar Analog reads are known to be very sensitive. See the Arduino forum for more information.
  //A simple fix is to average out a sample of n readings to get a more consistant reading.\\ 
  //Even with averaging I still find it to be less accurate than the pw method.\\ 
  //This loop gets 60 reads and averages them

  for(int i = 0; i < avgrange ; i++)
  {
    //Used to read in the analog voltage output that is being sent by the MaxSonar device.
    //Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
    //Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
    anVolt = (float)analogRead(anPin) / 2;
    Serial.println(anVolt);
    sum += anVolt;
    delay(10);
  }  
  cm = sum/avgrange;
  inches = cm / 2.54;

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  //reset sample total
  sum = 0;
  delay(500);
}
