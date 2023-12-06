/*
 * ESP8266 COMO PONTO DE ACESSO - Access Point
 */

#include <ESP8266WiFi.h> //Inclui a biblioteca

const char* ssid = "REDETESTE"; //Define o nome do ponto de acesso
const char* pass = "REDETESTE"; //Define a senha
 
WiFiServer sv(80); //Cria um servidor na porta 80

void setup() {
  Serial.begin(115200); //Inicia o monitor serial
  delay(10);  //Atraso de 10 milissegundos

  Serial.println("\n"); //Pula uma linha
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);

  IPAddress ip = WiFi.softAPIP(); //Endereço de IP
  
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(ip);

  sv.begin(); //Inicia o servidor 
  Serial.println("Servidor online"); //Imprime a mensagem de início
}

void loop() {
  WiFiClient client = sv.available(); //Cria o objeto cliente
  if (client) { //Se este objeto estiver disponível
    
    while (client.connected()) { //Enquanto estiver conectado
      if (client.available()) { //Se estiver disponível
        
            client.println("HTTP/1.1 200 OK"); //Envio padrão de início de comunicação
            client.println("Content-type:text/html");
            client.println();
            client.print("HELLO WORLD"); //
            
            client.println();
            break;
          } 
        } 
      }
    }
