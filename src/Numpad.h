#ifndef _NUMPAD_H_
#define _NUMPAD_H_

#include <MCUFRIEND_kbv.h>
#include <string.h>
using namespace std;

String Key[4][3] = {
    {"7", "8", "9"},
    {"4", "5", "6"},
    {"1", "2", "3"},
    {" ", "0", "C"}};

void drawNumpad(MCUFRIEND_kbv tft)
{
    // tft.getTextBounds()
    tft.fillRoundRect((tft.width() / 2) - 90, tft.height() - 270, 180, 240, 8, WHITE);
    tft.drawFastHLine((tft.width() / 2) - 90, tft.height() - 210, 180, BLACK);
    tft.drawFastHLine((tft.width() / 2) - 90, tft.height() - 150, 180, BLACK);
    tft.drawFastHLine((tft.width() / 2) - 90, tft.height() - 90, 180, BLACK);
    tft.drawFastVLine((tft.width() / 2) - 30, tft.height() - 270, 240, BLACK);
    tft.drawFastVLine((tft.width() / 2) + 30, tft.height() - 270, 240, BLACK);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            tft.setCursor((tft.width()/2-66) + (60 * x), (tft.height() - 250) + (60 * y));
            tft.setTextSize(3);
            tft.setTextColor(BLACK);
            tft.println(Key[y][x]);
        }
    }
}

#endif