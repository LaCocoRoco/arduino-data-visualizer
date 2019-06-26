#include <DataVisualizer.h>

DashboardSurfaceGrid dashboardSurfaceGrid;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");

    ConfigDashboardSurfaceGrid configDashboardSurfaceGrid;
    configDashboardSurfaceGrid.zIndex             = 0;
    configDashboardSurfaceGrid.x                  = 50;
    configDashboardSurfaceGrid.y                  = 50;
    configDashboardSurfaceGrid.width              = 300;
    configDashboardSurfaceGrid.height             = 300;
    configDashboardSurfaceGrid.backgroundAlpha    = 0;
    configDashboardSurfaceGrid.gradientAlpha      = 0;
    configDashboardSurfaceGrid.xRotation          = 35;
    configDashboardSurfaceGrid.yRotation          = -70;
    configDashboardSurfaceGrid.zRotation          = 0;
    configDashboardSurfaceGrid.showFill           = true;
    configDashboardSurfaceGrid.showMesh           = true;
    configDashboardSurfaceGrid.showXAxis          = true;
    configDashboardSurfaceGrid.showYAxis          = true;
    configDashboardSurfaceGrid.showZAxis          = true;
    configDashboardSurfaceGrid.usePaletteColoring = false;
    configDashboardSurfaceGrid.axisMinimum        = 0;
    configDashboardSurfaceGrid.axisMaximum        = 255;
    configDashboardSurfaceGrid.surfaceScaling     = SCALE_FLOOR;
    configDashboardSurfaceGrid.fillColor          = COLOR_GRAY;
    configDashboardSurfaceGrid.meshColor          = COLOR_MAROON;
    configDashboardSurfaceGrid.backgroundColor    = COLOR_WHITE;
    configDashboardSurfaceGrid.gradientColor      = COLOR_WHITE;
    configDashboardSurfaceGrid.axisColor          = COLOR_BLACK;
    configDashboardSurfaceGrid.tickLabelColor     = COLOR_BLACK;

    dashboardSurfaceGrid = dashboard.addSurfaceGrid (configDashboardSurfaceGrid, 10, 10);
  }
}
