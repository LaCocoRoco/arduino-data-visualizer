#ifndef DATA_VISUALIZER_DASHBOARD_PIE_CHART_H
#define DATA_VISUALIZER_DASHBOARD_PIE_CHART_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboard;
class DataVisualizerDashboardPieChartSlice;
class DataVisualizerDashboardPieChart {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  uint8_t plotCount;
  DataVisualizer* visualizer;
  DataVisualizerDashboard *dashboard;

 public:
  DataVisualizerDashboardPieChart (void);
  DataVisualizerDashboardPieChartSlice addSlice (const char* text);
};

typedef DataVisualizerDashboardPieChart DashboardPieChart;

#endif /* DATA_VISUALIZER_DASHBOARD_PIE_CHART_H */