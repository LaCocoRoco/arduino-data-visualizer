#ifndef DATA_VISUALIZER_GRAPH_AXIS_CHANNEL_H
#define DATA_VISUALIZER_GRAPH_AXIS_CHANNEL_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerGraphAxisChannel {
  friend class DataVisualizer;
  friend class DataVisualizerGraphAxis;

 private:
  uint16_t id;
  DataVisualizer* visualizer;

 public:
  DataVisualizerGraphAxisChannel (void);
  void write (int32_t value);
};

typedef DataVisualizerGraphAxisChannel GraphAxisChannel;

#endif /* DATA_VISUALIZER_GRAPH_AXIS_CHANNEL_H */