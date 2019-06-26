#include "DataVisualizerDashboardSegmentDisplay.h"

DataVisualizerDashboardSegmentDisplay::DataVisualizerDashboardSegmentDisplay (void) {
  this->id = 0;
  this->visualizer = 0;
}

void DataVisualizerDashboardSegmentDisplay::write (int32_t value) {
  if (!this->visualizer) return;
  if (!this->visualizer->handshake) return;

  this->visualizer->write (this->id, (uint8_t*) &value, sizeof (int32_t));
}