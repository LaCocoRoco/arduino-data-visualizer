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

#define POSITION_LABEL_FONT 12
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

#define RADIOGROUP_MAX 10

enum DashboardType {
    DB_TYPE_NONE,
    DB_TYPE_LABEL,
    DB_TYPE_BUTTON,
    DB_TYPE_TEXT,
    DB_TYPE_SIGNAL,
    DB_TYPE_RADIOGROUP,
    DB_TYPE_GRAPH
};

enum ButtonVariant {
    VARIANT_TOGGLED_OFF,
    VARIANT_TOGGLED_ON
};

struct ConfigDashboardLabel {
    uint8_t zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t fontSize;
    LabelAttribute attribute;
    LabelAligmentHorisontal aligmentHorisontal;
    LabelAligmentVertical aligmentVertical;
    RgbColor backgroundColor;
    uint8_t backgroundAlpha;
    RgbColor forgroundColor;
    uint8_t forgroundAlpha;
};

struct ConfigDashboardNumericInput {
    uint8_t  zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint32_t minimum;
    uint32_t maximum;
    uint32_t value;
};

struct ConfigDashboardButton {
    uint8_t zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t fontSize;
};

struct ConfigDashboardSignal {
    uint8_t  zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    RgbColor onColor;
    uint8_t onAlpha;
    RgbColor offColor;
    uint8_t offAlpha;
};

struct ConfigDashboardRadioGroup {
    uint8_t  zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t sizeItems;
    uint8_t numberItems;
    RadioOrientation orientation;
};

struct ConfigDashboardGraph {
    uint8_t  zIndex;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    RgbColor titleColor;
    RgbColor backgroundColor;
    RgbColor graphColor;
    uint8_t plotCount;
    float xMinimum;
    float xMaximum;
    float yMinimum;
    float yMaximum;
    bool mouseInteraction;
    bool fitToRight;
    bool autoscale;
    bool scrollByTime;
    bool showPlot;
    bool showPoints;
};

class DataVisualizer;
class DataVisualizerDashboardLabel;
class DataVisualizerDashboardButton;
class DataVisualizerDashboardNumericInput;
class DataVisualizerDashboardSignal;
class DataVisualizerDashboardRadioGroup;
class DataVisualizerDashboardGraph;
class DataVisualizerDashboard {
    friend class DataVisualizer;
    friend class DataVisualizerDashboardGraph;

  private:
    uint16_t id;
    DataVisualizer* visualizer;
    DataVisualizerDashboardButton addButton(const char* text, ConfigDashboardButton config, uint8_t toggle);
    DataVisualizerDashboardRadioGroup addRadioGroup(const char* text, ConfigDashboardRadioGroup config);

  public:
    DataVisualizerDashboard(void);
    DataVisualizerDashboardLabel addLabel(const uint8_t* config);
    DataVisualizerDashboardLabel addLabel(const char* text, ConfigDashboardLabel config);

    DataVisualizerDashboardNumericInput addNumericInput(const uint8_t* config);
    DataVisualizerDashboardNumericInput addNumericInput(ConfigDashboardNumericInput config);

    DataVisualizerDashboardButton addButton(const uint8_t* config);
    DataVisualizerDashboardButton addButton(const char* text, ConfigDashboardButton config);
    DataVisualizerDashboardButton addButton(const char* textOn, const char* textOff, ConfigDashboardButton config);

    DataVisualizerDashboardSignal addSignal(const uint8_t* config);
    DataVisualizerDashboardSignal addSignal(ConfigDashboardSignal config);

    DataVisualizerDashboardRadioGroup addRadioGroup(const uint8_t* config);
    DataVisualizerDashboardRadioGroup addRadioGroup(ConfigDashboardRadioGroup config);

    DataVisualizerDashboardGraph addGraph(uint8_t* config);
    DataVisualizerDashboardGraph addGraph(const char* text, ConfigDashboardGraph config);
};

typedef DataVisualizerDashboard Dashboard;

#endif /* DATA_VISUALIZER_DASHBOARD_H */