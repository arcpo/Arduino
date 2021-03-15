/* Parece que la placa nodeMCU de LoLin no se conecta al wifi de 
 * frecuencia 5GHz, para las frecuencias de 2.4Ghz anda bien 
 */

#include <ESP8266WiFi.h> //Libreria necesaria para usar ESP8266 con wifi

#include <ESP8266mDNS.h> //No se para que
#include <WiFiUdp.h> //No se para que
#include <ArduinoOTA.h> //Supongo que es para cargar los programas Over The Air

/*ADD YOUR PASSWORD BELOW*/
/*const char *ssid = "Enigma7";
const char *password = "P@rca651821";
*/
/*
const char *ssid = "Enigma 5.8GHz";
const char *password = "Enigm@2017";
*/
const char *ssid = "Fibertel WiFi276 2.4GHz";
const char *password = "0043057570";

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
  //Opcion 1
  //connectToWiFi();
  //opcion 2
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else 
        type = "filesystem";
      Serial.println("Start updating " + type);
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

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

/* ----------------------------------------------------------
   ----------------------- LOOP ----------------------------
 -----------------------------------------------------------*/

void loop() {
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

  //Para que ande lo del OTA
  ArduinoOTA.handle();


}

/* ------------ Funciones ----------------*/
void connectToWiFi(){
  //Connect to WiFi Network
  Serial.println();
  Serial.println();
  Serial.print("Connectig to WiFi");
  Serial.println("...");
  WiFi.mode(WIFI_STA); //Para que no inicie solamente en modo estación (aunque sin esto al wifi se conecta bien
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

    //La Magia del OTA para cargar el sketch por wifi
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
      Serial.println("Ready");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      //Y aca termina la magía de la carga del sketch
  }
  Serial.println(F("Setup ready"));
}
