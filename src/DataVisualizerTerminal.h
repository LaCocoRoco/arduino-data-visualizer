#ifndef DATA_VISUALIZER_TERMINAL_H
#define DATA_VISUALIZER_TERMINAL_H

#include "DataVisualizer.h"

#define ITOA_MAX_LENGTH 30
#define ITOA_DEC        10

struct DataPacket;
class DataVisualizer;
class DataVisualizerTerminal {
    friend class DataVisualizer;

  private:
    uint16_t id;
    uint16_t scan;
    DataPacket* packet;
    DataVisualizer* visualizer;

  public:
    DataVisualizerTerminal(void);
    uint16_t available(void);
    void print(int n);
    void print(long n);
    void print(char c);
    void print(const char *c);
    void println(int n);
    void println(long n);
    void println(char c);
    void println(const char *c);
    char read(void);
    void read(char* buffer);
};

typedef DataVisualizerTerminal Terminal;

#endif /* DATA_VISUALIZER_TERMINAL_H */