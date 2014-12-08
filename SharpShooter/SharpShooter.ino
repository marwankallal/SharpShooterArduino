
#define MOTORPIN 9
#define SONARPIN 1
#define SERVOPIN 11

//servo positions (0, .5, 1, ||1.5||, 2, 2.5, 3)

//Base voltage for voltage equation (0 point)
int baseVoltage = 0; //FIXME: FIND THE RIGHT VOLTAGE

int currentCup = 0;

//user input buffer
char userIn[1]; 

void setup(){
  
  Serial.begin(9600);
  
  Serial.println("Welcome to SharpShooter!\nPlease (s)tart to begin or (c)alibrate");
  
  if(waitAndGetLetter() == 'c'){
    calibrate();
  }
}

void loop(){
  
  
  
}

void calibrate(){
  //TODO: BUILD ME!
  Serial.println("Please enter a new base voltage:");
  baseVoltage = waitAndGetNumber();
}

char waitAndGetLetter(){
  //wait for user
  while (Serial.available()==0){ }
  Serial.readBytes(userIn, 1);
  return userIn[0];
}

int waitAndGetNumber(){
  //wait for user
  while (Serial.available()==0){ } 
  return Serial.parseInt();
}

int getCupPosition(int cupNum){
  switch(cupNum){
    case 0: return 1.5;
            break;
    case 1: return 1;
            break;
    case 2: return 2;
            break;
    case 3: return 0.5;
            break;
    case 4: return 1.5;
            break;
    case 5: return 2.5;
            break;
    case 6: return 0;
            break;
    case 7: return 1;
            break;
    case 8: return 2;
            break;
    case 9: return 3;
            break;
    default: Serial.println("ERROR: NO SUCH CUP (getCupPosition)");
            break;   
  }
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
