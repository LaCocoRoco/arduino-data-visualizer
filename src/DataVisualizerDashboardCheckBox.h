#ifndef DATA_VISUALIZER_DASHBOARD_CHECK_BOX_H
#define DATA_VISUALIZER_DASHBOARD_CHECK_BOX_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardCheckBox {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataPacket* packet;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardCheckBox(void);
  bool pressed(void);
  bool selected(void);
};

typedef DataVisualizerDashboardCheckBox DashboardCheckBox;

#endif /* DATA_VISUALIZER_DASHBOARD_CHECK_BOX_H */