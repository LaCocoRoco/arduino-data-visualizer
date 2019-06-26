#include "DataVisualizer.h"

/*********************************************************/
/* Internal                                              */
/*********************************************************/

void DataVisualizer::read (uint8_t* rxBuffer) {
  MsgPacketData* adp = (MsgPacketData*) rxBuffer;

  /* discard incorrect atmel data protocol packet */
  if (adp->bytesSent == 0) return;

  for (uint16_t i = 0; i < buffer.length; i++) {
    DataPacket* packet = this->buffer.cache[i].packet;

    if (adp->streamId == packet->id) {

      switch (packet->length) {
        case LENGTH_N_BYTE: {
          packet->sent = adp->bytesSent;
          memcpy (packet->data, adp->data, LENGTH_N_BYTE);
          break;
        }

        case LENGTH_4_BYTE: {
          packet->sent = LENGTH_4_BYTE;
          uint8_t index = adp->bytesSent - LENGTH_4_BYTE;
          memcpy (packet->data, &adp->data[index], LENGTH_4_BYTE);
          break;
        }

        case LENGTH_1_BYTE: {
          packet->sent = LENGTH_1_BYTE;
          packet->data[0] = adp->data[0];
          break;
        }
      }
    }
  }
}

void DataVisualizer::write (uint16_t id, uint8_t* data, uint8_t length) {
  uint8_t rxData[MSG_RES_DATA_PACKET_MAX_LEN];
  memset (rxData, 0, MSG_RES_DATA_PACKET_MAX_LEN);

  if (this->protocol.transceiveSingleStream (id, data, length, rxData)) {
    this->read (rxData);
  };
}

bool DataVisualizer::init (void) {
  if (this->handshake) {
    if (!this->initialized) {
      this->initialized = true;
      return true;
    }
  }
  return false;
}

void DataVisualizer::defaults (void) {
  this->index = 0;
  this->handshake = false;
  this->initialized = false;
  this->gateway = GATEWAY_NONE;
}

void DataVisualizer::release (void) {
  for (uint16_t i = 0; i < this->buffer.length; i++) {
    free (this->buffer.cache[i].packet);
  }
  free (this->buffer.cache);
}

DataPacket* DataVisualizer::pack (uint16_t id, DataLength length) {
  this->buffer.length++;

  uint16_t setLength =  this->buffer.length;
  DataCache* cache = (DataCache*) malloc (sizeof (DataCache) * setLength);
  memset (cache, 0 , sizeof (DataCache) * setLength);

  uint16_t copyLength = this->buffer.length - 1;
  memcpy (cache, this->buffer.cache, sizeof (DataCache) * copyLength);

  free (this->buffer.cache);
  this->buffer.cache = cache;

  uint16_t packetIndex = this->buffer.length - 1;
  this->buffer.cache[packetIndex].packet = new DataPacket;

  DataPacket* packet = this->buffer.cache[packetIndex].packet;
  packet->id = id;
  packet->sent = 0;
  packet->length = length;
  packet->data = new uint8_t[length];
  memset (packet->data, 0, length);

  return packet;
}

/*********************************************************/
/* Common                                                */
/*********************************************************/

DataVisualizer::DataVisualizer (void) {
  this->protocol.addAtmelDataGateway (this);
  this->defaults();
}

bool DataVisualizer::setup (Configuration config) {
  switch (config) {
    case CONFIGURATION_NONE:
      return this->init();

    case CONFIGURATION_AUTOSTART:
      this->request();
      this->refresh();
      return this->init();
  }

  return 0;
}

bool DataVisualizer::request (void) {
  if (!this->handshake) {
    uint8_t handshakeStatus;
    if (this->protocol.requestHandshake (ADP_VERSION, 0, &handshakeStatus)) {
      if (handshakeStatus == HANDSHAKE_ACCEPTED) {
        this->handshake = true;
      }
    }
  }
  return this->handshake;
}

void DataVisualizer::refresh (void) {
  if (this->handshake) {
    uint8_t rxData[MSG_RES_DATA_PACKET_MAX_LEN];
    memset (rxData, 0, MSG_RES_DATA_PACKET_MAX_LEN);

    if (this->protocol.receivePacketData (rxData)) {
      this->read (rxData);
    }
  }
}

void DataVisualizer::reset (void) {
  this->defaults();
  this->release();
}

/*********************************************************/
/* Elements                                              */
/*********************************************************/

void DataVisualizer::addInfo (const char *title, const char *description) {
  if (!this->handshake) return;

  this->protocol.addInfo (title, description);
}

DataVisualizerTerminal DataVisualizer::addTerminal (const char *title) {
  return this->addTerminal (title, COLOR_WHITE, COLOR_BLACK);
}

DataVisualizerTerminal DataVisualizer::addTerminal (const char *title, RgbColor bgColor, RgbColor fgColor) {
  DataVisualizerTerminal terminal;

  if (!this->handshake) return terminal;

  uint16_t terminalId          = this->index++;
  uint16_t terminalStreamIdIn  = this->index++;
  uint16_t terminalStreamIdOut = this->index++;

  terminal.visualizer = this;
  terminal.id         = terminalStreamIdOut;
  terminal.packet     = this->pack (terminalStreamIdIn, LENGTH_N_BYTE);

  MsgConfigTerminal msgConfigTerminal;
  this->protocol.configureTerminalGetDefaults (&msgConfigTerminal);
  msgConfigTerminal.terminalId    = terminalId;
  this->protocol.setColor (msgConfigTerminal.backgroundColor, bgColor);
  this->protocol.setColor (msgConfigTerminal.foregroundColor, fgColor);
  this->protocol.addTerminal (&msgConfigTerminal, title);

  MsgConfigStream msgConfigStream;
  this->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = terminalStreamIdIn;
  msgConfigStream.type     = STREAM_STRING;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->protocol.addStream (&msgConfigStream, "TerminalStreamIn");

  MsgConfigAddStreamToTerminal msgConfigTerminalStream;
  this->protocol.configureStreamToTerminalGetDefaults (&msgConfigTerminalStream);
  msgConfigTerminalStream.terminalId = terminalId;
  msgConfigTerminalStream.streamId   = terminalStreamIdIn;
  this->protocol.addStreamToTerminal (&msgConfigTerminalStream, "AddTerminalStreamIn");

  this->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = terminalStreamIdOut;
  msgConfigStream.type     = STREAM_STRING;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->protocol.addStream (&msgConfigStream, "TerminalStreamOut");

  this->protocol.configureStreamToTerminalGetDefaults (&msgConfigTerminalStream);
  msgConfigTerminalStream.terminalId = terminalId;
  msgConfigTerminalStream.streamId   = terminalStreamIdOut;
  this->protocol.addStreamToTerminal (&msgConfigTerminalStream, "AddTerminalStreamOut");

  return terminal;
}

DataVisualizerGraph DataVisualizer::addGraph (const char* title) {
  return this->addGraph (title, COLOR_BLACK);
}

DataVisualizerGraph DataVisualizer::addGraph (const char* title, RgbColor bgColor) {
  DataVisualizerGraph graph;

  if (!this->handshake) return graph;

  uint16_t graphId = this->index++;
  graph.visualizer = this;
  graph.id         = graphId;

  MsgConfigGraph msgConfigGraph;
  this->protocol.configureGraphGetDefaults (&msgConfigGraph);
  msgConfigGraph.graphId = graphId;
  this->protocol.setColor (msgConfigGraph.backgroundColor, bgColor);
  this->protocol.addGraph (&msgConfigGraph, title, "graph");

  return graph;
}

DataVisualizerDashboard DataVisualizer::addDashboard (const char* title) {
  return this->addDashboard (title, COLOR_WHITE, 400);
}

DataVisualizerDashboard DataVisualizer::addDashboard (const char* title, uint16_t height) {
  return this->addDashboard (title, COLOR_WHITE, height);
}

DataVisualizerDashboard DataVisualizer::addDashboard (const char* title, RgbColor color, uint16_t height) {
  DataVisualizerDashboard dashboard;

  if (!this->handshake) return dashboard;

  uint16_t dashboardId = this->index++;
  dashboard.visualizer = this;
  dashboard.id         = dashboardId;

  MsgConfigDahsboard msgConfigDashboard;
  this->protocol.configureDashboardGetDefaults (&msgConfigDashboard);
  msgConfigDashboard.dashboardId = dashboardId;
  msgConfigDashboard.height = height;
  this->protocol.setColor (msgConfigDashboard.color, color);
  this->protocol.addDashboard (&msgConfigDashboard, title);

  return dashboard;
}

/*********************************************************/
/* Gateway                                               */
/*********************************************************/

void DataVisualizer::onTransmit (void (*f) (uint8_t*, uint16_t)) {
  this->transmitCallback = f;
}

void DataVisualizer::onReceive (uint16_t (*f) (uint8_t*, uint16_t)) {
  this->receiveCallback = f;
}

void DataVisualizer::onTransceive (uint16_t (*f) (uint8_t*, uint8_t*, uint16_t)) {
  this->transceiveCallback = f;
}

void DataVisualizer::transmit (uint8_t* txBuffer, uint16_t length) {
  if (this->gateway == GATEWAY_EXTERNAL)
    this->transmitCallback (txBuffer, length);
#ifdef GATEWAY_INCLUDED_UART
  if (this->gateway == GATEWAY_UART)
    this->gatewayUart.transmit (txBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_TWI
  if (this->gateway == GATEWAY_TWI)
    this->gatewayTwi.transmit (txBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_SPI
  if (this->gateway == GATEWAY_SPI)
    this->gatewaySpi.transmit (txBuffer, length);
#endif
}

uint16_t DataVisualizer::receive (uint8_t* rxBuffer, uint16_t length) {
  if (this->gateway == GATEWAY_EXTERNAL)
    return this->receiveCallback (rxBuffer, length);
#ifdef GATEWAY_INCLUDED_UART
  if (this->gateway == GATEWAY_UART)
    return this->gatewayUart.receive (rxBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_TWI
  if (this->gateway == GATEWAY_TWI)
    return this->gatewayTwi.receive (rxBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_SPI
  if (this->gateway == GATEWAY_SPI)
    return this->gatewaySpi.receive (rxBuffer, length);
#endif
  return 0;
}

uint16_t DataVisualizer::transceive (uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length) {
  if (this->gateway == GATEWAY_EXTERNAL)
    return this->transceiveCallback (txBuffer, rxBuffer, length);
#ifdef GATEWAY_INCLUDED_UART
  if (this->gateway == GATEWAY_UART)
    return this->gatewayUart.transceive (txBuffer, rxBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_TWI
  if (this->gateway == GATEWAY_TWI)
    return this->gatewayTwi.transceive (txBuffer, rxBuffer, length);
#endif
#ifdef GATEWAY_INCLUDED_SPI
  if (this->gateway == GATEWAY_SPI)
    return this->gatewaySpi.transceive (txBuffer, rxBuffer, length);
#endif
  return 0;
}

void DataVisualizer::begin (DataGateway com) {
  this->gateway = com;
#ifdef GATEWAY_INCLUDED_UART
  if (com == GATEWAY_UART)
    this->gatewayUart.begin();
#endif
#ifdef GATEWAY_INCLUDED_TWI
  if (com == GATEWAY_TWI)
    this->gatewayTwi.begin();
#endif
#ifdef GATEWAY_INCLUDED_SPI
  if (com == GATEWAY_SPI)
    this->gatewaySpi.begin();
#endif
}

#ifdef GATEWAY_INCLUDED_UART
void DataVisualizer::begin (Stream* uart) {
  this->gateway = GATEWAY_UART;
  this->gatewayUart.begin (uart);
}
#endif

#ifdef GATEWAY_INCLUDED_TWI
void DataVisualizer::begin (TwoWire* twi, uint8_t address) {
  this->gateway = GATEWAY_TWI;
  this->gatewayTwi.begin (twi, address);
}
#endif

#ifdef GATEWAY_INCLUDED_SPI
void DataVisualizer::begin (SPIClass* spi, SPISettings settings, uint8_t ss) {
  this->gateway = GATEWAY_SPI;
  this->gatewaySpi.begin (spi, settings, ss);
}
#endif

DataVisualizer Visualizer = DataVisualizer();