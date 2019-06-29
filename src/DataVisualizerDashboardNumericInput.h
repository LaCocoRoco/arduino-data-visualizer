#ifndef DATA_VISUALIZER_DASHBOARD_NUMERIC_INPUT_H
#define DATA_VISUALIZER_DASHBOARD_NUMERIC_INPUT_H

#include "DataVisualizer.h"

struct DataPacket;
class DataVisualizer;
class DataVisualizerDashboardNumericInput {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataPacket* packet;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardNumericInput(void);
  bool feed(void);
  int32_t read(void);
};

typedef DataVisualizerDashboardNumericInput DashboardNumericInput;

#endif /* DATA_VISUALIZER_DASHBOARD_NUMERIC_INPUT_H */