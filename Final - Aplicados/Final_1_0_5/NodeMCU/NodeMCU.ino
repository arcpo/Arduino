/*
 * Este programa es para el NodeMU y espero mediante la conexion Serie el mensaje "Correo"
 * lo cual hace que envíe un correo al mail arcapouk2018@gmail.com
 */

#include "ESP8266WiFi.h"
#include "Gsender.h"
#include <string.h>

// configurando conexion WiFi
const char* ssid = "Fibertel WiFi276 2.4GHz"; //Ingresar SSID - "Enigma7"
const char* password = "0043057570"; //Ingresar Password - "P@rca651821"

// Otras variables
String Palabra = "";
boolean TransmisionCompleta = false;

//===================================================================
//                   Función SETUP
//===================================================================

void setup(void)
{
  Serial.begin(115200);
  // Coneccción a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.print("La dirección IP del Módulo ESP8266 es: ");
  Serial.print(WiFi.localIP());// Imprime la dirección IP

}

//===================================================================
//                       Función LOOP
//===================================================================

void loop() 
{
  while (Serial.available()) {
    char CharEntrada = Serial.read(); //Leer un byte del puerto serial
    Palabra += CharEntrada;  //Agregar el char anterior al string
    
    /*if (CharEntrada == '\n') {  //Si se detecta un fin de linea
      TransmisionCompleta = true;  //Se indica al programa que el usuario termino de ingresar la informacion
    }*/
  }
  
  if( strcmp("Correo", Palabra) == 0){
    // Armando y enviando el mail
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Aviso de casa";
    if(gsender->Subject(subject)->Send("arcapouk2018@gmail.com", "Bomba prendida")) {
      Serial.println("Message send.");
    } else {
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }
  }

  Palabra = "";
}

//===================================================================
//                      Funciones Extras
//===================================================================

//===================================================================
//                         COMENTARIOS
//===================================================================
