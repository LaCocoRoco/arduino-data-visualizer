#include "AtmelDataGatewayTwi.h"

#ifdef GATEWAY_INCLUDED_TWI

void AtmelDataGatewayTwi::begin (void) {
  Wire.begin();
  this->begin (&Wire, DEFAULT_TWI_ADDRESS);
}

void AtmelDataGatewayTwi::begin (TwoWire* twi, uint8_t address) {
  this->address = address;
  this->twi = twi;
  this->twi->setTimeout (DEFAULT_TWI_TIMEOUT);
}

void AtmelDataGatewayTwi::transmit (uint8_t* txBuffer, uint16_t length) {
  this->twi->beginTransmission (this->address);
  this->twi->write (txBuffer, length);
  this->twi->endTransmission();
}

uint16_t AtmelDataGatewayTwi::receive (uint8_t* rxBuffer, uint16_t length) {
  this->twi->requestFrom (this->address, length);
  uint16_t rxLength = this->twi->available();
  if (!rxLength) return 0;
  rxLength = rxLength > length ? length : rxLength;
  this->twi->readBytes (rxBuffer, rxLength);
  return rxLength;
}

uint16_t AtmelDataGatewayTwi::transceive (uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {
  this->transmit (txBuffer, length);
  return this->receive (rxBuffer, length);
}

#endif