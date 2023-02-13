/*
    
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "REDETESTE"
#define STAPSK  "Tatanka*2000"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);

String novoHostName = "EspDoBu";

void setup() {
  Serial.begin(115200);

  // prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Conectando a "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);

  WiFi.hostname(novoHostName.c_str());
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  
  Serial.println();
  Serial.println(F("WiFi conectado"));

  server.begin();
  Serial.println(F("Servidor Iniciado"));

  // Imprimindo IP
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Imprimindo o hostname
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname());
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}
