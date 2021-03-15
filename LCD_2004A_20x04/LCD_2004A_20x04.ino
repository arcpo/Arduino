/* Arduino UNO con LCD de 20 x 04
 * El display usado 2004A tiene conectado una placa que ayuda a usar I2C.
 * La dirección I2C por defecto del módulo puede ser 0x3F o en otros casos 0x27.
 * O se puede probar alguna de ellas o hay un programita .txt para correr en el arduino y saber la dirección
 * 
 * Las conexiones entre arduino y la placa I2C es: A4 (analogico) <--> SDA
 *                                                 A5 (analogico) <--> SCL
 *                                                             5V <--> Vcc
 *                                                            GND <--> GND
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,20,4);  //

void setup() {
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");
}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
}
