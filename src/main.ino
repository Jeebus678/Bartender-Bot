#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <SD.h>
#include <SPI.h>
#include <Pump.h>
#include <string.h>
#include <cocktail.h> 
using namespace std;

const uint8_t chipSelect = 10; // Sets the SD chip-select pin, enabled on Mega through SOFT-SPI
char drinkName[] = "Americano";

void searchCocktail(char drinkSelect[30])
{
    for (unsigned int i = 0; i < sizeof(&cocktailList); i++)
    {
        if (strcmp(cocktailList[i].name, drinkSelect) == 0)
        {
            for (unsigned int n = 0; n < sizeof(&cocktailList[i].ingridients); n++)
            {
                Serial.println(cocktailList[i].ingridients[n].liquor);
                Serial.println(cocktailList[i].ingridients[n].portion);
            }
        }
        else
        Serial.println("No cocktail found by name.");
    }
}

void setup()
{
    Serial.begin(9600);
    // while (!Serial)
    //     continue;
    Serial.println("Hello World 1");
    searchCocktail(drinkName);
    Serial.println("Hello World 2");
}

void loop()
{
}

// pinMode(SS, OUTPUT); // Required for SD library to function
//     if (!SD.begin(chipSelect))
//     {
//         Serial.println("SD initialization failed.");
//         return;
//     }
//     Serial.println("SD initialization done.");

