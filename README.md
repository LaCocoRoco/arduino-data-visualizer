# DataVisualizer
This library is intended to simplify the use from Microchip Data Visualizer via the Atmel Data Protocol.
The Atmel Data Protocol is a content independent protocol intended for transferring data from a target MCU to a host PC.
The connection can be established via a Serial Port or the Data Gateway Interface (EDBG-based Debugger). 

## Quick Guide
1. Download Michrochip Data Visualizer. <a href="https://www.microchip.com/mplab/avr-support/data-visualizer" target="_blank">`Link`</a>
2. Download Arduino Data Visualizer Library.
3. Open Arduino, select default example, compile and upload project.
4. Open Data Visualizer, select Serial Port Panel and press Connect.

## Known Issues
- No Y-Values displayed in Graph Visualization
> In the left Top Corner select Configuration.
> At the bottom in Configuration Window switch Theme (Dark/Light).
- Not all possible Graph Settings are available
> The Graph Module is bad supported.
> This is related to the Atmel Data Protocol.
- After connect there is a ADP Control Panel but nothing else
> This sometimes happens at a Baudrate of 9600. Just push Disconnect & Connect again.

## Roadmap
- [x] Add Gateway Uart
- [x] Add Gateway Twi
- [x] Add Gateway Spi
- [x] Add Gateway Callabck
- [x] Add Module Info
- [x] Add Module Terminal
- [x] Add Module Graph
- [x] Add Module Graph Axis
- [x] Add Module Graph Axis Channel
- [x] Add Module Graph Axis Cursor
- [x] Add Module Dashboard
- [x] Add Module Dashboard Label
- [x] Add Module Dashboard Button
- [x] Add Module Dashboard Numeric Input
- [x] Add Module Dashboard Signal
- [x] Add Module Dashboard Radio Group
- [x] Add Module Dashboard Graph
- [ ] Add Module Dashboard Table
- [ ] Add Module Dashboard Check Box
- [ ] Add Module Dashboard Slider
- [ ] Add Module Dashboard Progress Bar
- [ ] Add Module Dashboard Segment Display
- [ ] Add Module Dashboard Pie Chart
- [ ] Add Module Dashboard Surface Grid
- [ ] Add Module Dashboard Rectangle

## Reference
- <a href="https://www.microchip.com/webdoc/GUID-F897CF19-8EAC-457A-BE11-86BDAC9B59CF/index.html?GUID-477A2070-3316-4E56-BEA7-293CCCFB3EBA" target="_blank">`Data Visualizer User's Guid (HTML)`</a>
- <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/40001903B.pdf" target="_blank">`Data Visualizer User's Guid (PDF)`</a>
- <a href="https://www.microchip.com/mplab/avr-support/data-visualizer" target="_blank">`Microchip Data Visualizer`</a>


## Usage
- [Gateway](#gateway)
- [Common](#common)
- [Info](#info)
- [Terminal](#terminal)
- [Graph](#graph)
- [Dashboard](#dashboard)
- [Literal](#literal)

### Gateway
- #### Universal Asynchronous Receiver Transmitter (Serial)
```cpp
// Setup Uart Default (GATEWAY_SERIAL)
Visualizer.begin(GATEWAY_UART);

// Setup Uart Customized
Serial.begin(DEFAULT_UART_BAUDRATE);
Visualizer.begin(&Serial);
```

- #### Two Wire Interface
```cpp
// Setup Twi Default
Visualizer.begin(GATEWAY_TWI);

// Setup Twi Customized
Wire.begin();
Visualizer.begin(&Wire, DEFAULT_TWI_ADDRESS);
```

- #### Serial Peripheral Interface
```cpp
// Setup Spi Default
Visualizer.begin(GATEWAY_SPI);

// Setup Spi Customized
SPISettings settings(DEFAULT_SPI_FREQUENCY, MSBFIRST, SPI_MODE0);
SPI.begin();
Visualizer.begin(&SPI, settings, SS);
```

- #### External Interface
```cpp
// Setup External
Visualizer.begin(GATEWAY_EXTERN);
Visualizer.onTransmit(&transmit);
Visualizer.onReceive(&receive);
Visualizer.onTransceive(&transceive);

// External Transmit
void transmit(uint8_t* txBuffer, uint16_t length);

// External Receive
uint16_t receive(uint8_t* rxBuffer, uint16_t length);

// External Transceive
uint16_t transceive(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t length);

```

### Common
```cpp
// Element Setup Handler Configuration None
if(Visualizer.setup(CONFIGURATION_NONE)) {
  // initialize elements
}

// Element Setup Handler Configuration Autostart
if(Visualizer.setup(CONFIGURATION_AUTOSTART)) {
  // initialize elements
}

// Data Visualizer Handshake Request
 if(Visualizer.request()) {
  // handshake accepted
 }

// Data Visualizer Reset
Visualizer.reset();

// Request Data From Data Visualizer
Visualizer.refresh();
```

### Info
```cpp
// Add Atmel Data Protocol Environment Information
Visualizer.addInfo("My Visualizer", "My Environment");
```

### Terminal
```cpp
// Add Terminal
Terminal terminal = Visualizer.addTerminal("My Terminal");

// Read Single Byte From Terminal
while(terminal.available()) {
    char c = terminal.read();
}

// Read All Bytes From Terminal
while(terminal.available()) {
  char text[terminal.available()];
  terminal.read(text);
}

// Print Data In Terminal Console
terminal.print("My Text");

// Print Data In Terminal Console Carriage Return
terminal.println("My Text");
```

### Graph
```cpp
// Add Graph
Graph graph = Visualizer.addGraph("My Graph");

// Add Axis
GraphAxis graphAxis = graph.addAxis("My Axis");

// Add Channel
GraphAxisChannel graphAxisChannel = graphAxis.addChannel("My Channel");

// Add Cursor
GraphAxisCursor graphAxisCursor = graphAxis.addCursor("My Cursor");

// Send Data To Channel
graphAxisChannel.write(number);

// Cursor Data Changed
GraphAxisCursor.feed();

// Read Data From Cursor
GraphAxisCursor.read();
```

### Dashboard
```cpp
// Add Dashboard
Dashboard dashboard = Visualizer.addDashboard("My Dashboard");
```
- #### Label
```cpp
// Config Label
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

// Add Label
dashboard.addLabel("MyLabel", configDashboardLabel);
```
- #### Button
```cpp
// Config Button
ConfigDashboardButton configDashboardButton = {
	.zIndex   = 0,
	.x        = 50,
	.y        = 50,
	.width    = 150,
	.height   = 50,
	.fontSize = 20
};

// Add Button
DashboardButton dashboardButton = dashboard.addButton("MyButton", configDashboardButton);

// Add Toggle Button
DashboardButton dashboardButton = dashboard.addButton("MyOn", "MyOff", configDashboardButton);

// Button Pressed
dashboardButton.pressed();

// Button Toggled State
dashboardButton.toggled();
```
- #### Numeric Input
```cpp
// Config Numeric Input
ConfigDashboardNumericInput configDashboardNumericInput = {
	.zIndex   = 0,
	.x        = 50,
	.y        = 50,
	.width    = 150,
	.height   = 50,
	.fontSize = 20
};

// Add Numeric Input
DashboardNumericInput dashboardNumericInput = dashboard.addNumericInput(configDashboardNumericInput);

// Numeric Input New Data
dashboardNumericInput.feed();

// Read Numeric Data
dashboardNumericInput.read();
```
- #### Signal
```cpp
// Config Signal
ConfigDashboardSignal configDashboardSignal = {
	.zIndex   = 0,
	.x        = 50,
	.y        = 50,
	.width    = 50,
	.height   = 50,
	.onColor  = COLOR_RED,
	.onAlpha  = 255,
	.offColor = COLOR_GREEN,
	.offAlpha = 255
};

// Add Signal
DashboardSignal dashboardSignal = dashboard.addSignal(configDashboardSignal);

// Set Signal On
dashboardSignal.on();

// Set Signal Off
dashboardSignal.off();
```
- #### Radio Group
```cpp
// Config Radio Group
ConfigDashboardRadioGroup configDashboardRadioGroup = {
	.zIndex      = 0,
	.x           = 50,
	.y           = 50,
	.width       = 15,
	.height      = 150,
	.sizeItems   = 10,
	.numberItems = 6,
	.orientation = HORIZONTAL
};

// Add Signal
DashboardRadioGroup dashboardRadioGroup = dashboard.addRadioGroup(configDashboardRadioGroup);

// Radio Group New Data
dashboardRadioGroup.feed();

// Read Radio Group Data
dashboardRadioGroup.selected();
```
- #### Graph
```cpp
// Config Graph
ConfigDashboardGraph configDashboardGraph = {
    .zIndex                 = 0,
    .x                      = 50,
    .y                      = 50,
    .width                  = 400,
    .height                 = 200,
    .titleColor             = COLOR_WHITE,
    .backgroundColor        = COLOR_BLACK,
    .graphBackgroundColor   = COLOR_BLACK,
    .plotCount              = 1,
    .xMinimum               = 0,
    .xMaximum               = 10,
    .yMinimum               = -1000,
    .yMaximum               = +1000,
    .mouseInteraction       = true,
    .fitToRight             = false,
    .autoscale              = false,
    .scrollByTime           = true,
    .showPlot               = true,
    .showPoints             = false
};

// Add Graph
DashboardGraph dashboardGraph = dashboard.addGraph("My Graph", configDashboardGraph);

// Add Channel
DashboardGraphChannel dashboardGraphChannel = dashboardGraph.addChannel("My Channel A");

// Read Radio Group Data
dashboardGraphChannel.write(number);
```
- #### Predefined Configuration
```cpp
/* Data Visualizer has the possibility to predefine a Dashboard.
 * 1. Start Data Visualizer.
 * 2. On the top left corner press "Configuration".
 * 3. In Modules select "Visualization" and then "Custom Dashboard".
 * 4. In the "Dashboard Panel" on the bottom left press "Edit".
 * 5. In the "Dashboard Panel" on the right side expand "Elements".
 * 6. Create your own Dashboard.
 * 7. In the "Dashboard Panel" on the bottom press "Save".
 * 8. The configuration per element will be saved as byte arrays.
 * 9. Use the configuration file in combination with the Visualizer.
 **/

// Dashboard Configuration Example Button
byte configDashboardButton[] = {
    0, // Dashboard ID
    0, // Element ID
    DB_TYPE_BUTTON, // Element Type
    0, // Z-Index (GUI stack order)
    50, 0, // X-coordinate
    50, 0, // Y-coordinate
    150, 0, // Width
    50, 0, // Height
    20, // Font Size
    'M', 'y', 'B', 'u', 't', 't', 'o', 'n', '\0', // Text
    0,
};

// Add Button Via Configuration
DashboardButton dashboardButton = dashboard.addButton(configDashboardButton);
```

### Literal
```cpp
CONFIGURATION_NONE
CONFIGURATION_AUTOSTART

GATEWAY_EXTERNAL
GATEWAY_TWI
GATEWAY_SPI
GATEWAY_UART
GATEWAY_SERIAL

BAUDRATE_9600
BAUDRATE_19200
BAUDRATE_38400
BAUDRATE_57600
BAUDRATE_115200
BAUDRATE_230400
BAUDRATE_500000
BAUDRATE_1000000
BAUDRATE_2000000

COLOR_WHITE
COLOR_BLACK
COLOR_SILVER
COLOR_GRAY
COLOR_MAROON
COLOR_RED
COLOR_PURPLE
COLOR_FUCHSIA
COLOR_GREEN
COLOR_LIME
COLOR_OLIVE
COLOR_YELLOW
COLOR_NAVY
COLOR_BLUE
COLOR_TEAL
COLOR_AQUA
COLOR_ORANGE

BOLD_OFF_ITALIC_OFF
BOLD_ON_ITALIC_OFF
BOLD_OFF_ITALIC_ON
BOLD_ON_ITALIC_ON

HORISONTAL_ALIGNMENT_LEFT
HORISONTAL_ALIGNMENT_CENTER
HORISONTAL_ALIGNMENT_RIGHT

VERTICAL_ALIGNMENT_TOP
VERTICAL_ALIGNMENT_CENTER
VERTICAL_ALIGNMENT_BOTTOM

HORIZONTAL
VERTICAL

DB_TYPE_LABEL
DB_TYPE_BUTTON
DB_TYPE_TEXT
DB_TYPE_SIGNAL
DB_TYPE_RADIOGROUP

DEFAULT_UART_BAUDRATE
DEFAULT_UART_TIMEOUT
DEFAULT_TWI_ADDRESS
DEFAULT_TWI_FREQUENCY
DEFAULT_TWI_TIMEOUT
DEFAULT_SPI_FREQUENCY
DEFAULT_VIEW
```