#include <DataVisualizer.h>

Terminal terminal;
GraphAxisChannel graphAxisChannel;
GraphAxisCursor cursor;
int valueChannel, valueCursor;

void setup() {
  Visualizer.begin (GATEWAY_UART);
}

void loop() {
  /****************************************************************/
  /* WARNING: Initializing elements blocks process                */
  /****************************************************************/
  if (Visualizer.setup (CONFIGURATION_AUTOSTART)) {
    /* add atmel data protocol environment info */
    Visualizer.addInfo ("My Visualizer", "My Environment");
    /* add terminal */
    terminal = Visualizer.addTerminal ("My Terminal");
    /* add graph, axis, channel & cursor */
    Graph graph = Visualizer.addGraph ("My Graph");
    GraphAxis axis = graph.addAxis ("My Axis");
    graphAxisChannel = axis.addChannel ("My Channel");
    cursor = axis.addCursor ("My Cursor");
  }

  /* only read data if necessary */
  while (terminal.available()) {
    /* read text from terminal */
    char text[terminal.available()];
    terminal.read (text);
    /* convert text into integer */
    String string = String (text);
    valueChannel = string.toInt();
    /* write text to terminal console */
    string = "Terminal Input: " + string;
    terminal.println (string.c_str());

  }

  /* only write data if value changed */
  if (cursor.read() != valueCursor) {
    /* read value from cursor */
    valueCursor = cursor.read();
    /* write cursor value to terminal */
    String string = String (valueCursor);
    string = "Cursor Input: " + string;
    terminal.println (string.c_str());
  }

  /* write terminal value to channel */
  graphAxisChannel.write (valueChannel);
}