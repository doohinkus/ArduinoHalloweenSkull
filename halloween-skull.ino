#include <Servo.h>

Servo myServo;

//set up pins for devices
const int trigPin = 7;
const int servo = 9;

//sets the amount of spin/sweep range on the servo
const int sweepRange = 90;

//variables for distnace calculations
long cm;
long duration;


//sets the target range of the sensor in centimeters--how far away something is to trigger servo
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
  
  //This is for serial output feedback, you can fine tune distance setting with this info
  Serial.begin(9600);
  
  //attach servo
  myServo.attach(servo);

}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void loop() {
  //check distance by creating pulses
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  //four pin models have a separate pins for this, which makes better sense. 
  pinMode(trigPin, INPUT);
  duration = pulseIn(trigPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  
  //output distance, change the range of the sensor in the variables at the top
  Serial.print("Distance: ");
  Serial.println(cm);
  
  //trigger servo sweep when in range
  if (cm < range){
     sweepServo();     
  }else{
  //reset servo when out of range--this is kind of cool, it makes the skull seem more lively
  restServo();
  }
}
