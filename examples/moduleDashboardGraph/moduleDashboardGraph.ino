#include <DataVisualizer.h>

DashboardGraphChannel dashboardGraphChannel;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

        ConfigDashboardGraph configDashboardGraph = {
            .zIndex           = 0,
            .x                = 50,
            .y                = 50,
            .width            = 400,
            .height           = 200,
            .titleColor       = COLOR_WHITE,
            .backgroundColor  = COLOR_BLACK,
            .graphColor       = COLOR_BLACK,
            .plotCount        = 1,
            .xMinimum         = 0,
            .xMaximum         = 10,
            .yMinimum         = -1000,
            .yMaximum         = +1000,
            .mouseInteraction = true,
            .fitToRight       = false,
            .autoscale        = false,
            .scrollByTime     = true,
            .showPlot         = true,
            .showPoints       = false
        };

        DashboardGraph dashboardGraph = dashboard.addGraph("My Graph", configDashboardGraph);

        dashboardGraphChannel = dashboardGraph.addChannel("My Channel");
    }

    dashboardGraphChannel.write(500);
}