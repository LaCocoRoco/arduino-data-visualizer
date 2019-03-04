#include <DataVisualizer.h>

DashboardSignal dashboardSignal;

long tick;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    /****************************************************************/
    /* WARNING: Initializing elements blocks process.               */
    /****************************************************************/
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

        ConfigDashboardSignal configDashboardSignal = {
            .zIndex   = 0,
            .x        = 50,
            .y        = 50,
            .width    = 50,
            .height   = 50,
            .onColor  = COLOR_RED,
            .onAlpha  = 255,
            .offColor = COLOR_GREEN,
            .offAlpha = 255
        };

        dashboardSignal = dashboard.addSignal(configDashboardSignal);
    }

    tick++;

    if(tick > 2000) tick = 0;

    if(tick < 1000) {
        dashboardSignal.on();
    } else {
        dashboardSignal.off();
    }
}