#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <Scheduler.h>
#include <SD.h>
#include <SPI.h>
#include <Pump.h>
#include <Parser.h>
#include <string.h>
using namespace std;

parser Parser;
Pump pump1(1), pump2(2), pump3(3), pump4(4), pump5(5), pump6(6), pump7(7), pump8(8), pump9(9), pump10(10);
Pump *allPumps[10] = {&pump1, &pump2, &pump3, &pump4, &pump5, &pump6, &pump7, &pump8, &pump9, &pump10};

unsigned int ingrLength = sizeof(Parser.cocktail.ingridients) / sizeof(Parser.cocktail.ingridients[0]);
unsigned int pumpLength = sizeof(allPumps) / sizeof(allPumps[0]);
const uint8_t chipSelect = 10; // Sets the SD chip-select pin, enabled on Mega through SOFT-SPI

void fill(char drinkName[30])
{
    Parser.getRecipe(drinkName); //Saves recipe to memory
    for (int i = 0; i < ingrLength; i++)
    {
        for (int n = 0; n < pumpLength; n++)
        {
            if (strcmp(allPumps[n]->drink, Parser.cocktail.ingridients[i].liquor) == 0)
            {
                allPumps[n]->on(atoi(Parser.cocktail.ingridients[i].portion[0]));
                Serial.println(allPumps[n]->drink);
                break;
            }
        }
    }
}

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

    pump1.label("simple syrup");
    pump2.label("cointreau");
    pump3.label("soda water");
    pump4.label("gin");
    pump5.label("lemon juice");
    pump6.label("cointreau");
    pump7.label("lime juice");
    pump8.label("passionfruit syrup");
    pump9.label("white rum");
    pump10.label("grenadine");

    Parser.setFile("RECIPES.txt");
    Parser.getOptions(allPumps);

    uint8_t i = 0;
    while (Parser.drinksBuffer[0][i] != '\0')
    {
        Serial.println(Parser.drinksBuffer[i]);
        i++;
    }

    fill("Daiquiri");
    Scheduler.startLoop(pumpScheduler);
}

void loop()
{
}

void pumpScheduler()
{
    unsigned long currentMillis = millis();
    unsigned long millisDifference;
    for (int n = 0; n < pumpLength; n++)
    {
        if (allPumps[n]->status == true)
        {
            millisDifference = currentMillis - allPumps[n]->lastMillis;
            if (millisDifference >= allPumps[n]->delayTime)
            {
                allPumps[n]->off();
            }
        }
    }
}