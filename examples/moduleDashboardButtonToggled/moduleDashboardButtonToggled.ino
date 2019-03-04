#include <DataVisualizer.h>

Terminal terminal;
DashboardButton dashboardButton;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
        terminal = Visualizer.addTerminal("My Terminal");

        ConfigDashboardButton configDashboardButton = {
            .zIndex   = 0,
            .x        = 50,
            .y        = 50,
            .width    = 150,
            .height   = 50,
            .fontSize = 20
        };

        dashboardButton = dashboard.addButton("MyOn", "MyOff", configDashboardButton);
    }

    if(dashboardButton.pressed()) {
        if(dashboardButton.toggled()) {
            terminal.println("My Button Toggled On");
        } else {
            terminal.println("My Button Toggled Off");
        }
    }
}