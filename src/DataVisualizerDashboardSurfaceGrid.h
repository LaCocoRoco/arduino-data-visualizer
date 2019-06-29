#ifndef DATAV_ISUALIZER_DASHBOARD_SURFACE_GRID_H
#define DATAV_ISUALIZER_DASHBOARD_SURFACE_GRID_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardSurfaceGrid {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardSurfaceGrid(void);
  void set(void);
  void update(void);
};

typedef DataVisualizerDashboardSurfaceGrid DashboardSurfaceGrid;

#endif /* DATAV_ISUALIZER_DASHBOARD_SURFACE_GRID_H */