#include "AtmelDataProtocol.h"

AtmelDataProtocol::AtmelDataProtocol(void) {
    this->lastReceivedMessageId = ADP_TOKEN;
    this->packetReceived        = false;
    this->prevData              = 0;
}

void AtmelDataProtocol::addAtmelDataGateway(AtmelDataGateway* gateway) {
    this->gateway = gateway;
}

void AtmelDataProtocol::setColor(uint8_t *structMember, RgbColor color) {
    structMember[0] = color.red;
    structMember[1] = color.green;
    structMember[2] = color.blue;
}

void AtmelDataProtocol::configureStreamGetDefaults(MsgConfigStream *const config) {
    config->streamId = 0;
    config->type     = STREAM_UINT_8;
    config->mode     = STREAM_OUT;
    config->state    = STREAM_ON;
}

void AtmelDataProtocol::configureGraphGetDefaults(MsgConfigGraph *const config) {
    config->graphId           = 0;
    config->xMin              = 0;
    config->xMax              = 0;
    config->xScaleNumerator   = 0;
    config->xScaleDenominator = 0;
    /* Bug: Auto scaling results in bouncing y scale */
    config->scaleMode         = GRAPH_SCALE_OFF;
    /* Bug: Scroll by time not working */
    config->scrollMode        = GRAPH_SCROLL_SCROLL;
    setColor(config->backgroundColor, COLOR_BLACK);
}

void AtmelDataProtocol::addAxisToGraphGetDefaults(MsgConfigAxis *const config) {
    config->axisId            = 0;
    config->graphId           = 0;
    config->yMin              = 0;
    config->yMax              = 0;
    config->xScaleNumerator   = 0;
    config->xScaleDenominator = 0;
    config->mode              = 0;
    setColor(config->color, COLOR_BLACK);
}

void AtmelDataProtocol::addStreamToAxisGetDefaults(MsgAddStreamToAxis *const config) {
    config->graphId               = 0;
    config->axisId                = 0;
    config->streamId              = 0;
    config->sampleRateNumerator   = 0;
    config->sampleRateDenominator = 0;
    config->yScaleNumerator       = 0;
    config->yScaleDenominator     = 0;
    config->yOffset               = 0;
    config->transparency          = 0;
    config->mode                  = AXIS_LINE_bm;
    config->lineThickness         = 1;
    setColor(config->lineColor, COLOR_BLACK);
}

void AtmelDataProtocol::addCursorToGraphGetDefaults(MsgAddCursorToGraph *const config) {
    config->streamId         = 0;
    config->graphId          = 0;
    config->axisId           = 0;
    config->thickness        = 1;
    config->initialValue     = 0;
    config->minimumValue     = 0;
    config->maximumValue     = 0;
    config->scaleNumerator   = 0;
    config->scaleDenominator = 0;
    config->scaleOffset      = 0;
    config->lineStyle        = 0;
    setColor(config->color, COLOR_WHITE);
}

void AtmelDataProtocol::addGpioToGraphGetDefaults(MsgConfigGpioToGraph *const config) {
    config->graphId       = 0;
    config->gpioNumber    = 0;
    config->groupId       = 0;
    config->transparency  = 0;
    config->mode          = 0;
    config->lineThickness = 1;
    config->lineStyle     = 0;
    setColor(config->lineColorHighState, COLOR_WHITE);
    setColor(config->lineColorLowState, COLOR_WHITE);
}

void AtmelDataProtocol::configureTerminalGetDefaults(MsgConfigTerminal *const config) {
    config->terminalId  = 0;
    config->width       = 80;
    config->height      = 25;
    setColor(config->backgroundColor, COLOR_WHITE);
    setColor(config->foregroundColor, COLOR_BLACK);
}

void AtmelDataProtocol::addStreamToTerminalGetDefaults(MsgConfigAddStreamToTerminal *const config) {
    config->terminalId  = 0;
    config->streamId    = 0;
    config->mode        = 0;
    setColor(config->textColor, COLOR_BLACK);
    setColor(config->tagTextColor, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardGetDefaults(MsgConfigDahsboard *const config) {
    config->dashboardId = 0;
    config->height      = 100;
    setColor(config->color, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardElementGetDefaults(MsgConfigDashboardElementCommon *const config) {
    config->dashboardId = 0;
    config->elementId   = 0;
    config->zIndex      = 0;
    config->x           = 0;
    config->y           = 0;
    config->width       = 0;
    config->height      = 0;
}

void AtmelDataProtocol::configureDashboardLabelGetDefaults(MsgConfigDashboardElementLabel *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType            = ELEMENT_TYPE_LABEL;
    config->fontSize               = 10;
    config->attribute              = 0;
    config->horisontalAlignment    = HORISONTAL_ALIGNMENT_LEFT;
    config->verticalAlignment      = VERTICAL_ALIGNMENT_CENTER;
    config->backgroundTransparency = 0;
    config->foregroundTransparency = 0;
    setColor(config->backgroundColor, COLOR_BLACK);
    setColor(config->foregroundColor, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardButtonGetDefaults(MsgConfigDashboardElementButton *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType = ELEMENT_TYPE_BUTTON;
    config->fontSize    = 10;
    config->toggle      = 0;
}

void AtmelDataProtocol::configureDashboardTextGetDefaults(MsgConfigDashboardElementText *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType = ELEMENT_TYPE_TEXT;
    memset(config->minimum, 0, 4);
    memset(config->maximum, 0, 4);
    memset(config->value,   0, 4);
}

void AtmelDataProtocol::configureDashboardSliderGetDefaults(MsgConfigDashboardElementSlider *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType  = ELEMENT_TYPE_SLIDER;
    config->minimumValue = 0;
    config->maximumValue = 100;
    config->initialValue = 0;
}

void AtmelDataProtocol::configureDashboardSignalGetDefaults(MsgConfigDashboardElementSignal *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType     = ELEMENT_TYPE_SIGNAL;
    config->onTransparency  = 0;
    config->offTransparency = 0;
    setColor(config->onColor, COLOR_WHITE);
    setColor(config->offColor, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardPrograssGetDefaults(MsgConfigDashboardElementProgress *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elemntType   = ELEMENT_TYPE_PROGRESS;
    config->minimumValue = 0;
    config->maximumValue = 100;
    config->initialValue = 0;
    setColor(config->color, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardSegmentGetDefaults(MsgConfigDashboardElementSegment *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType   = ELEMENT_TYPE_SEGMENT;
    config->segmentCount  = 1;
    config->base          = 10;
    config->transparency  = 0;
    setColor(config->color, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardGraphGetDefaults(MsgConfigDashboardElementGraph *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType           = ELEMENT_TYPE_GRAPH;
    config->plotCount             = 1;
    config->xMin                  = 0;
    config->xMax                  = 10;
    config->yMin                  = 0;
    config->yMax                  = 5;
    config->mode.bit.autoscale    = 0;
    config->mode.bit.fitGraph     = 1;
    config->mode.bit.mouse        = 0;
    config->mode.bit.scrollByTime = 0;
    config->mode.bit.showPlot     = 0;
    config->mode.bit.showPoints   = 0;
    setColor(config->titleColor, COLOR_WHITE);
    setColor(config->backgroundColor, COLOR_BLACK);
    setColor(config->graphBackgroundColor, COLOR_BLACK);
}

void AtmelDataProtocol::configureDashboardRadioGetDefaults(MsgConfigDashboardElementRadio *const config) {
    configureDashboardElementGetDefaults((MsgConfigDashboardElementCommon *)config);
    config->elementType = ELEMENT_TYPE_RADIO;
    config->fontSize    = 10;
    config->numberItems = 1;
    config->orientation = HORIZONTAL;
}

uint16_t AtmelDataProtocol::addSendByte(uint8_t *buffer, uint8_t index, uint8_t *data, uint16_t length) {
    for(uint16_t i = 0; i < length; i++) {
        if(*(data + i) == ADP_TOKEN) {
            *(buffer + index) = ADP_TOKEN;
            index++;
        }
        *(buffer + index) = *(data + i);
        index++;
    }

    return index;
}

bool AtmelDataProtocol::addReceiveByte(uint8_t data) {
    static uint8_t messageId;

    if((rxState == RX_STATE_GOT_SYMBOL) && (data != ADP_TOKEN)) {
        /* Abort packet reception, new packet incoming */
        rxState = RX_STATE_WAIT_LENGTH_LSB;
    }

    switch(rxState) {
        case RX_STATE_IDLE:
            packetReceived          = false;
            lastReceivedMessageId = 0xFF;
            /* We are waiting for a new packet. */
            if(data != ADP_TOKEN) {
                return false;
            }
            /* Got start symbol, wait for message ID */
            rxState = RX_STATE_WAIT_MSG_ID;
            return false;

        case RX_STATE_WAIT_MSG_ID:
            if(data == ADP_TOKEN) {
                /* Restart. Don't change state. Wait for new message ID */
                return false;
            }
            messageId = data;
            rxState   = RX_STATE_WAIT_LENGTH_LSB;
            return false;

        case RX_STATE_WAIT_LENGTH_LSB:
            if(data == ADP_TOKEN) {
                if(prevData != ADP_TOKEN) {
                    prevData = ADP_TOKEN;
                    return false;
                }
            }
            lengthReceived = data;
            rxState        = RX_STATE_WAIT_LENGTH_MSB;
            prevData       = 0;
            return false;

        case RX_STATE_WAIT_LENGTH_MSB:
            if(data == ADP_TOKEN) {
                if(prevData != ADP_TOKEN) {
                    prevData = ADP_TOKEN;
                    return false;
                }
            }
            lengthReceived += (uint16_t)data << 8;
            prevData = 0;
            /* Got valid length, do we expect data? */
            if(lengthReceived == 0) {
                /* No data here, wait for next packet */
                rxState               = RX_STATE_IDLE;
                packetReceived        = true;
                lastReceivedMessageId = messageId;
                return false;
            }

            /* Wait for packet data */
            bytesReceived = 0;
            rxState       = RX_STATE_GET_DATA;
            return false;

        case RX_STATE_GET_DATA:
        case RX_STATE_GOT_SYMBOL:
            if((data == ADP_TOKEN) && (rxState == RX_STATE_GET_DATA)) {
                rxState = RX_STATE_GOT_SYMBOL;
                return false;
            }
            /* Add new data to rx buffer */
            bytesReceived++;
            /* Are we done yet? */

            if(bytesReceived >= lengthReceived || lengthReceived > MSG_RES_DATA_MAX_LEN) {
                /* Yes we are! */
                packetReceived        = true;
                rxState               = RX_STATE_IDLE;
                lastReceivedMessageId = messageId;
                return true;
            }
            /* Not done yet.. keep on receiving */
            rxState = RX_STATE_GET_DATA;
            return true;
    }
    return false;
}

bool AtmelDataProtocol::isReceived(void) {
    if(bytesReceived == 0) {
        return false;
    }
    return packetReceived;
}

uint8_t AtmelDataProtocol::packetReceiveGetId(void) {
    return lastReceivedMessageId;
}

bool AtmelDataProtocol::protocolAddByte(uint8_t rxId, uint8_t *rxBuffer, uint16_t rxLength, uint8_t *rxPacket, uint16_t rxPacketLength) {
    uint8_t i;

    for(i = 0; i < rxLength; i++) {
        if(addReceiveByte(*(rxBuffer + i)) == true) {
            /* This is a data byte */
            rxPacketBuffer[bytesReceived - 1] = *(rxBuffer + i);
        }

        if(isReceived() && (packetReceiveGetId() == rxId)) {
            memcpy(rxPacket, rxPacketBuffer, rxPacketLength);
            memset(rxPacketBuffer, 0, MSG_RES_DATA_PACKET_MAX_LEN);

            return true;
        }
    }

    return false;
}

bool AtmelDataProtocol::checkForResponse(uint8_t rxId, uint8_t *rxPacket, uint16_t rxPacketLength) {
    uint16_t txLength = rxPacketLength + ADP_LENGTH_PACKET_HEADER;
    uint8_t  retry    = ADP_CHECK_FOR_RESPONSE_RETRYS;

    uint8_t rxBuffer[txLength];
    memset(rxBuffer, 0, txLength);

    rxState        = RX_STATE_IDLE;
    packetReceived = false;
    memset(rxPacketBuffer, 0, MSG_RES_DATA_PACKET_MAX_LEN);

    while(!isReceived() & (retry-- > 0)) {
        uint16_t rxLength = this->gateway->receive(rxBuffer, txLength);
        if(protocolAddByte(rxId, rxBuffer, rxLength, rxPacket, rxPacketLength)) return true;
    }

    return false;
}

void AtmelDataProtocol::waitForResponse(uint8_t rxId, uint8_t *rxPacket, uint16_t rxPacketLength) {
    uint16_t txLength = rxPacketLength + ADP_LENGTH_PACKET_HEADER;

    uint8_t rxBuffer[txLength];
    memset(rxBuffer, 0, txLength);

    rxState        = RX_STATE_IDLE;
    packetReceived = false;
    memset(rxPacketBuffer, 0, MSG_RES_DATA_PACKET_MAX_LEN);

    while(!isReceived()) {
        uint16_t rxLength = this->gateway->receive(rxBuffer, txLength);
        protocolAddByte(rxId, rxBuffer, rxLength, rxPacket, rxPacketLength);
    }
}

bool AtmelDataProtocol::requestHandshake(uint8_t protocolVersion, uint8_t options, uint8_t *rxPacket) {
    uint16_t txLength = MSQ_REQ_HANDSHAKE_LEN + ADP_LENGTH_PACKET_HEADER;
    uint8_t  key[8]    = ADP_HANDSHAKE_KEY;

    MsgFormat           msgFormat;
    MsgRequestHandshake msgRequestHandshake;

    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_REQ_HANDSHAKE;
    msgFormat.dataLength    = MSQ_REQ_HANDSHAKE_LEN;

    msgRequestHandshake.protocolVersion = ADP_VERSION;
    msgRequestHandshake.options         = HANDSHAKE_OPTIONS_GPIO;

    memcpy(&msgRequestHandshake.key, key, 8);
    memcpy((uint8_t *)&msgFormat.data, &msgRequestHandshake, sizeof(msgRequestHandshake));

    /* Send the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_RES_HANDSHAKE;
    uint16_t rxPacketLength = 1;

    return checkForResponse(rxId, rxPacket, rxPacketLength);
}

HandshakeStatus AtmelDataProtocol::waitForHandshake(void) {
    uint8_t handshake_status;

    /* Keep sending handshake until we get something back */
    while(!requestHandshake(ADP_VERSION, 0, &handshake_status));

    /* Return status */
    return ((HandshakeStatus)handshake_status);
}

StatusCode AtmelDataProtocol::requestStatus(void) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_REQ_STATUS;
    msgFormat.dataLength    = MSG_REQ_STATUS_LEN;

    uint16_t tx_length = MSG_REQ_STATUS_LEN + ADP_LENGTH_PACKET_HEADER;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, tx_length);

    uint8_t  rxId = MSG_RES_STATUS;
    uint16_t rxPacket;
    uint16_t rxPacketLength = 2;

    /* Wait for response from PC */
    waitForResponse(rxId, (uint8_t *)&rxPacket, rxPacketLength);

    return ((StatusCode)rxPacket);
}

uint16_t AtmelDataProtocol::verifyDataLength(uint16_t length) {
    return length <= ADP_MAX_PROTOCOL_LEN ? length : ADP_MAX_PROTOCOL_LEN;
}

bool AtmelDataProtocol::configureInfo(const char *title, const char *description) {
    /* Add null-termination to length */
    uint16_t titleLength       = strlen(title) + 1;
    uint16_t descriptionLength = strlen(description) + 1;

    /* Make sure the strings are not too long */
    uint16_t dataLength = verifyDataLength(MSG_CONF_INFO_LEN + titleLength + descriptionLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_INFO;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)title, titleLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)description, descriptionLength);

    uint16_t tx_length = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, tx_length);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::configureStream(MsgConfigStream *const config, const char *label) {
    /* Add null-termination to length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure the strings are not too long */
    uint16_t dataLength = verifyDataLength(MSG_CONF_STREAM_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_STREAM;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->type, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->state, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);

    uint16_t tx_length = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, tx_length);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::toggleStream(MsgToggleStream *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_TOGGLE_STREAM;
    msgFormat.dataLength    = MSG_CONF_TOGGLE_STREAM_LEN;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->state, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}


bool AtmelDataProtocol::configureGraph(MsgConfigGraph *const config, const char *graphLabel, const char *xLabel) {
    /* Add 0-termination to label string length */
    uint16_t graphLabelLength = strlen(graphLabel) + 1;
    uint16_t xLabelLength     = strlen(xLabel) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_GRAPH_LEN + graphLabelLength + xLabelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_GRAPH;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)graphLabel, graphLabelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xMin, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xMax, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)xLabel, xLabelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xScaleNumerator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xScaleDenominator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->scaleMode, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->scrollMode, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::configureTerminal(MsgConfigTerminal *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_TERMINAL_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_TERMINAL;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->terminalId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->width, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->height, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->foregroundColor, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addStreamToTerminal(MsgConfigAddStreamToTerminal *const config, const char *tagText) {
    /* Add 0-termination to label string length */
    uint16_t tagTextLength = strlen(tagText) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_ADD_TO_TERMINAL_LEN + tagTextLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_ADD_TO_TERMINAL;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->terminalId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->textColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)tagText, tagTextLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->tagTextColor, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addAxisToGraph(MsgConfigAxis *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_AXIS_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_AXIS;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->axisId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yMin, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yMax, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xScaleNumerator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xScaleDenominator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->color, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addStreamToAxis(MsgAddStreamToAxis *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_ADD_STREAM_TO_AXIS;
    msgFormat.dataLength    = MSG_CONF_ADD_STREAM_TO_AXIS_LEN;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->axisId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->sampleRateNumerator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->sampleRateDenominator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yScaleNumerator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yScaleDenominator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yOffset, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->transparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineThickness, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)ADP_BUG_FIX, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addCursorToGraph(MsgAddCursorToGraph *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_CURSOR_TO_GRAPH_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_CURSOR_TO_GRAPH;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->axisId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->thickness, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->color, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->initialValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->minimumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->maximumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->scaleNumerator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->scaleDenominator, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->scaleOffset, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineStyle, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addGpioToGraph(MsgConfigGpioToGraph *const config, const char *tagHighState, const char *tagLowState) {
    /* Add 0-termination to label string length */
    uint16_t tagHighStateLength = strlen(tagHighState) + 1;
    uint16_t tagLowStateLength  = strlen(tagLowState) + 1;
    uint16_t labelLength        = tagHighStateLength + tagLowStateLength;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_GPIO_TO_GRAPH_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_GPIO_TO_GRAPH;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->gpioNumber, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphId, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)tagHighState, tagHighStateLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)tagLowState, tagLowStateLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->transparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineThickness, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineColorHighState, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineColorLowState, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->lineStyle, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addDashboard(MsgConfigDahsboard *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(MSG_CONF_DASHBOARD_LEN + labelLength);

    MsgFormat msgFormat;

    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->dashboardId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->color, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->height, 2);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

uint16_t AtmelDataProtocol::addSendByteDashboard(uint8_t *addBuffer, uint16_t index, MsgConfigDashboardElementCommon *const config) {
    index = addSendByte(addBuffer, index, (uint8_t *)&config->dashboardId, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->elementId, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->zIndex, 1);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->x, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->y, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->width, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->height, 2);
    index = addSendByte(addBuffer, index, (uint8_t *)&config->elementType, 1);

    return index;
}

bool AtmelDataProtocol::addLabelToDashboard(MsgConfigDashboardElementLabel *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(ELEMENT_TYPE_LABEL_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->fontSize, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->attribute, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->horisontalAlignment, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->verticalAlignment, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundTransparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->foregroundTransparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->foregroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addButtonToDashboard(MsgConfigDashboardElementButton *const config, const char *label) {
    /* Add 0-termination to label string length */
    uint16_t labelLength = strlen(label) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(ELEMENT_TYPE_BUTTON_LEN + labelLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->fontSize, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)label, labelLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->toggle, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Send the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addSliderToDashboard(MsgConfigDashboardElementSlider *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = ELEMENT_TYPE_SLIDER_LEN;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->minimumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->maximumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->initialValue, 4);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addProgressToDashboard(MsgConfigDashboardElementProgress *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = ELEMENT_TYPE_PROGRESS_LEN;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->minimumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->maximumValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->initialValue, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->color, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Send the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addSignalToDashboard(MsgConfigDashboardElementSignal *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = ELEMENT_TYPE_SIGNAL_LEN;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->onTransparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->onColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->offTransparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->offColor, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addSegmentToDashboard(MsgConfigDashboardElementSegment *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = ELEMENT_TYPE_SEGMENT_LEN;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->segmentCount, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->base, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->transparency, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->color, 3);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addGraphToDashboard(MsgConfigDashboardElementGraph *const config, const char *title) {
    /* Add 0-termination to label string length */
    uint16_t titleLength = strlen(title) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(ELEMENT_TYPE_GRAPH_LEN + titleLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->titleColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->graphBackgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)title, titleLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->plotCount, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xMin, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->xMax, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yMin, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->yMax, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->mode, 2);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addTextToDashboard(MsgConfigDashboardElementText *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = ELEMENT_TYPE_TEXT_LEN;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->minimum, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->maximum, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->value, 4);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)ADP_BUG_FIX, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addRadioToDashboard(MsgConfigDashboardElementRadio *const config, const char *text) {
    /* Add 0-termination to label string length */
    uint16_t textLength = strlen(text) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(ELEMENT_TYPE_RADIO_LEN + textLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->fontSize, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->numberItems, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->orientation, 1);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)text, textLength);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addPieToDashboard(MsgConfigDashboardElementPie *const config, const char *title) {
    /* Add 0-termination to label string length */
    uint16_t titleLength = strlen(title) + 1;

    /* Make sure label isn't too big */
    uint16_t dataLength = verifyDataLength(ELEMENT_TYPE_PIE_LEN + titleLength);

    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_DASHBOARD_ELEMENT;
    msgFormat.dataLength    = dataLength;

    uint16_t index = 0;

    index = addSendByteDashboard((uint8_t *)&msgFormat.data, index, (MsgConfigDashboardElementCommon *)config);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->backgroundColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->titleColor, 3);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)title, titleLength);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->numberSlices, 1);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::addStreamToElement(MsgConfigAddStreamToElement *const config) {
    MsgFormat msgFormat;
    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_CONF_ADD_STREAM_TO_ELEMENT;
    msgFormat.dataLength    = MSG_CONF_ADD_STREAM_TO_ELEMENT_LEN;

    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->dashboardId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->elementId, 2);
    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&config->streamId, 2);

    uint16_t txLength = ADP_LENGTH_PACKET_HEADER + index;

    /* Transmit the protocol packet data */
    this->gateway->transmit((uint8_t *)&msgFormat, txLength);

    uint8_t  rxId = MSG_CONF_ACK;
    uint8_t  rxPacket;
    uint16_t rxPacketLength = 1;

    /* Wait for response and return status */
    waitForResponse(rxId, &rxPacket, rxPacketLength);

    return (rxPacket == ACK_OK);
}

bool AtmelDataProtocol::transceiveStream(MsgDataStream *const streamData, uint8_t *rxPacket) {
    MsgFormat msgFormat;

    uint16_t dataLength = 1;
    uint16_t index = 0;

    index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&streamData->numberOfStreams, 1);

    for(uint8_t stream_num = 0; stream_num < streamData->numberOfStreams; stream_num++) {
        index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&streamData->stream[stream_num].streamId, 2);
        index = addSendByte((uint8_t *)&msgFormat.data, index, (uint8_t *)&streamData->stream[stream_num].dataSize, 1);
        index = addSendByte((uint8_t *)&msgFormat.data, index, streamData->stream[stream_num].data, streamData->stream[stream_num].dataSize);
        /* 2 bytes stream.stream_id and 1 byte stream.data_size */
        dataLength += 2 + 1 + streamData->stream[stream_num].dataSize;
    }

    msgFormat.protocolToken = ADP_TOKEN;
    msgFormat.protocolMsgId = MSG_DATA_STREAM;
    msgFormat.dataLength    = dataLength;

    uint16_t txrxLength     = ADP_LENGTH_PACKET_HEADER + index;
    uint16_t rxPacketLength = MSG_RES_DATA_PACKET_MAX_LEN;
    uint8_t  rxId           = MSG_RES_DATA;

    uint8_t rxBuffer[txrxLength];
    memset(rxBuffer, 0, txrxLength);

    /* Transmit and receive protocol packet data */
    uint16_t rxLength = this->gateway->transceive((uint8_t *)&msgFormat, rxBuffer, txrxLength);

    return protocolAddByte(rxId, rxBuffer, rxLength, rxPacket, rxPacketLength);
}

bool AtmelDataProtocol::transceiveSingleStream(uint16_t streamId, uint8_t *data, uint8_t dataSize, uint8_t *rxPacket) {
    MsgDataStream msgDataStream;

    msgDataStream.numberOfStreams    = 1;
    msgDataStream.stream[0].streamId = streamId;
    msgDataStream.stream[0].dataSize = dataSize;
    msgDataStream.stream[0].data     = data;

    uint8_t status = transceiveStream(&msgDataStream, rxPacket);

    return status;
}

bool AtmelDataProtocol::receivePacketData(uint8_t *rxPacket) {
    uint16_t rxPacketLength = MSG_RES_DATA_PACKET_MAX_LEN;
    uint8_t  txrxLength     = MSG_RES_DATA_REQUEST;
    uint8_t  rxId           = MSG_RES_DATA;

    uint8_t rxBuffer[txrxLength];
    memset(rxBuffer, 0, txrxLength);

    /* Transmit and receive protocol packet data */
    uint16_t rxLength = this->gateway->receive(rxBuffer, txrxLength);

    return protocolAddByte(rxId, rxBuffer, rxLength, rxPacket, rxPacketLength);
}