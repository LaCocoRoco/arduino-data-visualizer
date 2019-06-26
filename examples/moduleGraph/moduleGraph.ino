#include <DataVisualizer.h>

GraphAxisChannel graphAxisChannel;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process.               */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    Graph graph = Visualizer.addGraph ("My Graph");
    GraphAxis graphAxis = graph.addAxis ("My Axis");
    graphAxisChannel = graphAxis.addChannel ("My Channel");
  }

  /* write data to channel */
  graphAxisChannel.write (10000);
}