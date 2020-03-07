void setUpRF() {
  Serial.println("-----------------------------");
  Serial.println("Iniciando RF");
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);
  radio.openWritingPipe(direccion[0]);
  radio.stopListening();
  Serial.println("RF iniciado!");
  Serial.println("-----------------------------");
}
