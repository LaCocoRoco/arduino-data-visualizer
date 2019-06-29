#include <DataVisualizer.h>

void setup() {
  SPISettings settings(DEFAULT_SPI_FREQUENCY, MSBFIRST, SPI_MODE0);

  SPI.begin();

  Visualizer.begin(&SPI, settings, SS);
}

void loop() {

}
