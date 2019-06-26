#include <DataVisualizer.h>

DashboardSignal dashboardSignal;

int tick;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process.               */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");

    ConfigDashboardSignal configDashboardSignal;
    configDashboardSignal.zIndex   = 0;
    configDashboardSignal.x        = 50;
    configDashboardSignal.y        = 50;
    configDashboardSignal.width    = 50;
    configDashboardSignal.height   = 50;
    configDashboardSignal.onColor  = COLOR_RED;
    configDashboardSignal.onAlpha  = 255;
    configDashboardSignal.offColor = COLOR_GREEN;
    configDashboardSignal.offAlpha = 255;

    dashboardSignal = dashboard.addSignal (configDashboardSignal);
  }

  /* switch signal on and off */
  if (tick < 1000) {
    dashboardSignal.on();
  } else {
    dashboardSignal.off();
  }

  /* reset tick */
  if (tick++ > 2000) tick = 0;
}