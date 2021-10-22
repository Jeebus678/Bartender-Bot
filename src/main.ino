#include <Arduino.h>
#include <Scheduler.h>
#include <SD.h>
#include <SPI.h>
#include "Pump.h"
#include "Parser.h"
#include "Draw.h"
#include <string.h>
using namespace std;

draw Draw;
Pump pump1(23), pump2(25), pump3(27), pump4(29), pump5(31), pump6(33), pump7(35), pump8(37), pump9(39), pump10(41), pump11(43), pump12(45), pump13(47), pump14(49);
Pump *allPumps[14] = {&pump1, &pump2, &pump3, &pump4, &pump5, &pump6, &pump7, &pump8, &pump9, &pump10, &pump11, &pump12, &pump13, &pump14};

unsigned int ingrLength = sizeof(Parser.cocktail.ingridients) / sizeof(Parser.cocktail.ingridients[0]);
unsigned int pumpLength = sizeof(allPumps) / sizeof(allPumps[0]);
unsigned int longestDuration;
bool found;
int drinksBufferElement = 0;
int drinksBufferSize = 0;
const uint8_t chipSelect = 10; // Sets the SD chip-select pin, enabled on Mega through SOFT-SPI

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        continue;
    }
    randomSeed(analogRead(7));
    pinMode(SS, OUTPUT); // Required for SD library to function
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD initialization failed.");
        return;
    }
    Serial.println("SD initialization done.");
    pump1.label("Simple Syrup");
    pump2.label("Cointreau");
    pump3.label("Cherry Liqueur");
    pump4.label("White Vermouth");
    pump5.label("Dark rum");
    pump6.label("Tequila");
    pump7.label("empty");
    pump8.label("Red Vermouth");
    pump9.label("Campari");
    pump10.label("empty");
    pump11.label("empty");
    pump12.label("Scotch");
    pump13.label("Lemon Juice");
    pump14.label("Vodka");
    Parser.setFile("RECIPES.txt");
    Parser.getOptions(allPumps);
    while (Parser.drinksBuffer[drinksBufferElement] != '\0')
    {
        Serial.println(Parser.drinksBuffer[drinksBufferElement]);
        drinksBufferElement++;
        drinksBufferSize++;
    }
    initGUI();
}

void loop()
{
    while (true)
    {
        if (Draw.detectTouch(Draw.randomBtn))
        {
            Parser.getRecipe(Parser.drinksBuffer[randomInt()]);
            Draw.drawDrink();
            while (true)
            {
                if (Draw.detectTouch(Draw.pourBtn))
                {
                    pour();
                    break;
                }
                else if (Draw.detectHeader() > 0)
                {
                    break;
                }
            }
        }
        else if (Draw.detectTouch(Draw.customBtn))
        {
            Draw.drawCustom(allPumps);
        }
        else if (Draw.detectTouch(Draw.browseBtn))
        {
            char inputChar = drawKeyboardWaitForChar();
            while (!searchDrinkInBuffer(inputChar))
            {
                inputChar = drawKeyboardWaitForChar();
            }
            drawDrinkNavigator();
            while (true)
            {
                if (Draw.detectTouch(Draw.forwardBtn))
                {
                    drawNextDrink();
                }
                else if (Draw.detectTouch(Draw.backBtn))
                {
                    drawPreviousDrink();
                }
                else if (Draw.detectTouch(Draw.pourBtn))
                {
                    pour();
                    break;
                }
                else if (detectHeaderInput())
                {
                    break;
                }
            }
        }
        else if (detectHeaderInput())
        {
            break;
        }
    }
}

void enableDrinkPumps(char drinkName[30])
{
    int ingrIter = 0;
    longestDuration = 0;
    while (Parser.cocktail.ingridients[ingrIter].liquor[0] != '\0')
    {
        for (int pumpIter = 0; pumpIter < sizeof(allPumps); pumpIter++)
        {
            if (strcmp(allPumps[pumpIter]->drink, Parser.cocktail.ingridients[ingrIter].liquor) == 0)
            {
                allPumps[pumpIter]->on(int(Parser.cocktail.ingridients[ingrIter].portion));
                if (int(Parser.cocktail.ingridients[ingrIter].portion) > longestDuration)
                {
                    longestDuration = int(Parser.cocktail.ingridients[ingrIter].portion);
                }
                ingrIter++;
                break;
            }
        }
    }
}

void waitForPumps()
{
    while (true)
    {
        int stillPouring = 0;
        for (int pumpIter = 0; pumpIter < 14; pumpIterg++)
        {
            if (allPumps[pumpIter]->status)
            {
                Serial.println("Device is on");
                stillPouring++;
                unsigned long currentMillis = millis();
                if (allPumps[pumpIter]->offMillis < currentMillis)
                {
                    allPumps[pumpIter]->off();
                    stillPouring--;
                }
            }
        }
        if (stillPouring == 0)
        {
            Serial.println("all devices off");
            break;
        }
    }
}

void initGUI()
{
    Draw.setupTFT();
    Draw.drawSplash();
    Draw.drawMenu();
}

bool searchDrinkInBuffer(char x)
{
    drinksBufferElement = 0;
    while (Parser.drinksBuffer[drinksBufferElement][0] != '\0')
    {
        if (Parser.drinksBuffer[drinksBufferElement][0] == x)
        {
            return true;
        }
        drinksBufferElement++;
    }
    return false;
}

void drawNextDrink()
{
    drinksBufferElement++;
    drawDrinkNavigator();
}

void drawPreviousDrink()
{
    drinksBufferElement--;
    drawDrinkNavigator();
}

void drawDrinkNavigator()
{
    Parser.getRecipe(Parser.drinksBuffer[drinksBufferElement]);
    Draw.drawBrowse();
}

char drawKeyboardWaitForChar()
{
    Draw.drawKeyboard();
    char x = Draw.waitKeyboard();
    return x;
}

void pour()
{
    enableDrinkPumps(Parser.cocktail.name);
    waitForPumps();
    Draw.drawMenu();
}

int randomInt()
{
    int randNumber;
    if (randNumber != random(drinksBufferSize))
    {
        return randNumber = random(drinksBufferSize);
    }
    else if (randNumber == random(drinksBufferSize))
    {
        return randNumber++;
    }
}

bool detectHeaderInput()
{
    switch (Draw.detectHeader())
    {
    case (1):
        Draw.drawMenu();
        return true;
    case (2):
        drawSettingsPage();
        return true;
    case (3):
        break;
    default:
        continue;
    }
}

void drawSettingsPage()
{
    Draw.drawSettingsPage();
    while (true)
    {
        if (Draw.detectTouch(Draw.pushPumps))
        {
            for (int i = 0; i < 14; i++)
            {
                Serial.print("Pump #");
                Serial.println(i + 1);
                allPumps[i]->on(2);
                delay(5000);
                allPumps[i]->off();
            }
            return true;
        }
        else if (detectHeaderInput())
        {
            break;
        }
    }
}