#ifndef DATA_VISUALIZER_DASHBOARD_TABLE_H
#define DATA_VISUALIZER_DASHBOARD_TABLE_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboard;
class DataVisualizerDashboardTableCell;
class DataVisualizerDashboardTable {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  uint8_t plotCount;
  DataVisualizer* visualizer;
  DataVisualizerDashboard *dashboard;

 public:
  DataVisualizerDashboardTable (void);
  DataVisualizerDashboardTableCell addCell (const char* text);
};

typedef DataVisualizerDashboardTable DashboardTable;

#endif /* DATA_VISUALIZER_DASHBOARD_TABLE_H */