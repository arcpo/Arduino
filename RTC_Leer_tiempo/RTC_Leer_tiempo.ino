#include <Wire.h>
#include <DS1307RTC.h>
 
void setup() {
 
  // Configurar la comunicacion a 9600 baudios
  Serial.begin(9600);
}
 
void loop() {
  // Declaramos una estructura "tm" llamada datetime para almacenar
  // La fecha y la hora actual obtenida desde el chip RTC.
  tmElements_t datetime;
 
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
}
 
/**
   Funcion auxiliar para imprimir siempre 2 digitos
*/
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
