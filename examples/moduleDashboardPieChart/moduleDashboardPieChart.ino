#include <DataVisualizer.h>

DashboardPieChartSlice dashboardPieChartSliceA;
DashboardPieChartSlice dashboardPieChartSliceB;

void setup() {
  Visualizer.begin(GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup(CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

    ConfigDashboardPieChart configDashboardPieChart;
    configDashboardPieChart.zIndex          = 0;
    configDashboardPieChart.x               = 50;
    configDashboardPieChart.y               = 50;
    configDashboardPieChart.width           = 300;
    configDashboardPieChart.height          = 300;
    configDashboardPieChart.numberSlices    = 2;
    configDashboardPieChart.titleColor      = COLOR_BLACK;
    configDashboardPieChart.backgroundColor = COLOR_WHITE;

    DashboardPieChart dashboardPieChart = dashboard.addPieChart("My Pie Chart", configDashboardPieChart);

    dashboardPieChartSliceA = dashboardPieChart.addSlice("My Slice A");
    dashboardPieChartSliceB = dashboardPieChart.addSlice("My Slice B");
  }

  dashboardPieChartSliceA.write(100);
  dashboardPieChartSliceB.write(200);
}