#ifndef DATA_VISUALIZER_DASHBOARD_RADIO_GROUP_H
#define DATA_VISUALIZER_DASHBOARD_RADIO_GROUP_H

#include "DataVisualizer.h"

class DataVisualizer;
class DataVisualizerDashboardRadioGroup {
    friend class DataVisualizerDashboard;

  private:
    uint16_t id;
    DataPacket* packet;
    DataVisualizer* visualizer;

  public:
    DataVisualizerDashboardRadioGroup(void);
    uint8_t selected(void);
    bool feed(void);
};

typedef DataVisualizerDashboardRadioGroup DashboardRadioGroup;

#endif /* DATA_VISUALIZER_DASHBOARD_RADIO_GROUP_H */