#include <Arduino.h>

// Constants for pins and speeds
const int MOT1 = D8;
const int MOT2 = D7;
const int MOT3 = D6;
const int MOT4 = D5;
const int SENSOR_LEFT = D1;
const int SENSOR_RIGHT = D2;

// Speed settings
const int FORWARD_SPEED = 75;
const int INITIAL_SPEED = 75;
const int TURN_SPEED = 75;

// State variables
int leftSensorState = 0;
int rightSensorState = 0;

// Timeout settings
const unsigned long TIMEOUT_DURATION = 500; // 1 second timeout

// Function prototypes
void turnLeft();
void turnRight();
void stop();
void forward();
void readSensors();
void debugOutput();

void setup()
{
  // Motor pins setup
  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(MOT3, OUTPUT);
  pinMode(MOT4, OUTPUT);

  // Sensor pins setup with pull-up resistors
  pinMode(SENSOR_LEFT, INPUT_PULLUP);
  pinMode(SENSOR_RIGHT, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  forward(); // Start moving forward

  while (true)
  {
    readSensors();
    debugOutput();

    if (leftSensorState == 0 && rightSensorState == 1)
    {
      turnLeft();
    }
    else if (rightSensorState == 0 && leftSensorState == 1)
    {
      turnRight();
    }
  }
}

void readSensors()
{
  leftSensorState = digitalRead(SENSOR_LEFT);
  rightSensorState = digitalRead(SENSOR_RIGHT);
}

void forward()
{
  analogWrite(MOT1, INITIAL_SPEED);
  analogWrite(MOT2, 0);
  analogWrite(MOT3, INITIAL_SPEED);
  analogWrite(MOT4, 0);
}

void turnLeft()
{
  analogWrite(MOT3, 0);
  analogWrite(MOT4, TURN_SPEED);

  unsigned long startTime = millis(); // Record the start time

  while (leftSensorState == 0)
  {
    readSensors();
    debugOutput();

    if (rightSensorState == 0)
    {
      int prevLeft = leftSensorState;
      int prevRight = rightSensorState;
      stop();

      // Wait for a sensor change or timeout
      while (prevLeft == leftSensorState && prevRight == rightSensorState)
      {
        readSensors();
        if (millis() - startTime > TIMEOUT_DURATION) // Check for timeout
        {
          forward(); // Resume moving forward if timeout occurs
          return;    // Exit the function
        }
      }
    }
    analogWrite(MOT1, FORWARD_SPEED);
    analogWrite(MOT2, 0);
  }
  forward();
}

void turnRight()
{
  analogWrite(MOT1, 0);
  analogWrite(MOT2, TURN_SPEED);

  unsigned long startTime = millis(); // Record the start time

  while (rightSensorState == 0)
  {
    readSensors();
    debugOutput();

    if (leftSensorState == 0)
    {
      int prevLeft = leftSensorState;
      int prevRight = rightSensorState;
      stop();

      // Wait for a sensor change or timeout
      while (prevLeft == leftSensorState && prevRight == rightSensorState)
      {
        readSensors();
        if (millis() - startTime > TIMEOUT_DURATION) // Check for timeout
        {
          forward(); // Resume moving forward if timeout occurs
          return;    // Exit the function
        }
      }
    }
    analogWrite(MOT3, FORWARD_SPEED);
    analogWrite(MOT4, 0);
  }
  forward();
}

void stop()
{
  analogWrite(MOT1, 0);
  analogWrite(MOT2, 0);
  analogWrite(MOT3, 0);
  analogWrite(MOT4, 0);
}

void debugOutput()
{
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorState);
  Serial.print(" | Right Sensor: ");
  Serial.println(rightSensorState);
}
