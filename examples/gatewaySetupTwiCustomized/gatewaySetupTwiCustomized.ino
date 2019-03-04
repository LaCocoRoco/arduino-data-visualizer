#include <DataVisualizer.h>

void setup() {
    Wire.begin();

    Visualizer.begin(&Wire, DEFAULT_TWI_ADDRESS);
}

void loop() {

}