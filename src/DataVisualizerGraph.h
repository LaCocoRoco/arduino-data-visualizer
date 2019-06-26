#ifndef DATA_VISUALIZER_GRAPH_H
#define DATA_VISUALIZER_GRAPH_H

#include "DataVisualizer.h"

#define DEFAULT_GRAPH_MIN     -32767
#define DEFAULT_GRAPH_MAX     +32767

class DataVisualizer;
class DataVisualizerGraphAxis;
class DataVisualizerGraph {
  friend class DataVisualizer;
  friend class DataVisualizerGraphAxis;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerGraph (void);
  DataVisualizerGraphAxis addAxis (const char *title);
  DataVisualizerGraphAxis addAxis (const char *title, RgbColor color);
  DataVisualizerGraphAxis addAxis (const char *title, RgbColor color, int32_t yMin, int32_t yMax);
};

typedef DataVisualizerGraph Graph;

#endif /* DATA_VISUALIZER_GRAPH_H */