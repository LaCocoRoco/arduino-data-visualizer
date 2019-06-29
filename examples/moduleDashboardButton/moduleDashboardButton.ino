#include <DataVisualizer.h>

Terminal terminal;
DashboardButton dashboardButton;

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
    terminal = Visualizer.addTerminal("My Terminal");

    ConfigDashboardButton configDashboardButton;
    configDashboardButton.zIndex   = 0;
    configDashboardButton.x        = 50;
    configDashboardButton.y        = 50;
    configDashboardButton.width    = 150;
    configDashboardButton.height   = 50;
    configDashboardButton.fontSize = 20;

    dashboardButton = dashboard.addButton("My Button", configDashboardButton);
  }

  /* send button pressed to terminal*/
  if (dashboardButton.pressed()) {
    terminal.println("My Button Pressed");
  }
}