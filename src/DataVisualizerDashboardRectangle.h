#ifndef DATA_VISUALIZER_DASHBOARD_RECTANGLE_H
#define DATA_VISUALIZER_DASHBOARD_RECTANGLE_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardRectangle {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardRectangle(void);
};

typedef DataVisualizerDashboardRectangle DashboardRectangle;

#endif /* DATA_VISUALIZER_DASHBOARD_RECTANGLE_H */