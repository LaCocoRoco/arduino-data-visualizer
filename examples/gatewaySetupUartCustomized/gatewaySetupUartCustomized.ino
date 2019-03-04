#include <DataVisualizer.h>

void setup() {
    Serial.begin(DEFAULT_UART_BAUDRATE);

    Visualizer.begin(&Serial);
}

void loop() {

}
