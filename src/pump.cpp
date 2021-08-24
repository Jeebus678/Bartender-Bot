#include <pump.h>

Pump::Pump(unsigned char pin) {
  this->pin = pin;
  init();
}

void Pump::init() {
  pinMode(pin, OUTPUT);
}

void Pump::on() {
  digitalWrite(pin, HIGH);
}
void Pump::off() {
  digitalWrite(pin, LOW);
}