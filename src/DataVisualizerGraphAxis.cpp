#include "DataVisualizerGraphAxis.h"

DataVisualizerGraphAxis::DataVisualizerGraphAxis(void) {
  this->id = 0;
  this->visualizer = 0;
  this->graph = 0;
}

DataVisualizerGraphAxisChannel DataVisualizerGraphAxis::addChannel(const char *label) {
  return this->addChannel(label, COLOR_RED);
}

DataVisualizerGraphAxisChannel DataVisualizerGraphAxis::addChannel(const char *label, RgbColor color) {
  DataVisualizerGraphAxisChannel channel;

  if (!this->visualizer) return channel;
  if (!this->visualizer->handshake) return channel;

  uint16_t streamId  = this->visualizer->index++;
  channel.visualizer = this->visualizer;
  channel.id         = streamId;

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults(&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream(&msgConfigStream, label);

  MsgAddStreamToAxis msgAddStreamToAxis;
  this->visualizer->protocol.configureStreamToAxisGetDefaults(&msgAddStreamToAxis);
  msgAddStreamToAxis.graphId  = this->graph->id;
  msgAddStreamToAxis.axisId   = this->id;
  msgAddStreamToAxis.streamId = streamId;
  this->visualizer->protocol.setColor(msgAddStreamToAxis.lineColor, color);
  this->visualizer->protocol.addStreamToAxis(&msgAddStreamToAxis);

  return channel;
}

DataVisualizerGraphAxisCursor DataVisualizerGraphAxis::addCursor(const char *label) {
  return this->addCursor(label, COLOR_GREEN);
}

DataVisualizerGraphAxisCursor DataVisualizerGraphAxis::addCursor(const char *label, RgbColor color) {
  DataVisualizerGraphAxisCursor cursor;

  if (!this->visualizer) return cursor;
  if (!this->visualizer->handshake) return cursor;

  uint16_t streamId = this->visualizer->index++;
  cursor.visualizer = this->visualizer;
  cursor.id         = streamId;
  cursor.packet     = this->visualizer->pack(streamId, LENGTH_4_BYTE);

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults(&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_IN;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream(&msgConfigStream, label);

  MsgAddCursorToGraph msgAddCursorToGraph;
  this->visualizer->protocol.configureCursorToGraphGetDefaults(&msgAddCursorToGraph);
  msgAddCursorToGraph.streamId         = streamId;
  msgAddCursorToGraph.graphId          = this->graph->id;
  msgAddCursorToGraph.axisId           = this->id;
  msgAddCursorToGraph.scaleNumerator   = 1;
  msgAddCursorToGraph.scaleDenominator = 1;
  this->visualizer->protocol.setColor(msgAddCursorToGraph.color, color);
  this->visualizer->protocol.addCursorToGraph(&msgAddCursorToGraph, label);

  return cursor;
}