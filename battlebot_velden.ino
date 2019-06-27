int ultraSonicTrigPin = 9;    
int ultraSonicEchoPin = 12;    
long ultraSonicDuration, mm;  
int infraRedSensorPin = 13; 
int leftSpeedPin = 6;
int rightSpeedPin = 5;
int leftDirectionPin = 7;
int rightDirectionPin = 4;
int motorRight = 255;
int motorLeft = 255;
int leftSpeed = 255;
int rightSpeed = 255;
bool leftDirection = true;
bool rightDirection = true;
unsigned long searchTime = 0;
unsigned long searchTimeNow = 0;

void setup() {
 Serial.begin (9600);
 pinMode(ultraSonicTrigPin, OUTPUT);
 pinMode(ultraSonicEchoPin, INPUT);
 pinMode(4, OUTPUT);
 pinMode(leftSpeedPin, OUTPUT);
 pinMode(rightSpeedPin, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(13, INPUT);
 resetSearchTime ();
}

void resetSearchTime () {
  searchTime = millis();
}

void ultraSonicSensorFunction () {
  float Period1 = 0.005;
  float Period2 = 0.01;
  if (millis() == ultraSonicTimeNow) { 
    digitalWrite(ultraSonicTrigPin, LOW);
  }
  if (millis() > ultraSonicTimeNow + Period1){
    digitalWrite(ultraSonicTrigPin, HIGH);
  }
  if (millis() > ultraSonicTimeNow + Period2){
     digitalWrite(ultraSonicTrigPin, LOW);
    ultraSonicTimeNow = millis;
  }
  
  pinMode(ultraSonicEchoPin, INPUT);
  ultraSonicDuration = pulseIn(ultraSonicEchoPin, HIGH);
 
  mm = (ultraSonicDuration/2) / 2.91;     
  Serial.print(mm);
  Serial.print("mm");
  Serial.println();
}

void outOfBounds () {
leftDirection = 0;
rightDirection = 0;
motorFunction ();
}

void motorFunction () {
 digitalWrite(leftDirectionPin, leftDirection);
 digitalWrite(rightDirectionPin, rightDirection);
 analogWrite(leftSpeed, leftSpeed);
 analogWrite(rightSpeed, leftSpeed);
}

void searchMode () {
int periodOne = 2000;
int periodTwo = 5000;
int periodThree = 7000;
searchTimeNow = millis();
if(searchTimeNow - searchTime <= periodOne){
 leftDirection = false;
 rightDirection = true;
 leftSpeed = 50;
 rightSpeed = 25;
 motorFunction ();
} else if (searchTimeNow - searchTime <= periodTwo){
 leftDirection = false;
 rightDirection = false;
 leftSpeed = 50;
 rightSpeed = 50;
motorFunction ();
} else if (searchTimeNow - searchTime <= periodThree){
 leftDirection = true; 
 rightDirection = false;
 leftSpeed = 25; 
 rightSpeed = 50;
 motorFunction ();
} 
else {
 resetSearchTime ();
}
}




void motorAttack () {
leftSpeed = 255;
rightSpeed = 255;
leftDirection = false;
rightDirection = false;
motorFunction ();
}

void loop() {
  /*ultraSonicSensorFunction ();
  while (digitalRead(infraRedSensorPin)==true){
 outOfBounds ();
  }
  
  while (mm <=500) {
    motorAttack ();
}*/
 searchMode ();
}
