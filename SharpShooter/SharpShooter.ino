#include <Servo.h> 

#define MOTORPIN 9
#define SONARPIN 1
#define SERVOPIN 11

//servo positions (0, 1, 2, ||3||, 4, 5, 6)

//Base voltage for voltage equation (0 point)
int baseVoltage = 0; //FIXME: FIND THE RIGHT STARTING VOLTAGE

int currentCup = 0;

//user input buffer
char userIn[1]; 

Servo trackServo;

void setup(){
  //basic setup
  Serial.begin(9600);
  trackServo.attach(SERVOPIN);
  
  //start user promtp and play flow
  Serial.println("Welcome to SharpShooter!\nPlease (s)tart to begin or (c)alibrate");
  
  if(waitAndGetLetter() == 'c'){
    calibrate();
  }
  else{
    moveServoToPosition(4);
  }
}

void loop(){
  
  
  
}

void calibrate(){
  Serial.println("Please enter a new base voltage (IN ARDUINO STEPS):");
  baseVoltage = waitAndGetInt();
}

char waitAndGetLetter(){
  //wait for user
  while (Serial.available()==0){ }
  Serial.readBytes(userIn, 1);
  return userIn[0];
}

int waitAndGetInt(){
  //wait for user
  while (Serial.available()==0){ } 
  return Serial.parseInt();
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
  
  mov > 0 ? trackServo.write(180) : trackServo.write(0); //check which way to move and move there
  delay(200 * mov); //TODO: FIND PROPER DELAY FOR ONE POSITION
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
