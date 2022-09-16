#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "REDETESTE"
#define STAPSK  "REDETESTE"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

//Mensagens que serao exibidas
String msg1 = "Sistemas Embarcados";
String msg2 = "Turma B Grupo1";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

 
  // Conectando a rede
  Serial.println();
  Serial.println();
  Serial.print(F("Conectando a "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi conectado"));

  // Iniciando o servidor
  server.begin();
  Serial.println(F("Servidor iniciado"));

  // Exibindo o IP adquirido
  Serial.println(WiFi.localIP());
}

// Funcao que retornara o script htm ja com as duas mensagens inseridas
String html(String msg1,String msg2 ) {                                   
  String cd = "<!DOCTYPE html>\n";
  cd += "<html lang=\"pt-br\">\n";
  cd += "<head>\n";
  cd += "<meta charset=\"UTF-8\">\n";
  cd += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  cd += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";

  cd += "<title>Meu Primeiro Webserver no Esp32</title>\n";

  cd += "<style>\n";
  cd += "html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  cd += "body{margin-top: 50px;} \n";
  cd += "h1 {color: #444444; margin: 50px auto 30px;}\n";
  cd += "p {font-size: 24px; color: #444444; margin-bottom: 10px;}\n";
  cd += "</style>\n";

  cd += "</head>\n";
  cd += "<body>\n";
  cd += "<div id=\"webpage\">\n";
  cd += "<h1>Mensagem 1: </h1>\n";
  cd += msg1;
  cd += "<h1>Mensagem 2: </h1>\n";
  cd += msg2;
  cd += "</div>\n";
  cd += "</body>\n";  
  cd += "</html>\n";

  return cd;   //Retorna o script                                             
} 

void loop() {
  // Verificando se o cliente esta conectado
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("Novo cliente"));
  client.setTimeout(5000); // padrao e 1000
  client.print(html(msg1,msg2));
  Serial.println(F("Desconectando do cliente"));
}
