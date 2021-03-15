#include <Servo.h>

Servo servoprueba; //Creo el uso de un servo


void setup() {
  servoprueba.attach(A0); //Uso el pin analogico 0

  servoprueba.write(0); //coloca en la posicion 0
}

void loop() {
  int i;

  for(i=0;i<180;i++){
    servoprueba.write(i);
    delay(20);
  }
  delay(200);
  for(i=180;i>0;i--){
    servoprueba.write(i);
    delay(20);
  }
  delay(200);

}
