#include "DataVisualizerDashboardRadioGroup.h"

DataVisualizerDashboardRadioGroup::DataVisualizerDashboardRadioGroup(void) {
    this->id = 0;
    this->visualizer = 0;
    this->packet = 0;
}

uint8_t DataVisualizerDashboardRadioGroup::selected(void) {
    if(!this->visualizer) return 0;
    if(!this->visualizer->handshake) return 0;

    return this->packet->data[0];
}

bool DataVisualizerDashboardRadioGroup::feed(void) {
    if(!this->visualizer) return 0;
    if(!this->visualizer->handshake) return 0;

    if(this->packet->sent) {
        this->packet->sent = 0;

        return true;
    }

    return false;
}
