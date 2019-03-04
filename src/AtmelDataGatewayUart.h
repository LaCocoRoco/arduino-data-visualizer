#ifndef ATMEL_DATA_GATEWAY_INCLUDED_UART_H
#define ATMEL_DATA_GATEWAY_INCLUDED_UART_H

#include "AtmelDataGateway.h"

#ifdef GATEWAY_INCLUDED_UART

#include "AtmelDataProtocol.h"

#include <Arduino.h>
#include <Stream.h>

#define BAUDRATE_9600           9600
#define BAUDRATE_19200          19200
#define BAUDRATE_38400          38400
#define BAUDRATE_57600          57600
#define BAUDRATE_115200         115200
#define BAUDRATE_230400         230400
#define BAUDRATE_500000         500000
#define BAUDRATE_1000000        1000000
#define BAUDRATE_2000000        2000000

#define DEFAULT_UART_BAUDRATE   BAUDRATE_230400
#define DEFAULT_UART_TIMEOUT    0

class AtmelDataGatewayUart {
  private:
    Stream *uart;

  public:
    void begin(void);
    void begin(Stream* uart);
    void transmit(uint8_t* txBuffer, uint16_t length);
    uint16_t receive(uint8_t* rxBuffer, uint16_t length);
    uint16_t transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);
};

#endif

#endif