#include "ESP8266WiFi.h"
 
const char* ssid = "ssid"; //Ingresar SSID
const char* password = "password"; //Ingresar Password
 
void setup(void)
{ 
  Serial.begin(115200);
  // Coneccción a WiFi
  WiFi.begin("Fibertel WiFi276 2.4GHz", "0043057570"); //WiFi.begin("Enigma7", "P@rca651821");
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
 
void loop() 
{
  // VACIO
}
