#ifndef DATA_VISUALIZER_DASHBOARD_GRAPH_CHANNEL_H
#define DATA_VISUALIZER_DASHBOARD_GRAPH_CHANNEL_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardGraphChannel {
  friend class DataVisualizerDashboardGraph;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardGraphChannel(void);
  void write(int32_t value);
};

typedef DataVisualizerDashboardGraphChannel DashboardGraphChannel;

#endif /* DATA_VISUALIZER_DASHBOARD_GRAPH_CHANNEL_H */