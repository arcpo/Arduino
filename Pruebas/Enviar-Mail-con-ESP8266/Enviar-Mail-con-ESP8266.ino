#include "ESP8266WiFi.h"
#include "Gsender.h"

// configurando conexion WiFi
const char* ssid = "Fibertel WiFi276 2.4GHz"; //Ingresar SSID - "Enigma7"
const char* password = "0043057570"; //Ingresar Password - "P@rca651821"

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

  // Armando y enviando el mail

  Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
  String subject = "Subject is optional!";
  if(gsender->Subject(subject)->Send("arcapouk2018@gmail.com", "Setup test")) {
    Serial.println("Message send.");
  } else {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}
 
void loop() 
{
  // VACIO
}
