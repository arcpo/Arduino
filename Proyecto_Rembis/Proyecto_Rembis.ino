#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

//-------------------------------------------------
//      Variables globales - Config. Opciones
//-------------------------------------------------

int rele = 2; //Pin donde conectar el Rele (D2)
int riego1 = 7; //Indica la primera hora de riego (no los minutos)
int riego2 = 20; //Indica la segunda hora de riego
int MinutosDeRiego = 7; //Cuantos minutos va a regar
int segundo,minuto,hora,dia,mes;
long anio; //variable año
DateTime HoraFecha;


//-------------------------------------------------
//            Setear Arduino
//-------------------------------------------------

void setup () {
  Serial.begin(9600);
  rtc.begin(); //Inicializamos el RTC
  pinMode(rele, OUTPUT); //Configuro el pin como salida para activar/desactivar el rele
  digitalWrite(rele, LOW); //Inicio al rele desactivado

  Serial.print("Hora de riego a las: ");
  Serial.print(riego2);
  Serial.print(":00 hs");
  Serial.print("\nTiempo de riego: ");
  Serial.print(MinutosDeRiego);
  Serial.print(" minutos");
  Serial.print("\n========================================\n");
}

//-------------------------------------------------
//           Algoritmo a correr
//-------------------------------------------------

void loop () {
    
    HoraFecha = rtc.now(); //obtenemos la hora y fecha actual y se guarda en variable global
    fechayhora(); //Función para mostrar fecha y hora por conexion serie
    delay(1000);
    if ( hora == riego1 ||  hora == riego2){ 
      if (0 <= minuto && minuto < MinutosDeRiego){  //para que riegue la cantidad de minutos indicado
        digitalWrite(rele, HIGH); // Se activa el rele
      } else {
        digitalWrite(rele, LOW); // Corta el Rele
      }
    }

}

//-------------------------------------------------
//         Definicion de funciones extras
//-------------------------------------------------

void fechayhora(void) {
  segundo=HoraFecha.second();
    minuto=HoraFecha.minute();
    hora=HoraFecha.hour();
    dia=HoraFecha.day();
    mes=HoraFecha.month();
    anio=HoraFecha.year();

    //Enviamos por el puerto serie la hora y fecha.
    Serial.print("Hora = ");
    Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.print("  Fecha = ");
    Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    Serial.print(anio);
    Serial.println();

    /*
    if((segundo%5) == 0){
       for(int i=0;i<10;i++) {
        Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
    */
}

/*=======================================================================
 La placa RTC se conecta de la siguiente manera:
 - el Pin SDA en el pin A4 del arduino NANO
 - el Pin SCL en el pin A5 del arduino NANO
 
 =======================================================================*/
