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

void Pump::on()
{
  digitalWrite(pin, HIGH);
  status = true;
}

void Pump::off()
{
  digitalWrite(pin, LOW);
  status = false;
}

void Pump::label(char *drink)
{
  this->drink = drink;
}

