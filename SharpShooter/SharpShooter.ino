#include <Servo.h> 

int MOTORPIN = 6; //DONT USE 9 OR 10, SERVO DISABLES THEM
int SONARPIN = 1;
int SERVOPIN = 9;

//servo positions (0, 1, 2, ||3||, 4, 5, 6)

//Base voltage for voltage equation (FRONT CUP)
int baseVoltageSteps = 41; //v = b + .5v/3.3in * inchesFromFront

int currentCup = 3;

//user input buffer
char userIn[1]; 

Servo trackServo;

void setup(){
  //basic setup
  Serial.begin(9600);
  trackServo.attach(SERVOPIN);
  pinMode(MOTORPIN, OUTPUT);
  
  //start user prompt and play flow
  Serial.println("Welcome to SharpShooter!\nPlease 0 to (s)tart or 1 to (c)alibrate");
  
  if(waitAndGetInt() == 1){
    calibrate();
  }
}

void loop(){
  //TODO READ SONAR TO GET DISTANCE
  
  setMotorVoltageSteps(baseVoltageSteps + ((float)getCupRow(currentCup) * 0.5));
  
  Serial.println("enter anything to kill");
  waitAndGetInt();
  
  setMotorVoltageSteps(0);
  
  Serial.println("HIT (0) or MISS (1)");
  
  if(waitAndGetInt() == 0){
    moveServoToPosition(getCupPosition(currentCup + 1));
    currentCup++;
  }
}

//returns distance in inches
int readSonar(){
  long anVolt, inches, cm;
  int sum=0;//Create sum variable so it can be averaged
  int avgrange=60;//Quantity of values to average (sample size)
  
  for(int i = 0; i < avgrange ; i++)
  {
    //Used to read in the analog voltage output that is being sent by the MaxSonar device.
    //Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
    //Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
    anVolt = (float)analogRead(SONARPIN) / 2;
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
  
  return inches;
}

void calibrate(){
  Serial.println("Please enter a new base voltage (IN ARDUINO STEPS):");
  baseVoltageSteps = waitAndGetInt();
}

int waitAndGetInt(){
  //wait for user
  while (Serial.available()==0){ } 
  return Serial.parseInt();
}

void setMotorVoltage(float volts){
  analogWrite(MOTORPIN, volts * 255.0 / 5.0 );
}

void setMotorVoltageSteps(int voltSteps){
  analogWrite(MOTORPIN, voltSteps);
}

int getCupPosition(int cupNum){
  switch(cupNum){
    case 0: return 3;
            break;
    case 1: return 2;
            break;
    case 2: return 4;
            break;
    case 3: return 1;
            break;
    case 4: return 3;
            break;
    case 5: return 5;
            break;
    case 6: return 0;
            break;
    case 7: return 2;
            break;
    case 8: return 4;
            break;
    case 9: return 6;
            break;
    default: Serial.println("ERROR: NO SUCH CUP (getCupPosition)");
            break;   
  }
}

void moveServoToPosition(int pos){
  //NOTE: CONTINUOUS ROTATION SERVOS HAVE NO ANGLE MODIFIERS. THEY TAKE SPEEDS (180 FULL SPEED, -180 FULL REVERSE)
  int mov = pos - getCupPosition(currentCup);
  
  mov < 0 ? trackServo.write(180) : trackServo.write(0); //check which way to move and move there
  delay(400 * mov); //TODO: FIND PROPER DELAY FOR ONE POSITION
  trackServo.write(90);
  
}

int getCupRow(int cupNum){
  switch(cupNum){
     case 0: return 0;
             break;
     case 1:
     case 2: return 1;
             break;
     case 3:
     case 4:
     case 5: return 2;
             break;
     case 6:
     case 7:
     case 8:
     case 9: return 3;
             break;
     default: Serial.println("ERROR: NO SUCH CUP (getCupRow)");
  }
}
