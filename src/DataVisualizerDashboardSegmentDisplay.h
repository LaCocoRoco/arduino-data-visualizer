#ifndef DATAV_VISUALIZER_DASHBOARD_SEGMENT_DISPLAY_H
#define DATAV_VISUALIZER_DASHBOARD_SEGMENT_DISPLAY_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardSegmentDisplay {
  friend class DataVisualizerDashboard;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerDashboardSegmentDisplay (void);
  void write (int32_t value);
};

typedef DataVisualizerDashboardSegmentDisplay DashboardSegmentDisplay;

#endif /* DATAV_VISUALIZER_DASHBOARD_SEGMENT_DISPLAY_H */