#include <DataVisualizer.h>

Terminal terminal;

void setup() {
    Visualizer.begin(GATEWAY_SERIAL);
}

void loop() {
    /****************************************************************/
    /* WARNING: Initializing elements blocks process.               */
    /****************************************************************/
    if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
        terminal = Visualizer.addTerminal("My Terminal");
    }

    /****************************************************************/
    /* Read data from terminal and write to terminal console        */
    /****************************************************************/
    while(terminal.available()) {
        char c = terminal.read();
        terminal.println(c);
    }
}