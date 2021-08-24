#include <Arduino.h>
#include <ArduinoJson.h>
#include <Pump.h>
#include <TFT_HX8357.h> // Hardware-specific library
#include <Cocktail.json>
#include <string.h>
using namespace std;

#define ILI9486
#define ILI9486_TFTWIDTH 320
#define ILI9486_TFTHEIGHT 480

TFT_HX8357 tft = TFT_HX8357(); // Invoke custom library

void setup()
{
  // Set up all control pins, touch screen, etc.
  // Determine input drinks and their volumes.
  // Determine all the potential drinks based off input drinks
  // and save them as objects.
}

void loop()
{
  // Touch GUI displays all potential drinks after calculating
  // them in the setup() part. The loop() waits for user input,
  // waiting for them to select a drink on the screen. Once selected,
  // the loop checks the object for it's proper recipe and creates
  // the drink accordingly. After it is done, it goes back to waiting
  // for user input.
}
