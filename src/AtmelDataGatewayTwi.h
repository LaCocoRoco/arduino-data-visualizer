#ifndef ATMEL_DATA_GATEWAY_INCLUDED_TWI_H
#define ATMEL_DATA_GATEWAY_INCLUDED_TWI_H

#include "AtmelDataGateway.h"

#ifdef GATEWAY_INCLUDED_TWI

#include "AtmelDataProtocol.h"

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_TWI_TIMEOUT     0
#define DEFAULT_TWI_ADDRESS     40
#define DEFAULT_TWI_FREQUENCY   100000

class AtmelDataGatewayTwi {
  private:
    TwoWire* twi;
    uint8_t address;

  public:
    void begin(void);
    void begin(TwoWire* twi, uint8_t address);
    void transmit(uint8_t* txBuffer, uint16_t length);
    uint16_t receive(uint8_t* rxBuffer, uint16_t length);
    uint16_t transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);
};

#endif

#endif