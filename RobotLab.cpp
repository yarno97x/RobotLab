//Code for EB, YG, LB, and NM
#include <Servo.h>
Servo leftservo;  
Servo rightservo;  
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const float time;
float gaptime; 
float duration;
const float speed = 35.64; //speed (cm/s) obtained experimentally
int initial_dist;
int dist;
float duration2;

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
  if (1400 > dist > 800) {
      Get_initial_dist();
    }
    else {
      Serial.println(initial_dist);
    }
}
    
    
void Get_dist() {
    //clear the ping pin
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    //send the 10 microsecond trigger
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    //get the pulse duration in microseconds
    duration2 = pulseIn(echoPin, HIGH);
    dist = duration2*0.034/2;
    if (1400 > dist > 800) { 
      Get_dist();
    }
    else {
      Serial.println(dist);
    }

}
void straight() {
    leftservo.write(140); //experimentally obtained; change if needed
    rightservo.write(-170); //experimentally obtained; change if needed
}
void TurnRight() {
    leftservo.write(180);
    rightservo.write(180);
    delay(350); //experimentally obtained; change if needed
}
void TurnLeft() {
    leftservo.write(-180);
    rightservo.write(-180);
    delay(500); //experimentally obtained; change if needed
}

void setup() {
  // put your setup code here, to run once:
  leftservo.attach(9);  
  rightservo.attach(10);
   //set up the Serial
  Serial.begin(9600);
  //setupt the pin modes  
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Get_initial_dist();
  gaptime = (150 - initial_dist)/speed;
}

void loop() {
  straight();
  delay(200); //experimentally obtained; change if needed
  Get_dist();
  
  if(dist > 200) {
    TurnRight();
    straight();
    delay(gaptime*1000+1000); //+1000 is an error margin, otherwise the robot may turn into the wall; modify if needed
    TurnLeft();
    straight();
    delay(10000);
  }
  else {
    return;
  }
  delay(1000);
}