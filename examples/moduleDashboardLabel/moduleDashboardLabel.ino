#include <DataVisualizer.h>

Terminal terminal;

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

    ConfigDashboardLabel configDashboardLabel;
    configDashboardLabel.zIndex             = 0;
    configDashboardLabel.x                  = 50;
    configDashboardLabel.y                  = 50;
    configDashboardLabel.width              = 100;
    configDashboardLabel.height             = 25;
    configDashboardLabel.fontSize           = 20;
    configDashboardLabel.bolt               = false;
    configDashboardLabel.italic             = false;
    configDashboardLabel.aligmentHorizontal = HORIZONTAL_ALIGNMENT_CENTER;
    configDashboardLabel.aligmentVertical   = VERTICAL_ALIGNMENT_CENTER;
    configDashboardLabel.backgroundColor    = COLOR_WHITE;
    configDashboardLabel.backgroundAlpha    = 0;
    configDashboardLabel.foregroundColor    = COLOR_BLACK;
    configDashboardLabel.foregroundAlpha    = 255;

    dashboard.addLabel("MyLabel", configDashboardLabel);
  }
}