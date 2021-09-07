#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <SD.h>
#include <SPI.h>
#include <Pump.h>
#include <Parser.h>
#include <string.h>
using namespace std;

const uint8_t chipSelect = 10; // Sets the SD chip-select pin, enabled on Mega through SOFT-SPI
char *drinkName;

parser Parser;
Pump pump1(1), pump2(2), pump3(3), pump4(4), pump5(5), pump6(6), pump7(7), pump8(8);
Pump *allPumps[8] = {&pump1, &pump2, &pump3, &pump4, &pump5, &pump6, &pump7, &pump8};

void pump(int *mL, char *liquor[30])
{
    // unsigned long currentMillis;
    // unsigned long lastMillis;
    // unsigned int onMillis;
    int seconds = *mL * 0.6;
    for (unsigned short i = 0; i < sizeof(allPumps); i++)
    {
        if (strcmp(allPumps[i]->drink, *liquor) == 0)
        {
            // currentMillis = millis();
            allPumps[i]->on();
            delay(seconds * 1000);
            allPumps[i]->off();
        }
    }
}

// getOptions():
// Go through every ingridient of every line one by one
// search for the ingridient string in every pump label
// if true in one of them, copy cocktail name to a string array
// and move on to the next ingridient
// if all are false, break to the next line

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        continue;
    pinMode(SS, OUTPUT); // Required for SD library to function
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD initialization failed.");
        return;
    }
    Serial.println("SD initialization done.");

    Parser.setFile("RECIPES.txt");
    Serial.println(Parser.getOptions(allPumps[8], sizeof(8)));
}

void loop()
{
}
