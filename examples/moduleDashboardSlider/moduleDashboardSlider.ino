#include <DataVisualizer.h>

Terminal terminal;
DashboardSlider dashboardSlider;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process.               */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");
    terminal = Visualizer.addTerminal ("My Terminal");

    ConfigDashboardSlider configDashboardSlider;
    configDashboardSlider.zIndex  = 0;
    configDashboardSlider.x       = 50;
    configDashboardSlider.y       = 50;
    configDashboardSlider.width   = 200;
    configDashboardSlider.height  = 25;
    configDashboardSlider.minimum = 0;
    configDashboardSlider.maximum = 10;
    configDashboardSlider.initial = 5;

    dashboardSlider = dashboard.addSlider (configDashboardSlider);
  }

  /* read data from slider */
  if (dashboardSlider.feed()) {
    terminal.print ("Slider Input: ");
    terminal.println (dashboardSlider.read());
  }
}