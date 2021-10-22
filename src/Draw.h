#ifndef _DRAW_H_
#define _DRAW_H_

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GRAY 0x31A6
#define MINPRESSURE 100
#define MAXPRESSURE 1000
#define PI 3.1415926535897932384626433832795

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <string.h>
#include "Parser.h"
#include "Pump.h"
using namespace std;

class draw
{
private:
    const int XP = 6, XM = A2, YP = A1, YM = 7; //320x480 ID=0x1581
    const int TS_LEFT = 170, TS_RT = 929, TS_TOP = 174, TS_BOT = 967;
    MCUFRIEND_kbv tft;
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
    String version = "1.0";
    int16_t BOXSIZE;
    uint16_t ID;
    uint16_t xpos, ypos;
    bool down;

    bool Touch_getXY(void);
    void printCenter(char *string);
    void fillBody();
    void drawHome();
    void drawReturn();
    void drawSettings(); 
    void drawHeader();
    void drawLoading(int x, int y);
    void drawPourButton();

public:
    Adafruit_GFX_Button settingsBtn, returnBtn, homeBtn, randomBtn, browseBtn, pourBtn, customBtn, pumpBtn, forwardBtn, backBtn, pushPumps; 
     Adafruit_GFX_Button A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
    Adafruit_GFX_Button buttons[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    char alphabet[26][4] = {" A ", " B ", " C ", " D ", " E ", " F ", " G ", " H ", " I ", " J ", " K ", " L ", " M ", " N ", " O ", " P ", " Q ", " R ", " S ", " T ", " U ", " V ", " W ", " X ", " Y ", " Z "};

    void setupTFT();
    void drawSetup();
    void drawBrowse();
    int detectHeader();
    int drawDrink();
    bool drawSplash();
    int drawMenu();
    bool initHeaderButtons();
    char waitKeyboard(); 
    void drawKeyboard();
    void drawKeypad();
    void drawSettingsPage(); 
    bool detectTouch(Adafruit_GFX_Button btn);

    template <size_t N>
    void drawCustom(Pump *(&allPumps)[N])
    {
        fillBody();
        for (int i = 0; i < N; i++)
        {
            if ((i % 2) == 0)
            {
                pumpBtn.initButton(&tft, (tft.width() / 3) - 25, (tft.height() / 2 + 200) - (30 * i), 140, 50, WHITE, WHITE, BLACK, allPumps[i]->drink, 1);
                pumpBtn.drawButton(false);
            }
            else if ((i % 2) == 1)
            {
                pumpBtn.initButton(&tft, ((tft.width() / 3) * 2) + 25, (tft.height() / 2 + 200) - (30 * (i - 1)), 140, 50, WHITE, WHITE, BLACK, allPumps[i]->drink, 1);
                pumpBtn.drawButton(false);
            }
        }
        while (true)
        {
            if (detectHeader() > 0)
            {
                break; 
            }
        }
    }
};

#endif