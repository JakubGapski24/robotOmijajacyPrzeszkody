#include <Arduino.h>

class Robot {
  private:
          int L_direction;
          int L_speed;
          int R_speed;
          int R_direction;

  public:
          Robot() {
            L_direction = 4;
            L_speed = 5;
            R_speed = 6;
            R_direction = 9;
          }


          int getL_direction() {
            return L_direction;
          }
          int getL_speed() {
            return L_speed;
          }
          int getR_speed() {
            return R_speed;
          }
          int getR_direction() {
            return R_direction;
          }

          void leftMotor (int speed) {
            if (speed > 0) { //jedź do przodu

              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(L_direction, 0); //lewy silnik - obrót w prawo
              analogWrite(L_speed, speed); //prędkość lewego silnika PWM
            }
            else if (speed < 0) { //jedź do tyłu
              speed = abs(speed); //zamień na liczbę dodatnią
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(L_direction, 1); //lewy silnik - obrót w lewo
              analogWrite(L_speed, speed); //prędkość lewego silnika w PWM
            }
            else {
              analogWrite(L_speed, 0);
            }
          }

          void rightMotor (int speed) {
            if (speed > 0) { //jedź do przodu
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(R_direction, 0); //prawy silnik - obrót w prawo
              analogWrite(R_speed, speed); //prędkość prawego silnika PWM
            }
            else if (speed < 0) { //jedź do tyłu
              speed = abs(speed); //zamień na liczbę dodatnią
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(R_direction, 1); //lewy silnik - obrót w lewo
              analogWrite(R_speed, speed); //prędkość lewego silnika w procentach
            }
            else {
              analogWrite(R_speed, 0);
            }
          }

          void stopRobot() {
            analogWrite(L_speed, 0);
            analogWrite(R_speed, 0);
          }
};

class ObstacleAvoider : public Robot {
  private:
          int buzzer;
          int L_switch;
          int R_switch;

  public:
          ObstacleAvoider() {
            buzzer = 10;
            L_switch = 15;
            R_switch = 14;
          }

          int getBuzzer() {
            return buzzer;
          }
          int getL_switch() {
            return L_switch;
          }
          int getR_switch() {
            return R_switch;
          }

          void L_SWITCH (short Random) {
            if (digitalRead(L_switch) == LOW) {
              digitalWrite(buzzer, HIGH);
              leftMotor(-40);
              rightMotor(-40);
              delay(500);
              digitalWrite(buzzer, LOW);
              leftMotor(-50);
              rightMotor(50);
              delay(300 + Random);
            }
          }

          void R_SWITCH (short Random) {
            if (digitalRead(R_switch) == LOW) {
                digitalWrite(buzzer, HIGH);
                leftMotor(-40);
                rightMotor(-40);
                delay(500);
                digitalWrite(buzzer, LOW);
                leftMotor(50);
                rightMotor(-50);
                delay(300 + Random);
            }
          }
};

ObstacleAvoider robot;

void setup() {
  pinMode(robot.getL_direction(), OUTPUT);
  pinMode(robot.getL_speed(), OUTPUT);
  pinMode(robot.getR_speed(), OUTPUT);
  pinMode(robot.getR_direction(), OUTPUT);
  pinMode(robot.getBuzzer(), OUTPUT);
  digitalWrite(robot.getBuzzer(), LOW);
  pinMode(robot.getL_switch(), INPUT_PULLUP);
  pinMode(robot.getR_switch(), INPUT_PULLUP);
  randomSeed(analogRead(A2));
}

void loop() {
  robot.leftMotor(50);
  robot.rightMotor(50);
  short Random = random(5,20) * 10;
  robot.L_SWITCH(Random);
  robot.R_SWITCH(Random);
}