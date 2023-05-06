//Teste de higrometro

int PinoAnalogico = A0; // Define o pino A0 como Pino Analógico do sensor
int ValAnalogIn; // Valor analógico no código
void setup() {
Serial.begin(115200);
}
void loop() {
ValAnalogIn = analogRead(PinoAnalogico);
Serial.print("Leitura: "); // Imprime o símbolo no valor
Serial.println(ValAnalogIn); // Imprime o valor em Porcentagem no monitor Serial
delay(3000);
}
