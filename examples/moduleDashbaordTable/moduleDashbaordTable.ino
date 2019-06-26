#include <DataVisualizer.h>

DashboardTableCell dashboardTableCellA1;
DashboardTableCell dashboardTableCellA2;
DashboardTableCell dashboardTableCellB1;
DashboardTableCell dashboardTableCellB2;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");

    ConfigDashboardTable configDashboardTable;
    configDashboardTable.zIndex                  = 0;
    configDashboardTable.x                       = 50;
    configDashboardTable.y                       = 50;
    configDashboardTable.width                   = 300;
    configDashboardTable.height                  = 300;
    configDashboardTable.dataFontSize            = 12;
    configDashboardTable.labelFontSize           = 12;
    configDashboardTable.dataWidth               = 50;
    configDashboardTable.labelWidth              = 100;
    configDashboardTable.rowHeight               = 30;
    configDashboardTable.numberOfRows            = 2;
    configDashboardTable.numberOfColumns         = 2;
    configDashboardTable.autoLabels              = true;
    configDashboardTable.dataBold                = false;
    configDashboardTable.dataItalic              = false;
    configDashboardTable.labelBold               = true;
    configDashboardTable.labelItalic             = false;
    configDashboardTable.backgroundColor         = COLOR_WHITE;
    configDashboardTable.backgroundAlpha         = 0;
    configDashboardTable.foregroundColor         = COLOR_BLACK;
    configDashboardTable.foregroundAlpha         = 255;
    configDashboardTable.labelHorizontalAligment = HORIZONTAL_ALIGNMENT_CENTER;
    configDashboardTable.dataHorizontalAligment  = HORIZONTAL_ALIGNMENT_CENTER;

    DashboardTable dashboardTable = dashboard.addTable ("My Table", configDashboardTable);

    /* The Cells will be added from left to right */
    dashboardTableCellA1 = dashboardTable.addCell ("My Cell A1");
    dashboardTableCellB1 = dashboardTable.addCell ("My Cell B1");
    dashboardTableCellA2 = dashboardTable.addCell ("My Cell A2");
    dashboardTableCellB2 = dashboardTable.addCell ("My Cell B2");
  }

  dashboardTableCellA1.write (100);
  dashboardTableCellA2.write (200);
  dashboardTableCellB1.write (300);
  dashboardTableCellB2.write (400);
}