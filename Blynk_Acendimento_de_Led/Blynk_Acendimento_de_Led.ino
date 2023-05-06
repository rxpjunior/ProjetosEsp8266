/*************************************************************

 Você precisará:
   - Aplicativo Blynk IoT (baixe na App Store ou Google Play)
   - Placa ESP8266
   - Decida como se conectar ao Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  Há um monte de ótimos esboços de exemplo incluídos para mostrar como obter
  iniciado. Pense neles como peças de LEGO e combine-os como quiser.
  Por exemplo, pegue o esboço do Escudo Ethernet e combine-o com o
  Exemplo de servo ou escolha um esboço USB e adicione um código de SendData
  exemplo.
 *************************************************************/

/* Preencha as informações do Blynk Device Info aqui */
/* Usados daddos do email da ETEC*/
#define BLYNK_TEMPLATE_ID "XXXX"
#define BLYNK_TEMPLATE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "XXXX"

/* Comente esta linha para não imprimir informações no serial */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Suas credenciais de rede.
// Set password to "" for open networks.
char ssid[] = "REDETESTE";
char pass[] = "TATANKA*2000";

void setup()
{
  // Console de debug
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // Você também pode especificar o servidor:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // Você pode injetar seu proprio código ou combinar outros sketches.
  // Verifique outros exemplos na comunidade do blynk. 
  // Evite o uso da função Delay!
}
