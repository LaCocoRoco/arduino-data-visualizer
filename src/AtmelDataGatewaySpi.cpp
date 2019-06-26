#include "AtmelDataGatewaySpi.h"

#ifdef GATEWAY_INCLUDED_SPI

void AtmelDataGatewaySpi::begin (void) {
  SPISettings settings (DEFAULT_SPI_FREQUENCY, MSBFIRST, SPI_MODE0);
  SPI.begin();
  this->begin (&SPI, settings, SS);
}

void AtmelDataGatewaySpi::begin (SPIClass* spi, SPISettings settings, uint8_t ss) {
  pinMode (ss, OUTPUT);
  this->spi = spi;
  this->ss = ss;
  this->settings = settings;
}

void AtmelDataGatewaySpi::transmit (uint8_t* txBuffer, uint16_t length) {
  digitalWrite (this->ss, LOW);
  this->spi->beginTransaction (this->settings);
  for (uint8_t i = 0; i < length; i++) this->spi->transfer (txBuffer[i]);
  this->spi->endTransaction();
  digitalWrite (this->ss, HIGH);
}

uint16_t AtmelDataGatewaySpi::receive (uint8_t* rxBuffer, uint16_t length) {
  digitalWrite (this->ss, LOW);
  this->spi->beginTransaction (this->settings);
  for (uint8_t i = 0; i < length; i++) rxBuffer[i] = this->spi->transfer (DEFAULT_TOKEN);
  this->spi->endTransaction();
  digitalWrite (this->ss, HIGH);
  return length;
}

uint16_t AtmelDataGatewaySpi::transceive (uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {
  digitalWrite (this->ss, LOW);
  this->spi->beginTransaction (this->settings);
  for (uint8_t i = 0; i < length; i++) rxBuffer[i] = this->spi->transfer (txBuffer[i]);
  this->spi->endTransaction();
  digitalWrite (this->ss, HIGH);
  return length;
}

#endif