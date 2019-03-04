#include "AtmelDataGatewayUart.h"

#ifdef GATEWAY_INCLUDED_UART

void AtmelDataGatewayUart::begin(void) {
    Serial.begin(DEFAULT_UART_BAUDRATE);
    this->begin(&Serial);
}

void AtmelDataGatewayUart::begin(Stream* uart) {
    this->uart = uart;
    this->uart->setTimeout(DEFAULT_UART_TIMEOUT);
}

void AtmelDataGatewayUart::transmit(uint8_t* txBuffer, uint16_t length) {
    this->uart->write(txBuffer, length);
}

uint16_t AtmelDataGatewayUart::receive(uint8_t* rxBuffer, uint16_t length) {
    uint16_t rxLength = this->uart->available();
    if(!rxLength) return 0;
    rxLength = rxLength > length ? length : rxLength;
    this->uart->readBytes(rxBuffer, rxLength);
    return rxLength;
}

uint16_t AtmelDataGatewayUart::transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {
    this->transmit(txBuffer, length);
    return this->receive(rxBuffer, length);
}

#endif