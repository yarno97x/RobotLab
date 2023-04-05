//Code for EB, YG, LB, and NM
#include <Servo.h>
Servo leftservo;  
Servo rightservo;  
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
float time;
const float speed = 35.64; //speed (cm/s) obtained experimentally
int initial_dist;

void setup() {
  leftservo.attach(9);  
  rightservo.attach(10);
   //set up the Serial
  Serial.begin(9600);
  //setupt the pin modes  
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Get_initial_dist(); // Get y distance
  GetTime();
  TurnRight();
  straight();
  delay(time*1000);
  TurnLeft();
  straight();
}

void Get_initial_dist() {
    //clear the ping pin
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    //send the 10 microsecond trigger
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    //get the pulse duration in microseconds
    duration = pulseIn(echoPin, HIGH);
    initial_dist = duration*0.034/2;
    Serial.println(initial_dist);
}
void GetTime() {
    time =(80-initial_dist)/speed; // Get time to go 20 cm from the lower wall
}
void straight() {
    leftservo.write(170);
    rightservo.write(-180);
}
void TurnRight() {
    leftservo.write(180);
    rightservo.write(180);
    delay(1320);
}
void TurnLeft() {
    leftservo.write(-180);
    rightservo.write(-180);
    delay(1320);\
}

void loop() {
    Get_initial_dist();
    if(initial_dist > 200) { // hits the gap
        TurnRight();
        straight(); // crosses second gap
        delay(2000);
        TurnLeft();
        straight(); //move indefinitely through last straight
        delay(10000);
    }
}