#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
double l1 = 74;
double l2 = 54;
double theta1;
double theta2;
double c2;
double s2;

void setup () {
  Serial.begin(9600);
  servo1.attach(3,544,2400);
  servo2.attach(4,544,2400);
  servo3.attach(2,544,2400);
}

void loop () {
  line(-90,-60,50);
}

void getAngles(float Px, float Py) {
  // first find theta2 where c2 = cos(theta2) and s2 = sin(theta2)
  c2 = (pow(Px,2) + pow(Py,2) - pow(l1,2) - pow(l2,2))/(2*l1*l2); //is btwn -1 and 1
  //if (elbowup == false) {
  s2 = sqrt(1 - pow(c2,2));  //sqrt can be + or -, and each corresponds to a different orientation
  // } else if (elbowup == true) {
  //   s2 = -sqrt(1 - pow(c2,2));
  // }
  theta2 = degrees(atan2(s2,c2));  // solves for the angle in degrees and places in correct quadrant
  theta2 = int(theta2);
  theta1 = degrees(atan2(-l2*s2*Px + (l1 +  l2*c2)*Py, \
                         (l1 + l2*c2)*Px + l2*s2*Py));
  theta1 = int(theta1);
}

void line(int low, int high, int constY) {
  for(int x=low; x<high; x++) {
    getAngles(x, constY);
    moveArms();
  }
  for(int x=high; x>low; x--) {
    getAngles(x, constY);
    moveArms();
  }
}

void moveArms() {
  Serial.print(theta1);
  Serial.print(",");
  Serial.println(theta2);
  servo1.write(int(theta1));
  servo2.write(int(theta2));
  delay(30); 
}
