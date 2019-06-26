#include "DataVisualizerDashboardTable.h"

DataVisualizerDashboardTable::DataVisualizerDashboardTable (void) {
  this->id = 0;
  this->visualizer = 0;
  this->plotCount = 0;
}

DataVisualizerDashboardTableCell DataVisualizerDashboardTable::addCell (const char* text) {
  DataVisualizerDashboardTableCell dashboardTableCell;

  if (!this->visualizer) return dashboardTableCell;
  if (!this->visualizer->handshake) return dashboardTableCell;
  if (this->plotCount == 0) return dashboardTableCell;

  this->plotCount--;

  uint16_t streamId = this->visualizer->index++;

  dashboardTableCell.visualizer = this->visualizer;
  dashboardTableCell.id         = streamId;

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

  return dashboardTableCell;
}