#include "DataVisualizerDashboardSurfaceGrid.h"

DataVisualizerDashboardSurfaceGrid::DataVisualizerDashboardSurfaceGrid (void) {
  this->id = 0;
  this->visualizer = 0;
}

void DataVisualizerDashboardSurfaceGrid::set (void) {
  if (!this->visualizer) return;
  if (!this->visualizer->handshake) return;
}

void DataVisualizerDashboardSurfaceGrid::update (void) {
  if (!this->visualizer) return;
  if (!this->visualizer->handshake) return;
}