#ifndef DATA_VISUALIZER_GRAPH_AXIS_H
#define DATA_VISUALIZER_GRAPH_AXIS_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerGraph;
class DataVisualizerGraphAxisChannel;
class DataVisualizerGraphAxisCursor;
class DataVisualizerGraphAxis {
  friend class DataVisualizer;
  friend class DataVisualizerGraph;

 private:
  uint16_t id;
  DataVisualizer* visualizer;
  DataVisualizerGraph* graph;

 public:
  DataVisualizerGraphAxis(void);
  DataVisualizerGraphAxisChannel addChannel(const char *label);
  DataVisualizerGraphAxisChannel addChannel(const char *label, RgbColor color);
  DataVisualizerGraphAxisCursor addCursor(const char *label);
  DataVisualizerGraphAxisCursor addCursor(const char *label, RgbColor color);
};

typedef DataVisualizerGraphAxis GraphAxis;

#endif /* DATA_VISUALIZER_GRAPH_AXIS_H */