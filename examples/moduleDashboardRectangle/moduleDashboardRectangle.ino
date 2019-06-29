#include <DataVisualizer.h>

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

    ConfigDashboardRectangle configDashboardRectangle;
    configDashboardRectangle.zIndex          = 0;
    configDashboardRectangle.x               = 50;
    configDashboardRectangle.y               = 50;
    configDashboardRectangle.width           = 100;
    configDashboardRectangle.height          = 25;
    configDashboardRectangle.backgroundColor = COLOR_BLACK;
    configDashboardRectangle.backgroundAlpha = 255;
    configDashboardRectangle.foregroundColor = COLOR_WHITE;
    configDashboardRectangle.foregroundAlpha = 0;

    DashboardRectangle dashboardRectangle = dashboard.addRectangle(configDashboardRectangle);
  }
}