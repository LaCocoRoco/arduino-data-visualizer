#ifndef DATA_VISUALIZER_DASHBOARD_TABLE_CELL_H
#define DATA_VISUALIZER_DASHBOARD_TABLE_CELL_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardTableCell {
  friend class DataVisualizerDashboardTable;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardTableCell (void);
  void write (int32_t value);
};

typedef DataVisualizerDashboardTableCell DashboardTableCell;

#endif /* DATA_VISUALIZER_DASHBOARD_TABLE_CELL_H */