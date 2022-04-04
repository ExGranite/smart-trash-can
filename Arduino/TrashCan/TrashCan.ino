#include <Servo.h>
Servo motor; 
int servoposition = 0;  
// IR Sensor Pins
int IRsensor = 8;
int IRData;
// Ultrasonic sensor Pins
const int trigPin = 11;
const int echoPin = 12;
int low = 4;
int full = 5;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IRsensor, INPUT);
  pinMode(low, OUTPUT);
  pinMode(full, OUTPUT);
  motor.attach(7); // Servo Motor
}

long duration, distance;

void loop() {
  delay(500);
  // Servo and IR Sensor Logic
  depth();
  char reading  = Serial.read(); 
  if (reading == 'F') {
    digitalWrite(full,HIGH);
    digitalWrite(low,LOW);
    Serial.println("Full");
  } else if (reading == 'L') {
    digitalWrite(full,LOW);
    digitalWrite(low,HIGH);
    Serial.println("Empty");
  }
  IRData = digitalRead(IRsensor);
  if (IRData == 1) {
    motor.write(120);
    Serial.println("Open");
  } else {
    motor.write(0);
    Serial.println("Close");
  }
}
void depth()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration/10);
}
