#ifndef PUMP_H
#define PUMP_H
#include <Arduino.h>
#include <String.h> 
using namespace std; 

class Pump
{
private:
    unsigned char pin;
    String drink; 
    bool status;
public:
    Pump(unsigned char pin);
    void label(String drink); 
    void init(); 
    void on();
    void off(); // Will use ASync delay 
};

#endif