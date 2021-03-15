/* Creo que está al pepe, por eso lo comento 
#include <Wire.h>
*/

// Pines digitales para el detector de nivel (sensor ultrasonico)
// Configuramos los pines del sensor Trigger y Echo
const int PinTrig = 7;
const int PinEcho = 6;

// Variables para niveles de agua del sensor ultrasonico
const int DistMin = 25;
const int DistN2 = 45;
const int DistMax = 70;

// Constante velocidad sonido en cm/s
const float VelSon = 36000.0; //En verdad la velocidad es 34320 pero el numero puesto se acerca mas a la realidad
 
float distancia;

// Pin Digital para abrir o cerrar el rele que activa la bomba
const int pinReleBomba = 8;

//Una variable por las dudas
//int i = 0;
int BombaON = 0; //Bomba apagada = 0; bomba encendida = 1

//===================================================================
//                   Función SETUP
//===================================================================

void setup() {

  // Configurar la comunicacion a 9600 baudios para usar el serial
  Serial.begin(9600);
/* Creo que está al pepe así que lo comento 
  // Preparar la librería Wire (I2C) 
  Wire.begin();
*/ 
  // Imprimir encabezado a la terminal
  Serial.println("Control de Bomba por rele sensando nivel del agua");
  Serial.println("----------------------------------------------------");
  
  // Para el sensor ultrasonico
  // Ponemos el pin Trig en modo salida
  pinMode(PinTrig, OUTPUT);
  // Ponemos el pin Echo en modo entrada
  pinMode(PinEcho, INPUT);

  // Para el rele
  pinMode(pinReleBomba, OUTPUT);
  // Para que el rele empiece desactivado
  digitalWrite(pinReleBomba, HIGH);
  Serial.println("configuramos el pin del rele para que este desactivado");

}

//===================================================================
//                   Función LOOP
//===================================================================

void loop() {
  // Esperar 1 segundo
  delay(1000);
  
  if(BombaON == 1){
    if(distancia < DistMin){
      digitalWrite(pinReleBomba, HIGH);
      Serial.println("Bomba apagada");
      BombaON = 0;
    }
  }else{
    if(distancia > DistN2){
      digitalWrite(pinReleBomba, LOW);
      Serial.println("Bomba prendida");
      BombaON = 1;
      // Envío mensaje por Serial a NodeMCU
      Serial.println("Correo");
    }
  }
  delay(1000);

  // Preparamos el sensor de ultrasonidos
  iniciarTrigger();
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
  
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  distancia = tiempo * 0.000001 * VelSon / 2.0;
  
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();

}

//===================================================================
//                   Funciones Extras
//===================================================================
 
// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(20);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}

//============================================================
//                    COMENTARIOS
//============================================================
/*
 * 
 * Respecto de la version FINAL_1_0_3 se quitó lo siguiente:
 * El display que mostraba la hora y el nivel del tanque
 * Y se saco el reloj que por ahora no se usa
 * 
 * A este programa se le agregó una placa WiFi, que avise por mail cada vez que se active la bomba
 * Para ver que ande todo correctamente, la idea es después que avise cualquier problema
 * pero para ello habrá que hacer una buena lógica.
 * 
 * y se está por agregar que la bomba trate de llenar el tanque de noche si es necesarío
 * por ejemplo que siempre empiece el día con el tanque lleno, y si falta poco para
 * que sea de noche, que aguante un poco mas para llenar el tanque.
 * 
 * Mas adelante la idea es poner un sensor que mida el tanque cisterna
 * para cuidar que siempre haya agua y proteger a la bomba para que 
 * nunca trabaje en vacio.
 */
