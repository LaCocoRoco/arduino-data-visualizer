#ifndef DATAV_ISUALIZER_DASHBOARD_PROGRESS_BAR_H
#define DATAV_ISUALIZER_DASHBOARD_PROGRESS_BAR_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardProgressBar {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardProgressBar (void);
  void write (int32_t value);
};

typedef DataVisualizerDashboardProgressBar DashboardProgressBar;

#endif /* DATAV_ISUALIZER_DASHBOARD_PROGRESS_BAR_H */