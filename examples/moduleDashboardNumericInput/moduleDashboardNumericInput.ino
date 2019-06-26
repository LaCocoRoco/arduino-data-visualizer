#include <DataVisualizer.h>

Terminal terminal;
DashboardNumericInput dashboardNumericInput;

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

    ConfigDashboardNumericInput configDashboardNumericInput;
    configDashboardNumericInput.zIndex  = 0;
    configDashboardNumericInput.x       = 50;
    configDashboardNumericInput.y       = 50;
    configDashboardNumericInput.width   = 100;
    configDashboardNumericInput.height  = 20;
    configDashboardNumericInput.minimum = -100;
    configDashboardNumericInput.maximum = +100;
    configDashboardNumericInput.value   = 0;

    dashboardNumericInput = dashboard.addNumericInput (configDashboardNumericInput);
  }

  /* send data from slider to terminal */
  if (dashboardNumericInput.feed()) {
    terminal.print ("Numeric Input Value: ");
    terminal.println (dashboardNumericInput.read());
  }
}