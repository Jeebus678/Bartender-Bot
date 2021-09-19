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
Pump pump1(1), pump2(2), pump3(3), pump4(4), pump5(5), pump6(6), pump7(7), pump8(8), pump9(9), pump10(10);
Pump *allPumps[10] = {&pump1, &pump2, &pump3, &pump4, &pump5, &pump6, &pump7, &pump8, &pump9, &pump10};

// void pump(int *mL, char *liquor[30])
// {
//     // unsigned long currentMillis;
//     // unsigned long lastMillis;
//     // unsigned int onMillis;
//     int seconds = *mL * 0.6;
//     for (unsigned short i = 0; i < sizeof(allPumps); i++)
//     {
//         if (strcmp(allPumps[i]->drink, *liquor) == 0)
//         {
//             // currentMillis = millis();
//             allPumps[i]->on();
//             delay(seconds * 1000);
//             allPumps[i]->off();
//         }
//     }
// }

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

    pump1.drink = "campari";
    pump2.drink = "vodka";
    pump3.drink = "soda water";
    pump4.drink = "gin";
    pump5.drink = "lemon juice";
    pump6.drink = "cointreau";
    pump7.drink = "red vermouth";
    pump8.drink = "triple sec";
    pump9.drink = "simple syrup";
    pump10.drink = "white vermouth";

    Parser.setFile("RECIPES.txt");
    Parser.getOptions(allPumps);
    for (uint8_t i = 0; i < sizeof(Parser.drinksBuffer[0]); i++)
    {
        if (Parser.drinksBuffer[0][i] == '\0')
        {
            break;
        }
        else
            Serial.println(Parser.drinksBuffer[i]);
    }
}

void loop()
{
  
}
