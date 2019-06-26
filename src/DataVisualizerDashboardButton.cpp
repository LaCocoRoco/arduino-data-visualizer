#include "DataVisualizerDashboardButton.h"

DataVisualizerDashboardButton::DataVisualizerDashboardButton (void) {
  this->id = 0;
  this->toggle = 0;
  this->visualizer = 0;
  this->packet = 0;
}

bool DataVisualizerDashboardButton::pressed (void) {
  if (!this->visualizer) return 0;
  if (!this->visualizer->handshake) return 0;

  if (this->packet->sent) {
    if (this->packet->data[0]) {
      this->toggle = true;
    } else {
      this->toggle = false;
    }
    this->packet->data[0] = 0;
    this->packet->sent = 0;
    return true;
  }

  return false;
}

bool DataVisualizerDashboardButton::toggled (void) {
  this->pressed();
  return this->toggle;
}