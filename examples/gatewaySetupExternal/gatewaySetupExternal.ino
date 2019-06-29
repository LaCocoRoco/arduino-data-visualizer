#include <DataVisualizer.h>

void transmit(uint8_t* txBuffer, uint16_t length) {

}

uint16_t receive(uint8_t* rxBuffer, uint16_t length) {

}

uint16_t transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {

}

void setup() {
  Visualizer.begin(GATEWAY_EXTERNAL);
  Visualizer.onTransmit(&transmit);
  Visualizer.onReceive(&receive);
  Visualizer.onTransceive(&transceive);
}

void loop() {

}