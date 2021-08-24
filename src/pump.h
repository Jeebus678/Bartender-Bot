#ifndef PUMP_H
#define PUMP_H
#include <Arduino.h>

class Pump
{
private:
    unsigned char pin;
    bool status;
public:
    Pump(unsigned char pin);
    void init(); 
    void on();
    void off(); // Will use ASync delay 
};

#endif