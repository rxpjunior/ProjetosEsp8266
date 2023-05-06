/*****
 Conexao MQTT com passagem de dado via Serial para acender led interno
 Publisher e Subscriber MQTT
 Aluno: Roberto Xavier
 
*****/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

String entradaSerial = ""; // Variavel para receber dados da serial do ESP

// Dados de conexao com a rede
const char* ssid = "REDETESTE";
const char* password = "Tatanka*2000";

// Credenciais do MQTT(Deixe em NULL se não haver necessidade)
const char* MQTT_username = NULL; 
const char* MQTT_password = NULL; 

// Broker do MQTT
const char* mqtt_server = "test.mosquitto.org";

//Inicializa o espClienteKAJOROS. Você deve alterar o nome do espClienteKAJOROS se tiver vários ESPs em execução no sistema de automação residencialWiFiClient espClienteKAJOROS;
WiFiClient espClienteKAJOROS;
PubSubClient client(espClienteKAJOROS);

// Esta função conecta o ESP ao roteador
void setup_wifi() {
  delay(10);
  // Começamos conectando-nos a uma rede WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi conectado - IP: ");
  Serial.println(WiFi.localIP());
}

// Esta função é executada quando algum dispositivo publica uma mensagem para um tópico que seu ESP8266 está inscrito
// Altere a função abaixo para adicionar lógica ao seu programa, assim quando um dispositivo publicar uma mensagem para um topico que
// seu ESP8266 está inscrito, você pode realmente fazer algo
void callback(String topico, byte* mensagem, unsigned int length) {
  Serial.print("Mensagem recebida no topico: ");
  Serial.print(topico);
  Serial.print(". mensagem: ");
  String mensagemRecebida;
  
  for (int i = 0; i < length; i++) {
    //Serial.print((char)mensagem[i]);
    mensagemRecebida += (char)mensagem[i];
  }
  Serial.print(mensagemRecebida);
  
  // Sinta-se à vontade para adicionar mais instruções if para controlar mais GPIOs com MQTT
  if(topico=="ETEC-IoT/KAJOROS/LIGARLED"){
      if(mensagemRecebida.toInt() == 22 ){
        Serial.print("Mundando led para ");
        Serial.println("LIGADO");
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if(mensagemRecebida.toInt() == 13){
        Serial.print("Mundando led para ");
        Serial.println("DESLIGADO");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if(mensagemRecebida.toInt()){
        Serial.println("SENHA INVALIDA: MANTENDO ESTADO");
      }
      else{
        Serial.println("CARACTERE NAO NUMERICO RECEBIDO. MANTENDO ESTADO");
      } 
  }
  if(topico=="ETEC-IoT/#"){
      Serial.print("Lendo o topico:");
      Serial.println(topico);
      Serial.println(mensagemRecebida);
  }
  Serial.println();
}

// Esta função reconecta seu ESP8266 ao seu broker MQTT
// Altere a função abaixo caso queira assinar mais tópicos com seu ESP8266
void reconnect() {
  // Loop até nos reconectarmos
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT...");
   // Tenta conectar
    /*
     VOCÊ PODE PRECISAR ALTERAR ESTA LINHA SE ESTIVER TENDO PROBLEMAS COM MÚLTIPLAS CONEXÕES MQTT
     Para alterar o ID do dispositivo ESP, você terá que dar um novo nome ao ESP8266.
     Veja como fica:
       if (client.connect("ESP8266KAJOROS")) {
     Você pode fazer assim:
       if (client.connect("ESP1_Office")) {
     Então, para o outro ESP:
       if (client.connect("ESP2_Garage")) {
      Isso deve resolver seu problema de múltiplas conexões MQTT
    */
    if (client.connect("ESP8266KAJOROS", MQTT_username, MQTT_password)) {
      Serial.println("connected");  
      // Inscrever-se ou re-inscrever-se em um tópico
      // Você pode se inscrever em mais tópicos (para controlar mais LEDs neste exemplo)
      client.subscribe("ETEC-IoT/KAJOROS/#");
      client.subscribe("ETEC-IoT/KAJOROS/LIGARLED");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      //Aguandando 5 segundos
      delay(5000);
    }
  }
}

// A função de configuração define seus ESP GPIOs para saídas, inicia a comunicação serial a uma taxa de transmissão de 115200
// Define seu broker mqtt e define a função de retorno de chamada
// A função callback é o que recebe as mensagens e realmente controla os LEDs
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
 
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

// Para este projeto, você não precisa alterar nada na função de loop. Basicamente, garante que seu ESP esteja conectado ao seu broker
void loop() {
   
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266KAJOROS", MQTT_username, MQTT_password);

   // Ao inserir alguma inforção via Serial esta é enviada via publisher 
   if (Serial.available() > 0) {
    entradaSerial = Serial.readString();
    //client.publish("ETEC-IoT/KAJOROS", String(entradaSerial).c_str());
    client.publish("ETEC-IoT/KAJOROS/LIGARLED", entradaSerial.c_str());
  }       
} 
