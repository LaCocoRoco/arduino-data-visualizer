#ifndef ATMEL_DATA_GATEWAY_INCLUDED_SPI_H
#define ATMEL_DATA_GATEWAY_INCLUDED_SPI_H

#include "AtmelDataGateway.h"

#ifdef GATEWAY_INCLUDED_SPI

#include "AtmelDataProtocol.h"

#include <Arduino.h>
#include <SPI.h>

#define DEFAULT_TWI_TIMEOUT     0
#define DEFAULT_SPI_FREQUENCY   4000000
#define DEFAULT_TOKEN           ADP_TOKEN

class AtmelDataGatewaySpi {
  private:
    SPIClass* spi;
    SPISettings settings;
    uint8_t ss;

  public:
    void begin(void);
    void begin(SPIClass* spi, SPISettings settings, uint8_t ss);
    void transmit(uint8_t* txBuffer, uint16_t length);
    uint16_t receive(uint8_t* rxBuffer, uint16_t length);
    uint16_t transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);
};

#endif

#endif