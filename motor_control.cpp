#include <Arduino.h>

#define BLACK 1
#define WHITE 0

const int MOT1 = D8;
const int MOT2 = D7;
const int MOT3 = D6;
const int MOT4 = D5;
const int SENSOR_LEFT = D1;
const int SENSOR_RIGHT = D2;

const int MAX_SPEED = 90;
const int INITIAL_SPEED = 75;
const int TURN_SPEED = 75;
const int BACKWARD_SPEED = 76;

void setup()
{
    pinMode(MOT1, OUTPUT);
    pinMode(MOT2, OUTPUT);
    pinMode(MOT3, OUTPUT);
    pinMode(MOT4, OUTPUT);
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
}

void forward()
{
    analogWrite(MOT1, INITIAL_SPEED);
    analogWrite(MOT2, 0);
    analogWrite(MOT3, INITIAL_SPEED);
    analogWrite(MOT4, 0);
}

void reverse()
{
    analogWrite(MOT1, 0);
    analogWrite(MOT2, BACKWARD_SPEED);
    analogWrite(MOT3, 0);
    analogWrite(MOT4, BACKWARD_SPEED);
}

void turnLeft()
{
    analogWrite(MOT1, 0);
    analogWrite(MOT2, TURN_SPEED);
    analogWrite(MOT3, TURN_SPEED);
    analogWrite(MOT4, 0);
}

void turnRight()
{
    analogWrite(MOT1, TURN_SPEED);
    analogWrite(MOT2, 0);
    analogWrite(MOT3, 0);
    analogWrite(MOT4, TURN_SPEED);
}

void stop()
{
    analogWrite(MOT1, 0);
    analogWrite(MOT2, 0);
    analogWrite(MOT3, 0);
    analogWrite(MOT4, 0);
}

void loop()
{
    forward();
    delay(2000);
    stop();
    delay(1000);

    reverse();
    delay(2000);
    stop();
    delay(1000);

    turnLeft();
    delay(2000);
    stop();
    delay(1000);

    turnRight();
    delay(2000);
    stop();
    delay(1000);

    while (1)
        ;
}