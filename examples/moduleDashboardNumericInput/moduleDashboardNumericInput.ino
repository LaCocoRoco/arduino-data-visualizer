#include <DataVisualizer.h>

Terminal terminal;
DashboardNumericInput dashboardNumericInput;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
        terminal = Visualizer.addTerminal("My Terminal");

        ConfigDashboardNumericInput configDashboardNumericInput = {
            .zIndex  = 0,
            .x       = 50,
            .y       = 50,
            .width   = 100,
            .height  = 20,
            .minimum = -100,
            .maximum = +100,
            .value   = 0
        };

        dashboardNumericInput = dashboard.addNumericInput(configDashboardNumericInput);
    }

    if(dashboardNumericInput.feed()) {
        terminal.print("Numeric Input Value: ");
        terminal.println(dashboardNumericInput.read());
    }
}