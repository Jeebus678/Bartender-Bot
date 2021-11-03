#ifndef PUMP_H
#define PUMP_H
#include <Arduino.h>
#include <String.h>
#include <Adafruit_GFX.h>
using namespace std;

class Pump
{
private:
    unsigned char pin;
    const uint8_t portionSize = 10;      // mL per shot
    const uint8_t secondsPerPortion = 6; // # of seconds to keep a pump on per portion

public:
    Adafruit_GFX_Button pumpButton; 
    unsigned long lastMillis;
    unsigned int delayTime; // Milisecond delay time per portions required
    unsigned long offMillis;
    char *drink;
    bool status = false;
    int capacity;
    Pump(unsigned char pin);
    void label(char *drink);
    void init();
    void on(int portion);
    void off();
};

#endif