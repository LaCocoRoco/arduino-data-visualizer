#ifndef DATA_VISUALIZER_DASHBOARD_LABEL_H
#define DATA_VISUALIZER_DASHBOARD_LABEL_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardLabel {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardLabel (void);
};

typedef DataVisualizerDashboardLabel DashboardLabel;

#endif /* DATA_VISUALIZER_DASHBOARD_LABEL_H */