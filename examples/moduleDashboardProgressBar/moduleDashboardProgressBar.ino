#include <DataVisualizer.h>

DashboardProgressBar dashboardProgressBar;

int tick, data;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");

    ConfigDashboardProgressBar configDashboardProgressBar;
    configDashboardProgressBar.zIndex  = 0;
    configDashboardProgressBar.x       = 50;
    configDashboardProgressBar.y       = 50;
    configDashboardProgressBar.width   = 200;
    configDashboardProgressBar.height  = 20;
    configDashboardProgressBar.minimum = 0;
    configDashboardProgressBar.maximum = 200;
    configDashboardProgressBar.value   = 100;
    configDashboardProgressBar.color   = COLOR_GREEN;

    dashboardProgressBar = dashboard.addProgressBar (configDashboardProgressBar);
  }

  /* write value to progress bar */
  if (tick++ > 500) {
    tick = 0;
    /* reset data if necessary */
    if (data++ > 200) data = 0;
    /* write data */
    dashboardProgressBar.write (data);
  }
}