#include <Servo.h>

Servo myServo;

//set up pins for devices
const int trigPin = 2;
const int echoPin = 7;
const int servo = 9;

//sets the amount of spin on the servo
const int sweepRange = 90;

//variables for distnace calculations
int pos = 0;
long duration;
int distance;

//sets the range of the sensor in centimeters
int range = 70;

//sweep servo function
void sweepServo(){
  for (pos = 0; pos <= sweepRange; pos += 1){
    myServo.write(pos);
    delay(10);
  }
  for (pos = sweepRange; pos >= 0; pos -= 1){
    myServo.write(pos);
    delay(7);
  }
}

//reset servo function
void restServo(){
  myServo.write(15);
}

void setup() {
  // set up inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //This is for serial output feedback, you can fine tune distance setting with this info
  Serial.begin(9600);
  
  //attach servo
  myServo.attach(servo);

}

void loop() {
  //check distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //calcucate distance
  duration = pulseIn(echoPin,HIGH);
  distance = duration*.034/2;
  
  //output distance, change the range of the sensor in the variables at the top
  Serial.print("Distance: ");
  Serial.println(distance);
  
  //trigger servo sweep when in range
  if (distance<range){
     sweepServo();     
  }else{
  //reset servo when out of range--this is kind of cool, it makes the skull seem more lively
  restServo();
  }
}
