#ifndef PUMP_H
#define PUMP_H
#include <Arduino.h>
#include <String.h>
using namespace std;

class Pump
{
private:
    unsigned char pin;

public:
    const char *drink = "gin";
    bool status;
    Pump(unsigned char pin);
    void label(char *drink);
    void init();
    void on();
    void off(); // Will use ASync delay
};



#endif