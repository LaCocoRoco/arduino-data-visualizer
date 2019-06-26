#include <DataVisualizer.h>

Terminal terminal;
DashboardRadioGroup dashboardRadioGroup;

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

    ConfigDashboardRadioGroup configDashboardRadioGroup = {
      configDashboardRadioGroup.zIndex      = 0;
      configDashboardRadioGroup.x           = 50;
      configDashboardRadioGroup.y           = 50;
      configDashboardRadioGroup.width       = 15;
      configDashboardRadioGroup.height      = 150;
      configDashboardRadioGroup.sizeItems   = 10;
      configDashboardRadioGroup.numberItems = 6;
      configDashboardRadioGroup.orientation = VERTICAL;

      dashboardRadioGroup = dashboard.addRadioGroup (configDashboardRadioGroup);
    }

    /* send selected radio group to terminal */
    if (dashboardRadioGroup.pressed()) {
      terminal.println (dashboardRadioGroup.selected());
    }
  }