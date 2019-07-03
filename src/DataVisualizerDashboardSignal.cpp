#include "DataVisualizerDashboardSignal.h"

DataVisualizerDashboardSignal::DataVisualizerDashboardSignal(void) {
  this->id = 0;
  this->visualizer = 0;
}

void DataVisualizerDashboardSignal::on(void) {
  if (!this->visualizer) return;
  if (!this->visualizer->handshake) return;

  this->visualizer->write(this->id, (uint8_t*) true, 1);
}

void DataVisualizerDashboardSignal::off(void) {
  if (!this->visualizer) return;
  if (!this->visualizer->handshake) return;

  this->visualizer->write(this->id, (uint8_t*) false, 1);
}