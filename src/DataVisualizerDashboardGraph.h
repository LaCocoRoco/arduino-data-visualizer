#ifndef DATA_VISUALIZER_DASHBOARD_GRAPH_H
#define DATA_VISUALIZER_DASHBOARD_GRAPH_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboard;
class DataVisualizerDashboardGraphChannel;
class DataVisualizerDashboardGraph {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  uint8_t plotCount;
  DataVisualizer* visualizer;
  DataVisualizerDashboard *dashboard;

 public:
  DataVisualizerDashboardGraph(void);
  DataVisualizerDashboardGraphChannel addChannel(const char* text);
};

typedef DataVisualizerDashboardGraph DashboardGraph;

#endif /* DATA_VISUALIZER_DASHBOARD_GRAPH_H */