/* 
 * ESP8266 COMO PONTO DE ACESSO IP FIXO e DHT11
 * Para ligação do DHT no Esp usamos: 
 * Um pino de 3v3 para alimentação do sensor
 * Um pino GND para ligar o negativo do sensor
 * O pino D2, cuja constante é 4 o pino de dados do DHT11 
 */

#include <ESP8266WiFi.h> //Inclui a biblioteca
#include<ESP8266WebServer.h> //Biblioteca para o ESP funcionar como servidor
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11

const char* ssid = "REDETESTE"; //Define o nome do ponto de acesso
const char* pass = "REDETESTE"; //Define a senha
 
ESP8266WebServer sv(80); //Cria um servidor na porta 80

//DEFINICAO DE IP FIXO
IPAddress ip(192,168,4,10);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

#define DHTPIN 4 //Pino digital D2 (GPIO4) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

float temperatura; //variável para armazenar a temperatura
float umidade; //Variável para armazenar a umidade

void setup() {
  Serial.begin(115200); //Inicia o monitor serial
  delay(10);  //Atraso de 10 milissegundos

  pinMode(DHTPIN, INPUT_PULLUP); // Para não haver necessidade de uso de resistor PULLUP

  Serial.println("\n"); //Pula uma linha
  WiFi.softAPConfig(ip, gateway, subnet); //Os dados de IP serao inseridos na funcao aqui
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);

  IPAddress ip = WiFi.softAPIP(); //Endereço de IP
  
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(ip);

  sv.on("/", handle_OnConnect); //Servidor recebe uma solicitação HTTP - chama a função handle_OnConnect
  sv.onNotFound(handle_NotFound); //Servidor recebe uma solicitação HTTP não especificada - chama a função handle_NotFound
  
  sv.begin(); //Inicia o servidor 
  Serial.println("Servidor online"); //Imprime a mensagem de início
}

void loop() {
  sv.handleClient(); //Chama o método handleClient()
    }

void handle_OnConnect() {
  temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  umidade = dht.readHumidity(); //Realiza a leitura da umidade
  Serial.print("Temperatura: ");
  Serial.print(temperatura); //Imprime no monitor serial o valor da temperatura lida
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade); //Imprime no monitor serial o valor da umidade lida
  Serial.println(" %");
  sv.send(200, "text/html", EnvioHTML(temperatura, umidade)); //Envia as informações usando o código 200, especifica o conteúdo como "text/html" e chama a função EnvioHTML
  delay(3000);
}

void handle_NotFound() { //Função para lidar com o erro 404
  sv.send(404, "text/plain", "Não encontrado"); //Envia o código 404, especifica o conteúdo como "text/pain" e envia a mensagem "Não encontrado"

}

String EnvioHTML(float Temperaturastat, float Umidadestat) { //Função de Exibindo a página da web em HTML
  String ptr = "<!DOCTYPE html> <html>\n"; //Indica o envio do código HTML
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; //Torna a página da Web responsiva em qualquer navegador Web
  ptr += "<meta http-equiv='refresh' content='3'>";//Atualizar browser a cada 2 segundos
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Monitor de Temperatura e Umidade</title>\n"; //Define o título da página

  //Configurações de fonte do título e do corpo do texto da página web
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #000000;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Monitor de Temperatura e Umidade</h1>\n";
  ptr += "<h2>NODEMCU ESP8266 Web Server</h2>\n";

  //Exibe as informações de temperatura e umidade na página web
  ptr += "<p><b>Temperatura: </b>";
  ptr += (float)Temperaturastat;
  ptr += " Graus Celsius</p>";
  ptr += "<p><b>Umidade: </b>";
  ptr += (float)Umidadestat;
  ptr += " %</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;

}
