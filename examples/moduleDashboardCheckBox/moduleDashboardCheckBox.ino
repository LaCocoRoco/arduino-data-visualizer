#include <DataVisualizer.h>

Terminal terminal;
DashboardCheckBox dashboardCheckBox;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");
    terminal = Visualizer.addTerminal ("My Terminal");

    ConfigDashboardCheckBox configDashboardCheckBox;
    configDashboardCheckBox.zIndex   = 0;
    configDashboardCheckBox.x        = 50;
    configDashboardCheckBox.y        = 50;
    configDashboardCheckBox.width    = 100;
    configDashboardCheckBox.height   = 25;
    configDashboardCheckBox.fontSize = 12;

    dashboardCheckBox = dashboard.addCheckBox ("My CheckBox", configDashboardCheckBox);
  }

  /* send check box state to terminal */
  if (dashboardCheckBox.pressed()) {
    if (dashboardCheckBox.selected()) {
      terminal.println ("My CheckBox selected");
    } else {
      terminal.println ("My CheckBox unselected");
    }
  }
}