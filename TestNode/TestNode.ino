#include <SPI.h>
#include "RF24.h"

//RF
RF24 radio(10, 9);
byte direccion[][6] = {"0", "1"};

typedef struct {
  byte id;
  byte typeOfData;
  float data;
  int8_t foo;
  
}
inputData;

inputData datos;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciado");
  setUpRF();
  datos.id=2;
  datos.typeOfData=5;
  datos.data=1.0;
  datos.foo=1;
  Serial.print("Tamaño");
  Serial.println(sizeof(datos));
}

void loop() {
  Serial.print("Enviando: ");
  bool ok = radio.write( &datos, sizeof(datos) );
  Serial.println(datos.data);
  datos.data++;
  datos.foo++;
  delay(2000);

}
