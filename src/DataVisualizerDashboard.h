#ifndef DATA_VISUALIZER_DASHBOARD_H
#define DATA_VISUALIZER_DASHBOARD_H

#include "DataVisualizer.h"

#define POSITION_TYPE 2
#define POSITION_Z_INDEX 3
#define POSITION_X 4
#define POSITION_Y 6
#define POSITION_WIDTH 8
#define POSITION_HEIGHT 10

#define POSITION_BUTTON_FONT_SIZE 12
#define POSITION_BUTTON_TEXT 13

#define POSITION_TEXT_MINIMUM 12
#define POSITION_TEXT_MAXIMUM 16
#define POSITION_TEXT_VALUE 20

#define POSITION_SLIDER_MINIMUM 12
#define POSITION_SLIDER_MAXIMUM 16
#define POSITION_SLIDER_VALUE 20

#define POSITION_LABEL_FONT_SIZE 12
#define POSITION_LABEL_ATTRIBUTE 13
#define POSITION_LABEL_HOR_ALIG 14
#define POSITION_LABEL_VER_ALIG 15
#define POSITION_LABEL_ALPHA_BACKGROUND 16
#define POSITION_LABEL_COLOR_BACKGROUND 17
#define POSITION_LABEL_ALPHA_FOREGROUND 20
#define POSITION_LABEL_COLOR_FOREGROUND 21
#define POSITION_LABEL_TEXT 24

#define POSITION_SIGNAL_ALPHA_ON 12
#define POSITION_SIGNAL_COLOR_ON 13
#define POSITION_SIGNAL_ALPHA_OFF 16
#define POSITION_SIGNAL_COLOR_OFF 17

#define POSITION_RADIOGROUP_SIZE_ITEMS 12
#define POSITION_RADIOGROUP_NUMBER_ITEMS 13
#define POSITION_RADIOGROUP_ORIENTATION 14
#define POSITION_RADIOGROUP_TEXT 15

#define POSITION_GRAPH_COLOR_TITLE 12
#define POSITION_GRAPH_COLOR_BACKGROUND 15
#define POSITION_GRAPH_COLOR_GRAPH 18
#define POSITION_GRAPH_TEXT 21
#define POSITION_GRAPH_PLOT_COUNT 21
#define POSITION_GRAPH_X_MINIMUM 22
#define POSITION_GRAPH_X_MAXIMUM 26
#define POSITION_GRAPH_Y_MINIMUM 30
#define POSITION_GRAPH_Y_MAXIMUM 34
#define POSITION_GRAPH_MODE_LB 38
#define POSITION_GRAPH_MODE_HB 39

#define POSITION_PROGRESS_MINIMUM 12
#define POSITION_PROGRESS_MAXIMUM 16
#define POSITION_PROGRESS_VALUE 20
#define POSITION_PROGRESS_COLOR 24

#define POSITION_CHECKBOX_FONT_SIZE 12
#define POSITION_CHECKBOX_TEXT 13

#define POSITION_SEGMENT_COUNT 12
#define POSITION_SEGMENT_BASE 13
#define POSITION_SEGMENT_ALPHA 14
#define POSITION_SEGMENT_COLOR 15

#define POSITION_PIE_COLOR_TITLE 12
#define POSITION_PIE_COLOR_BACKGROUND 15
#define POSITION_PIE_TEXT 20
#define POSITION_PIE_PLOT_COUNT 20

#define POSITION_RECTANGLE_ALPHA_BACKGROUND 12
#define POSITION_RECTANGLE_COLOR_BACKGROUND 13
#define POSITION_RECTANGLE_ALPHA_FOREGROUND 16
#define POSITION_RECTANGLE_COLOR_FOREGROUND 17

#define POSITION_SURFACE_FILL_COLOR 12
#define POSITION_SURFACE_MESH_COLOR 15
#define POSITION_SURFACE_BACKGROUND_ALPHA 18
#define POSITION_SURFACE_BACKGROUND_COLOR 19
#define POSITION_SURFACE_GRADIENT_ALPHA 22
#define POSITION_SURFACE_GRADIENT_COLOR 23
#define POSITION_SURFACE_AXIS_COLOR 26
#define POSITION_SURFACE_TICK_LABEL_COLOR 29
#define POSITION_SURFACE_X_ROTATION 32
#define POSITION_SURFACE_Y_ROTATION 33
#define POSITION_SURFACE_Z_ROTATION 34
#define POSITION_SURFACE_ATTRIBUTES 35
#define POSITION_SURFACE_SURFACE_SCALING 36
#define POSITION_SURFACE_AXIS_MINIMUM 37
#define POSITION_SURFACE_AXIS_MAXIMUM 41

#define POSITION_TABLE_DATA_FONT_SIZE 12
#define POSITION_TABLE_LABEL_FONT_SIZE 13
#define POSITION_TABLE_DATA_WIDTH 14
#define POSITION_TABLE_LABEL_WIDTH 16
#define POSITION_TABLE_ROW_HEIGHT 18
#define POSITION_TABLE_NUMBER_OF_ROWS 20
#define POSITION_TABLE_NUMBER_OF_COLUMNS 21
#define POSITION_TABLE_AUTO_LABELS 22
#define POSITION_TABLE_TEXT 23
#define POSITION_TABLE_ATTRIBUTES 23
#define POSITION_TABLE_BACKGROUND_ALPHA 24
#define POSITION_TABLE_FOREGROUND_ALPHA 25
#define POSITION_TABLE_BACKGROUND_COLOR 28
#define POSITION_TABLE_FOREGROUND_COLOR 29
#define POSITION_TABLE_LABEL_HOZ_ALIGMENT 32
#define POSITION_TABLE_DATA_HOZ_ALIGMENT 33


#define RADIOGROUP_MAX 10

enum DashboardType {
  DB_TYPE_NONE,
  DB_TYPE_LABEL,
  DB_TYPE_BUTTON,
  DB_TYPE_SLIDER,
  DB_TYPE_SIGNAL,
  DB_TYPE_PROGRESS,
  DB_TYPE_SEGMENT,
  DB_TYPE_GRAPH,
  DB_TYPE_RADIOGROUP,
  DB_TYPE_PIE,
  DB_TYPE_TEXT,
  DB_TYPE_CHECKBOX,
  DB_TYPE_RECTANGLE,
  DB_TYPE_SURFACE,
  DB_TYPE_TABLE
};

enum ButtonVariant {
  VARIANT_TOGGLED_OFF,
  VARIANT_TOGGLED_ON
};

struct ConfigDashboardLabel {
  uint8_t  zIndex             = 0;
  uint16_t x                  = 0;
  uint16_t y                  = 0;
  uint16_t width              = 0;
  uint16_t height             = 0;
  uint8_t  fontSize           = 20;
  bool     bolt               = false;
  bool     italic             = false;
  AligHoz  aligmentHorizontal = HORIZONTAL_ALIGNMENT_LEFT;
  AligVert aligmentVertical   = VERTICAL_ALIGNMENT_CENTER;
  uint8_t  backgroundAlpha    = 0;
  uint8_t  foregroundAlpha    = 255;
  RgbColor backgroundColor    = COLOR_WHITE;
  RgbColor foregroundColor    = COLOR_BLACK;
};

struct ConfigDashboardButton {
  uint8_t  zIndex   = 0;
  uint16_t x        = 0;
  uint16_t y        = 0;
  uint16_t width    = 0;
  uint16_t height   = 0;
  uint8_t  fontSize = 12;
};

struct ConfigDashboardSlider {
  uint8_t  zIndex  = 0;
  uint16_t x       = 0;
  uint16_t y       = 0;
  uint16_t width   = 0;
  uint16_t height  = 0;
  uint32_t minimum = 0;
  uint32_t maximum = 10;
  uint32_t initial = 0;
};

struct ConfigDashboardProgressBar {
  uint8_t  zIndex  = 0;
  uint16_t x       = 0;
  uint16_t y       = 0;
  uint16_t width   = 0;
  uint16_t height  = 0;
  uint32_t minimum = 0;
  uint32_t maximum = 10;
  uint32_t value   = 0;
  RgbColor color   = COLOR_GREEN;
};

struct ConfigDashboardSignal {
  uint8_t  zIndex   = 0;
  uint16_t x        = 0;
  uint16_t y        = 0;
  uint16_t width    = 0;
  uint16_t height   = 0;
  RgbColor onColor  = COLOR_GREEN;
  uint8_t  onAlpha  = 255;
  RgbColor offColor = COLOR_RED;
  uint8_t  offAlpha = 255;
};

struct ConfigDashboardSegmentDisplay {
  uint8_t     zIndex = 0;
  uint16_t    x      = 0;
  uint16_t    y      = 0;
  uint16_t    width  = 0;
  uint16_t    height = 0;
  uint8_t     digits = 2;
  SegmentBase base   = BASE_DEC;
  RgbColor    color  = COLOR_RED;
  uint8_t     alpha  = 255;
};

struct ConfigDashboardGraph {
  uint8_t  zIndex           = 0;
  uint16_t x                = 0;
  uint16_t y                = 0;
  uint16_t width            = 0;
  uint16_t height           = 0;
  RgbColor titleColor       = COLOR_WHITE;
  RgbColor backgroundColor  = COLOR_BLACK;
  RgbColor graphColor       = COLOR_BLACK;
  uint8_t  numberChannels   = 1;
  float    xMinimum         = 0;
  float    xMaximum         = 10;
  float    yMinimum         = 0;
  float    yMaximum         = 10;
  bool     mouseInteraction = true;
  bool     fitToRight       = false;
  bool     autoscale        = false;
  bool     scrollByTime     = false;
  bool     showPlot         = true;
  bool     showPoints       = false;
};

struct ConfigDashboardNumericInput {
  uint8_t  zIndex  = 0;
  uint16_t x       = 0;
  uint16_t y       = 0;
  uint16_t width   = 0;
  uint16_t height  = 0;
  uint32_t minimum = 0;
  uint32_t maximum = 10;
  uint32_t value   = 0;
};

struct ConfigDashboardRadioGroup {
  uint8_t     zIndex      = 0;
  uint16_t    x           = 0;
  uint16_t    y           = 0;
  uint16_t    width       = 0;
  uint16_t    height      = 0;
  uint8_t     sizeItems   = 12;
  uint8_t     numberItems = 2;
  Orientation orientation = HORIZONTAL;
};

struct ConfigDashboardPieChart {
  uint8_t  zIndex          = 0;
  uint16_t x               = 0;
  uint16_t y               = 0;
  uint16_t width           = 0;
  uint16_t height          = 0;
  uint8_t  numberSlices    = 2;
  RgbColor titleColor      = COLOR_BLACK;
  RgbColor backgroundColor = COLOR_WHITE;
};

struct ConfigDashboardRectangle {
  uint8_t  zIndex          = 0;
  uint16_t x               = 0;
  uint16_t y               = 0;
  uint16_t width           = 0;
  uint16_t height          = 0;
  RgbColor backgroundColor = COLOR_BLACK;
  uint8_t  backgroundAlpha = 255;
  RgbColor foregroundColor = COLOR_WHITE;
  uint8_t  foregroundAlpha = 0;
};

struct ConfigDashboardCheckBox {
  uint8_t  zIndex   = 0;
  uint16_t x        = 0;
  uint16_t y        = 0;
  uint16_t width    = 0;
  uint16_t height   = 0;
  uint8_t  fontSize = 12;
};

struct ConfigDashboardSurfaceGrid {
  uint8_t   zIndex             = 0;
  uint16_t  x                  = 0;
  uint16_t  y                  = 0;
  uint16_t  width              = 0;
  uint16_t  height             = 0;
  RgbColor  fillColor          = COLOR_GRAY;
  RgbColor  meshColor          = COLOR_MAROON;
  uint8_t   backgroundAlpha    = 0;
  RgbColor  backgroundColor    = COLOR_WHITE;
  uint8_t   gradientAlpha      = 0;
  RgbColor  gradientColor      = COLOR_WHITE;
  RgbColor  axisColor          = COLOR_BLACK;
  RgbColor  tickLabelColor     = COLOR_BLACK;
  uint8_t   xRotation          = 35;
  uint8_t   yRotation          = -70;
  uint8_t   zRotation          = 0;
  bool      showXAxis          = true;
  bool      showYAxis          = true;
  bool      showZAxis          = true;
  bool      showFill           = true;
  bool      showMesh           = true;
  bool      usePaletteColoring = false;
  ScaleMode surfaceScaling     = SCALE_FLOOR;
  float     axisMinimum        = 0;
  float     axisMaximum        = 255;
};

struct ConfigDashboardTable {
  uint8_t   zIndex                  = 0;
  uint16_t  x                       = 0;
  uint16_t  y                       = 0;
  uint16_t  width                   = 0;
  uint16_t  height                  = 0;
  uint8_t   dataFontSize            = 12;
  uint8_t   labelFontSize           = 12;
  uint16_t  dataWidth               = 50;
  uint16_t  labelWidth              = 100;
  uint16_t  rowHeight               = 25;
  uint8_t   numberOfRows            = 2;
  uint8_t   numberOfColumns         = 2;
  bool      autoLabels              = false;
  bool      dataBold                = false;
  bool      dataItalic              = false;
  bool      labelBold               = false;
  bool      labelItalic             = false;
  RgbColor  backgroundColor         = COLOR_WHITE;
  uint8_t   backgroundAlpha         = 0;
  RgbColor  foregroundColor         = COLOR_BLACK;
  uint8_t   foregroundAlpha         = 255;
  AligHoz   labelHorizontalAligment = HORIZONTAL_ALIGNMENT_CENTER;
  AligHoz   dataHorizontalAligment  = HORIZONTAL_ALIGNMENT_CENTER;
};

class DataVisualizer;
class DataVisualizerDashboardLabel;
class DataVisualizerDashboardButton;
class DataVisualizerDashboardSlider;
class DataVisualizerDashboardProgressBar;
class DataVisualizerDashboardSignal;
class DataVisualizerDashboardSegmentDisplay;
class DataVisualizerDashboardGraph;
class DataVisualizerDashboardNumericInput;
class DataVisualizerDashboardRadioGroup;
class DataVisualizerDashboardPieChart;
class DataVisualizerDashboardRectangle;
class DataVisualizerDashboardCheckBox;
class DataVisualizerDashboardSurfaceGrid;
class DataVisualizerDashboardTable;
class DataVisualizerDashboard {
  friend class DataVisualizer;
  friend class DataVisualizerDashboardGraph;
  friend class DataVisualizerDashboardPieChart;
  friend class DataVisualizerDashboardTable;

 private:
  uint16_t id;
  DataVisualizer* visualizer;
  DataVisualizerDashboardButton addButton (const char* text, ConfigDashboardButton config, uint8_t toggle);
  DataVisualizerDashboardRadioGroup addRadioGroup (const char* text, ConfigDashboardRadioGroup config);

 public:
  DataVisualizerDashboard (void);

  DataVisualizerDashboardLabel addLabel (const uint8_t* config);
  DataVisualizerDashboardLabel addLabel (const char* text, ConfigDashboardLabel config);

  DataVisualizerDashboardButton addButton (const uint8_t* config);
  DataVisualizerDashboardButton addButton (const char* text, ConfigDashboardButton config);
  DataVisualizerDashboardButton addButton (const char* textOn, const char* textOff, ConfigDashboardButton config);

  DataVisualizerDashboardSlider addSlider (const uint8_t* config);
  DataVisualizerDashboardSlider addSlider (ConfigDashboardSlider config);

  DataVisualizerDashboardProgressBar addProgressBar (const uint8_t* config);
  DataVisualizerDashboardProgressBar addProgressBar (ConfigDashboardProgressBar config);

  DataVisualizerDashboardSignal addSignal (const uint8_t* config);
  DataVisualizerDashboardSignal addSignal (ConfigDashboardSignal config);

  DataVisualizerDashboardSegmentDisplay addSegmentDisplay (const uint8_t* config);
  DataVisualizerDashboardSegmentDisplay addSegmentDisplay (ConfigDashboardSegmentDisplay config);

  DataVisualizerDashboardGraph addGraph (const uint8_t* config);
  DataVisualizerDashboardGraph addGraph (const char* text, ConfigDashboardGraph config);

  DataVisualizerDashboardNumericInput addNumericInput (const uint8_t* config);
  DataVisualizerDashboardNumericInput addNumericInput (ConfigDashboardNumericInput config);

  DataVisualizerDashboardRadioGroup addRadioGroup (const uint8_t* config);
  DataVisualizerDashboardRadioGroup addRadioGroup (ConfigDashboardRadioGroup config);

  DataVisualizerDashboardPieChart addPieChart (const uint8_t* config);
  DataVisualizerDashboardPieChart addPieChart (const char* text, ConfigDashboardPieChart config);

  DataVisualizerDashboardRectangle addRectangle (const uint8_t* config);
  DataVisualizerDashboardRectangle addRectangle (ConfigDashboardRectangle config);

  DataVisualizerDashboardCheckBox addCheckBox (const uint8_t* config);
  DataVisualizerDashboardCheckBox addCheckBox (const char* text, ConfigDashboardCheckBox config);

  DataVisualizerDashboardSurfaceGrid addSurfaceGrid (const uint8_t* config, uint8_t depthOfGrid, uint8_t widhtOfGrid);
  DataVisualizerDashboardSurfaceGrid addSurfaceGrid (ConfigDashboardSurfaceGrid config, uint8_t depthOfGrid, uint8_t widhtOfGrid);

  DataVisualizerDashboardTable addTable (const uint8_t* config);
  DataVisualizerDashboardTable addTable (const char* text, ConfigDashboardTable config);
};

typedef DataVisualizerDashboard Dashboard;

#endif /* DATA_VISUALIZER_DASHBOARD_H */