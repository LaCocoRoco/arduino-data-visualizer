#include <DataVisualizer.h>

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    /****************************************************************/
    /* WARNING: Initializing elements blocks process.               */
    /****************************************************************/
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
    }
}