#include "DataVisualizerDashboardSlider.h"

DataVisualizerDashboardSlider::DataVisualizerDashboardSlider(void) {
  this->id = 0;
  this->visualizer = 0;
  this->packet = 0;
}

bool DataVisualizerDashboardSlider::feed(void) {
  if (!this->visualizer) return 0;
  if (!this->visualizer->handshake) return 0;

  if (this->packet->sent) {
    this->packet->sent = 0;

    return true;
  }

  return false;
}

int32_t DataVisualizerDashboardSlider::read(void) {
  if (!this->visualizer) return 0;
  if (!this->visualizer->handshake) return 0;

  int32_t value;
  memcpy(&value, this->packet->data, LENGTH_4_BYTE);
  return value;
}
