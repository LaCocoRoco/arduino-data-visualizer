#include "DataVisualizerDashboardPieChart.h"

DataVisualizerDashboardPieChart::DataVisualizerDashboardPieChart (void) {
  this->id = 0;
  this->visualizer = 0;
}

DataVisualizerDashboardPieChartSlice DataVisualizerDashboardPieChart::addSlice (const char* text) {
  DataVisualizerDashboardPieChartSlice dashboardPieChartSlice;

  if (!this->visualizer) return dashboardPieChartSlice;
  if (!this->visualizer->handshake) return dashboardPieChartSlice;
  if (this->plotCount == 0) return dashboardPieChartSlice;

  this->plotCount--;

  uint16_t streamId = this->visualizer->index++;

  dashboardPieChartSlice.visualizer = this->visualizer;
  dashboardPieChartSlice.id         = streamId;

  MsgConfigStream msgConfigStream;
  this->visualizer->protocol.configureStreamGetDefaults (&msgConfigStream);
  msgConfigStream.streamId = streamId;
  msgConfigStream.type     = STREAM_INT_32;
  msgConfigStream.mode     = STREAM_OUT;
  msgConfigStream.state    = STREAM_ON;
  this->visualizer->protocol.addStream (&msgConfigStream, text);

  MsgConfigAddStreamToElement msgConfigAddStreamToElement;
  msgConfigAddStreamToElement.dashboardId = this->dashboard->id;
  msgConfigAddStreamToElement.elementId   = this->id;
  msgConfigAddStreamToElement.streamId    = streamId;
  this->visualizer->protocol.addStreamToElement (&msgConfigAddStreamToElement);

  return dashboardPieChartSlice;
}