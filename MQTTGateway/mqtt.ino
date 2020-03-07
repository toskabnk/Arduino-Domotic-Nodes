void callback(char* topic, byte* payload, unsigned int length) {
#ifdef PRUEBAS
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif

}

void reconnect() {
  // Loop hasta que nos conectemos
  while (!client.connected()) {
    Serial.print("Intentando conectar MQTT...");
    String clientId = "ESP8266GatewayMQTT";
    // Intentando conectar
    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
      // Una vez conectado envia mensaje
      client.publish("casa", "Esp8266 Conectado");
      // ... y resubscribe
      subscribir();
    } else {
      Serial.print("fallado, rc=");
      Serial.print(client.state());
      Serial.println(" intentado en 5 segundos");
      // Espera 5 segunda y vuelve a conectar
      delay(5000);
    }
  }
}

//Procesa los datos recibidos y los reenvia via MQTT segun los topicos hardcoded.
void procesaNFRData(byte id, byte type) {
  switch (id) {
    case 1:
      nfrtopic = "casa/entrada";
      break;
    default:
      break;
  }

#ifdef pruebas
  Serial.print("Contenido tras primer switch: ");
  Serial.println(nfrtopic);
#endif

  switch (type) {
    case 0:
      nfrtopic += "/bateria";
      break;
    case 1:
      nfrtopic += "/temperatura";
      break;
    case 2:
      nfrtopic += "/humedad";
      break;
    case 3:
      nfrtopic += "/luz";
      break;
    case 4:
      nfrtopic += "/switch";
      break;
    case 5:
      nfrtopic += "/vatios";
      break;
    case 6:
      nfrtopic += "/presion";
      break;
    default:
      break;
  }

#ifdef pruebas
  Serial.print("Contenido tras segundo switch: ");
  Serial.println(nfrtopic);
#endif
  nfrtopic.toCharArray(topics, 50);
}

/*
   Tipo de datos:
   0 - Bateria
   1 - Temperatura
   2 - Humedad
   3 - Luz
   4 - Switch
   5 - Consumo/Vatios

   ID Sensor:
   1 - Hijo
*/
