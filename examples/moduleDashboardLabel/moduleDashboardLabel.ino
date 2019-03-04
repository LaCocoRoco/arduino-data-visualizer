#include <DataVisualizer.h>

Terminal terminal;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        Dashboard dashboard = Visualizer.addDashboard("My Dashboard");

        ConfigDashboardLabel configDashboardLabel = {
            .zIndex             = 0,
            .x                  = 50,
            .y                  = 50,
            .width              = 100,
            .height             = 25,
            .fontSize           = 20,
            .attribute          = BOLD_ON_ITALIC_OFF,
            .aligmentHorisontal = HORISONTAL_ALIGNMENT_CENTER,
            .aligmentVertical   = VERTICAL_ALIGNMENT_CENTER,
            .backgroundColor    = COLOR_WHITE,
            .backgroundAlpha    = 0,
            .forgroundColor     = COLOR_BLACK,
            .forgroundAlpha     = 255
        };

        dashboard.addLabel("MyLabel", configDashboardLabel);
    }
}