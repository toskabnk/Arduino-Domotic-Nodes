#include <SPI.h>
#include "RF24.h"
#include "EmonLib.h"
#include "DHT.h"
#include "MillisTimer.h"

//DHT
#define DHTTYPE    DHT22
const int DHTPIN = 7;
DHT dht(DHTPIN, DHTTYPE);

//RF
RF24 radio(9, 10);
byte direccion[][6] = {"0", "1"};

//EnergyMonitor
EnergyMonitor eM;
float voltaje = 230;

//Timers
MillisTimer timer(300000);

typedef struct {
  byte id;
  byte typeOfData;
  float data;
  int8_t foo;

}
inputData;

inputData dataElectric;
inputData dataTemp;
inputData dataHum;

byte firstLoop = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciado");
  setUpRF();
  setUpData();
  dht.begin();
  eM.current(7, 6.06); //Pin analogico y factor de calibracion
  timer.setTimer();
}

void loop() {
  leeConsumo();
  leeTempYHum();
}

void leeConsumo() {
  double Irms = eM.calcIrms(1484);
  double potencia =  Irms * voltaje;
  dataElectric.data = (float) potencia;
  bool ok = radio.write( &dataElectric, sizeof(dataElectric) );
  Serial.print("Potencia: "); Serial.print(potencia);
  Serial.print("    Irms: "); Serial.println(Irms);
}

void leeTempYHum() {
  if (firstLoop == 0) {
    auxLeeTempYHum();
    firstLoop = 1;
    timer.setTimer();
  }
  else {
    if (timer.checkTimer()) {
      auxLeeTempYHum();
    }
  }

}

void auxLeeTempYHum() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
  }
  else {
    Serial.print("Temperatura: "); Serial.print(t);
    Serial.print("    Humedad: "); Serial.println(h);
    dataTemp.data = t;
    dataHum.data = h;
    bool ok = radio.write( &dataTemp, sizeof(dataTemp) );
    bool ok2 = radio.write( &dataHum, sizeof(dataHum) );
  }
}
