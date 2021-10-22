#include <Pump.h>

Pump::Pump(unsigned char pin)
{
  this->pin = pin;
  init();
}

void Pump::init()
{
  pinMode(pin, OUTPUT);
}

void Pump::on(int portion)
{
  digitalWrite(pin, HIGH);
  status = true;
  lastMillis = millis();
  delayTime = (portion * secondsPerPortion)*1000; 
  offMillis = lastMillis + delayTime; 
}

void Pump::off()
{
  digitalWrite(pin, LOW);
  status = false;
}

void Pump::label(char * drink)
{
  this->drink = drink;
}

