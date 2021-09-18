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

// void Pump::pump(int *mL, int *millis)
// {
//   // unsigned long currentMillis = millis();
//   // unsigned long lastMillis; 
//   int secondsPerML = 0.6; 
//   // lastMillis = currentMillis; 
//   on();
//   delay((secondsPerML)*(*mL)*(1000));
//   off(); 
// }