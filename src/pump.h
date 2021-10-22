#ifndef PUMP_H
#define PUMP_H
#include <Arduino.h>
#include <String.h>
using namespace std;

class Pump
{
private:
    unsigned char pin;       
    const float pumpRate = 100;                                 // mL per minute
    const float portionSize = 10;                                  // mL per shot
    const float secondsPerPortion = 6; // # of seconds to keep a pump on per portion

public: 
    unsigned long lastMillis;
    unsigned long delayTime;  // Milisecond delay time per portions required
    unsigned long offMillis; 
    char *drink;
    bool status = false;
    Pump(unsigned char pin);
    void label(char *drink);
    void init();
    void on(int portion);
    void off();
};

#endif