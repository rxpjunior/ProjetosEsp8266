/* Esp 8266 com Leds e Botões
 */

//Bibliotecas


//Definiçoes
#define ledVerde 16     //D0
#define ledAmarelo 5    //D1
#define ledVermelho 4   //D2

#define btnVerde 12     //D6
#define btnAmarelo 13   //D7
#define btnVermelho 15  //D8

int aux; // Para ler o valor dos pinos

int contVerde = 0;
int contAmarelo = 0;
int contVermelho = 0;

void setup() {
    
  Serial.begin(115200);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(btnVerde, INPUT);
  pinMode(btnAmarelo, INPUT);
  pinMode(btnVermelho, INPUT);
}

void loop() {
  if(digitalRead(btnVerde)){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);  
  }
  else if(digitalRead(btnAmarelo)){
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, HIGH);
      digitalWrite(ledVermelho, LOW);  
  }
  else if(digitalRead(btnVermeho)){
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho, HIGH);  
  }
}

  

  
