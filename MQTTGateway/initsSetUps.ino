void setUpWifi() {
  Serial.println("-----------------------------");
  WiFi.config(local_IP, primaryDNS, gateway, subnet); //No funciona
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando...");
  }
  Serial.println("Connectado!");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("-----------------------------");
}

void setUpRF() {
  Serial.println("Iniciando RF");
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);
  radio.openReadingPipe(1, direccion[0]);
  radio.startListening();
  Serial.println("RF iniciado!");
  Serial.println("-----------------------------");
}

void setUpMQTT(){
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
