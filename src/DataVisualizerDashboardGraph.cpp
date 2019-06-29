#include "DataVisualizerDashboardGraph.h"

DataVisualizerDashboardGraph::DataVisualizerDashboardGraph(void) {
  this->id = 0;
  this->visualizer = 0;
}

DataVisualizerDashboardGraphChannel DataVisualizerDashboardGraph::addChannel(const char* text) {
  DataVisualizerDashboardGraphChannel dashboardGraphChannel;

  if (!this->visualizer) return dashboardGraphChannel;
  if (!this->visualizer->handshake) return dashboardGraphChannel;
  if (this->plotCount == 0) return dashboardGraphChannel;

  this->plotCount--;

  uint16_t streamId = this->visualizer->index++;

  dashboardGraphChannel.visualizer = this->visualizer;
  dashboardGraphChannel.id         = streamId;

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults(&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream(&msgConfigStream, text);

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->dashboard->id;
  msgConfigAddStreamToElement.elementId   = this->id;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement(&msgConfigAddStreamToElement);

  return dashboardGraphChannel;
}