#include <MillisTimer.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include "RF24.h"
#include <PubSubClient.h>

#define PRUEBAS

//WiFi
const char* ssid = "ssid";
const char* password = "password";
WiFiClient espClient;
//IP
IPAddress local_IP(192, 168, 1, x);
IPAddress gateway(192, 168, 1, 1);
//DNS
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 8, 4); //optional
//MQTT
const char* mqtt_server = "192.168.1.x";
PubSubClient client(espClient);
char topics[50];
int value = 0;
String nfrtopic;

//RF
RF24 radio(4, 15);
byte direccion[][6] = {"0", "1"};

//Data Struct
typedef struct {
  byte id;
  byte typeOfData;
  float data;
  int8_t foo;
}
__attribute((__packed__)) inputData;

inputData datos;


void setup() {
  Serial.begin(115200);
  Serial.println("Iniciado!");
  setUpWifi();
  setUpRF();
  setUpMQTT();
}

void loop() {

  //NFR Data
  if (radio.available())
  {
    radio.read( &datos, sizeof(datos) );
#ifdef PRUEBAS
    Serial.print("ID: ");
    Serial.print(datos.id);
    Serial.print(" Tipo de dato: ");
    Serial.print(datos.typeOfData);
    Serial.print(" Dato: ");
    Serial.print(datos.data);
    Serial.print(" Foo: ");
    Serial.println(datos.foo);
#endif
    procesaNFRData(datos.id, datos.typeOfData);
    client.publish(topics, floatToChar(datos.data));

  }

  //MQTT Data
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
