#ifndef DATA_VISUALIZER_DASHBOARD_PIE_CHART_SLICE_H
#define DATA_VISUALIZER_DASHBOARD_PIE_CHART_SLICE_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardPieChartSlice {
  friend class DataVisualizerDashboardPieChart;


 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardPieChartSlice (void);
  void write (int32_t value);
};

typedef DataVisualizerDashboardPieChartSlice DashboardPieChartSlice;

#endif /* DATA_VISUALIZER_DASHBOARD_PIE_CHART_SLICE_H */