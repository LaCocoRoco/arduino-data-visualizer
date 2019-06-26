#include "DataVisualizerDashboard.h"

DataVisualizerDashboard::DataVisualizerDashboard (void) {
  this->id = 0;
  this->visualizer = 0;
}

DataVisualizerDashboardLabel DataVisualizerDashboard::addLabel (const uint8_t* config) {
  DataVisualizerDashboardLabel dashboardLabel;

  if (config[POSITION_TYPE] != DB_TYPE_LABEL) return dashboardLabel;

  uint8_t length = strlen ( (const char*) (config + POSITION_LABEL_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_LABEL_TEXT, length);

  ConfigDashboardLabel configDashboardLabel;
  memcpy (&configDashboardLabel.zIndex,             config + POSITION_Z_INDEX,                sizeof (configDashboardLabel.zIndex));
  memcpy (&configDashboardLabel.x,                  config + POSITION_X,                      sizeof (configDashboardLabel.x));
  memcpy (&configDashboardLabel.y,                  config + POSITION_Y,                      sizeof (configDashboardLabel.y));
  memcpy (&configDashboardLabel.width,              config + POSITION_WIDTH,                  sizeof (configDashboardLabel.width));
  memcpy (&configDashboardLabel.height,             config + POSITION_HEIGHT,                 sizeof (configDashboardLabel.height));
  memcpy (&configDashboardLabel.fontSize,           config + POSITION_LABEL_FONT_SIZE,        sizeof (configDashboardLabel.fontSize));
  memcpy (&configDashboardLabel.backgroundAlpha,    config + POSITION_LABEL_ALPHA_BACKGROUND, sizeof (configDashboardLabel.backgroundAlpha));
  memcpy (&configDashboardLabel.foregroundAlpha,    config + POSITION_LABEL_ALPHA_FOREGROUND, sizeof (configDashboardLabel.foregroundAlpha));
  memcpy (&configDashboardLabel.aligmentHorizontal, config + POSITION_LABEL_HOR_ALIG,         sizeof (configDashboardLabel.aligmentHorizontal));
  memcpy (&configDashboardLabel.aligmentVertical,   config + POSITION_LABEL_VER_ALIG,         sizeof (configDashboardLabel.aligmentVertical));
  memcpy (&configDashboardLabel.backgroundColor,    config + POSITION_LABEL_COLOR_BACKGROUND, sizeof (configDashboardLabel.backgroundColor));
  memcpy (&configDashboardLabel.foregroundColor,    config + POSITION_LABEL_COLOR_FOREGROUND, sizeof (configDashboardLabel.foregroundColor));

  configDashboardLabel.bolt   = config[POSITION_LABEL_ATTRIBUTE] & 0x01;
  configDashboardLabel.italic = config[POSITION_LABEL_ATTRIBUTE] & 0x02;

  this->addLabel (text, configDashboardLabel);
}

DataVisualizerDashboardLabel DataVisualizerDashboard::addLabel (const char* text, ConfigDashboardLabel config) {
  DataVisualizerDashboardLabel dashboardLabel;

  if (!this->visualizer) return dashboardLabel;
  if (!this->visualizer->handshake) return dashboardLabel;

  uint16_t elementId = this->visualizer->index++;

  dashboardLabel.visualizer = this->visualizer;
  dashboardLabel.id         = elementId;

  MsgConfigDashboardElementLabel msgConfigDashboardElementLabel;
  msgConfigDashboardElementLabel.elementType            = ELEMENT_TYPE_LABEL;
  msgConfigDashboardElementLabel.dashboardId            = this->id;
  msgConfigDashboardElementLabel.elementId              = elementId;
  msgConfigDashboardElementLabel.zIndex                 = config.zIndex;
  msgConfigDashboardElementLabel.x                      = config.x;
  msgConfigDashboardElementLabel.y                      = config.y;
  msgConfigDashboardElementLabel.width                  = config.width;
  msgConfigDashboardElementLabel.height                 = config.height;
  msgConfigDashboardElementLabel.fontSize               = config.fontSize;
  msgConfigDashboardElementLabel.attributes.bit.bold     = config.bolt;
  msgConfigDashboardElementLabel.attributes.bit.italic   = config.italic;
  msgConfigDashboardElementLabel.horisontalAlignment    = config.aligmentHorizontal;
  msgConfigDashboardElementLabel.verticalAlignment      = config.aligmentVertical;
  msgConfigDashboardElementLabel.backgroundTransparency = config.backgroundAlpha;
  msgConfigDashboardElementLabel.foregroundTransparency = config.foregroundAlpha;
  this->visualizer->protocol.setColor (msgConfigDashboardElementLabel.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementLabel.foregroundColor, config.foregroundColor);
  this->visualizer->protocol.addLabelToDashboard (&msgConfigDashboardElementLabel, text);

  return dashboardLabel;
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton (const char* text, ConfigDashboardButton config) {
  return this->addButton (text, config, VARIANT_TOGGLED_OFF);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton (const char* textOn, const char* textOff, ConfigDashboardButton config) {

  uint8_t length = strlen (textOn) + strlen (textOff) + 2;

  const char delimiter[] = "/";
  char text[length];

  strcat (text, textOn);
  strcat (text, delimiter);
  strcat (text, textOff);

  return this->addButton (text, config, VARIANT_TOGGLED_ON);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton (const uint8_t* config) {
  DataVisualizerDashboardButton dashboardButton;

  if (config[POSITION_TYPE] != DB_TYPE_BUTTON) return dashboardButton;

  uint8_t length = strlen ( (const char*) (config + POSITION_BUTTON_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_BUTTON_TEXT, length);

  ConfigDashboardButton configDashboardButton;
  memcpy (&configDashboardButton.zIndex,   config + POSITION_Z_INDEX,          sizeof (configDashboardButton.zIndex));
  memcpy (&configDashboardButton.x,        config + POSITION_X,                sizeof (configDashboardButton.x));
  memcpy (&configDashboardButton.y,        config + POSITION_Y,                sizeof (configDashboardButton.y));
  memcpy (&configDashboardButton.width,    config + POSITION_WIDTH,            sizeof (configDashboardButton.width));
  memcpy (&configDashboardButton.height,   config + POSITION_HEIGHT,           sizeof (configDashboardButton.height));
  memcpy (&configDashboardButton.fontSize, config + POSITION_BUTTON_FONT_SIZE, sizeof (configDashboardButton.fontSize));

  uint8_t toggle = config[POSITION_BUTTON_TEXT + length];

  return this->addButton (text, configDashboardButton, toggle);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton (const char* text, ConfigDashboardButton config, uint8_t toggle) {
  DataVisualizerDashboardButton dashboardButton;

  if (!this->visualizer) return dashboardButton;
  if (!this->visualizer->handshake) return dashboardButton;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardButton.visualizer = this->visualizer;
  dashboardButton.id         = elementId;
  dashboardButton.packet     = this->visualizer->pack (streamId, LENGTH_1_BYTE);

  MsgConfigDashboardElementButton msgConfigDashboardElementButton;
  msgConfigDashboardElementButton.elementType = ELEMENT_TYPE_BUTTON;
  msgConfigDashboardElementButton.dashboardId = this->id;
  msgConfigDashboardElementButton.elementId   = elementId;
  msgConfigDashboardElementButton.zIndex      = config.zIndex;
  msgConfigDashboardElementButton.x           = config.x;
  msgConfigDashboardElementButton.y           = config.y;
  msgConfigDashboardElementButton.width       = config.width;
  msgConfigDashboardElementButton.height      = config.height;
  msgConfigDashboardElementButton.fontSize    = config.fontSize;
  msgConfigDashboardElementButton.toggle      = toggle;
  this->visualizer->protocol.addButtonToDashboard (&msgConfigDashboardElementButton, text);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_UINT_8;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "Button");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardButton;
}

DataVisualizerDashboardSlider DataVisualizerDashboard::addSlider (const uint8_t* config) {
  DataVisualizerDashboardSlider dashboardSlider;

  if (config[POSITION_TYPE] != DB_TYPE_SLIDER) return dashboardSlider;

  ConfigDashboardSlider configDashboardSlider;
  memcpy (&configDashboardSlider.zIndex,  config + POSITION_Z_INDEX,        sizeof (configDashboardSlider.zIndex));
  memcpy (&configDashboardSlider.x,       config + POSITION_X,              sizeof (configDashboardSlider.x));
  memcpy (&configDashboardSlider.y,       config + POSITION_Y,              sizeof (configDashboardSlider.y));
  memcpy (&configDashboardSlider.width,   config + POSITION_WIDTH,          sizeof (configDashboardSlider.width));
  memcpy (&configDashboardSlider.height,  config + POSITION_HEIGHT,         sizeof (configDashboardSlider.height));
  memcpy (&configDashboardSlider.minimum, config + POSITION_SLIDER_MINIMUM, sizeof (configDashboardSlider.minimum));
  memcpy (&configDashboardSlider.maximum, config + POSITION_SLIDER_MAXIMUM, sizeof (configDashboardSlider.maximum));
  memcpy (&configDashboardSlider.initial, config + POSITION_SLIDER_VALUE,   sizeof (configDashboardSlider.initial));

  return this->addSlider (configDashboardSlider);
}

DataVisualizerDashboardSlider DataVisualizerDashboard::addSlider (ConfigDashboardSlider config) {
  DataVisualizerDashboardSlider dashboardSlider;

  if (!this->visualizer) return dashboardSlider;
  if (!this->visualizer->handshake) return dashboardSlider;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardSlider.visualizer = this->visualizer;
  dashboardSlider.id         = elementId;
  dashboardSlider.packet     = this->visualizer->pack (streamId, LENGTH_4_BYTE);
  memcpy (dashboardSlider.packet->data, &config.initial, LENGTH_4_BYTE);

  MsgConfigDashboardElementSlider msgConfigDashboardElementSlider;
  msgConfigDashboardElementSlider.elementType  = ELEMENT_TYPE_SLIDER;
  msgConfigDashboardElementSlider.dashboardId  = this->id;
  msgConfigDashboardElementSlider.elementId    = elementId;
  msgConfigDashboardElementSlider.zIndex       = config.zIndex;
  msgConfigDashboardElementSlider.x            = config.x;
  msgConfigDashboardElementSlider.y            = config.y;
  msgConfigDashboardElementSlider.width        = config.width;
  msgConfigDashboardElementSlider.height       = config.height;
  msgConfigDashboardElementSlider.minimumValue = config.minimum;
  msgConfigDashboardElementSlider.maximumValue = config.maximum;
  msgConfigDashboardElementSlider.initialValue = config.initial;
  this->visualizer->protocol.addSliderToDashboard (&msgConfigDashboardElementSlider);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "SliderInput");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardSlider;
}

DataVisualizerDashboardProgressBar DataVisualizerDashboard::addProgressBar (const uint8_t* config) {
  DataVisualizerDashboardProgressBar dashboardProgressBar;

  if (config[POSITION_TYPE] != DB_TYPE_PROGRESS) return dashboardProgressBar;

  ConfigDashboardProgressBar configDashboardProgressBar;
  memcpy (&configDashboardProgressBar.zIndex,  config + POSITION_Z_INDEX,          sizeof (configDashboardProgressBar.zIndex));
  memcpy (&configDashboardProgressBar.x,       config + POSITION_X,                sizeof (configDashboardProgressBar.x));
  memcpy (&configDashboardProgressBar.y,       config + POSITION_Y,                sizeof (configDashboardProgressBar.y));
  memcpy (&configDashboardProgressBar.width,   config + POSITION_WIDTH,            sizeof (configDashboardProgressBar.width));
  memcpy (&configDashboardProgressBar.height,  config + POSITION_HEIGHT,           sizeof (configDashboardProgressBar.height));
  memcpy (&configDashboardProgressBar.minimum, config + POSITION_PROGRESS_MINIMUM, sizeof (configDashboardProgressBar.minimum));
  memcpy (&configDashboardProgressBar.maximum, config + POSITION_PROGRESS_MAXIMUM, sizeof (configDashboardProgressBar.maximum));
  memcpy (&configDashboardProgressBar.value,   config + POSITION_PROGRESS_VALUE,   sizeof (configDashboardProgressBar.value));
  memcpy (&configDashboardProgressBar.color,   config + POSITION_PROGRESS_COLOR,   sizeof (configDashboardProgressBar.color));

  return this->addProgressBar (configDashboardProgressBar);
}

DataVisualizerDashboardProgressBar DataVisualizerDashboard::addProgressBar (ConfigDashboardProgressBar config) {
  DataVisualizerDashboardProgressBar dashboardProgressBar;

  if (!this->visualizer) return dashboardProgressBar;
  if (!this->visualizer->handshake) return dashboardProgressBar;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardProgressBar.visualizer = this->visualizer;
  dashboardProgressBar.id         = streamId;

  MsgConfigDashboardElementProgress msgConfigCashboardElementProgress;
  msgConfigCashboardElementProgress.elemntType   = ELEMENT_TYPE_PROGRESS;
  msgConfigCashboardElementProgress.dashboardId  = this->id;
  msgConfigCashboardElementProgress.elementId    = elementId;
  msgConfigCashboardElementProgress.zIndex       = config.zIndex;
  msgConfigCashboardElementProgress.x            = config.x;
  msgConfigCashboardElementProgress.y            = config.y;
  msgConfigCashboardElementProgress.width        = config.width;
  msgConfigCashboardElementProgress.height       = config.height;
  msgConfigCashboardElementProgress.minimumValue = config.minimum;
  msgConfigCashboardElementProgress.maximumValue = config.maximum;
  msgConfigCashboardElementProgress.initialValue = config.value;
  this->visualizer->protocol.setColor (msgConfigCashboardElementProgress.color, config.color);

  this->visualizer->protocol.addProgressToDashboard (&msgConfigCashboardElementProgress);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_UINT_32;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "Progress Bar");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardProgressBar;
}

DataVisualizerDashboardSignal DataVisualizerDashboard::addSignal (const uint8_t* config) {
  DataVisualizerDashboardSignal dashboardSignal;

  if (config[POSITION_TYPE] != DB_TYPE_SIGNAL) return dashboardSignal;

  ConfigDashboardSignal configDashboardSignal;
  memcpy (&configDashboardSignal.zIndex,   config + POSITION_Z_INDEX,          sizeof (configDashboardSignal.zIndex));
  memcpy (&configDashboardSignal.x,        config + POSITION_X,                sizeof (configDashboardSignal.x));
  memcpy (&configDashboardSignal.y,        config + POSITION_Y,                sizeof (configDashboardSignal.y));
  memcpy (&configDashboardSignal.width,    config + POSITION_WIDTH,            sizeof (configDashboardSignal.width));
  memcpy (&configDashboardSignal.height,   config + POSITION_HEIGHT,           sizeof (configDashboardSignal.height));
  memcpy (&configDashboardSignal.onAlpha,  config + POSITION_SIGNAL_ALPHA_ON,  sizeof (configDashboardSignal.onAlpha));
  memcpy (&configDashboardSignal.offAlpha, config + POSITION_SIGNAL_ALPHA_OFF, sizeof (configDashboardSignal.offAlpha));
  memcpy (&configDashboardSignal.onColor,  config + POSITION_SIGNAL_COLOR_ON,  sizeof (configDashboardSignal.onColor));
  memcpy (&configDashboardSignal.offColor, config + POSITION_SIGNAL_COLOR_OFF, sizeof (configDashboardSignal.offColor));

  return this->addSignal (configDashboardSignal);
}

DataVisualizerDashboardSignal DataVisualizerDashboard::addSignal (ConfigDashboardSignal config) {
  DataVisualizerDashboardSignal dashboardSignal;

  if (!this->visualizer) return dashboardSignal;
  if (!this->visualizer->handshake) return dashboardSignal;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardSignal.visualizer = this->visualizer;
  dashboardSignal.id         = streamId;

  MsgConfigDashboardElementSignal msgConfigCashboardElementSignal;
  msgConfigCashboardElementSignal.elementType     = ELEMENT_TYPE_SIGNAL;
  msgConfigCashboardElementSignal.dashboardId     = this->id;
  msgConfigCashboardElementSignal.elementId       = elementId;
  msgConfigCashboardElementSignal.zIndex          = config.zIndex;
  msgConfigCashboardElementSignal.x               = config.x;
  msgConfigCashboardElementSignal.y               = config.y;
  msgConfigCashboardElementSignal.width           = config.width;
  msgConfigCashboardElementSignal.height          = config.height;
  msgConfigCashboardElementSignal.onTransparency  = config.onAlpha;
  msgConfigCashboardElementSignal.offTransparency = config.offAlpha;
  this->visualizer->protocol.setColor (msgConfigCashboardElementSignal.onColor, config.onColor);
  this->visualizer->protocol.setColor (msgConfigCashboardElementSignal.offColor, config.offColor);
  this->visualizer->protocol.addSignalToDashboard (&msgConfigCashboardElementSignal);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_UINT_8;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "Signal");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardSignal;
}

DataVisualizerDashboardSegmentDisplay DataVisualizerDashboard::addSegmentDisplay (const uint8_t* config) {
  DataVisualizerDashboardSegmentDisplay dashboardSegmentDisplay;

  if (config[POSITION_TYPE] != DB_TYPE_SEGMENT) return dashboardSegmentDisplay;

  ConfigDashboardSegmentDisplay configDashboardSegmentDisplay;
  memcpy (&configDashboardSegmentDisplay.zIndex, config + POSITION_Z_INDEX,       sizeof (configDashboardSegmentDisplay.zIndex));
  memcpy (&configDashboardSegmentDisplay.x,      config + POSITION_X,             sizeof (configDashboardSegmentDisplay.x));
  memcpy (&configDashboardSegmentDisplay.y,      config + POSITION_Y,             sizeof (configDashboardSegmentDisplay.y));
  memcpy (&configDashboardSegmentDisplay.width,  config + POSITION_WIDTH,         sizeof (configDashboardSegmentDisplay.width));
  memcpy (&configDashboardSegmentDisplay.height, config + POSITION_HEIGHT,        sizeof (configDashboardSegmentDisplay.height));
  memcpy (&configDashboardSegmentDisplay.digits, config + POSITION_SEGMENT_COUNT, sizeof (configDashboardSegmentDisplay.digits));
  memcpy (&configDashboardSegmentDisplay.base,   config + POSITION_SEGMENT_BASE,  sizeof (configDashboardSegmentDisplay.base));
  memcpy (&configDashboardSegmentDisplay.alpha,  config + POSITION_SEGMENT_ALPHA, sizeof (configDashboardSegmentDisplay.alpha));
  memcpy (&configDashboardSegmentDisplay.color,  config + POSITION_SEGMENT_COLOR, sizeof (configDashboardSegmentDisplay.color));

  return this->addSegmentDisplay (configDashboardSegmentDisplay);
}

DataVisualizerDashboardSegmentDisplay DataVisualizerDashboard::addSegmentDisplay (ConfigDashboardSegmentDisplay config) {
  DataVisualizerDashboardSegmentDisplay dashboardSegmentDisplay;

  if (!this->visualizer) return dashboardSegmentDisplay;
  if (!this->visualizer->handshake) return dashboardSegmentDisplay;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardSegmentDisplay.visualizer = this->visualizer;
  dashboardSegmentDisplay.id         = streamId;

  MsgConfigDashboardElementSegment msgConfigCashboardElementSegment;
  msgConfigCashboardElementSegment.elementType  = ELEMENT_TYPE_SEGMENT;
  msgConfigCashboardElementSegment.dashboardId  = this->id;
  msgConfigCashboardElementSegment.elementId    = elementId;
  msgConfigCashboardElementSegment.zIndex       = config.zIndex;
  msgConfigCashboardElementSegment.x            = config.x;
  msgConfigCashboardElementSegment.y            = config.y;
  msgConfigCashboardElementSegment.width        = config.width;
  msgConfigCashboardElementSegment.height       = config.height;
  msgConfigCashboardElementSegment.segmentCount = config.digits;
  msgConfigCashboardElementSegment.base         = config.base;
  msgConfigCashboardElementSegment.transparency = config.alpha;
  this->visualizer->protocol.setColor (msgConfigCashboardElementSegment.color, config.color);
  this->visualizer->protocol.addSegmentToDashboard (&msgConfigCashboardElementSegment);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_UINT_32;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "Segment");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardSegmentDisplay;
}

DataVisualizerDashboardGraph DataVisualizerDashboard::addGraph (const uint8_t* config) {
  DataVisualizerDashboardGraph dashboardGraph;

  if (config[POSITION_TYPE] != DB_TYPE_GRAPH) return dashboardGraph;

  uint8_t length = strlen ( (const char*) (config + POSITION_GRAPH_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_GRAPH_TEXT, length);

  ConfigDashboardGraph configDashboardGraph;
  memcpy (&configDashboardGraph.zIndex,          config + POSITION_Z_INDEX,                   sizeof (configDashboardGraph.zIndex));
  memcpy (&configDashboardGraph.x,               config + POSITION_X,                         sizeof (configDashboardGraph.x));
  memcpy (&configDashboardGraph.y,               config + POSITION_Y,                         sizeof (configDashboardGraph.y));
  memcpy (&configDashboardGraph.width,           config + POSITION_WIDTH,                     sizeof (configDashboardGraph.width));
  memcpy (&configDashboardGraph.height,          config + POSITION_HEIGHT,                    sizeof (configDashboardGraph.height));
  memcpy (&configDashboardGraph.numberChannels,  config + POSITION_GRAPH_PLOT_COUNT + length, sizeof (configDashboardGraph.numberChannels));
  memcpy (&configDashboardGraph.xMinimum,        config + POSITION_GRAPH_X_MINIMUM  + length, sizeof (configDashboardGraph.xMinimum));
  memcpy (&configDashboardGraph.xMaximum,        config + POSITION_GRAPH_X_MAXIMUM  + length, sizeof (configDashboardGraph.xMaximum));
  memcpy (&configDashboardGraph.yMinimum,        config + POSITION_GRAPH_Y_MINIMUM  + length, sizeof (configDashboardGraph.yMinimum));
  memcpy (&configDashboardGraph.yMaximum,        config + POSITION_GRAPH_Y_MAXIMUM  + length, sizeof (configDashboardGraph.yMaximum));
  memcpy (&configDashboardGraph.titleColor,      config + POSITION_GRAPH_COLOR_TITLE,         sizeof (configDashboardGraph.titleColor));
  memcpy (&configDashboardGraph.backgroundColor, config + POSITION_GRAPH_COLOR_BACKGROUND,    sizeof (configDashboardGraph.backgroundColor));
  memcpy (&configDashboardGraph.graphColor,      config + POSITION_GRAPH_COLOR_GRAPH,         sizeof (configDashboardGraph.graphColor));

  configDashboardGraph.mouseInteraction = config[POSITION_GRAPH_MODE_LB + length] & 0x01;
  configDashboardGraph.fitToRight       = config[POSITION_GRAPH_MODE_LB + length] & 0x02;
  configDashboardGraph.autoscale        = config[POSITION_GRAPH_MODE_LB + length] & 0x04;
  configDashboardGraph.scrollByTime     = config[POSITION_GRAPH_MODE_LB + length] & 0x08;
  configDashboardGraph.showPlot         = config[POSITION_GRAPH_MODE_HB + length] & 0x01;
  configDashboardGraph.showPoints       = config[POSITION_GRAPH_MODE_HB + length] & 0x02;

  return this->addGraph (text, configDashboardGraph);
}

DataVisualizerDashboardGraph DataVisualizerDashboard::addGraph (const char* text, ConfigDashboardGraph config) {
  DataVisualizerDashboardGraph dashboardGraph;

  if (!this->visualizer) return dashboardGraph;
  if (!this->visualizer->handshake) return dashboardGraph;

  uint16_t elementId = this->visualizer->index++;

  dashboardGraph.visualizer = this->visualizer;
  dashboardGraph.dashboard  = this;
  dashboardGraph.id         = elementId;
  dashboardGraph.plotCount  = config.numberChannels;

  MsgConfigDashboardElementGraph msgConfigDashboardElementGraph;
  msgConfigDashboardElementGraph.elementType           = ELEMENT_TYPE_GRAPH;
  msgConfigDashboardElementGraph.dashboardId           = this->id;
  msgConfigDashboardElementGraph.elementId             = elementId;
  msgConfigDashboardElementGraph.zIndex                = config.zIndex;
  msgConfigDashboardElementGraph.x                     = config.x;
  msgConfigDashboardElementGraph.y                     = config.y;
  msgConfigDashboardElementGraph.width                 = config.width;
  msgConfigDashboardElementGraph.height                = config.height;
  msgConfigDashboardElementGraph.plotCount             = config.numberChannels;
  msgConfigDashboardElementGraph.xMin                  = config.xMinimum;
  msgConfigDashboardElementGraph.xMax                  = config.xMaximum;
  msgConfigDashboardElementGraph.yMin                  = config.yMinimum;
  msgConfigDashboardElementGraph.yMax                  = config.yMaximum;
  msgConfigDashboardElementGraph.mode.bit.fitGraph     = config.fitToRight;
  msgConfigDashboardElementGraph.mode.bit.mouse        = config.mouseInteraction;
  msgConfigDashboardElementGraph.mode.bit.autoscale    = config.autoscale;
  msgConfigDashboardElementGraph.mode.bit.scrollByTime = config.scrollByTime;
  msgConfigDashboardElementGraph.mode.bit.showPlot     = config.showPlot;
  msgConfigDashboardElementGraph.mode.bit.showPoints   = config.showPoints;
  this->visualizer->protocol.setColor (msgConfigDashboardElementGraph.titleColor, config.titleColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementGraph.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementGraph.graphBackgroundColor, config.graphColor);
  this->visualizer->protocol.addGraphToDashboard (&msgConfigDashboardElementGraph, text);

  return dashboardGraph;
}

DataVisualizerDashboardNumericInput DataVisualizerDashboard::addNumericInput (const uint8_t* config) {
  DataVisualizerDashboardNumericInput dashboardNumericInput;

  if (config[POSITION_TYPE] != DB_TYPE_TEXT) return dashboardNumericInput;

  ConfigDashboardNumericInput configDashboardNumericInput;
  memcpy (&configDashboardNumericInput.zIndex,  config + POSITION_Z_INDEX,      sizeof (configDashboardNumericInput.zIndex));
  memcpy (&configDashboardNumericInput.x,       config + POSITION_X,            sizeof (configDashboardNumericInput.x));
  memcpy (&configDashboardNumericInput.y,       config + POSITION_Y,            sizeof (configDashboardNumericInput.y));
  memcpy (&configDashboardNumericInput.width,   config + POSITION_WIDTH,        sizeof (configDashboardNumericInput.width));
  memcpy (&configDashboardNumericInput.height,  config + POSITION_HEIGHT,       sizeof (configDashboardNumericInput.height));
  memcpy (&configDashboardNumericInput.minimum, config + POSITION_TEXT_MINIMUM, sizeof (configDashboardNumericInput.minimum));
  memcpy (&configDashboardNumericInput.maximum, config + POSITION_TEXT_MAXIMUM, sizeof (configDashboardNumericInput.maximum));
  memcpy (&configDashboardNumericInput.value,   config + POSITION_TEXT_VALUE,   sizeof (configDashboardNumericInput.value));

  return this->addNumericInput (configDashboardNumericInput);
}

DataVisualizerDashboardNumericInput DataVisualizerDashboard::addNumericInput (ConfigDashboardNumericInput config) {
  DataVisualizerDashboardNumericInput dashboardNumericInput;

  if (!this->visualizer) return dashboardNumericInput;
  if (!this->visualizer->handshake) return dashboardNumericInput;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardNumericInput.visualizer = this->visualizer;
  dashboardNumericInput.id         = elementId;
  dashboardNumericInput.packet     = this->visualizer->pack (streamId, LENGTH_4_BYTE);
  memcpy (dashboardNumericInput.packet->data, &config.value, LENGTH_4_BYTE);

  MsgConfigDashboardElementText msgConfigDashboardElementText;
  msgConfigDashboardElementText.elementType = ELEMENT_TYPE_TEXT;
  msgConfigDashboardElementText.dashboardId = this->id;
  msgConfigDashboardElementText.elementId   = elementId;
  msgConfigDashboardElementText.zIndex      = config.zIndex;
  msgConfigDashboardElementText.x           = config.x;
  msgConfigDashboardElementText.y           = config.y;
  msgConfigDashboardElementText.width       = config.width;
  msgConfigDashboardElementText.height      = config.height;
  memcpy (msgConfigDashboardElementText.minimum, &config.minimum, LENGTH_4_BYTE);
  memcpy (msgConfigDashboardElementText.maximum, &config.maximum, LENGTH_4_BYTE);
  memcpy (msgConfigDashboardElementText.value,   &config.value,   LENGTH_4_BYTE);
  this->visualizer->protocol.addTextToDashboard (&msgConfigDashboardElementText);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "NumericInput");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardNumericInput;
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup (const uint8_t* config) {
  DataVisualizerDashboardRadioGroup dashboardRadioGroup;

  if (config[POSITION_TYPE] != DB_TYPE_RADIOGROUP) return dashboardRadioGroup;

  uint8_t length = strlen ( (const char*) (config + POSITION_RADIOGROUP_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_RADIOGROUP_TEXT, length);

  ConfigDashboardRadioGroup configDashboardRadioGroup;
  memcpy (&configDashboardRadioGroup.zIndex,      config + POSITION_Z_INDEX,                 sizeof (configDashboardRadioGroup.zIndex));
  memcpy (&configDashboardRadioGroup.x,           config + POSITION_X,                       sizeof (configDashboardRadioGroup.x));
  memcpy (&configDashboardRadioGroup.y,           config + POSITION_Y,                       sizeof (configDashboardRadioGroup.y));
  memcpy (&configDashboardRadioGroup.width,       config + POSITION_WIDTH,                   sizeof (configDashboardRadioGroup.width));
  memcpy (&configDashboardRadioGroup.height,      config + POSITION_HEIGHT,                  sizeof (configDashboardRadioGroup.height));
  memcpy (&configDashboardRadioGroup.sizeItems,   config + POSITION_RADIOGROUP_SIZE_ITEMS,   sizeof (configDashboardRadioGroup.sizeItems));
  memcpy (&configDashboardRadioGroup.numberItems, config + POSITION_RADIOGROUP_NUMBER_ITEMS, sizeof (configDashboardRadioGroup.numberItems));
  memcpy (&configDashboardRadioGroup.orientation, config + POSITION_RADIOGROUP_ORIENTATION,  sizeof (configDashboardRadioGroup.orientation));

  return this->addRadioGroup (text, configDashboardRadioGroup);
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup (ConfigDashboardRadioGroup config) {
  config.numberItems = config.numberItems > RADIOGROUP_MAX ? RADIOGROUP_MAX : config.numberItems;

  char text[config.numberItems];
  for (uint8_t i = 0; i < config.numberItems; i++) text[i] = '/';

  return this->addRadioGroup (text, config);
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup (const char* text, ConfigDashboardRadioGroup config) {
  DataVisualizerDashboardRadioGroup dashboardRadioGroup;

  if (!this->visualizer) return dashboardRadioGroup;
  if (!this->visualizer->handshake) return dashboardRadioGroup;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardRadioGroup.visualizer = this->visualizer;
  dashboardRadioGroup.id         = elementId;
  dashboardRadioGroup.packet     = this->visualizer->pack (streamId, LENGTH_1_BYTE);

  MsgConfigDashboardElementRadio msgConfigDashboardElementRadio;
  msgConfigDashboardElementRadio.elementType = ELEMENT_TYPE_RADIO;
  msgConfigDashboardElementRadio.dashboardId = this->id;
  msgConfigDashboardElementRadio.elementId   = elementId;
  msgConfigDashboardElementRadio.zIndex      = config.zIndex;
  msgConfigDashboardElementRadio.x           = config.x;
  msgConfigDashboardElementRadio.y           = config.y;
  msgConfigDashboardElementRadio.width       = config.width;
  msgConfigDashboardElementRadio.height      = config.height;
  msgConfigDashboardElementRadio.fontSize    = config.sizeItems;
  msgConfigDashboardElementRadio.orientation = config.orientation;
  msgConfigDashboardElementRadio.numberItems = config.numberItems;
  this->visualizer->protocol.addRadioToDashboard (&msgConfigDashboardElementRadio, text);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_UINT_8;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "RadioGroup");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardRadioGroup;
}

DataVisualizerDashboardPieChart DataVisualizerDashboard::addPieChart (const uint8_t* config) {
  DataVisualizerDashboardPieChart dashboardPieChart;

  if (config[POSITION_TYPE] != DB_TYPE_PIE) return dashboardPieChart;

  uint8_t length = strlen ( (const char*) (config + POSITION_PIE_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_PIE_TEXT, length);

  ConfigDashboardPieChart configDashboardPieChart;
  memcpy (&configDashboardPieChart.zIndex,          config + POSITION_Z_INDEX,                 sizeof (configDashboardPieChart.zIndex));
  memcpy (&configDashboardPieChart.x,               config + POSITION_X,                       sizeof (configDashboardPieChart.x));
  memcpy (&configDashboardPieChart.y,               config + POSITION_Y,                       sizeof (configDashboardPieChart.y));
  memcpy (&configDashboardPieChart.width,           config + POSITION_WIDTH,                   sizeof (configDashboardPieChart.width));
  memcpy (&configDashboardPieChart.height,          config + POSITION_HEIGHT,                  sizeof (configDashboardPieChart.height));
  memcpy (&configDashboardPieChart.titleColor,      config + POSITION_PIE_COLOR_TITLE,         sizeof (configDashboardPieChart.titleColor));
  memcpy (&configDashboardPieChart.backgroundColor, config + POSITION_PIE_COLOR_BACKGROUND,    sizeof (configDashboardPieChart.backgroundColor));
  memcpy (&configDashboardPieChart.numberSlices,    config + POSITION_PIE_PLOT_COUNT + length, sizeof (configDashboardPieChart.numberSlices));

  return this->addPieChart (text, configDashboardPieChart);
}

DataVisualizerDashboardPieChart DataVisualizerDashboard::addPieChart (const char* text, ConfigDashboardPieChart config) {
  DataVisualizerDashboardPieChart dashboardPieChart;

  if (!this->visualizer) return dashboardPieChart;
  if (!this->visualizer->handshake) return dashboardPieChart;

  uint16_t elementId = this->visualizer->index++;

  dashboardPieChart.visualizer = this->visualizer;
  dashboardPieChart.dashboard  = this;
  dashboardPieChart.id         = elementId;
  dashboardPieChart.plotCount  = config.numberSlices;

  MsgConfigDashboardElementPie msgConfigDashboardElementPie;
  msgConfigDashboardElementPie.elementType  = ELEMENT_TYPE_PIE;
  msgConfigDashboardElementPie.dashboardId  = this->id;
  msgConfigDashboardElementPie.elementId    = elementId;
  msgConfigDashboardElementPie.zIndex       = config.zIndex;
  msgConfigDashboardElementPie.x            = config.x;
  msgConfigDashboardElementPie.y            = config.y;
  msgConfigDashboardElementPie.width        = config.width;
  msgConfigDashboardElementPie.height       = config.height;
  msgConfigDashboardElementPie.numberSlices = config.numberSlices;
  this->visualizer->protocol.setColor (msgConfigDashboardElementPie.titleColor, config.titleColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementPie.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.addPieToDashboard (&msgConfigDashboardElementPie, text);

  return dashboardPieChart;
}

DataVisualizerDashboardRectangle DataVisualizerDashboard::addRectangle (const uint8_t* config) {
  DataVisualizerDashboardRectangle dashboardRectangle;

  if (config[POSITION_TYPE] != DB_TYPE_RECTANGLE) return dashboardRectangle;

  ConfigDashboardRectangle configDashboardRectangle;
  memcpy (&configDashboardRectangle.zIndex,          config + POSITION_Z_INDEX,                    sizeof (configDashboardRectangle.zIndex));
  memcpy (&configDashboardRectangle.x,               config + POSITION_X,                          sizeof (configDashboardRectangle.x));
  memcpy (&configDashboardRectangle.y,               config + POSITION_Y,                          sizeof (configDashboardRectangle.y));
  memcpy (&configDashboardRectangle.width,           config + POSITION_WIDTH,                      sizeof (configDashboardRectangle.width));
  memcpy (&configDashboardRectangle.height,          config + POSITION_HEIGHT,                     sizeof (configDashboardRectangle.height));
  memcpy (&configDashboardRectangle.backgroundAlpha, config + POSITION_RECTANGLE_ALPHA_BACKGROUND, sizeof (configDashboardRectangle.backgroundAlpha));
  memcpy (&configDashboardRectangle.backgroundColor, config + POSITION_RECTANGLE_COLOR_BACKGROUND, sizeof (configDashboardRectangle.backgroundColor));
  memcpy (&configDashboardRectangle.foregroundAlpha, config + POSITION_RECTANGLE_ALPHA_FOREGROUND, sizeof (configDashboardRectangle.foregroundAlpha));
  memcpy (&configDashboardRectangle.foregroundColor, config + POSITION_RECTANGLE_COLOR_FOREGROUND, sizeof (configDashboardRectangle.foregroundColor));

  this->addRectangle (configDashboardRectangle);
}

DataVisualizerDashboardRectangle DataVisualizerDashboard::addRectangle (ConfigDashboardRectangle config) {
  DataVisualizerDashboardRectangle dashboardRectangle;

  if (!this->visualizer) return dashboardRectangle;
  if (!this->visualizer->handshake) return dashboardRectangle;

  uint16_t elementId = this->visualizer->index++;

  dashboardRectangle.visualizer = this->visualizer;
  dashboardRectangle.id         = elementId;

  MsgConfigDashboardElementRectangle msgConfigDashboardElementRectangle;
  msgConfigDashboardElementRectangle.elementType            = ELEMENT_TYPE_RECTANGLE;
  msgConfigDashboardElementRectangle.dashboardId            = this->id;
  msgConfigDashboardElementRectangle.elementId              = elementId;
  msgConfigDashboardElementRectangle.zIndex                 = config.zIndex;
  msgConfigDashboardElementRectangle.x                      = config.x;
  msgConfigDashboardElementRectangle.y                      = config.y;
  msgConfigDashboardElementRectangle.width                  = config.width;
  msgConfigDashboardElementRectangle.height                 = config.height;
  msgConfigDashboardElementRectangle.backgroundTransparency = config.backgroundAlpha;
  msgConfigDashboardElementRectangle.foregroundTransparency = config.foregroundAlpha;
  this->visualizer->protocol.setColor (msgConfigDashboardElementRectangle.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementRectangle.foregroundColor, config.foregroundColor);
  this->visualizer->protocol.addRectangleToDashboard (&msgConfigDashboardElementRectangle);

  return dashboardRectangle;
}

DataVisualizerDashboardCheckBox DataVisualizerDashboard::addCheckBox (const uint8_t* config) {
  DataVisualizerDashboardCheckBox dashboardCheckBox;

  if (config[POSITION_TYPE] != DB_TYPE_CHECKBOX) return dashboardCheckBox;

  uint8_t length = strlen ( (const char*) (config + POSITION_CHECKBOX_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_CHECKBOX_TEXT, length);

  ConfigDashboardCheckBox configDashboardCheckBox;
  memcpy (&configDashboardCheckBox.zIndex,   config + POSITION_Z_INDEX,          sizeof (configDashboardCheckBox.zIndex));
  memcpy (&configDashboardCheckBox.x,        config + POSITION_X,                sizeof (configDashboardCheckBox.x));
  memcpy (&configDashboardCheckBox.y,        config + POSITION_Y,                sizeof (configDashboardCheckBox.y));
  memcpy (&configDashboardCheckBox.width,    config + POSITION_WIDTH,            sizeof (configDashboardCheckBox.width));
  memcpy (&configDashboardCheckBox.height,   config + POSITION_HEIGHT,           sizeof (configDashboardCheckBox.height));
  memcpy (&configDashboardCheckBox.fontSize, config + POSITION_BUTTON_FONT_SIZE, sizeof (configDashboardCheckBox.fontSize));

  return this->addCheckBox (text, configDashboardCheckBox);
}

DataVisualizerDashboardCheckBox DataVisualizerDashboard::addCheckBox (const char* text, ConfigDashboardCheckBox config) {
  DataVisualizerDashboardCheckBox dashboardCheckBox;

  if (!this->visualizer) return dashboardCheckBox;
  if (!this->visualizer->handshake) return dashboardCheckBox;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardCheckBox.visualizer = this->visualizer;
  dashboardCheckBox.id         = elementId;
  dashboardCheckBox.packet     = this->visualizer->pack (streamId, LENGTH_1_BYTE);

  MsgConfigDashboardElementCheckBox msgConfigDashboardElementCheckBox;
  msgConfigDashboardElementCheckBox.elementType = ELEMENT_TYPE_CHECKBOX;
  msgConfigDashboardElementCheckBox.dashboardId = this->id;
  msgConfigDashboardElementCheckBox.elementId   = elementId;
  msgConfigDashboardElementCheckBox.zIndex      = config.zIndex;
  msgConfigDashboardElementCheckBox.x           = config.x;
  msgConfigDashboardElementCheckBox.y           = config.y;
  msgConfigDashboardElementCheckBox.width       = config.width;
  msgConfigDashboardElementCheckBox.height      = config.height;
  msgConfigDashboardElementCheckBox.fontSize    = config.fontSize;
  this->visualizer->protocol.addCheckBoxToDashboard (&msgConfigDashboardElementCheckBox, text);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_BOOL;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "CheckBox");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardCheckBox;
}

DataVisualizerDashboardSurfaceGrid DataVisualizerDashboard::addSurfaceGrid (const uint8_t* config, uint8_t depthOfGrid, uint8_t widhtOfGrid) {
  DataVisualizerDashboardSurfaceGrid dashboardSurfaceGrid;

  if (config[POSITION_TYPE] != DB_TYPE_SURFACE) return dashboardSurfaceGrid;

  ConfigDashboardSurfaceGrid configDashboardSurfaceGrid;
  memcpy (&configDashboardSurfaceGrid.zIndex,                  config + POSITION_Z_INDEX,                  sizeof (configDashboardSurfaceGrid.zIndex));
  memcpy (&configDashboardSurfaceGrid.x,                       config + POSITION_X,                        sizeof (configDashboardSurfaceGrid.x));
  memcpy (&configDashboardSurfaceGrid.y,                       config + POSITION_Y,                        sizeof (configDashboardSurfaceGrid.y));
  memcpy (&configDashboardSurfaceGrid.width,                   config + POSITION_WIDTH,                    sizeof (configDashboardSurfaceGrid.width));
  memcpy (&configDashboardSurfaceGrid.height,                  config + POSITION_HEIGHT,                   sizeof (configDashboardSurfaceGrid.height));
  memcpy (&configDashboardSurfaceGrid.fillColor,               config + POSITION_SURFACE_FILL_COLOR,       sizeof (configDashboardSurfaceGrid.fillColor));
  memcpy (&configDashboardSurfaceGrid.meshColor,               config + POSITION_SURFACE_MESH_COLOR,       sizeof (configDashboardSurfaceGrid.meshColor));
  memcpy (&configDashboardSurfaceGrid.backgroundAlpha,         config + POSITION_SURFACE_BACKGROUND_ALPHA, sizeof (configDashboardSurfaceGrid.backgroundAlpha));
  memcpy (&configDashboardSurfaceGrid.backgroundColor,         config + POSITION_SURFACE_BACKGROUND_COLOR, sizeof (configDashboardSurfaceGrid.backgroundColor));
  memcpy (&configDashboardSurfaceGrid.gradientAlpha,           config + POSITION_SURFACE_GRADIENT_ALPHA,   sizeof (configDashboardSurfaceGrid.gradientAlpha));
  memcpy (&configDashboardSurfaceGrid.gradientColor,           config + POSITION_SURFACE_GRADIENT_COLOR,   sizeof (configDashboardSurfaceGrid.gradientColor));
  memcpy (&configDashboardSurfaceGrid.axisColor,               config + POSITION_SURFACE_AXIS_COLOR,       sizeof (configDashboardSurfaceGrid.axisColor));
  memcpy (&configDashboardSurfaceGrid.tickLabelColor,          config + POSITION_SURFACE_TICK_LABEL_COLOR, sizeof (configDashboardSurfaceGrid.tickLabelColor));
  memcpy (&configDashboardSurfaceGrid.xRotation,               config + POSITION_SURFACE_X_ROTATION,       sizeof (configDashboardSurfaceGrid.xRotation));
  memcpy (&configDashboardSurfaceGrid.yRotation,               config + POSITION_SURFACE_Y_ROTATION,       sizeof (configDashboardSurfaceGrid.yRotation));
  memcpy (&configDashboardSurfaceGrid.zRotation,               config + POSITION_SURFACE_Z_ROTATION,       sizeof (configDashboardSurfaceGrid.zRotation));
  memcpy (&configDashboardSurfaceGrid.surfaceScaling,          config + POSITION_SURFACE_SURFACE_SCALING,  sizeof (configDashboardSurfaceGrid.height));
  memcpy (&configDashboardSurfaceGrid.axisMinimum,             config + POSITION_SURFACE_AXIS_MINIMUM,     sizeof (configDashboardSurfaceGrid.axisMinimum));
  memcpy (&configDashboardSurfaceGrid.axisMaximum,             config + POSITION_SURFACE_AXIS_MAXIMUM,     sizeof (configDashboardSurfaceGrid.axisMaximum));

  configDashboardSurfaceGrid.showFill           = config[POSITION_SURFACE_ATTRIBUTES] & 0x01;
  configDashboardSurfaceGrid.showMesh           = config[POSITION_SURFACE_ATTRIBUTES] & 0x02;
  configDashboardSurfaceGrid.showXAxis          = config[POSITION_SURFACE_ATTRIBUTES] & 0x04;
  configDashboardSurfaceGrid.showYAxis          = config[POSITION_SURFACE_ATTRIBUTES] & 0x08;
  configDashboardSurfaceGrid.showZAxis          = config[POSITION_SURFACE_ATTRIBUTES] & 0x10;
  configDashboardSurfaceGrid.usePaletteColoring = config[POSITION_SURFACE_ATTRIBUTES] & 0x20;

  this->addSurfaceGrid (configDashboardSurfaceGrid, depthOfGrid, widhtOfGrid);
}

DataVisualizerDashboardSurfaceGrid DataVisualizerDashboard::addSurfaceGrid (ConfigDashboardSurfaceGrid config, uint8_t depthOfGrid, uint8_t widhtOfGrid) {
  DataVisualizerDashboardSurfaceGrid dashboardSurfaceGrid;

  if (!this->visualizer) return dashboardSurfaceGrid;
  if (!this->visualizer->handshake) return dashboardSurfaceGrid;

  uint16_t elementId = this->visualizer->index++;
  uint16_t streamId  = this->visualizer->index++;

  dashboardSurfaceGrid.visualizer = this->visualizer;
  dashboardSurfaceGrid.id         = streamId;

  MsgConfigDashboardElementSurface msgConfigDashboardElementSurface;
  msgConfigDashboardElementSurface.elementType                       = ELEMENT_TYPE_SURFACE;
  msgConfigDashboardElementSurface.dashboardId                       = this->id;
  msgConfigDashboardElementSurface.elementId                         = elementId;
  msgConfigDashboardElementSurface.zIndex                            = config.zIndex;
  msgConfigDashboardElementSurface.x                                 = config.x;
  msgConfigDashboardElementSurface.y                                 = config.y;
  msgConfigDashboardElementSurface.width                             = config.width;
  msgConfigDashboardElementSurface.height                            = config.height;
  msgConfigDashboardElementSurface.backgroundTransparency            = config.backgroundAlpha;
  msgConfigDashboardElementSurface.backgroundGradientTransparency    = config.gradientAlpha;
  msgConfigDashboardElementSurface.xRotation                         = config.xRotation;
  msgConfigDashboardElementSurface.yRotation                         = config.yRotation;
  msgConfigDashboardElementSurface.zRotation                         = config.zRotation;
  msgConfigDashboardElementSurface.attributes.bit.showFill           = config.showFill;
  msgConfigDashboardElementSurface.attributes.bit.showMesh           = config.showMesh;
  msgConfigDashboardElementSurface.attributes.bit.showXAxis          = config.showXAxis;
  msgConfigDashboardElementSurface.attributes.bit.showYAxis          = config.showYAxis;
  msgConfigDashboardElementSurface.attributes.bit.showZAxis          = config.showZAxis;
  msgConfigDashboardElementSurface.attributes.bit.usePaletteColoring = config.usePaletteColoring;
  msgConfigDashboardElementSurface.axisMinimum                       = config.axisMinimum;
  msgConfigDashboardElementSurface.axisMaximum                       = config.axisMaximum;
  msgConfigDashboardElementSurface.mode                              = config.surfaceScaling;
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.fillColor, config.fillColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.meshColor, config.meshColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.backgroundGradientColor, config.gradientColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.axisColor, config.axisColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementSurface.tickLabelColor, config.tickLabelColor);
  this->visualizer->protocol.addSurfaceToDashboard (&msgConfigDashboardElementSurface);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId                = streamId;
  msgConfigStream.type                    = STREAM_GRID;
  msgConfigStream.mode                    = STREAM_OUT;
  msgConfigStream.state                   = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, "Grid");

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->id;
  msgConfigAddStreamToElement.elementId   = elementId;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardSurfaceGrid;
}

DataVisualizerDashboardTable DataVisualizerDashboard::addTable (const uint8_t* config) {
  DataVisualizerDashboardTable dashboardTable;

  if (config[POSITION_TYPE] != DB_TYPE_TABLE) return dashboardTable;

  uint8_t length = strlen ( (const char*) (config + POSITION_TABLE_TEXT)) + 1;
  char text[length];
  memcpy (&text, config + POSITION_TABLE_TEXT, length);

  ConfigDashboardTable configDashboardTable;
  memcpy (&configDashboardTable.zIndex,                  config + POSITION_Z_INDEX,                           sizeof (configDashboardTable.zIndex));
  memcpy (&configDashboardTable.x,                       config + POSITION_X,                                 sizeof (configDashboardTable.x));
  memcpy (&configDashboardTable.y,                       config + POSITION_Y,                                 sizeof (configDashboardTable.y));
  memcpy (&configDashboardTable.width,                   config + POSITION_WIDTH,                             sizeof (configDashboardTable.width));
  memcpy (&configDashboardTable.height,                  config + POSITION_HEIGHT,                            sizeof (configDashboardTable.height));
  memcpy (&configDashboardTable.dataFontSize,            config + POSITION_TABLE_DATA_FONT_SIZE,              sizeof (configDashboardTable.dataFontSize));
  memcpy (&configDashboardTable.labelFontSize,           config + POSITION_TABLE_LABEL_FONT_SIZE,             sizeof (configDashboardTable.labelFontSize));
  memcpy (&configDashboardTable.dataWidth,               config + POSITION_TABLE_DATA_WIDTH,                  sizeof (configDashboardTable.dataWidth));
  memcpy (&configDashboardTable.labelWidth,              config + POSITION_TABLE_LABEL_WIDTH,                 sizeof (configDashboardTable.labelWidth));
  memcpy (&configDashboardTable.rowHeight,               config + POSITION_TABLE_ROW_HEIGHT,                  sizeof (configDashboardTable.rowHeight));
  memcpy (&configDashboardTable.numberOfRows,            config + POSITION_TABLE_NUMBER_OF_ROWS,              sizeof (configDashboardTable.numberOfRows));
  memcpy (&configDashboardTable.numberOfColumns,         config + POSITION_TABLE_NUMBER_OF_COLUMNS,           sizeof (configDashboardTable.numberOfColumns));
  memcpy (&configDashboardTable.autoLabels,              config + POSITION_TABLE_AUTO_LABELS,                 sizeof (configDashboardTable.autoLabels));
  memcpy (&configDashboardTable.labelHorizontalAligment, config + POSITION_TABLE_LABEL_HOZ_ALIGMENT + length, sizeof (configDashboardTable.labelHorizontalAligment));
  memcpy (&configDashboardTable.dataHorizontalAligment,  config + POSITION_TABLE_DATA_HOZ_ALIGMENT + length,  sizeof (configDashboardTable.dataHorizontalAligment));
  memcpy (&configDashboardTable.backgroundAlpha,         config + POSITION_TABLE_BACKGROUND_ALPHA + length,   sizeof (configDashboardTable.backgroundAlpha));
  memcpy (&configDashboardTable.foregroundAlpha,         config + POSITION_TABLE_FOREGROUND_ALPHA + length,   sizeof (configDashboardTable.foregroundAlpha));
  memcpy (&configDashboardTable.backgroundColor,         config + POSITION_TABLE_BACKGROUND_COLOR + length,   sizeof (configDashboardTable.backgroundColor));
  memcpy (&configDashboardTable.foregroundColor,         config + POSITION_TABLE_FOREGROUND_COLOR + length,   sizeof (configDashboardTable.foregroundColor));

  configDashboardTable.dataBold    = config[POSITION_TABLE_ATTRIBUTES + length] & 0x01;
  configDashboardTable.dataItalic  = config[POSITION_TABLE_ATTRIBUTES + length] & 0x02;
  configDashboardTable.labelBold   = config[POSITION_TABLE_ATTRIBUTES + length] & 0x04;
  configDashboardTable.labelItalic = config[POSITION_TABLE_ATTRIBUTES + length] & 0x08;

  return this->addTable (text, configDashboardTable);
}

DataVisualizerDashboardTable DataVisualizerDashboard::addTable (const char* text, ConfigDashboardTable config) {
  DataVisualizerDashboardTable dashboardTable;

  if (!this->visualizer) return dashboardTable;
  if (!this->visualizer->handshake) return dashboardTable;

  uint16_t elementId = this->visualizer->index++;

  dashboardTable.visualizer = this->visualizer;
  dashboardTable.dashboard  = this;
  dashboardTable.id         = elementId;
  dashboardTable.plotCount  = config.numberOfColumns * config.numberOfRows;

  MsgConfigDashboardElementTable msgConfigDashboardElementTable;
  msgConfigDashboardElementTable.elementType                = ELEMENT_TYPE_TABLE;
  msgConfigDashboardElementTable.dashboardId                = this->id;
  msgConfigDashboardElementTable.elementId                  = elementId;
  msgConfigDashboardElementTable.zIndex                     = config.zIndex;
  msgConfigDashboardElementTable.x                          = config.x;
  msgConfigDashboardElementTable.y                          = config.y;
  msgConfigDashboardElementTable.width                      = config.width;
  msgConfigDashboardElementTable.height                     = config.height;
  msgConfigDashboardElementTable.dataFontSize               = config.dataFontSize;
  msgConfigDashboardElementTable.labelFontSize              = config.labelFontSize;
  msgConfigDashboardElementTable.dataWidth                  = config.dataWidth;
  msgConfigDashboardElementTable.labelWidth                 = config.labelWidth;
  msgConfigDashboardElementTable.rowHeight                  = config.rowHeight;
  msgConfigDashboardElementTable.numberOfRows               = config.numberOfRows;
  msgConfigDashboardElementTable.numberOfColumns            = config.numberOfColumns;
  msgConfigDashboardElementTable.autoLabels                 = config.autoLabels;
  msgConfigDashboardElementTable.attributes.bit.dataBold    = config.dataBold;
  msgConfigDashboardElementTable.attributes.bit.dataItalic  = config.dataItalic;
  msgConfigDashboardElementTable.attributes.bit.labelBold   = config.labelBold;
  msgConfigDashboardElementTable.attributes.bit.labelItalic = config.labelItalic;
  msgConfigDashboardElementTable.labelHorizontalAligment    = config.labelHorizontalAligment;
  msgConfigDashboardElementTable.dataHorizontalAligment     = config.dataHorizontalAligment;
  msgConfigDashboardElementTable.backgroundTransparency     = config.backgroundAlpha;
  msgConfigDashboardElementTable.foregroundTransparency     = config.foregroundAlpha;
  this->visualizer->protocol.setColor (msgConfigDashboardElementTable.backgroundColor, config.backgroundColor);
  this->visualizer->protocol.setColor (msgConfigDashboardElementTable.foregroundColor, config.foregroundColor);
  this->visualizer->protocol.addTableToDashboard (&msgConfigDashboardElementTable, text);

  return dashboardTable;
}
