#include <Servo.h>

Servo servo;

void setup() {

servo.attach(2); //D4

servo.write(0);

delay(2000);

//lampOn();

changeColor();

}

void loop() {





}

void changeColor(){
  delay(100);
  servo.write(54);
  delay(2000);
  servo.write(0);
}


void lampOn(){
  delay(100);
  servo.write(57);
  delay(300);
  servo.write(0);
}
