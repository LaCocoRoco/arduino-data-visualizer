#ifndef DATA_VISUALIZER_DASHBOARD_SLIDER_H_
#define DATA_VISUALIZER_DASHBOARD_SLIDER_H_

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardSlider {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataPacket* packet;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardSlider (void);
  bool feed (void);
  int32_t read (void);
};

typedef DataVisualizerDashboardSlider DashboardSlider;

#endif /* DATA_VISUALIZER_DASHBOARD_SLIDER_H_ */