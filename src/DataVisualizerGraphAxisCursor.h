#ifndef DATA_VISUALIZER_GRAPH_AXIS_CURSOR_H
#define DATA_VISUALIZER_GRAPH_AXIS_CURSOR_H

#include "DataVisualizer.h"

struct DataPacket;
class DataVisualizer;
class DataVisualizerGraphAxisCursor {
    friend class DataVisualizer;
    friend class DataVisualizerGraphAxis;

  private:
    uint16_t id;
    DataPacket* packet;
    DataVisualizer* visualizer;

  public:
    DataVisualizerGraphAxisCursor(void);
    int32_t read(void);
    bool feed(void);
};

typedef DataVisualizerGraphAxisCursor GraphAxisCursor;

#endif /* DATA_VISUALIZER_GRAPH_AXIS_CURSOR_H */