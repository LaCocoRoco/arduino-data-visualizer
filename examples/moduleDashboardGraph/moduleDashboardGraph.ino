#include <DataVisualizer.h>

DashboardGraphChannel dashboardGraphChannelA;
DashboardGraphChannel dashboardGraphChannelB;

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

    ConfigDashboardGraph configDashboardGraph;
    configDashboardGraph.zIndex           = 0;
    configDashboardGraph.x                = 50;
    configDashboardGraph.y                = 50;
    configDashboardGraph.width            = 400;
    configDashboardGraph.height           = 200;
    configDashboardGraph.titleColor       = COLOR_WHITE;
    configDashboardGraph.backgroundColor  = COLOR_BLACK;
    configDashboardGraph.graphColor       = COLOR_BLACK;
    configDashboardGraph.numberChannels   = 2;
    configDashboardGraph.xMinimum         = 0;
    configDashboardGraph.xMaximum         = 10;
    configDashboardGraph.yMinimum         = -1000;
    configDashboardGraph.yMaximum         = +1000;
    configDashboardGraph.mouseInteraction = true;
    configDashboardGraph.fitToRight       = false;
    configDashboardGraph.autoscale        = false;
    configDashboardGraph.scrollByTime     = true;
    configDashboardGraph.showPlot         = true;
    configDashboardGraph.showPoints       = false;

    DashboardGraph dashboardGraph = dashboard.addGraph("My Graph", configDashboardGraph);

    dashboardGraphChannelA = dashboardGraph.addChannel("My Channel A");
    dashboardGraphChannelB = dashboardGraph.addChannel("My Channel B");
  }

  /* send data to graph channel */
  dashboardGraphChannelA.write(+500);
  dashboardGraphChannelB.write(-500);
}