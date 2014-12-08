// this sketch sends 6-bit digital number 
// to Arduino outputs D5, D4 D3, D2, D1 and D0.
// the digital number then gets converted into analog signal via D/A converter.

int del=0;  //delay in milliseconds

// the setup routine runs once when you press reset:
void setup() {           
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT);  
  pinMode(1, OUTPUT);  
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);    
}

// the loop routine runs over and over again forever:
void loop() {

  // next sequence sends 000111 digital signal to the output.

   digitalWrite(5,LOW);  //sets pin D5 to LOW (0V output) 
   digitalWrite(4,LOW);
   digitalWrite(3,LOW);
   digitalWrite(2,LOW);
   digitalWrite(1,LOW);
   digitalWrite(0,LOW);  //sets pin D0 to HIGH (5V output)
   
   Serial.println((float)analogRead(A0) * 5.0 / 1023.0);
   
   delay(del);
}


