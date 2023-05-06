#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
#define NET_SSID "REDETESTE" // Substituir SSID pelo nome da rede WiFi
#define NET_PASSWORD "Tatanka*2000"  // Substituir SENHA pela senha da rede WiFi

char mensagem[50];
 

//Configuração do Broker MQTT
#define MQTT_ID "KaJoRoS" //Substituir MQTT-ID pela identificação do cliente no MQTT no Broker
#define MQTT_BROKER "test.mosquitto.org" //Substituir MQTT-BROKER pelo domínio do MQTT no Broker
#define MQTT_PORT 1883 //Substituir XXXX pela porta do Broker. Normalmente será a 1883
#define MQTT_TOPIC_ENVIA "ETEC-IoT/KAJOROS" //Substituir MQTT-TOPIC pelo tópico a ser utiizado no MQTT Broker
#define MQTT_TOPIC_RECEBE "ETEC-IoT/#" //Substituir MQTT-TOPIC pelo tópico a ser utiizado no MQTT Broker
WiFiClient espClient; //Cliente da rede
PubSubClient MQTT(espClient); //Cliente MQTT

String newHostname = "KaJoRoSA"; //Substituir YYYYYY pelo nome do grupo

void setupWiFi() {
  //Configura a conexão à rede sem fio
  if (WiFi.status() == WL_CONNECTED) // Verifica se o ESP está conectado ao WiFi
      return;
  Serial.println();
  Serial.print("Conectando a rede WiFi ");
  Serial.println(NET_SSID);
  
  WiFi.begin(NET_SSID, NET_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  WiFi.hostname(newHostname.c_str());
  
  Serial.println("");
  Serial.print(WiFi.hostname());
  Serial.print(" conectado a rede WiFi: ");
  Serial.println(NET_SSID);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void setupMQTT() {
  MQTT.setServer(MQTT_BROKER, MQTT_PORT); //Informa a qual Broker e em qual porta deverá ser conectado
  
  while (!MQTT.connected())
  {
    Serial.print("Tentando conectar-se ao Broker MQTT: ");
    Serial.println(MQTT_BROKER);
    if (MQTT.connect(MQTT_ID))
        {
          Serial.println("Conectado com sucesso ao Broker MQTT!");
        }
        else
        {
          Serial.println("FALHA ao conectar no Broker MQTT!");
          Serial.println("Nova tentativa em 2s");
          delay(2000);
        }
   }
}

void setup(void) {
  Serial.begin(115200);
  
  setupWiFi();
  
  setupMQTT();
}

void loop(void) {
  int aux = 1;
  snprintf (mensagem, 75, "Aqui eh o Esp do KAJOROS: %s", String(aux));

  MQTT.publish(MQTT_TOPIC_ENVIA, newHostname.c_str());
  MQTT.publish(MQTT_TOPIC_ENVIA, mensagem);
  
  setupWiFi();
  setupMQTT();
  delay(2000);
}
