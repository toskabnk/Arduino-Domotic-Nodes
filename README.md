# Arduino Domotic Nodes

Differents nodes for a custom domotic project.

You need some Nodes with the microcontroller you want, a ESP8266 for the MQTT gateway and a Raspberry with Node-Red and Dashboard.

You must modify the MQTTGateway.ino with your network info. Its better fix the IP for the Raspberry, you can find tutorials to do that in Google.

The ElectricNode use a sct-013-000 for sensing the current, I use this tutorial: https://programarfacil.com/blog/arduino-blog/sct-013-consumo-electrico-arduino/ (Its in spanish).

As the project advance, I will add more nodes and update the code.

I will add the specific libraries I use later.