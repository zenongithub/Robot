#include <NewPing.h>

#define ULTRASONIC_LEFT_TRIG A5
#define ULTRASONIC_LEFT_ECHO A4
#define ULTRASONIC_CENTER_TRIG A3
#define ULTRASONIC_CENTER_ECHO A2
#define ULTRASONIC_RIGHT_TRIG A1
#define ULTRASONIC_RIGHT_ECHO A0

#define MOTOR_ADJUST_SPEED 150
#define DISTANCE_TO_CHECK 30

// Right motor
int enableRightMotor = 7;
int rightMotorPin1 = 6;
int rightMotorPin2 = 5;

// Left motor
int enableLeftMotor = 2;
int leftMotorPin1 = 4;
int leftMotorPin2 = 3;

NewPing sonarLeft(ULTRASONIC_LEFT_TRIG, ULTRASONIC_LEFT_ECHO, 400);
NewPing sonarCenter(ULTRASONIC_CENTER_TRIG, ULTRASONIC_CENTER_ECHO, 400);
NewPing sonarRight(ULTRASONIC_RIGHT_TRIG, ULTRASONIC_RIGHT_ECHO, 400);

void setup() {

  Serial.begin(9600);

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
}


void loop() {

  int leftDistance = sonarLeft.ping_cm();
  int centerDistance = sonarCenter.ping_cm();
  int rightDistance = sonarRight.ping_cm();

  Serial.print("Sensor Kiri: ");
  Serial.print(leftDistance);
  Serial.print(" cm\t");

  Serial.print("Sensor Tengah: ");
  Serial.print(centerDistance);
  Serial.print(" cm\t");

  Serial.print("Sensor Kanan: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  if (centerDistance > 0 && centerDistance < DISTANCE_TO_CHECK) {

    rotateMotor(0, 0);
    delay(500);

    rotateMotor(-MOTOR_ADJUST_SPEED, -MOTOR_ADJUST_SPEED);
    delay(200);

    rotateMotor(0, 0);
    delay(500);

    int distanceLeft = sonarLeft.ping_cm();
    int distanceRight = sonarRight.ping_cm();

    if (distanceLeft == 0) {
      rotateMotor(MOTOR_ADJUST_SPEED, -MOTOR_ADJUST_SPEED);
      delay(200);
    } else if (distanceRight == 0) {
      rotateMotor(-MOTOR_ADJUST_SPEED, MOTOR_ADJUST_SPEED);
      delay(200);
    } else if (distanceLeft >= distanceRight) {
      rotateMotor(MOTOR_ADJUST_SPEED, -MOTOR_ADJUST_SPEED);
      delay(200);
    } else {
      rotateMotor(-MOTOR_ADJUST_SPEED, MOTOR_ADJUST_SPEED);
      delay(200);
    }
    rotateMotor(0, 0);
    delay(200);
  } else if (leftDistance <= 10) {
    rotateMotor(0, MOTOR_ADJUST_SPEED);
    delay(200);
  } else if (rightDistance <= 10) {
    rotateMotor(MOTOR_ADJUST_SPEED, 0);
    delay(200);
  } else {
    rotateMotor(MOTOR_ADJUST_SPEED, MOTOR_ADJUST_SPEED);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed >= 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed >= 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}