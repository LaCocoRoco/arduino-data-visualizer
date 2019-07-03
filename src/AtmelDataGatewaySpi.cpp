#include "AtmelDataGatewaySpi.h"

#ifdef GATEWAY_INCLUDED_SPI

void AtmelDataGatewaySpi::begin(void) {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  this->begin(&SPI, SS);
}

void AtmelDataGatewaySpi::begin(SPIClass* spi, uint8_t ss) {
  pinMode(ss, OUTPUT);
  this->spi = spi;
  this->ss = ss;
}

void AtmelDataGatewaySpi::transmit(uint8_t* txBuffer, uint16_t length) {
  digitalWrite(this->ss, LOW);
  for (uint8_t i = 0; i < length; i++) this->spi->transfer(txBuffer[i]);
  digitalWrite(this->ss, HIGH);
}

uint16_t AtmelDataGatewaySpi::receive(uint8_t* rxBuffer, uint16_t length) {
  digitalWrite(this->ss, LOW);
  for (uint8_t i = 0; i < length; i++) rxBuffer[i] = this->spi->transfer(DEFAULT_TOKEN);
  digitalWrite(this->ss, HIGH);
  return length;
}

uint16_t AtmelDataGatewaySpi::transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {
  digitalWrite(this->ss, LOW);
  for (uint8_t i = 0; i < length; i++) rxBuffer[i] = this->spi->transfer(txBuffer[i]);
  digitalWrite(this->ss, HIGH);
  return length;
}

#endif