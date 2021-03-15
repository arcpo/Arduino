/* Parece que la placa nodeMCU de LoLin no se conecta al wifi de 
 * frecuencia 5GHz, para las frecuencias de 2.4Ghz anda bien 
 */

#include <ESP8266WiFi.h> //Libreria necesaria para usar ESP8266 con wifi

#include <ESP8266mDNS.h> //No se para que
#include <WiFiUdp.h> //No se para que
#include <ArduinoOTA.h> //Supongo que es para cargar los programas Over The Air

/*ADD YOUR PASSWORD BELOW*/
const char *ssid = "Enigma7";
const char *password = "P@rca651821";

WiFiClient client;

//------------- Funciones
//Funcion para conectar al wifi
void connectToWiFi();

// Declaración de constantes y variables
unsigned long previousMillis = 0;
int ledState = LOW;
int tiempoLED = 1500; //intervalo de tiempo que esta prendido y apagado el LED en milisegundos

/* ----------------------------------------------------------
 * ----------------------- SETUP ----------------------------
 -----------------------------------------------------------*/
void setup() {
  //Para el led
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //Comunicación Serial
  Serial.begin(115200);
  
  //Aca puede ir mas opciones de codigo para setear/configurar
  
  connectToWiFi();
  
  //La magía de la OTA
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

}

/* ----------------------------------------------------------
   ----------------------- LOOP ----------------------------
 -----------------------------------------------------------*/

void loop() {
  // Codigo para el OTA
  ArduinoOTA.handle(); //Lo ideal para que no se ejecute a cada rato esta funación sería que se ejecute con un boton
  
  // Codigo para el led
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= tiempoLED) {
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;  // Note that this switches the LED *off*
    else
      ledState = LOW;   // Note that this switches the LED *on*
    digitalWrite(2, ledState);
  }

}

/* ------------ Funciones ----------------*/
void connectToWiFi(){
  //Connect to WiFi Network
  Serial.println();
  Serial.println();
  Serial.print("Connectig to WiFi");
  Serial.println("...");
  WiFi.begin(ssid, password);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
    retries++;
    delay(1000);
    Serial.print(". ");
  }
  if (retries > 14) {
    Serial.println(F("WiFi connection FAILED"));
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  Serial.println(F("Setup ready"));
}
