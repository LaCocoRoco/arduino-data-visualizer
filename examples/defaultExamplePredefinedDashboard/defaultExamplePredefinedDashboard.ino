#include <DataVisualizer.h>

/* Data Visualizer has the possibility to predefine a Dashboard.
 * 1. Start Data Visualizer.
 * 2. On the top left corner press "Configuration".
 * 3. In Modules select "Visualization" and then "Custom Dashboard".
 * 4. In the "Dashboard Panel" on the bottom left press "Edit".
 * 5. In the "Dashboard Panel" on the right side expand "Elements".
 * 6. Create your own Dashboard.
 * 7. In the "Dashboard Panel" on the bottom press "Save".
 * 8. The configuration per element will be saved as byte arrays.
 * 9. Use the configuration file in combination with the Visualizer.
 **/

DashboardNumericInput dashboardNumericInput;
DashboardButton dashboardButton;
DashboardGraphChannel dashboardGraphChannel;

int value;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Dashboard dashboard = Visualizer.addDashboard ("My Dashboard");

    byte configDashboardLabelTop[] = {
      0, // Dashboard ID
      0, // Element ID
      DB_TYPE_LABEL, // Element Type
      0, // Z-Index (GUI stack order)
      50, 0, // X-coordinate
      50, 0, // Y-coordinate
      250, 0, // Width
      30, 0, // Height
      20, // Font Size
      1,
      0, // Horizontal Alignment
      0, // Vertical Alignment
      0, 255, 255, 255, // Background Color
      255, 0, 0, 0, // Foreground Color
      'M', 'y', ' ', 'P', 'r', 'e', 'd', 'e', 'f', 'i', 'n', 'e', 'd', ' ', 'D', 'a', 's', 'h', 'b', 'o', 'a', 'r', 'd', '\0', // Text
    };
    dashboard.addLabel (configDashboardLabelTop);

    byte configDashboardGraph[] = {
      0, // Dashboard ID
      1, // Element ID
      DB_TYPE_GRAPH, // Element Type
      0, // Z-Index (GUI stack order)
      50, 0, // X-coordinate
      80, 0, // Y-coordinate
      104, 1, // Width
      250, 0, // Height
      255, 255, 255, // Title color
      0, 0, 0, // Background color
      20, 20, 20, // Graph background color
      'M', 'y', ' ', 'G', 'r', 'a', 'p', 'h', '\0', // Title
      1, // Number of plots
      0, 0, 0, 0, // X Minimum
      0, 0, 32, 65, // X Maximum
      0, 0, 122, 196, // Y Minimum
      0, 0, 122, 68, // Y Maximum
      1,
      1,
    };
    DashboardGraph dashboardGraph = dashboard.addGraph (configDashboardGraph);
    dashboardGraphChannel = dashboardGraph.addChannel ("My Channel");

    byte configDashboardNumericInput[] = {
      0, // Dashboard ID
      2, // Element ID
      DB_TYPE_TEXT, // Element Type
      1, // Z-Index (GUI stack order)
      210, 0, // X-coordinate
      134, 1, // Y-coordinate
      60, 0, // Width
      20, 0, // Height
      24, 252, 255, 255, // Minimum
      232, 3, 0, 0, // Maximum
      0, 0, 0, 0, // Value
    };
    dashboardNumericInput = dashboard.addNumericInput (configDashboardNumericInput);

    byte configDashboardLabelValue[] = {
      0, // Dashboard ID
      3, // Element ID
      DB_TYPE_LABEL, // Element Type
      0, // Z-Index (GUI stack order)
      50, 0, // X-coordinate
      134, 1, // Y-coordinate
      160, 0, // Width
      20, 0, // Height
      15, // Font Size
      0,
      0, // Horizontal Alignment
      1, // Vertical Alignment
      0, 255, 255, 255, // Background Color
      255, 0, 0, 0, // Foreground Color
      'O', 'v', 'e', 'r', 'r', 'i', 'd', 'e', ' ', 'G', 'r', 'a', 'p', 'h', ' ', 'V', 'a', 'l', 'u', 'e', ':', '\0', // Text
    };
    dashboard.addLabel (configDashboardLabelValue);

    byte configDashboardButton[] = {
      0, // Dashboard ID
      4, // Element ID
      DB_TYPE_BUTTON, // Element Type
      0, // Z-Index (GUI stack order)
      44, 1, // X-coordinate
      134, 1, // Y-coordinate
      110, 0, // Width
      20, 0, // Height
      12, // Font Size
      'R', 'e', 's', 'e', 't', ' ', 'G', 'r', 'a', 'p', 'h', ' ', 'V', 'a', 'l', 'u', 'e', '\0', // Text
      0,
    };
    dashboardButton = dashboard.addButton (configDashboardButton);
  }

  /* read data from numeric input */
  if (dashboardNumericInput.feed()) {
    value = dashboardNumericInput.read();
  }

  /* reset value when button pressed */
  if (dashboardButton.pressed()) {
    value = 0;
  }

  /* send data to graph channel */
  dashboardGraphChannel.write (value);
}