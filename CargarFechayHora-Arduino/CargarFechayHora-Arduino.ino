/* 
 *  En Arduino Uno, Nano y Mini Pro, SDA es el pin A4 y el SCL el pin A5
 */

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc ;

void setup() {
  // Configurar la comunicacion a 9600 baudios
  Serial.begin(9600);

  rtc.begin(); //Para inicializar el RTC
  
  // Imprimir encabezado a la terminal
  Serial.println(F("----------------------------------------------------"));
  Serial.println(F("              Inicializando el RTC                  "));
  Serial.println(F("----------------------------------------------------"));

  rtc.adjust(DateTime(F(__DATE__),F(__TIME__))); //Pone en fecha y hora el modulo RTC

  Serial.println("DS1307 actualizado con la hora y fecha que se compilo este programa:");
  Serial.print("Fecha = ");
  Serial.print(__DATE__);
  Serial.print("  Hora = ");
  Serial.println(__TIME__);
}
 
void loop() {
  /*
  // Obtener la fecha y hora desde el chip RTC
  if (RTC.read(datetime)) {
 
    // Comenzamos a imprimir la informacion
    Serial.print(F("OK, Time = "));
    print2digits(datetime.Hour);
    Serial.write(':');
    print2digits(datetime.Minute);
    Serial.write(':');
    print2digits(datetime.Second);
    Serial.print(F(", Date (D/M/Y) = "));
    Serial.print(datetime.Day);
    Serial.write('/');
    Serial.print(datetime.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(datetime.Year));
    Serial.println();
    delay(1000);
  }
  else {
    if (RTC.chipPresent()) {
      // El reloj esta detenido, es necesario ponerlo a tiempo
      Serial.println(F("EL DS1307 ESTA DETENIDO"));
      Serial.println(F("CORRE EL PROGRAMA PARA PONERLO A TIEMPO"));
    }
    else {
      // No se puede comunicar con el RTC en el bus I2C, revisar las conexiones.
      Serial.println(F("NO SE DETECTO EL DS1307"));
      Serial.println(F("REVISA TUS CONEXIONES E INTENTA DE NUEVO"));
    }
    // Esperamos indefinidamente
    for (;;);
  }
  */
}
 
