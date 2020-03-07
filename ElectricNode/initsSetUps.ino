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

void setUpData(){
  dataTemp.id=7;
  dataTemp.typeOfData=1;
  dataHum.id=7;
  dataHum.typeOfData=2;
  dataElectric.id=7;
  dataElectric.typeOfData=5;
}
