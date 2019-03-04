#include "DataVisualizerGraph.h"

DataVisualizerGraph::DataVisualizerGraph(void) {
    this->id = 0;
    this->visualizer = 0;
}

DataVisualizerGraphAxis DataVisualizerGraph::addAxis(const char *title) {
    return this->addAxis(title, COLOR_RED, DEFAULT_GRAPH_MIN, DEFAULT_GRAPH_MAX);
}

DataVisualizerGraphAxis DataVisualizerGraph::addAxis(const char *title, RgbColor color) {
    return this->addAxis(title, color, DEFAULT_GRAPH_MIN, DEFAULT_GRAPH_MAX);
}

DataVisualizerGraphAxis DataVisualizerGraph::addAxis(const char *title, RgbColor color, int32_t yMin, int32_t yMax) {
    DataVisualizerGraphAxis axis;

    if(!this->visualizer) return axis;
    if(!this->visualizer->handshake) return axis;

    uint16_t axisId = this->visualizer->index++;
    axis.visualizer = this->visualizer;
    axis.graph      = this;
    axis.id         = axisId;

    MsgConfigAxis msgConfigAxis;
    this->visualizer->protocol.addAxisToGraphGetDefaults(&msgConfigAxis);
    msgConfigAxis.graphId           = this->id;
    msgConfigAxis.axisId            = axisId;
    msgConfigAxis.yMin              = yMin;
    msgConfigAxis.yMax              = yMax;
    msgConfigAxis.xScaleNumerator   = 1;
    msgConfigAxis.xScaleDenominator = 1;
    this->visualizer->protocol.setColor(msgConfigAxis.color, color);
    this->visualizer->protocol.addAxisToGraph(&msgConfigAxis, title);

    return axis;
}