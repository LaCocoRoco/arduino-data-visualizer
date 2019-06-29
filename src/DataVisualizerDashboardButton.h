#ifndef DATA_VISUALIZER_DASHBOARD_BUTTON_H
#define DATA_VISUALIZER_DASHBOARD_BUTTON_H

#include "DataVisualizer.h"

struct DataPacket;
class DataVisualizer;
class DataVisualizerDashboardButton {
  friend class DataVisualizerDashboard;

 private:
  bool toggle;
  uint16_t id;
  DataPacket* packet;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardButton(void);
  bool pressed(void);
  bool toggled(void);
};

typedef DataVisualizerDashboardButton DashboardButton;

#endif /* DATA_VISUALIZER_DASHBOARD_BUTTON_H */