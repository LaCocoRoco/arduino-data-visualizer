#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

#include "AtmelDataProtocol.h"
#include "AtmelDataGatewayUart.h"
#include "AtmelDataGatewaySpi.h"
#include "AtmelDataGatewayTwi.h"
#include "DataVisualizerTerminal.h"
#include "DataVisualizerGraph.h"
#include "DataVisualizerGraphAxis.h"
#include "DataVisualizerGraphAxisCursor.h"
#include "DataVisualizerGraphAxisChannel.h"
#include "DataVisualizerDashboard.h"
#include "DataVisualizerDashboardLabel.h"
#include "DataVisualizerDashboardButton.h"
#include "DataVisualizerDashboardSlider.h"
#include "DataVisualizerDashboardSignal.h"
#include "DataVisualizerDashboardProgressBar.h"
#include "DataVisualizerDashboardSegmentDisplay.h"
#include "DataVisualizerDashboardGraph.h"
#include "DataVisualizerDashboardGraphChannel.h"
#include "DataVisualizerDashboardRadioGroup.h"
#include "DataVisualizerDashboardPieChart.h"
#include "DataVisualizerDashboardPieChartSlice.h"
#include "DataVisualizerDashboardNumericInput.h"
#include "DataVisualizerDashboardCheckBox.h"
#include "DataVisualizerDashboardRectangle.h"
#include "DataVisualizerDashboardSurfaceGrid.h"
#include "DataVisualizerDashboardTable.h"
#include "DataVisualizerDashboardTableCell.h"

enum Configuration {
  CONFIGURATION_NONE,
  CONFIGURATION_AUTOSTART
};

enum DataGateway {
  GATEWAY_NONE,
  GATEWAY_EXTERNAL,
  GATEWAY_TWI,
  GATEWAY_SPI,
  GATEWAY_UART,
};

enum DataLength {
  LENGTH_1_BYTE = 1,
  LENGTH_4_BYTE = 4,
  LENGTH_N_BYTE = MSG_RES_DATA_MAX_LEN
};

struct DataPacket {
  uint16_t    id;
  uint16_t    sent;
  uint8_t*    data;
  DataLength  length;
};

struct DataCache {
  DataPacket* packet;
};

struct DataBuffer {
  uint16_t    length;
  DataCache*  cache;
};

class DataVisualizerGraph;
class DataVisualizerTerminal;
class DataVisualizerDashboard;
class DataVisualizer : AtmelDataGateway {
  friend class DataVisualizerTerminal;
  friend class DataVisualizerGraph;
  friend class DataVisualizerGraphAxis;
  friend class DataVisualizerGraphAxisChannel;
  friend class DataVisualizerGraphAxisCursor;
  friend class DataVisualizerDashboard;
  friend class DataVisualizerDashboardButton;
  friend class DataVisualizerDashboardNumericInput;
  friend class DataVisualizerDashboardSlider;
  friend class DataVisualizerDashboardSignal;
  friend class DataVisualizerDashboardRadioGroup;
  friend class DataVisualizerDashboardGraph;
  friend class DataVisualizerDashboardGraphChannel;
  friend class DataVisualizerDashboardProgressBar;
  friend class DataVisualizerDashboardCheckBox;
  friend class DataVisualizerDashboardSegmentDisplay;
  friend class DataVisualizerDashboardPieChart;
  friend class DataVisualizerDashboardPieChartSlice;
  friend class DataVisualizerDashboardRectangle;
  friend class DataVisualizerDashboardSurfaceGrid;
  friend class DataVisualizerDashboardTable;
  friend class DataVisualizerDashboardTableCell;

 private:
  bool handshake;
  bool initialized;
  uint16_t index;
  DataBuffer buffer;
  AtmelDataProtocol protocol;

  /*********************************************************/
  /* Internal                                              */
  /*********************************************************/
  bool init (void);
  void defaults (void);
  void release (void);
  void read (uint8_t* rxBuffer);
  void write (uint16_t id, uint8_t* data, uint8_t length);
  DataPacket* pack (uint16_t id, DataLength length);

 public:
  DataVisualizer (void);

  /*********************************************************/
  /* Common                                                */
  /*********************************************************/
  bool setup (Configuration config);
  bool request (void);
  void refresh (void);
  void reset (void);

  /*********************************************************/
  /* Modules                                              */
  /*********************************************************/
  void addInfo (const char* title, const char* description);

  DataVisualizerTerminal addTerminal (const char* title);
  DataVisualizerTerminal addTerminal (const char* title, RgbColor bgColor, RgbColor fgColor);

  DataVisualizerGraph addGraph (const char* title);
  DataVisualizerGraph addGraph (const char* title, RgbColor bgColor);

  DataVisualizerDashboard addDashboard (const char* title);
  DataVisualizerDashboard addDashboard (const char* title, RgbColor color, uint16_t height);

  /*********************************************************/
  /* Gateway                                               */
  /*********************************************************/
 private:
  DataGateway gateway;

  virtual void transmit (uint8_t* txBuffer, uint16_t length);
  virtual uint16_t receive (uint8_t* rxBuffer, uint16_t length);
  virtual uint16_t transceive (uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);

 public:
  void begin (DataGateway com);

  /*********************************************************/
  /* Gateway External                                      */
  /*********************************************************/
 private:
  void (*transmitCallback) (uint8_t*, uint16_t) = NULL;
  uint16_t (*receiveCallback) (uint8_t*, uint16_t) = NULL;
  uint16_t (*transceiveCallback) (uint8_t*, uint8_t*, uint16_t) = NULL;

 public:
  void onTransmit (void (*) (uint8_t*, uint16_t));
  void onReceive (uint16_t (*) (uint8_t*, uint16_t));
  void onTransceive (uint16_t (*) (uint8_t*, uint8_t*, uint16_t));

#ifdef GATEWAY_INCLUDED_UART
  /*********************************************************/
  /* Gateway Universal Asynchronous Receiver Transmitter   */
  /*********************************************************/
 private:
  AtmelDataGatewayUart gatewayUart;

 public:
  void begin (Stream* uart);
#endif

#ifdef GATEWAY_INCLUDED_TWI
  /*********************************************************/
  /* Gateway Two Wire Interface                            */
  /*********************************************************/
 private:
  AtmelDataGatewayTwi gatewayTwi;

 public:
  void begin (TwoWire* twi, uint8_t address);
#endif

#ifdef GATEWAY_INCLUDED_SPI
  /*********************************************************/
  /* Gateway Serial Peripheral Interface                   */
  /*********************************************************/
 private:
  AtmelDataGatewaySpi gatewaySpi;

 public:
  void begin (SPIClass* spi, SPISettings settings, uint8_t ss);
#endif
};

extern DataVisualizer Visualizer;

#endif /* DATA_VISUALIZER_H */