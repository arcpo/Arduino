//Arduino Mega
/* La idea es variar la intensidad de luz de un tira led. 
 * Controlando la base de un transistor (TIP 31 en este caso)
 * y usando PWM en la base, usando ciclos de encendido y apagado
 */

#define PWM1 9 //Salida PWM a la base del transistor
#define PIN2 61 //Entrada por donde mide la resistencia

int Pote = 0;
float luz = 0;
float tensionPote = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
}

void loop() {
  Pote=analogRead(PIN2);
  Pantalla();
  luz = map(Pote,0,1023,0,255);
  analogWrite(PWM1,luz);
  delay(100);  
}

void Pantalla(){
      Serial.print("valor analogico: ");
      Serial.print(Pote);
      Serial.print(" valor tension: ");
      tensionPote=Pote*(5.0/1023.0);
      Serial.println(tensionPote);
      return;
      }
