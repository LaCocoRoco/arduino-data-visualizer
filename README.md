# DataVisualizer
This library is intended to simplify the use from Microchip Data Visualizer via the Atmel Data Protocol.
The Atmel Data Protocol is a content independent protocol intended for transferring data from a target MCU to a host PC.
The connection can be established via a Serial Port or the Data Gateway Interface (EDBG-based Debugger). 

## Quick Guide
1. Download Michrochip Data Visualizer. <a href="https://www.microchip.com/mplab/avr-support/data-visualizer" target="_blank">`Link`</a>
2. Download Arduino Data Visualizer Library.
3. Open Arduino, select default example, compile and upload project.
4. Open Data Visualizer, select Serial Port Panel and press Connect.

## Known Issues & Solution
- No Y-Values displayed in Graph Visualization
> In the left Top Corner select Configuration.
> At the bottom in Configuration Window switch Theme (Dark/Light).
- Not all possible Graph Settings are available
> The Graph Module is bad supported.
> This is related to the Atmel Data Protocol.
- After connect there is a ADP Control Panel but nothing else
> This sometimes happens at a Baudrate of 9600. Just push Disconnect & Connect again.
- Received Dashboard Slider values are inconsistent
> The Samplingrate of the Dashboard Slider is vague.
> The Slider has to be moved slowly.

## Reference
- <a href="https://www.microchip.com/webdoc/GUID-F897CF19-8EAC-457A-BE11-86BDAC9B59CF/index.html?GUID-477A2070-3316-4E56-BEA7-293CCCFB3EBA" target="_blank">`Data Visualizer User's Guid (HTML)`</a>
- <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/40001903B.pdf" target="_blank">`Data Visualizer User's Guid (PDF)`</a>
- <a href="https://www.microchip.com/mplab/avr-support/data-visualizer" target="_blank">`Microchip Data Visualizer`</a>

## Functions Tree Overview
```bash
DataVisualizer
├── bool setup(Configuration config);
├── bool request(void);
├── void refresh(void);
├── void reset(void);	
├── void onTransmit(void (*)(uint8_t*, uint16_t));
├── void onReceive(uint16_t (*)(uint8_t*, uint16_t));
├── void onTransceive(uint16_t (*)(uint8_t*, uint8_t*, uint16_t));
├── void begin(DataGateway com);
├── void begin(Stream* uart);
├── void begin(TwoWire* twi, uint8_t address);    
├── void begin(SPIClass* spi, SPISettings settings, uint8_t ss);
├── void addInfo(const char* title, const char* description);
├── Terminal addTerminal(const char* title);
├── Terminal addTerminal(const char* title, RgbColor bgColor, RgbColor fgColor);
│   ├── uint16_t available(void);
│   ├── void print(int n);
│   ├── void print(long n);
│   ├── void print(char c);
│   ├── void print(const char *c);
│   ├── void println(int n);
│   ├── void println(long n);
│   ├── void println(char c);
│   ├── void println(const char *c);
│   ├── char read(void);
│   └── void read(char* buffer);
├── Graph addGraph(const char* title);
├── Graph addGraph(const char* title, RgbColor bgColor);
├── GraphAxis addAxis(const char *title, RgbColor color);
└── GraphAxis addAxis(const char *title, RgbColor color, int32_t yMin, int32_t yMax);
│   ├── GraphAxisChannel addChannel(const char *label);
│   └── GraphAxisChannel addChannel(const char *label, RgbColor color);
│   	├── GraphAxisCursor addCursor(const char *label);
│   	└── GraphAxisCursor addCursor(const char *label, RgbColor color);
├── Dashboard addDashboard(const char* title);
└── Dashboard addDashboard(const char* title, RgbColor color, uint16_t height);
	├── DashboardButton addButton(const uint8_t* config);
	├── DashboardButton addButton(const char* text, ConfigDashboardButton config);
	├── DashboardButton addButton(const char* textOn, const char* textOff, ConfigDashboardButton config);
	│   ├── bool pressed(void);
	│   └── bool toggled(void);
	├── DashboardLabel addLabel(const uint8_t* config);
	├── DashboardLabel addLabel(const char* text, ConfigDashboardLabel config);
	├── DashboardSlider addSlider(const uint8_t* config);
	├── DashboardSlider addSlider(ConfigDashboardSlider config);
	│   ├── bool feed(void);
	│   └── int32_t read(void);
	├── DashboardSignal addSignal(const uint8_t* config);
	├── DashboardSignal addSignal(ConfigDashboardSignal config);
	│   ├── void on(void);
	│   └── void off(void);
	├── DashboardProgressBar addProgressBar(const uint8_t* config);
	├── DashboardProgressBar addProgressBar(ConfigDashboardProgressBar config);
	│   └── void write(int32_t value);
	├── DashboardSegmentDisplay addSegmentDisplay(const uint8_t* config);
	├── DashboardSegmentDisplay addSegmentDisplay(ConfigDashboardSegmentDisplay config);
	│   └── void write(int32_t value);
	├── DashboardGraph addGraph(const uint8_t* config);
	├── DashboardGraph addGraph(const char* text, ConfigDashboardGraph config);
	│   └── DataVisualizerDashboardGraphChannel addChannel(const char* text);
	│       └── void write(int32_t value);
	├── DashboardRadioGroup addRadioGroup(const uint8_t* config);
	├── DashboardRadioGroup addRadioGroup(ConfigDashboardRadioGroup config);
	│   ├── bool pressed(void);
	│   └── uint8_t selected(void);
	├── DashboardPieChart addPieChart(const uint8_t* config);
	├── DashboardPieChart addPieChart(const char* text, ConfigDashboardPieChart config);
	│   └── DataVisualizerDashboardPieChartSlice addSlice(const char* text);
	│       └── void write(int32_t value);
	├── DashboardNumericInput addNumericInput(const uint8_t* config);
	├── DashboardNumericInput addNumericInput(ConfigDashboardNumericInput config);
	│   ├── bool feed(void);
	│   └── int32_t read(void);
	├── DashboardCheckBox addCheckBox(const uint8_t* config);
	├── DashboardCheckBox addCheckBox(const char* text, ConfigDashboardCheckBox config);
	│   ├── bool pressed(void);
	│   └── bool selected(void);
	├── DashboardRectangle addRectangle(const uint8_t* config);
	├── DashboardRectangle addRectangle(ConfigDashboardRectangle config);
	├── DataVisualizerDashboardSurfaceGrid addSurfaceGrid(const uint8_t* config);
	├── DataVisualizerDashboardSurfaceGrid addSurfaceGrid(ConfigDashboardSurfaceGrid config);
	└── DataVisualizerDashboardTable addTable(const uint8_t* config);
	    └── DataVisualizerDashboardTableCell addCell(const char* text);
			└── void write(int32_t value);
```

## Literals
CONFIGURATION_NONE
CONFIGURATION_AUTOSTART

GATEWAY_EXTERNAL
GATEWAY_TWI
GATEWAY_SPI
GATEWAY_UART
GATEWAY_SERIAL

UART_BAUDRATE_19200
UART_BAUDRATE_38400
UART_BAUDRATE_57600
UART_BAUDRATE_115200
UART_BAUDRATE_230400
UART_BAUDRATE_500000
UART_BAUDRATE_1000000
UART_BAUDRATE_2000000

DEFAULT_UART_BAUDRATE
DEFAULT_UART_TIMEOUT
DEFAULT_TWI_ADDRESS
DEFAULT_TWI_FREQUENCY
DEFAULT_TWI_TIMEOUT
DEFAULT_SPI_FREQUENCY
DEFAULT_VIEW

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

HORIZONTAL_ALIGNMENT_LEFT
HORIZONTAL_ALIGNMENT_CENTER
HORIZONTAL_ALIGNMENT_RIGHT

VERTICAL_ALIGNMENT_TOP
VERTICAL_ALIGNMENT_CENTER
VERTICAL_ALIGNMENT_BOTTOM

HORIZONTAL
VERTICAL

BASE_BIN
BASE_OCT
BASE_DEC
BASE_HEX

GRAPH_SCROLL_OFF
GRAPH_SCROLL_STEP
GRAPH_SCROLL_SCROLL
GRAPH_SCROLL_CIRCULAR

SCALLE_STATIC
SCALE_ROOF_AND_FLOOR
SCALE_ROOF
SCALE_FLOOR
STICKY_SCALE_ROOF_AND_FLOOR
STICKY_SCALE_ROOF
STICKY_SCALE_FLOOR

DB_TYPE_NONE
DB_TYPE_LABEL
DB_TYPE_BUTTON
DB_TYPE_SLIDER
DB_TYPE_SIGNAL
DB_TYPE_PROGRESS
DB_TYPE_SEGMENT
DB_TYPE_GRAPH
DB_TYPE_RADIOGROUP
DB_TYPE_PIE
DB_TYPE_TEXT
DB_TYPE_CHECKBOX
DB_TYPE_RECTANGLE
DB_TYPE_SURFACE
DB_TYPE_TABLE