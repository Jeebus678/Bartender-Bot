#include <Arduino.h>
#include <Adafruit_GFX.h>
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
int ingrIter = 0;
int pumpIter = 0;
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
    pump2.label("Tequila");
    pump3.label("Cherry Liqueur");
    pump4.label("Cointreau");
    pump5.label("Dark rum");
    pump6.label("Malibu");
    pump7.label("Lime Juice");
    pump8.label("Pineapple Juice");
    pump9.label("Campari");
    pump10.label("Gin");
    pump11.label("Coffee Liqueur");
    pump12.label("Baileys");
    pump13.label("Lemon Juice");
    pump14.label("Vodka");
    Parser.setFile("RECIPES.txt");
    Parser.getPossibleDrinkOptions(allPumps);
    while (Parser.drinksBuffer[drinksBufferSize][0] != '\0')
    {
        Serial.println(Parser.drinksBuffer[drinksBufferSize]);
        drinksBufferSize++;
    }
    initGUI();
}

void loop()
{
    while (true)
    {
        if (Draw.detectTouch(Draw.randomBtn)) // If "Random" pressed
        {
            drawRandomDrink();
        }
        else if (Draw.detectTouch(Draw.customBtn)) // If "Custom" pressed
        {
            Draw.drawAllPumps(allPumps);
            while (true)
            {
                manualPumpControl();
                detectHeaderInput();
            }
        }
        else if (Draw.detectTouch(Draw.browseBtn)) // If "Browse" pressed
        {
            drinksBufferElement = 0; 
            drawDrinkNavigator();
            getDrinkNavigatorResponse(); 
        }
        else if (detectHeaderInput())
        {
            break;
        }
    }
}

void enableDrinkPumps(char drinkName[30])
{
    ingrIter = 0;
    longestDuration = 0;
    while (Parser.cocktail.ingridients[ingrIter].liquor[0] != '\0')
    {
        for (pumpIter = 0; pumpIter < sizeof(allPumps); pumpIter++)
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
        for (pumpIter = 0; pumpIter < 14; pumpIter++)
        {
            if (allPumps[pumpIter]->status)
            {
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
    bool previousDrink = true;
    bool nextDrink = true;
    if ((drinksBufferElement+1) > drinksBufferSize)
    {
        nextDrink = false;
    }
    if ((drinksBufferElement-1) < 0)
    {
        previousDrink = false;
    }
    Parser.getRecipe(Parser.drinksBuffer[drinksBufferElement]);
    Draw.drawBrowse(previousDrink, nextDrink);
}

void pour()
{
    enableDrinkPumps(Parser.cocktail.name);
    waitForPumps();
    Draw.drawMenu();
}

int getRandomInt()
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
        drawRandomDrink();
        return true;
    default:
        return false;
    }
}

void drawSettingsPage()
{
    Draw.fillBody();
    Draw.drawAllPumps(allPumps);
    while (true)
    {
        automaticPumpControl();
        detectHeaderInput();
    }
}

void drawRandomDrink()
{
    Parser.getRecipe(Parser.drinksBuffer[getRandomInt()]);
    Draw.drawDrink();
    while (true)
    {
        if (Draw.detectTouch(Draw.pourBtn))
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

void manualPumpControl()
{
    for (pumpIter = 0; pumpIter < sizeof(allPumps); pumpIter++)
    {
        bool pressed = Draw.getTouchCoords();
        if (getPumpButtonStatus(pressed))
        {
            if (allPumps[pumpIter]->status)
            {
                allPumps[pumpIter]->off();
            }
            else
            {
                allPumps[pumpIter]->on(0);
            }
        }
    }
}

void automaticPumpControl()
{
    for (pumpIter = 0; pumpIter < sizeof(allPumps); pumpIter++)
    {
        unsigned long currentMillis;
        bool pressed = Draw.getTouchCoords();
        if (getPumpButtonStatus(pressed) && allPumps[pumpIter]->status != true)
        {
            currentMillis = millis();
            allPumps[pumpIter]->on(0);
            allPumps[pumpIter]->offMillis = currentMillis + 5500;
        }
    }
    waitForPumps();
}

bool getPumpButtonStatus(bool pressed)
{
    if (pressed && allPumps[pumpIter]->pumpButton.contains(Draw.xpos, Draw.ypos))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getDrinkNavigatorResponse(){
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