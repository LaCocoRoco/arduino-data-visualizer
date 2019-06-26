#ifndef DATAV_ISUALIZER_DASHBOARD_SIGNAL_H
#define DATAV_ISUALIZER_DASHBOARD_SIGNAL_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardSignal {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardSignal (void);
  void on (void);
  void off (void);
};

typedef DataVisualizerDashboardSignal DashboardSignal;

#endif /* DATAV_ISUALIZER_DASHBOARD_SIGNAL_H */