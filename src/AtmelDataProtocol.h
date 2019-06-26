#ifndef ATMEL_DATA_PROTOCOL_H
#define ATMEL_DATA_PROTOCOL_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

/** Bug Fix if last byte of message is ADP Token */
#define ADP_BUG_FIX 0x00

/** Version of ADP implemented here */
#define ADP_VERSION 1

/** Start token for ADP data */
#define ADP_TOKEN 0xFF

/** Maximum number of streams from PC to target */
#define ADP_MAX_INCOMMING_STREAMS 5

/** Maximum number of streams from target to PC */
#define ADP_MAX_OUTGOING_STREAMS 5

/** Key used to identify proper handshake message */
#define ADP_HANDSHAKE_KEY {0x58, 0x99, 0xAB, 0xC9, 0x0F, 0xE2, 0xF7, 0xAA}

/** Maximum retry for handshake request  */
#define ADP_CHECK_FOR_RESPONSE_RETRYS 50

/** Length of ADP packet header: Token, Message ID, Data Length */
#define ADP_LENGTH_PACKET_HEADER 4

/** Maximum number of bytes in data part of ADP packet out */
#define ADP_MAX_PROTOCOL_LEN 250

/** Max length of labels */
#define ADP_CONF_MAX_LABEL 20

/** ADP RGB color definitions. Other RGB values can be used as well */
#define COLOR_WHITE   (RgbColor) {0xFF, 0xFF, 0xFF}
#define COLOR_BLACK   (RgbColor) {0x00, 0x00, 0x00}
#define COLOR_SILVER  (RgbColor) {0xC0, 0xC0, 0xC0}
#define COLOR_GRAY    (RgbColor) {0x80, 0x80, 0x80}
#define COLOR_MAROON  (RgbColor) {0x80, 0x00, 0x00}
#define COLOR_RED     (RgbColor) {0xFF, 0x00, 0x00}
#define COLOR_PURPLE  (RgbColor) {0x80, 0x00, 0x80}
#define COLOR_FUCHSIA (RgbColor) {0xFF, 0x00, 0xFF}
#define COLOR_GREEN   (RgbColor) {0x00, 0x80, 0x00}
#define COLOR_LIME    (RgbColor) {0x00, 0xFF, 0x00}
#define COLOR_OLIVE   (RgbColor) {0x80, 0x80, 0x00}
#define COLOR_YELLOW  (RgbColor) {0xFF, 0xFF, 0x00}
#define COLOR_NAVY    (RgbColor) {0x00, 0x00, 0x80}
#define COLOR_BLUE    (RgbColor) {0x00, 0x00, 0xFF}
#define COLOR_TEAL    (RgbColor) {0x00, 0x80, 0x80}
#define COLOR_AQUA    (RgbColor) {0x00, 0xFF, 0xFF}
#define COLOR_ORANGE  (RgbColor) {0xFF, 0xA5, 0x00}

#define ACK_NOT_OK 0
#define ACK_OK 1

#define AXIS_LINE_bm 0x01
#define AXIS_POINTS_bm 0x02

#define MSG_DATA_STREAM 0x40

#define MSG_REQ_HANDSHAKE 0x00
#define MSQ_REQ_HANDSHAKE_LEN 10

#define MSG_REQ_STATUS 0x02
#define MSG_REQ_STATUS_LEN 0

#define MSG_RES_HANDSHAKE 0x10
#define MSG_RES_STATUS 0x12
#define MSG_RES_DATA 0x14
#define MSG_RES_DATA_REQUEST 10
#define MSG_RES_DATA_PACKET_MAX_LEN 250
#define MSG_RES_DATA_MAX_LEN MSG_RES_DATA_PACKET_MAX_LEN - 3

#define MSG_CONF_ACK 0x30

#define MSG_CONF_INFO 0x28
#define MSG_CONF_INFO_LEN 0

#define MSG_CONF_STREAM 0x20
#define MSG_CONF_STREAM_LEN 5

#define MSG_CONF_TOGGLE_STREAM 0x21
#define MSG_CONF_TOGGLE_STREAM_LEN 3

#define MSG_CONF_TERMINAL 0x26
#define MSG_CONF_TERMINAL_LEN 10

#define MSG_CONF_ADD_TO_TERMINAL 0x27
#define MSG_CONF_ADD_TO_TERMINAL_LEN 11

#define MSG_CONF_GRAPH 0x22
#define MSG_CONF_GRAPH_LEN 23

#define MSG_CONF_AXIS 0x29
#define MSG_CONF_AXIS_LEN 24

#define MSG_CONF_ADD_STREAM_TO_AXIS 0x23
#define MSG_CONF_ADD_STREAM_TO_AXIS_LEN 32

#define MSG_CONF_CURSOR_TO_GRAPH 0x24
#define MSG_CONF_CURSOR_TO_GRAPH_LEN 35

#define MSG_CONF_GPIO_TO_GRAPH 0x25
#define MSG_CONF_GPIO_TO_GRAPH_LEN 15

#define MSG_CONF_DASHBOARD 0x2A
#define MSG_CONF_DASHBOARD_LEN 7

#define MSG_CONF_DASHBOARD_ELEMENT 0x2B
#define MSG_CONF_DASHBOARD_COMMON_LEN 14

#define MSG_CONF_ADD_STREAM_TO_ELEMENT 0x2C
#define MSG_CONF_ADD_STREAM_TO_ELEMENT_LEN 6

#define ELEMENT_TYPE_LABEL_LEN     (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
#define ELEMENT_TYPE_BUTTON_LEN    (MSG_CONF_DASHBOARD_COMMON_LEN + 2 )
#define ELEMENT_TYPE_SLIDER_LEN    (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
#define ELEMENT_TYPE_PROGRESS_LEN  (MSG_CONF_DASHBOARD_COMMON_LEN + 15)
#define ELEMENT_TYPE_SIGNAL_LEN    (MSG_CONF_DASHBOARD_COMMON_LEN + 8 )
#define ELEMENT_TYPE_SEGMENT_LEN   (MSG_CONF_DASHBOARD_COMMON_LEN + 6 )
#define ELEMENT_TYPE_GRAPH_LEN     (MSG_CONF_DASHBOARD_COMMON_LEN + 28)
#define ELEMENT_TYPE_TEXT_LEN      (MSG_CONF_DASHBOARD_COMMON_LEN + 12)
#define ELEMENT_TYPE_RADIO_LEN     (MSG_CONF_DASHBOARD_COMMON_LEN + 3 )
#define ELEMENT_TYPE_PIE_LEN       (MSG_CONF_DASHBOARD_COMMON_LEN + 7 )
#define ELEMENT_TYPE_RECTANGLE_LEN (MSG_CONF_DASHBOARD_COMMON_LEN + 8 )
#define ELEMENT_TYPE_CHECKBOX_LEN  (MSG_CONF_DASHBOARD_COMMON_LEN + 1 )
#define ELEMENT_TYPE_SURFACE_LEN   (MSG_CONF_DASHBOARD_COMMON_LEN + 33)
#define ELEMENT_TYPE_TABLE_LEN     (MSG_CONF_DASHBOARD_COMMON_LEN + 22)


/** States in receive state machine */
enum RxState {
  /** We are idle, waiting for a new packet */
  RX_STATE_IDLE,
  /** Start symbol received, waiting for Message ID */
  RX_STATE_WAIT_MSG_ID,
  /** Message ID received, waiting for data length */
  RX_STATE_WAIT_LENGTH_LSB,
  /** Message ID received, waiting for data length */
  RX_STATE_WAIT_LENGTH_MSB,
  /** Length received; we are receiving packet data */
  RX_STATE_GET_DATA,
  /** Start symbol received */
  RX_STATE_GOT_SYMBOL,
};

enum HandshakeOptions {
  /* Use GPIO */
  HANDSHAKE_OPTIONS_GPIO,
  /* Lock configuration */
  HANDSHAKE_OPTIONS_LOCK,
};

enum HandshakeStatus {
  /* Handshake accepted */
  HANDSHAKE_ACCEPTED,
  /* Handshake rejected. Invalid protocol version */
  HANDSHAKE_REJECTED_PROTOCOL,
  /* Handshake rejected. Other reason */
  HANDSHAKE_REJECTED_OTHER,
};

enum StatusCode {
  /* Invalid packet received */
  STATUS_INVALID_PACKET,
  /* Invalid configuration data received */
  STATUS_INVALID_CONFIGURATION,
  /* Data ready to be transmitted to target */
  STATUS_DATA_READY,
  /* Invalid stream request (req_data) */
  STATUS_INVALID_REQUEST,
  /* No data available on stream (req_data) */
  STATUS_NO_DATA,
  /* Request target software reset */
  STATUS_RESET,
};

enum StreamType {
  STREAM_EVENT,
  STREAM_STRING,
  STREAM_UINT_8,
  STREAM_INT_8,
  STREAM_UINT_16,
  STREAM_INT_16,
  STREAM_UINT_32,
  STREAM_INT_32,
  STREAM_XY_8,
  STREAM_XY_16,
  STREAM_XY_32,
  STREAM_BOOL,
  STREAM_FLOAT,
  STREAM_DOUBLE,
  STREAM_GRID = 20
};

enum StreamState {
  STREAM_OFF,
  STREAM_ON,
};

enum StreaMode {
  STREAM_IN,
  STREAM_IN_SINGLE,
  STREAM_OUT,
};

enum GraphScaleMode {
  GRAPH_SCALE_OFF,
  GRAPH_SCALE_AUTO
};

enum GraphScrollMode {
  GRAPH_SCROLL_OFF,
  GRAPH_SCROLL_STEP,
  GRAPH_SCROLL_SCROLL,
  GRAPH_SCROLL_CIRCULAR
};

enum DashboardElementType {
  ELEMENT_TYPE_LABEL,
  ELEMENT_TYPE_BUTTON,
  ELEMENT_TYPE_SLIDER,
  ELEMENT_TYPE_PROGRESS,
  ELEMENT_TYPE_SIGNAL,
  ELEMENT_TYPE_SEGMENT,
  ELEMENT_TYPE_GRAPH,
  ELEMENT_TYPE_TEXT,
  ELEMENT_TYPE_RADIO,
  ELEMENT_TYPE_PIE,
  ELEMENT_TYPE_RECTANGLE,
  ELEMENT_TYPE_CHECKBOX,
  ELEMENT_TYPE_PLACEHOLDER,
  ELEMENT_TYPE_SURFACE,
  ELEMENT_TYPE_TABLE
};

enum AligHoz {
  HORIZONTAL_ALIGNMENT_LEFT,
  HORIZONTAL_ALIGNMENT_CENTER,
  HORIZONTAL_ALIGNMENT_RIGHT,
};

enum AligVert {
  VERTICAL_ALIGNMENT_TOP,
  VERTICAL_ALIGNMENT_CENTER,
  VERTICAL_ALIGNMENT_BOTTOM,
};

enum Orientation {
  HORIZONTAL,
  VERTICAL,
};

enum ScaleMode {
  SCALLE_STATIC,
  SCALE_ROOF_AND_FLOOR,
  SCALE_ROOF,
  SCALE_FLOOR,
  STICKY_SCALE_ROOF_AND_FLOOR,
  STICKY_SCALE_ROOF,
  STICKY_SCALE_FLOOR
};

enum SegmentBase {
  BASE_BIN = 2,
  BASE_OCT = 8,
  BASE_DEC = 10,
  BASE_HEX = 16
};

struct RgbColor {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct MsgFormat {
  uint8_t protocolToken;
  uint8_t protocolMsgId;
  uint16_t dataLength;
  uint8_t data[ADP_MAX_PROTOCOL_LEN];
};

struct MsgRequestHandshake {
  uint8_t protocolVersion;
  uint8_t options;
  uint8_t key[8];
};

struct MsgResponseHandshake {
  HandshakeStatus status;
};

struct MsgResponseStatus {
  StatusCode status;
};

struct MsgPacketData {
  uint16_t streamId;
  uint8_t  bytesSent;
  uint8_t  data[MSG_RES_DATA_MAX_LEN];
};

struct StreamParameters {
  StreamType baseDataType;
  uint8_t widhtOfGrid;
  uint8_t depthOfGrid;
};

struct MsgConfigStream {
  uint16_t streamId;
  StreamType type;
  StreaMode mode;
  StreamState state;
  StreamParameters parameters;
};

struct MsgToggleStream {
  uint16_t streamId;
  StreamState state;
};

struct MsgConfigAddStreamToElement {
  uint16_t dashboardId;
  uint16_t elementId;
  uint16_t streamId;
};

struct MsgDataStreamData {
  uint16_t streamId;
  uint8_t dataSize;
  uint8_t* data;
};

struct MsgDataStream {
  uint8_t numberOfStreams;
  MsgDataStreamData stream[ADP_MAX_OUTGOING_STREAMS];
};

struct MsgConfigGraph {
  uint8_t graphId;
  uint32_t xMin;
  uint32_t xMax;
  uint32_t xScaleNumerator;
  uint32_t xScaleDenominator;
  GraphScaleMode scaleMode;
  uint8_t backgroundColor[3];
  GraphScrollMode scrollMode;
};

typedef union {
  struct {
    uint8_t scalingOff : 1;
    uint8_t autoScale : 1;
    uint8_t : 6;
  } bit;
  uint8_t reg;
} AxisMode;

struct MsgConfigAxis {
  uint16_t axisId;
  uint16_t graphId;
  int32_t yMin;
  int32_t yMax;
  uint32_t xScaleNumerator;
  uint32_t xScaleDenominator;
  AxisMode mode;
  uint8_t color[3];
};

struct MsgAddStreamToAxis {
  uint16_t graphId;
  uint16_t axisId;
  uint16_t streamId;
  uint32_t sampleRateNumerator;
  uint32_t sampleRateDenominator;
  uint32_t yScaleNumerator;
  uint32_t yScaleDenominator;
  uint32_t yOffset;
  uint8_t transparency;
  uint8_t mode;
  uint8_t lineThickness;
  uint8_t lineColor[3];
};

struct MsgAddCursorToGraph {
  uint16_t streamId;
  uint16_t graphId;
  uint16_t axisId;
  uint8_t thickness;
  uint8_t color[3];
  uint32_t initialValue;
  uint32_t minimumValue;
  uint32_t maximumValue;
  uint32_t scaleNumerator;
  uint32_t scaleDenominator;
  uint32_t scaleOffset;
  uint8_t lineStyle;
};

struct MsgConfigGpioToGraph {
  uint16_t graphId;
  uint8_t gpioNumber;
  uint8_t groupId;
  uint8_t transparency;
  uint16_t mode;
  uint8_t lineThickness;
  uint8_t lineColorHighState[3];
  uint8_t lineColorLowState[3];
  uint8_t lineStyle;
};

struct MsgConfigTerminal {
  uint16_t terminalId;
  uint8_t width;
  uint8_t height;
  uint8_t backgroundColor[3];
  uint8_t foregroundColor[3];
};

typedef union {
  struct {
    uint8_t : 4;
    uint8_t newLine : 1;
    uint8_t : 3;
  } bit;
  uint8_t reg;
} AddStreamToTerminalMod;

struct MsgConfigAddStreamToTerminal {
  uint16_t terminalId;
  uint16_t streamId;
  AddStreamToTerminalMod mode;
  uint8_t textColor[3];
  uint8_t tagTextColor[3];
};

struct MsgConfigDahsboard {
  uint16_t dashboardId;
  uint8_t  color[3];
  uint16_t height;
};

struct MsgConfigDashboardElementCommon {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
};

typedef union {
  struct {
    uint8_t bold : 1;
    uint8_t italic : 1;
    uint8_t : 6;
  } bit;
  uint8_t reg;
} LabelAttributes;

struct MsgConfigDashboardElementLabel {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t fontSize;
  LabelAttributes attributes;
  AligHoz horisontalAlignment;
  AligVert verticalAlignment;
  uint8_t backgroundTransparency;
  uint8_t backgroundColor[3];
  uint8_t foregroundTransparency;
  uint8_t foregroundColor[3];
};

struct MsgConfigDashboardElementButton {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t fontSize;
  uint8_t toggle;
};

struct MsgConfigDashboardElementSlider {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint32_t minimumValue;
  uint32_t maximumValue;
  uint32_t initialValue;
};

struct MsgConfigDashboardElementProgress {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elemntType;
  uint32_t minimumValue;
  uint32_t maximumValue;
  uint32_t initialValue;
  uint8_t color[3];
};

struct MsgConfigDashboardElementSignal {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t onTransparency;
  uint8_t onColor[3];
  uint8_t offTransparency;
  uint8_t offColor[3];
};

struct MsgConfigDashboardElementSegment {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t segmentCount;
  SegmentBase base;
  uint8_t transparency;
  uint8_t color[3];
};

typedef union {
  struct {
    uint8_t mouse : 1;
    uint8_t fitGraph : 1;
    uint8_t autoscale : 1;
    uint8_t scrollByTime : 1;
    uint8_t : 4;
    uint8_t showPlot : 1;
    uint8_t showPoints : 1;
    uint8_t : 6;
  } bit;
  uint16_t reg;
} DashboardElementGraphMode;

struct MsgConfigDashboardElementGraph {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t titleColor[3];
  uint8_t backgroundColor[3];
  uint8_t graphBackgroundColor[3];
  uint8_t plotCount;
  float xMin;
  float xMax;
  float yMin;
  float yMax;
  DashboardElementGraphMode mode;
};

struct MsgConfigDashboardElementText {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t minimum[4];
  uint8_t maximum[4];
  uint8_t value[4];
};

struct MsgConfigDashboardElementRadio {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t fontSize;
  uint8_t numberItems;
  Orientation orientation;
};

struct MsgConfigDashboardElementPie {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t titleColor[3];
  uint8_t backgroundColor[3];
  uint8_t numberSlices;
};

struct MsgConfigDashboardElementRectangle {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t backgroundTransparency;
  uint8_t backgroundColor[3];
  uint8_t foregroundTransparency;
  uint8_t foregroundColor[3];
};

struct MsgConfigDashboardElementCheckBox {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t fontSize;
};

typedef union {
  struct {
    uint8_t showXAxis : 1;
    uint8_t showYAxis : 1;
    uint8_t showZAxis : 1;
    uint8_t showFill : 1;
    uint8_t showMesh : 1;
    uint8_t usePaletteColoring : 1;
    uint8_t : 2;
  } bit;
  uint8_t reg;
} SurfaceAttributes;

struct MsgConfigDashboardElementSurface {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t fillColor[3];
  uint8_t meshColor[3];
  uint8_t backgroundTransparency;
  uint8_t backgroundColor[3];
  uint8_t backgroundGradientTransparency;
  uint8_t backgroundGradientColor[3];
  uint8_t axisColor[3];
  uint8_t tickLabelColor[3];
  uint8_t xRotation;
  uint8_t yRotation;
  uint8_t zRotation;
  SurfaceAttributes attributes;
  ScaleMode mode;
  float axisMinimum;
  float axisMaximum;
};

typedef union {
  struct {
    uint8_t dataBold : 1;
    uint8_t dataItalic : 1;
    uint8_t labelBold : 1;
    uint8_t labelItalic : 1;
    uint8_t : 4;
  } bit;
  uint8_t reg;
} TableAttributes;

struct MsgConfigDashboardElementTable {
  uint16_t dashboardId;
  uint16_t elementId;
  uint8_t zIndex;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  DashboardElementType elementType;
  uint8_t dataFontSize;
  uint8_t labelFontSize;
  uint16_t dataWidth;
  uint16_t labelWidth;
  uint16_t rowHeight;
  uint8_t numberOfRows;
  uint8_t numberOfColumns;
  uint8_t autoLabels;
  TableAttributes attributes;
  uint8_t backgroundTransparency;
  uint8_t backgroundColor[3];
  uint8_t foregroundTransparency;
  uint8_t foregroundColor[3];
  AligHoz labelHorizontalAligment;
  AligHoz dataHorizontalAligment;
};

struct AtmelDataGateway {
  virtual void transmit (uint8_t* txBuffer, uint16_t length);
  virtual uint16_t receive (uint8_t* rxBuffer, uint16_t length);
  virtual uint16_t transceive (uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);
};

class AtmelDataProtocol {
 private:
  bool packetReceived;
  uint8_t prevData;
  uint8_t lastReceivedMessageId;
  uint8_t rxPacketBuffer[MSG_RES_DATA_PACKET_MAX_LEN];
  uint16_t bytesReceived;
  uint16_t lengthReceived;
  RxState rxState;
  AtmelDataGateway* gateway;

  bool addReceiveByte (uint8_t data);
  bool isReceived (void);
  bool protocolAddByte (uint8_t rxId, uint8_t *rxBuffer, uint16_t rxLength, uint8_t *rxPacket, uint16_t rxPacketLength);
  bool checkForResponse (uint8_t rxId, uint8_t *rxPacket, uint16_t rxPacketLength);
  void waitForResponse (uint8_t rxId, uint8_t *rxPacket, uint16_t rxPacketLength);
  uint8_t packetReceiveGetId (void);
  uint16_t addSendByteDashboard (uint8_t *addBuffer, uint16_t index, struct MsgConfigDashboardElementCommon *const config);
  uint16_t verifyDataLength (uint16_t length);
  uint16_t addSendByte (uint8_t *buffer, uint8_t index, uint8_t *data, uint16_t length);

 public:
  AtmelDataProtocol (void);

  HandshakeStatus waitForHandshake (void);
  StatusCode requestStatus (void);
  bool requestHandshake (uint8_t protocolVersion, uint8_t options, uint8_t *protocolBuffer);
  bool receivePacketData (uint8_t *receiveBuffer);
  bool toggleStream (MsgToggleStream *const config);
  bool transceiveStream (MsgDataStream *const streamData, uint8_t *receiveBuffer);
  bool transceiveSingleStream (uint16_t streamId, uint8_t *data, uint8_t dataSize, uint8_t *receiveBuffer);

  void addAtmelDataGateway (AtmelDataGateway* adg);
  void setColor (uint8_t *structMember, RgbColor color);

  void configureStreamGetDefaults (MsgConfigStream *const config);
  void configureTerminalGetDefaults (MsgConfigTerminal *const config);
  void configureStreamToTerminalGetDefaults (MsgConfigAddStreamToTerminal *const config);
  void configureGraphGetDefaults (MsgConfigGraph *const config);
  void configureAxisToGraphGetDefaults (MsgConfigAxis *const config);
  void configureStreamToAxisGetDefaults (MsgAddStreamToAxis *const config);
  void configureCursorToGraphGetDefaults (MsgAddCursorToGraph *const config);
  void configureGpioToGraphGetDefaults (MsgConfigGpioToGraph *const config);
  void configureDashboardGetDefaults (MsgConfigDahsboard *const config);
  void configureDashboardElementGetDefaults (MsgConfigDashboardElementCommon *const config);
  void configureDashboardLabelGetDefaults (MsgConfigDashboardElementLabel *const config);
  void configureDashboardButtonGetDefaults (MsgConfigDashboardElementButton *const config);
  void configureDashboardSliderGetDefaults (MsgConfigDashboardElementSlider *const config);
  void configureDashboardPrograssGetDefaults (MsgConfigDashboardElementProgress *const config);
  void configureDashboardSignalGetDefaults (MsgConfigDashboardElementSignal *const config);
  void configureDashboardSegmentGetDefaults (MsgConfigDashboardElementSegment *const config);
  void configureDashboardGraphGetDefaults (MsgConfigDashboardElementGraph *const config);
  void configureDashboardTextGetDefaults (MsgConfigDashboardElementText *const config);
  void configureDashboardRadioGetDefaults (MsgConfigDashboardElementRadio *const config);
  void configureDashboardPieGetDefaults (MsgConfigDashboardElementPie *const config);
  void configureDashboardRectangleGetDefaults (MsgConfigDashboardElementRectangle *const config);
  void configureDashboardCheckBoxGetDefaults (MsgConfigDashboardElementCheckBox *const config);
  void configureDashboardSurfaceGetDefaults (MsgConfigDashboardElementSurface *const config);
  void configureDashboardTableGetDefaults (MsgConfigDashboardElementTable *const config);

  bool addInfo (const char *title, const char *description);
  bool addStream (MsgConfigStream *const config, const char *label);
  bool addTerminal (MsgConfigTerminal *const config, const char *label);
  bool addStreamToTerminal (MsgConfigAddStreamToTerminal *const config, const char *tagText);
  bool addGraph (MsgConfigGraph *const config, const char *graphLabel, const char *xLabel);
  bool addAxisToGraph (MsgConfigAxis *const config, const char *label);
  bool addStreamToAxis (MsgAddStreamToAxis *const config);
  bool addCursorToGraph (MsgAddCursorToGraph *const config, const char *label);
  bool addGpioToGraph (MsgConfigGpioToGraph *const config, const char *tagHighState, const char *tagLowState);
  bool addDashboard (MsgConfigDahsboard *const config, const char *label);
  bool addStreamToElement (MsgConfigAddStreamToElement *const config);
  bool addLabelToDashboard (MsgConfigDashboardElementLabel *const config, const char *label);
  bool addButtonToDashboard (MsgConfigDashboardElementButton *const config, const char *label);
  bool addSliderToDashboard (MsgConfigDashboardElementSlider *const config);
  bool addProgressToDashboard (MsgConfigDashboardElementProgress *const config);
  bool addSignalToDashboard (MsgConfigDashboardElementSignal *const config);
  bool addSegmentToDashboard (MsgConfigDashboardElementSegment *const config);
  bool addGraphToDashboard (MsgConfigDashboardElementGraph *const config, const char *title);
  bool addTextToDashboard (MsgConfigDashboardElementText *const config);
  bool addRadioToDashboard (MsgConfigDashboardElementRadio *const config, const char *text);
  bool addPieToDashboard (MsgConfigDashboardElementPie *const config, const char *title);
  bool addRectangleToDashboard (MsgConfigDashboardElementRectangle *const config);
  bool addCheckBoxToDashboard (MsgConfigDashboardElementCheckBox *const config, const char *label);
  bool addSurfaceToDashboard (MsgConfigDashboardElementSurface *const config);
  bool addTableToDashboard (MsgConfigDashboardElementTable *const config, const char *labelConfiguration);
};

#endif /* ATMEL_DATA_PROTOCOL_H */
