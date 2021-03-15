#include <Wire.h>
#include <LiquidCrystal.h>
#include <time.h>

// Para el RTC 
// Declaracion de las variables para almacenar informacion de tiempo leida desde RTC
uint8_t second, minute, hour, wday, day, month, year, ctrl;

// Para el LCD
// Lo primero is inicializar la librería indicando los pins de la interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Definimos las constantes
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
// String para guardar lo que se va a imprimir en el LCD
char Pantalla[16];
// DEFINICION DE CARACTERES PERSONALIZADOS
byte tanque_lleno[8] = {
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
};
byte tanque_tres_cuarto[8] = {
  0b00011111,
  0b00010001,
  0b00010011,
  0b00010111,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
};
byte tanque_mitad[8] = {
  0b00011111,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00011111,
};
byte tanque_un_cuarto[8] = {
  0b00011111,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010011,
  0b00010111,
  0b00011111,
};
byte tanque_vacio[8] = {
  0b00011111,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00010001,
  0b00011111,
};

// Para el detector de nivel (sensor ultrasonico)
// Configuramos los pines del sensor Trigger y Echo
const int PinTrig = 7;
const int PinEcho = 6;
// Variables para niveles de agua del sensor ultrasonico
const int DistMin = 25;
const int DistN1 = 35;
const int DistN2 = 45;
const int DistN3 = 55;
const int DistMax = 65;

// Constante velocidad sonido en cm/s
const float VelSon = 36000.0; //En verdad la velocidad es 34320 pero el numero puesto se acerca mas a la realidad
 
float distancia;

// Para abrir o cerrar el rele que activa la bomba
const int pinReleBomba = 8;

// Variable para el zumbador
int pinZumbador = 9;
int repeticiones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//              Do   Do#  Re   Re#  Mi   Fa   Fa#  Sol Sol#  La   


//Una variable por las dudas
int i = 0;
int Bomba = 0;
char input;
//*************************************************************
void setup() {

  // Configurar la comunicacion a 9600 baudios para usar el serial
  Serial.begin(9600);
 
  // Preparar la librería Wire (I2C)
  Wire.begin();
 
  // Imprimir encabezado a la terminal
  Serial.println("EJEMPLO LECTURA DE RTC DS1307 EN TINYRTC CON ARDUINO");
  Serial.println("----------------------------------------------------");
  
  // Para el LCD
  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS);
  // ENVIAR LOS MAPAS DE BITS AL CONTROLADOR DE PANTALLA
  lcd.createChar (0, tanque_lleno);
  lcd.createChar (1, tanque_tres_cuarto);
  lcd.createChar (2, tanque_mitad);
  lcd.createChar (3, tanque_un_cuarto);
  lcd.createChar (4, tanque_vacio);
  
  // Para el sensor ultrasonico
  // Ponemos el pin Trig en modo salida
  pinMode(PinTrig, OUTPUT);
  // Ponemos el pin Echo en modo entrada
  pinMode(PinEcho, INPUT);

  // Para el rele que activa la bomba
  pinMode(pinReleBomba, OUTPUT);
  // Para que el rele empiece desactivado
  digitalWrite(pinReleBomba, HIGH);
  Serial.println("configuramos el pin del rele para que este desactivado");
}

//****************************************************************
//****************************************************************

void loop() {
  // Esperar 1 segundo
  delay(1000);
 
  // Leer los registros del RTC
  if (read_ds1307()) {
    // Mostrar la fecha y hora
    print_time();
  } else {
    // No se puede leer desde le DS1307 (NACK en I2C)
    Serial.println("No se detecta el DS1307, revisar conexiones");
  }
  if(i>1){
      // Mostramos en la pantalla LCD
    lcd.clear();
    // Cantidada de líquido
    lcd.setCursor(0, 0);   //linea de arriba
    lcd.print("Tanque");
    if(distancia < DistMin){
      lcd.write((byte)0);
    } else {
      if(distancia < DistN1 && distancia > DistMin){
        lcd.write((byte)1);
      } else {
        if (distancia < DistN2 && distancia > DistN1){
          lcd.write((byte)2);
        } else { 
          if (distancia < DistN3 && distancia > DistN2){
            lcd.write((byte)3);
          } else {
            if (distancia < DistMax && distancia > DistN3){
              lcd.write((byte)4);
            } else {
              lcd.clear();
              lcd.write("Fuera de parametro");
            }
          }
        }
      }
    }

    // activo la bomba si el nivel del agua es menor a N3
    if (distancia > DistN2) {
      digitalWrite(pinReleBomba, LOW);
      Serial.println("Bomba prendida");
    }
    // Desactivo la bomba si ya llego al nivel necesario
    if (distancia < DistMin){
      digitalWrite(pinReleBomba, HIGH);
      Serial.println("Bomba apagada");
    }
    lcd.setCursor(0, 1);   //Segunda linea del LCD
    lcd.print("Nivel: ");
    lcd.print(distancia);
    lcd.print(" cm");
    i++;
  if (i >= 3){
    i=0;
  }
    delay(1000);
    
  } else {
    lcd.clear();
    // Cantidada de líquido
    lcd.setCursor(0, 0);
    // String(cantidadLiquido) + " ml"
    lcd.print(hour);
    lcd.print(":" );
    lcd.print(minute);
    lcd.print(":" );
    lcd.print(second);
 
    // Porcentaje
    lcd.setCursor(0, 1);
    if (Serial.available()>0){
      while (Serial.available()>0){
        input = Serial.read();
        lcd.print(input);
        i++;
      }
    } else {
      lcd.print("A la espera");
      i++;
    }
    delay(1000);
    i = 1 + i;
    
  }
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

//***************************************************************
//***************************************************************

/**
   Esta funcion establece la cominicación con el DS1307 y lee los registros
   de fecha y hora. Entrega la informacion horaria en las variables globales
   declaradas al principio del sketch.
*/
bool read_ds1307()
{
  // Iniciar el intercambio de información con el DS1307 (0xD0)
  Wire.beginTransmission(0x68);
 
  // Escribir la dirección del segundero
  Wire.write(0x00);
 
  // Terminamos la escritura y verificamos si el DS1307 respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission() != 0)
    return false;
 
  // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 8);
 
  // Recibimos el byte del registro 0x00 y lo convertimos a binario
  second = bcd2bin(Wire.read());
  minute = bcd2bin(Wire.read()); // Continuamos recibiendo cada uno de los registros
  hour = bcd2bin(Wire.read());
  wday = bcd2bin(Wire.read());
  day = bcd2bin(Wire.read());
  month = bcd2bin(Wire.read());
  year = bcd2bin(Wire.read());
 
  // Recibir los datos del registro de control en la dirección 0x07
  ctrl = Wire.read();
 
  // Operacion satisfactoria, retornamos verdadero
  return true;
}
 
/**
   Esta función convierte un número BCD a binario. Al dividir el número guardado
   en el parametro BCD entre 16 y multiplicar por 10 se convierten las decenas
   y al obtener el módulo 16 obtenemos las unidades. Ambas cantidades se suman
   para obtener el valor binario.
*/
uint8_t bcd2bin(uint8_t bcd)
{
  // Convertir decenas y luego unidades a un numero binario
  return (bcd / 16 * 10) + (bcd % 16);
}
 
/**
   Imprime la fecha y hora al monitor serial de arduino
*/
void print_time()
{
  Serial.print("Fecha: ");
  Serial.print(day);
  Serial.print('/');
  Serial.print(month);
  Serial.print('/');
  Serial.print(year);
 
  Serial.print("  Hora: ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);
 
  Serial.println();
}

// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(20);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}
