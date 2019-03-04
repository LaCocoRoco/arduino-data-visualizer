#include "DataVisualizerDashboard.h"

DataVisualizerDashboard::DataVisualizerDashboard(void) {
    this->id = 0;
    this->visualizer = 0;
}

DataVisualizerDashboardLabel DataVisualizerDashboard::addLabel(const uint8_t* config) {
    DataVisualizerDashboardLabel dashboardLabel;

    if(config[POSITION_TYPE] != DB_TYPE_LABEL) return dashboardLabel;

    uint8_t length = strlen((const char*)(config + POSITION_LABEL_TEXT)) + 1;
    char text[length];
    memcpy(&text, config + POSITION_LABEL_TEXT, length);

    ConfigDashboardLabel configDashboardLabel;
    memcpy(&configDashboardLabel.zIndex,             config + POSITION_Z_INDEX,                sizeof(configDashboardLabel.zIndex));
    memcpy(&configDashboardLabel.x,                  config + POSITION_X,                      sizeof(configDashboardLabel.x));
    memcpy(&configDashboardLabel.y,                  config + POSITION_Y,                      sizeof(configDashboardLabel.y));
    memcpy(&configDashboardLabel.width,              config + POSITION_WIDTH,                  sizeof(configDashboardLabel.width));
    memcpy(&configDashboardLabel.height,             config + POSITION_HEIGHT,                 sizeof(configDashboardLabel.height));
    memcpy(&configDashboardLabel.fontSize,           config + POSITION_LABEL_FONT,             sizeof(configDashboardLabel.fontSize));
    memcpy(&configDashboardLabel.backgroundAlpha,    config + POSITION_LABEL_ALPHA_BACKGROUND, sizeof(configDashboardLabel.backgroundAlpha));
    memcpy(&configDashboardLabel.forgroundAlpha,     config + POSITION_LABEL_ALPHA_FOREGROUND, sizeof(configDashboardLabel.forgroundAlpha));
    memcpy(&configDashboardLabel.attribute,          config + POSITION_LABEL_ATTRIBUTE,        sizeof(configDashboardLabel.attribute));
    memcpy(&configDashboardLabel.aligmentHorisontal, config + POSITION_LABEL_HOR_ALIG,         sizeof(configDashboardLabel.aligmentHorisontal));
    memcpy(&configDashboardLabel.aligmentVertical,   config + POSITION_LABEL_VER_ALIG,         sizeof(configDashboardLabel.aligmentVertical));
    memcpy(&configDashboardLabel.backgroundColor,    config + POSITION_LABEL_COLOR_BACKGROUND, sizeof(configDashboardLabel.backgroundColor));
    memcpy(&configDashboardLabel.forgroundColor,     config + POSITION_LABEL_COLOR_FOREGROUND, sizeof(configDashboardLabel.forgroundColor));

    this->addLabel(text, configDashboardLabel);
}

DataVisualizerDashboardLabel DataVisualizerDashboard::addLabel(const char* text, ConfigDashboardLabel config) {
    DataVisualizerDashboardLabel dashboardLabel;

    if(!this->visualizer) return dashboardLabel;
    if(!this->visualizer->handshake) return dashboardLabel;

    uint16_t elementId = this->visualizer->index++;

    dashboardLabel.visualizer = this->visualizer;
    dashboardLabel.id         = elementId;

    MsgConfigDashboardElementLabel msgConfigDashboardElementLabel;
    this->visualizer->protocol.configureDashboardLabelGetDefaults(&msgConfigDashboardElementLabel);
    msgConfigDashboardElementLabel.elementType            = ELEMENT_TYPE_LABEL;
    msgConfigDashboardElementLabel.dashboardId            = this->id;
    msgConfigDashboardElementLabel.elementId              = elementId;
    msgConfigDashboardElementLabel.zIndex                 = config.zIndex;
    msgConfigDashboardElementLabel.x                      = config.x;
    msgConfigDashboardElementLabel.y                      = config.y;
    msgConfigDashboardElementLabel.width                  = config.width;
    msgConfigDashboardElementLabel.height                 = config.height;
    msgConfigDashboardElementLabel.fontSize               = config.fontSize;
    msgConfigDashboardElementLabel.attribute              = config.attribute;
    msgConfigDashboardElementLabel.horisontalAlignment    = config.aligmentHorisontal;
    msgConfigDashboardElementLabel.verticalAlignment      = config.aligmentVertical;
    msgConfigDashboardElementLabel.backgroundTransparency = config.backgroundAlpha;
    msgConfigDashboardElementLabel.foregroundTransparency = config.forgroundAlpha;
    this->visualizer->protocol.setColor(msgConfigDashboardElementLabel.backgroundColor, config.backgroundColor);
    this->visualizer->protocol.setColor(msgConfigDashboardElementLabel.foregroundColor, config.forgroundColor);
    this->visualizer->protocol.addLabelToDashboard(&msgConfigDashboardElementLabel, text);

    return dashboardLabel;
}

DataVisualizerDashboardNumericInput DataVisualizerDashboard::addNumericInput(const uint8_t* config) {
    DataVisualizerDashboardNumericInput dashboardNumericInput;

    if(config[POSITION_TYPE] != DB_TYPE_TEXT) return dashboardNumericInput;

    ConfigDashboardNumericInput configDashboardNumericInput;
    memcpy(&configDashboardNumericInput.zIndex,  config + POSITION_Z_INDEX,      sizeof(configDashboardNumericInput.zIndex));
    memcpy(&configDashboardNumericInput.x,       config + POSITION_X,            sizeof(configDashboardNumericInput.x));
    memcpy(&configDashboardNumericInput.y,       config + POSITION_Y,            sizeof(configDashboardNumericInput.y));
    memcpy(&configDashboardNumericInput.width,   config + POSITION_WIDTH,        sizeof(configDashboardNumericInput.width));
    memcpy(&configDashboardNumericInput.height,  config + POSITION_HEIGHT,       sizeof(configDashboardNumericInput.height));
    memcpy(&configDashboardNumericInput.minimum, config + POSITION_TEXT_MINIMUM, sizeof(configDashboardNumericInput.minimum));
    memcpy(&configDashboardNumericInput.maximum, config + POSITION_TEXT_MAXIMUM, sizeof(configDashboardNumericInput.maximum));
    memcpy(&configDashboardNumericInput.value,   config + POSITION_TEXT_VALUE,   sizeof(configDashboardNumericInput.value));

    return this->addNumericInput(configDashboardNumericInput);
}

DataVisualizerDashboardNumericInput DataVisualizerDashboard::addNumericInput(ConfigDashboardNumericInput config) {
    DataVisualizerDashboardNumericInput dashboardNumericInput;

    if(!this->visualizer) return dashboardNumericInput;
    if(!this->visualizer->handshake) return dashboardNumericInput;

    uint16_t elementId = this->visualizer->index++;
    uint16_t streamId  = this->visualizer->index++;

    dashboardNumericInput.visualizer = this->visualizer;
    dashboardNumericInput.id         = elementId;
    dashboardNumericInput.packet     = this->visualizer->pack(streamId, LENGTH_4_BYTE);
    memcpy(dashboardNumericInput.packet->data, &config.value, LENGTH_4_BYTE);

    MsgConfigDashboardElementText msgConfigDashboardElementText;
    this->visualizer->protocol.configureDashboardTextGetDefaults(&msgConfigDashboardElementText);
    msgConfigDashboardElementText.elementType = ELEMENT_TYPE_TEXT;
    msgConfigDashboardElementText.dashboardId = this->id;
    msgConfigDashboardElementText.elementId   = elementId;
    msgConfigDashboardElementText.zIndex      = config.zIndex;
    msgConfigDashboardElementText.x           = config.x;
    msgConfigDashboardElementText.y           = config.y;
    msgConfigDashboardElementText.width       = config.width;
    msgConfigDashboardElementText.height      = config.height;
    memcpy(msgConfigDashboardElementText.minimum, &config.minimum, LENGTH_4_BYTE);
    memcpy(msgConfigDashboardElementText.maximum, &config.maximum, LENGTH_4_BYTE);
    memcpy(msgConfigDashboardElementText.value,   &config.value,   LENGTH_4_BYTE);
    this->visualizer->protocol.addTextToDashboard(&msgConfigDashboardElementText);

    MsgConfigStream msgConfigStream;
    msgConfigStream.streamId = streamId;
    msgConfigStream.type     = STREAM_INT_32;
    msgConfigStream.mode     = STREAM_IN;
    msgConfigStream.state    = STREAM_ON;
    this->visualizer->protocol.configureStream(&msgConfigStream, "NumericInput");

    MsgConfigAddStreamToElement msgConfigAddStreamToElement;
    msgConfigAddStreamToElement.dashboardId = this->id;
    msgConfigAddStreamToElement.elementId   = elementId;
    msgConfigAddStreamToElement.streamId    = streamId;
    this->visualizer->protocol.addStreamToElement(&msgConfigAddStreamToElement);

    return dashboardNumericInput;
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton(const char* text, ConfigDashboardButton config) {
    return this->addButton(text, config, VARIANT_TOGGLED_OFF);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton(const char* textOn, const char* textOff, ConfigDashboardButton config) {

    uint8_t length = strlen(textOn) + strlen(textOff) + 2;

    const char delimiter[] = "/";
    char text[length];

    strcat(text, textOn);
    strcat(text, delimiter);
    strcat(text, textOff);

    return this->addButton(text, config, VARIANT_TOGGLED_ON);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton(const uint8_t* config) {
    DataVisualizerDashboardButton dashboardButton;

    if(config[POSITION_TYPE] != DB_TYPE_BUTTON) return dashboardButton;

    uint8_t length = strlen((const char*)(config + POSITION_BUTTON_TEXT)) + 1;
    char text[length];
    memcpy(&text, config + POSITION_BUTTON_TEXT, length);

    ConfigDashboardButton configDashboardButton;
    memcpy(&configDashboardButton.zIndex,   config + POSITION_Z_INDEX,          sizeof(configDashboardButton.zIndex));
    memcpy(&configDashboardButton.x,        config + POSITION_X,                sizeof(configDashboardButton.x));
    memcpy(&configDashboardButton.y,        config + POSITION_Y,                sizeof(configDashboardButton.y));
    memcpy(&configDashboardButton.width,    config + POSITION_WIDTH,            sizeof(configDashboardButton.width));
    memcpy(&configDashboardButton.height,   config + POSITION_HEIGHT,           sizeof(configDashboardButton.height));
    memcpy(&configDashboardButton.fontSize, config + POSITION_BUTTON_FONT_SIZE, sizeof(configDashboardButton.fontSize));

    uint8_t toggle = config[POSITION_BUTTON_TEXT + length];

    return this->addButton(text, configDashboardButton, toggle);
}

DataVisualizerDashboardButton DataVisualizerDashboard::addButton(const char* text, ConfigDashboardButton config, uint8_t toggle) {
    DataVisualizerDashboardButton dashboardButton;

    if(!this->visualizer) return dashboardButton;
    if(!this->visualizer->handshake) return dashboardButton;

    uint16_t elementId = this->visualizer->index++;
    uint16_t streamId  = this->visualizer->index++;

    dashboardButton.visualizer = this->visualizer;
    dashboardButton.id         = elementId;
    dashboardButton.packet     = this->visualizer->pack(streamId, LENGTH_1_BYTE);

    MsgConfigDashboardElementButton msgConfigDashboardElementButton;
    this->visualizer->protocol.configureDashboardButtonGetDefaults(&msgConfigDashboardElementButton);
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
    this->visualizer->protocol.addButtonToDashboard(&msgConfigDashboardElementButton, text);

    MsgConfigStream msgConfigStream;
    msgConfigStream.streamId = streamId;
    msgConfigStream.type     = STREAM_UINT_8;
    msgConfigStream.mode     = STREAM_IN;
    msgConfigStream.state    = STREAM_ON;
    this->visualizer->protocol.configureStream(&msgConfigStream, "Button");

    MsgConfigAddStreamToElement msgConfigAddStreamToElement;
    msgConfigAddStreamToElement.dashboardId = this->id;
    msgConfigAddStreamToElement.elementId   = elementId;
    msgConfigAddStreamToElement.streamId    = streamId;
    this->visualizer->protocol.addStreamToElement(&msgConfigAddStreamToElement);

    return dashboardButton;
}

DataVisualizerDashboardSignal DataVisualizerDashboard::addSignal(const uint8_t* config) {
    DataVisualizerDashboardSignal dashboardSignal;

    if(config[POSITION_TYPE] != DB_TYPE_SIGNAL) return dashboardSignal;

    ConfigDashboardSignal configDashboardSignal;
    memcpy(&configDashboardSignal.zIndex,   config + POSITION_Z_INDEX,          sizeof(configDashboardSignal.zIndex));
    memcpy(&configDashboardSignal.x,        config + POSITION_X,                sizeof(configDashboardSignal.x));
    memcpy(&configDashboardSignal.y,        config + POSITION_Y,                sizeof(configDashboardSignal.y));
    memcpy(&configDashboardSignal.width,    config + POSITION_WIDTH,            sizeof(configDashboardSignal.width));
    memcpy(&configDashboardSignal.height,   config + POSITION_HEIGHT,           sizeof(configDashboardSignal.height));
    memcpy(&configDashboardSignal.onAlpha,  config + POSITION_SIGNAL_ALPHA_ON,  sizeof(configDashboardSignal.onAlpha));
    memcpy(&configDashboardSignal.offAlpha, config + POSITION_SIGNAL_ALPHA_OFF, sizeof(configDashboardSignal.offAlpha));
    memcpy(&configDashboardSignal.onColor,  config + POSITION_SIGNAL_COLOR_ON,  sizeof(configDashboardSignal.onColor));
    memcpy(&configDashboardSignal.offColor, config + POSITION_SIGNAL_COLOR_OFF, sizeof(configDashboardSignal.offColor));

    return this->addSignal(configDashboardSignal);
}

DataVisualizerDashboardSignal DataVisualizerDashboard::addSignal(ConfigDashboardSignal config) {
    DataVisualizerDashboardSignal dashboardSignal;

    if(!this->visualizer) return dashboardSignal;
    if(!this->visualizer->handshake) return dashboardSignal;

    uint16_t elementId = this->visualizer->index++;
    uint16_t streamId  = this->visualizer->index++;

    dashboardSignal.visualizer = this->visualizer;
    dashboardSignal.id         = streamId;

    MsgConfigDashboardElementSignal msgConfigCashboardElementSignal;
    this->visualizer->protocol.configureDashboardSignalGetDefaults(&msgConfigCashboardElementSignal);
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
    this->visualizer->protocol.setColor(msgConfigCashboardElementSignal.onColor, config.onColor);
    this->visualizer->protocol.setColor(msgConfigCashboardElementSignal.offColor, config.offColor);
    this->visualizer->protocol.addSignalToDashboard(&msgConfigCashboardElementSignal);

    MsgConfigStream msgConfigStream;
    msgConfigStream.streamId = streamId;
    msgConfigStream.type     = STREAM_UINT_8;
    msgConfigStream.mode     = STREAM_OUT;
    msgConfigStream.state    = STREAM_ON;
    this->visualizer->protocol.configureStream(&msgConfigStream, "Signal");

    MsgConfigAddStreamToElement msgConfigAddStreamToElement;
    msgConfigAddStreamToElement.dashboardId = this->id;
    msgConfigAddStreamToElement.elementId   = elementId;
    msgConfigAddStreamToElement.streamId    = streamId;
    this->visualizer->protocol.addStreamToElement(&msgConfigAddStreamToElement);

    return dashboardSignal;
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup(const uint8_t* config) {
    DataVisualizerDashboardRadioGroup dashboardRadioGroup;

    if(config[POSITION_TYPE] != DB_TYPE_RADIOGROUP) return dashboardRadioGroup;

    uint8_t length = strlen((const char*)(config + POSITION_RADIOGROUP_TEXT)) + 1;
    char text[length];
    memcpy(&text, config + POSITION_RADIOGROUP_TEXT, length);

    ConfigDashboardRadioGroup configDashboardRadioGroup;
    memcpy(&configDashboardRadioGroup.zIndex,      config + POSITION_Z_INDEX,                 sizeof(configDashboardRadioGroup.zIndex));
    memcpy(&configDashboardRadioGroup.x,           config + POSITION_X,                       sizeof(configDashboardRadioGroup.x));
    memcpy(&configDashboardRadioGroup.y,           config + POSITION_Y,                       sizeof(configDashboardRadioGroup.y));
    memcpy(&configDashboardRadioGroup.width,       config + POSITION_WIDTH,                   sizeof(configDashboardRadioGroup.width));
    memcpy(&configDashboardRadioGroup.height,      config + POSITION_HEIGHT,                  sizeof(configDashboardRadioGroup.height));
    memcpy(&configDashboardRadioGroup.sizeItems,   config + POSITION_RADIOGROUP_SIZE_ITEMS,   sizeof(configDashboardRadioGroup.sizeItems));
    memcpy(&configDashboardRadioGroup.numberItems, config + POSITION_RADIOGROUP_NUMBER_ITEMS, sizeof(configDashboardRadioGroup.numberItems));
    memcpy(&configDashboardRadioGroup.orientation, config + POSITION_RADIOGROUP_ORIENTATION,  sizeof(configDashboardRadioGroup.orientation));

    return this->addRadioGroup(text, configDashboardRadioGroup);
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup(ConfigDashboardRadioGroup config) {
    config.numberItems = config.numberItems > RADIOGROUP_MAX ? RADIOGROUP_MAX : config.numberItems;

    char text[config.numberItems];
    for(uint8_t i = 0; i < config.numberItems; i++) text[i] = '/';

    return this->addRadioGroup(text, config);
}

DataVisualizerDashboardRadioGroup DataVisualizerDashboard::addRadioGroup(const char* text, ConfigDashboardRadioGroup config) {
    DataVisualizerDashboardRadioGroup dashboardRadioGroup;

    if(!this->visualizer) return dashboardRadioGroup;
    if(!this->visualizer->handshake) return dashboardRadioGroup;

    uint16_t elementId = this->visualizer->index++;
    uint16_t streamId  = this->visualizer->index++;

    dashboardRadioGroup.visualizer = this->visualizer;
    dashboardRadioGroup.id         = elementId;
    dashboardRadioGroup.packet     = this->visualizer->pack(streamId, LENGTH_1_BYTE);

    MsgConfigDashboardElementRadio msgConfigDashboardElementRadio;
    this->visualizer->protocol.configureDashboardRadioGetDefaults(&msgConfigDashboardElementRadio);
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
    this->visualizer->protocol.addRadioToDashboard(&msgConfigDashboardElementRadio, text);

    MsgConfigStream msgConfigStream;
    msgConfigStream.streamId = streamId;
    msgConfigStream.type     = STREAM_UINT_8;
    msgConfigStream.mode     = STREAM_IN;
    msgConfigStream.state    = STREAM_ON;
    this->visualizer->protocol.configureStream(&msgConfigStream, "RadioGroup");

    MsgConfigAddStreamToElement msgConfigAddStreamToElement;
    msgConfigAddStreamToElement.dashboardId = this->id;
    msgConfigAddStreamToElement.elementId   = elementId;
    msgConfigAddStreamToElement.streamId    = streamId;
    this->visualizer->protocol.addStreamToElement(&msgConfigAddStreamToElement);

    return dashboardRadioGroup;
}

DataVisualizerDashboardGraph DataVisualizerDashboard::addGraph(uint8_t* config) {
    DataVisualizerDashboardGraph dashboardGraph;

    if(config[POSITION_TYPE] != DB_TYPE_GRAPH) return dashboardGraph;

    uint8_t length = strlen((const char*)(config + POSITION_GRAPH_TEXT)) + 1;
    char text[length];
    memcpy(&text, config + POSITION_GRAPH_TEXT, length);

    ConfigDashboardGraph configDashboardGraph;
    memcpy(&configDashboardGraph.zIndex,          config + POSITION_Z_INDEX,                   sizeof(configDashboardGraph.zIndex));
    memcpy(&configDashboardGraph.x,               config + POSITION_X,                         sizeof(configDashboardGraph.x));
    memcpy(&configDashboardGraph.y,               config + POSITION_Y,                         sizeof(configDashboardGraph.y));
    memcpy(&configDashboardGraph.width,           config + POSITION_WIDTH,                     sizeof(configDashboardGraph.width));
    memcpy(&configDashboardGraph.height,          config + POSITION_HEIGHT,                    sizeof(configDashboardGraph.height));
    memcpy(&configDashboardGraph.plotCount,       config + POSITION_GRAPH_PLOT_COUNT + length, sizeof(configDashboardGraph.plotCount));
    memcpy(&configDashboardGraph.xMinimum,        config + POSITION_GRAPH_X_MINIMUM  + length, sizeof(configDashboardGraph.xMinimum));
    memcpy(&configDashboardGraph.xMaximum,        config + POSITION_GRAPH_X_MAXIMUM  + length, sizeof(configDashboardGraph.xMaximum));
    memcpy(&configDashboardGraph.yMinimum,        config + POSITION_GRAPH_Y_MINIMUM  + length, sizeof(configDashboardGraph.yMinimum));
    memcpy(&configDashboardGraph.yMaximum,        config + POSITION_GRAPH_Y_MAXIMUM  + length, sizeof(configDashboardGraph.yMaximum));
    memcpy(&configDashboardGraph.titleColor,      config + POSITION_GRAPH_COLOR_TITLE,         sizeof(configDashboardGraph.titleColor));
    memcpy(&configDashboardGraph.backgroundColor, config + POSITION_GRAPH_COLOR_BACKGROUND,    sizeof(configDashboardGraph.backgroundColor));
    memcpy(&configDashboardGraph.graphColor,      config + POSITION_GRAPH_COLOR_GRAPH,         sizeof(configDashboardGraph.graphColor));

    configDashboardGraph.mouseInteraction = config[POSITION_GRAPH_MODE_LB + length] & 0x01;
    configDashboardGraph.fitToRight       = config[POSITION_GRAPH_MODE_LB + length] & 0x02;
    configDashboardGraph.autoscale        = config[POSITION_GRAPH_MODE_LB + length] & 0x04;
    configDashboardGraph.scrollByTime     = config[POSITION_GRAPH_MODE_LB + length] & 0x08;
    configDashboardGraph.showPlot         = config[POSITION_GRAPH_MODE_HB + length] & 0x01;
    configDashboardGraph.showPoints       = config[POSITION_GRAPH_MODE_HB + length] & 0x02;

    return this->addGraph(text, configDashboardGraph);
}

DataVisualizerDashboardGraph DataVisualizerDashboard::addGraph(const char* text, ConfigDashboardGraph config) {
    DataVisualizerDashboardGraph dashboardGraph;

    if(!this->visualizer) return dashboardGraph;
    if(!this->visualizer->handshake) return dashboardGraph;

    uint16_t elementId = this->visualizer->index++;

    dashboardGraph.visualizer = this->visualizer;
    dashboardGraph.dashboard  = this;
    dashboardGraph.id         = elementId;
    dashboardGraph.plotCount  = config.plotCount;

    MsgConfigDashboardElementGraph msgConfigDashboardElementGraph;
    this->visualizer->protocol.configureDashboardGraphGetDefaults(&msgConfigDashboardElementGraph);
    msgConfigDashboardElementGraph.elementType           = ELEMENT_TYPE_GRAPH;
    msgConfigDashboardElementGraph.dashboardId           = this->id;
    msgConfigDashboardElementGraph.elementId             = elementId;
    msgConfigDashboardElementGraph.zIndex                = config.zIndex;
    msgConfigDashboardElementGraph.x                     = config.x;
    msgConfigDashboardElementGraph.y                     = config.y;
    msgConfigDashboardElementGraph.width                 = config.width;
    msgConfigDashboardElementGraph.height                = config.height;
    msgConfigDashboardElementGraph.plotCount             = config.plotCount;
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
    this->visualizer->protocol.setColor(msgConfigDashboardElementGraph.titleColor, config.titleColor);
    this->visualizer->protocol.setColor(msgConfigDashboardElementGraph.backgroundColor, config.backgroundColor);
    this->visualizer->protocol.setColor(msgConfigDashboardElementGraph.graphBackgroundColor, config.graphColor);
    this->visualizer->protocol.addGraphToDashboard(&msgConfigDashboardElementGraph, text);

    return dashboardGraph;
}