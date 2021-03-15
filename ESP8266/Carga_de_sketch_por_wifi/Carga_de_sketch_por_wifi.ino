#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define rele D7 //Conviene poner el nombre del pin de esta manera en vez del numero solo, puede generar problemas sino.

const char* ssid = "Fibertel WiFi276 2.4GHz";
const char* password = "0043057570";

int contconexion = 0;

unsigned long previousMillis = 0;
int ledState = LOW;
int t_led = 2000; //Se cuenta en milisegundos



void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  //Activo el pin para manejar el rele
  pinMode (rele, OUTPUT);
  digitalWrite(rele, HIGH);
  
  WiFi.mode(WIFI_STA); //para que no inicie solamente en modo estación
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    Serial.print(".");
    delay(500);
  }
  if (contconexion <50) {
      //para usar con ip fija
      IPAddress Ip(192,168,0,203); 
      IPAddress Gateway(192,168,0,1); 
      IPAddress Subnet(255,255,255,0); 
      WiFi.config(Ip, Gateway, Subnet); 
      
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());

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
               
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}

void loop() {
  ArduinoOTA.handle();
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= t_led) {
    previousMillis = currentMillis;   
    if (ledState == LOW){
      ledState = HIGH;  // Note that this switches the LED *off*
      digitalWrite(rele, LOW);
    }
    else {
      ledState = LOW;   // Note that this switches the LED *on*
      digitalWrite(rele, HIGH);
    }
    digitalWrite(2, ledState);
  }
}
