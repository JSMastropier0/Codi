int lectura=0;

void setup() {

  Serial.begin(9600);

}

void loop() {
  lectura = analogRead(4);
  Serial.print("Valor: ");
  Serial.println(lectura);
  delay (1000);

}
