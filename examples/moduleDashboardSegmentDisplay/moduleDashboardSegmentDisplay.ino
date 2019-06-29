#include <DataVisualizer.h>

DashboardSegmentDisplay dashboardSegmentDisplay;

int tick, data;

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

    ConfigDashboardSegmentDisplay configDashboardSegmentDisplay;
    configDashboardSegmentDisplay.zIndex = 0;
    configDashboardSegmentDisplay.x      = 50;
    configDashboardSegmentDisplay.y      = 50;
    configDashboardSegmentDisplay.width  = 25;
    configDashboardSegmentDisplay.height = 25;
    configDashboardSegmentDisplay.digits = 2;
    configDashboardSegmentDisplay.base   = BASE_DEC;
    configDashboardSegmentDisplay.color  = COLOR_RED;
    configDashboardSegmentDisplay.alpha  = 255;

    dashboardSegmentDisplay = dashboard.addSegmentDisplay(configDashboardSegmentDisplay);
  }

  /* write value to segment display */
  if (tick++ > 5000) {
    tick = 0;
    /* reset data if necessary */
    if (data++ > 99) data = 0;
    /* write data */
    dashboardSegmentDisplay.write(data);
  }
}