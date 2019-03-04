#include <DataVisualizer.h>

Terminal terminal;
DashboardRadioGroup dashboardRadioGroup;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
        terminal = Visualizer.addTerminal("My Terminal");

        ConfigDashboardRadioGroup configDashboardRadioGroup = {
            .zIndex      = 0,
            .x           = 50,
            .y           = 50,
            .width       = 15,
            .height      = 150,
            .sizeItems   = 10,
            .numberItems = 6,
            .orientation = VERTICAL
        };

        dashboardRadioGroup = dashboard.addRadioGroup(configDashboardRadioGroup);
    }

    if(dashboardRadioGroup.feed()) {
        terminal.println(dashboardRadioGroup.selected());
    }
}