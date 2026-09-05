#include <Servo.h>

// LDR sensors
const int LDR_LEFT  = A0;
const int LDR_RIGHT = A1;

// Servo motor
const int SERVO_PIN = 9;

Servo trackerServo;

int servoAngle = 90;       // Initial panel position
const int MIN_ANGLE = 10;
const int MAX_ANGLE = 170;

const int TOLERANCE = 40;  // Difference required to move
const int STEP_SIZE = 1;   // Servo movement step

void setup() {

  Serial.begin(9600);

  trackerServo.attach(SERVO_PIN);

  // Start from the center position
  trackerServo.write(servoAngle);

  delay(1000);

  Serial.println("Solar Tracker Started");
}


void loop() {

  // Read LDR values
  int leftValue  = analogRead(LDR_LEFT);
  int rightValue = analogRead(LDR_RIGHT);

  // Calculate difference
  int difference = leftValue - rightValue;

  // Display sensor values
  Serial.print("Left LDR: ");
  Serial.print(leftValue);

  Serial.print(" | Right LDR: ");
  Serial.print(rightValue);

  Serial.print(" | Difference: ");
  Serial.println(difference);


  // Light is stronger on the left
  if (difference > TOLERANCE) {

    servoAngle += STEP_SIZE;

  }

  // Light is stronger on the right
  else if (difference < -TOLERANCE) {

    servoAngle -= STEP_SIZE;

  }

  // Keep servo within safe limits
  servoAngle = constrain(
    servoAngle,
    MIN_ANGLE,
    MAX_ANGLE
  );

  // Move solar panel
  trackerServo.write(servoAngle);

  // Small delay for stable movement
  delay(50);
}
