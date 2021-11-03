#include "Draw.h"
#include "Bitmaps.h"
#include "Numpad.h"

bool draw::detectTouch(Adafruit_GFX_Button btn)
{
    down = getTouchCoords();
    btn.press(down && btn.contains(xpos, ypos));
    if (btn.justPressed())
    {
        return true;
    }
    else
        return false;
}

int draw::detectHeader()
{
    if (detectTouch(homeBtn))
    {
        return 1;
    }
    if (detectTouch(settingsBtn))
    {
        return 2;
    }
    if (detectTouch(returnBtn))
    {
        return 3;
    }
    else
        return 0;
}

void draw::drawSettings()
{
    settingsBtn.initButton(&tft, (tft.width() / 2) - 80, 0, 50, 100, BLACK, BLACK, BLACK, " ", 1);
    settingsBtn.drawButton(false);
    tft.drawBitmap((tft.width() / 2) - 100, 10, settings, 32, 32, WHITE);
}

void draw::drawHome()
{
    homeBtn.initButton(&tft, (tft.width() / 2), 0, 50, 100, BLACK, BLACK, BLACK, " ", 1);
    homeBtn.drawButton(false);
    tft.drawBitmap((tft.width() / 2 - 20), 10, home, 32, 32, WHITE);
}

void draw::drawReturn()
{
    returnBtn.initButton(&tft, (tft.width() / 2) + 80, 0, 50, 100, BLACK, BLACK, BLACK, " ", 1);
    returnBtn.drawButton(false);
    tft.drawBitmap((tft.width() / 2) + 60, 10, back, 32, 32, WHITE);
}

void draw::drawHeader()
{
    drawSettings();
    drawHome();
    drawReturn();
}

void draw::fillBody()
{
    tft.fillRect(0, 50, tft.width(), tft.height(), BLACK);
}


void draw::drawLoading(int x, int y)
{
    int shade[8];
    shade[7] = tft.color565(30, 30, 30);
    shade[6] = tft.color565(60, 60, 60);
    shade[5] = tft.color565(90, 90, 90);
    shade[4] = tft.color565(120, 120, 120);
    shade[3] = tft.color565(150, 150, 150);
    shade[2] = tft.color565(180, 180, 180);
    shade[1] = tft.color565(210, 210, 210);
    shade[0] = tft.color565(255, 255, 255);
    for (int i = 0; i < 50; i++)
    {
        tft.fillCircle(x + 40 * (cos(-i * PI / 4)), y + 40 * (sin(-i * PI / 4)), 10, shade[0]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 1) * PI / 4)), y + 40 * (sin(-(i + 1) * PI / 4)), 10, shade[1]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 2) * PI / 4)), y + 40 * (sin(-(i + 2) * PI / 4)), 10, shade[2]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 3) * PI / 4)), y + 40 * (sin(-(i + 3) * PI / 4)), 10, shade[3]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 4) * PI / 4)), y + 40 * (sin(-(i + 4) * PI / 4)), 10, shade[4]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 5) * PI / 4)), y + 40 * (sin(-(i + 5) * PI / 4)), 10, shade[5]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 6) * PI / 4)), y + 40 * (sin(-(i + 6) * PI / 4)), 10, shade[6]);
        delay(15);
        tft.fillCircle(x + 40 * (cos(-(i + 7) * PI / 4)), y + 40 * (sin(-(i + 7) * PI / 4)), 10, shade[7]);
        delay(15);
    }
}

bool draw::getTouchCoords(void)
{
    TSPoint tp = ts.getPoint();
    pinMode(YP, OUTPUT); // restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH); // because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (tp.z > MINPRESSURE && tp.z < MAXPRESSURE);
    if (pressed)
    {
        xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
        ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

void draw::drawBrowse(bool previousDrink, bool nextDrink)
{
    forwardBtn.initButton(&tft, (tft.width() / 12) * 11, tft.height() / 2 - 40, 45, 100, BLACK, BLACK, WHITE, ">", 5);
    backBtn.initButton(&tft, (tft.width() / 12), tft.height() / 2 - 40, 45, 100, BLACK, BLACK, WHITE, "<", 5);
    drawDrink();
    if (previousDrink)
    {
        backBtn.drawButton(false);
    }
    if (nextDrink)
    {
        forwardBtn.drawButton(false);
    }
}

void draw::printCenter(char *str)
{
    int16_t x, y, x1, y1;
    uint16_t w, h;
    x = tft.width() / 2;
    y = tft.getCursorY();
    tft.getTextBounds(str, 0, y, &x1, &y1, &w, &h);
    tft.setCursor(x - (w / 2), y);
    tft.print(str);
}

int draw::drawDrink()
{
    uint8_t ingrIter = 0;
    fillBody();
    tft.setCursor(60, 75);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    printCenter(Parser.cocktail.name);
    while (Parser.cocktail.ingridients[ingrIter].liquor[0] != '\0')
    {
        tft.setTextSize(2);
        tft.setCursor(60, (24 * ingrIter) + 120);
        printCenter(Parser.cocktail.ingridients[ingrIter].liquor);
        ingrIter++;
    }
    if (Parser.required[0] != '\0')
    {
        tft.setTextColor(RED);
        tft.setCursor(tft.width() / 2, tft.height() / 2);
        printCenter("REQUIRES:");
        tft.setCursor(tft.width() / 2, tft.height() / 2 + 20);
        printCenter(Parser.required);
    }
    if (Parser.garnish[0] != '\0')
    {
        tft.setTextColor(WHITE);
        tft.setCursor(tft.width() / 2, tft.height() / 2 + 40);
        printCenter("Garnish with:");
        tft.setCursor(tft.width() / 2, tft.height() / 2 + 60);
        printCenter(Parser.garnish);
    }
    pourBtn.initButton(&tft, (tft.height() - tft.width()), tft.height() - 100, tft.width() - 80, 100, BLACK, WHITE, BLACK, "Pour", 3);
    pourBtn.drawButton(false);
}

int draw::drawMenu()
{
    fillBody();
    drawHeader();
    randomBtn.initButton(&tft, (tft.width() / 2), tft.height() / 2 - 100, 260, 110, WHITE, WHITE, BLACK, "Random", 3);
    browseBtn.initButton(&tft, (tft.width() / 2), tft.height() / 2 + 30, 260, 110, WHITE, WHITE, BLACK, "Browse", 3);
    customBtn.initButton(&tft, (tft.width() / 2), tft.height() / 2 + 160, 260, 110, WHITE, WHITE, BLACK, "Custom", 3);
    randomBtn.drawButton(false);
    browseBtn.drawButton(false);
    customBtn.drawButton(false);
}

void draw::setupTFT()
{
    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(2);
    tft.fillScreen(BLACK);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
}

bool draw::drawSplash()
{
    tft.setTextSize(4);
    tft.setCursor((tft.width() / 2) - 28, 30);
    tft.print("The");
    tft.setCursor(60, 55);
    tft.print("Bartender");
    // tft.drawLine(40, 95, tft.width() - 40, 95, WHITE);
    // tft.drawLine(40, 96, tft.width() - 40, 96, WHITE);
    tft.drawBitmap(0, 115, cocktails, 320, 120, WHITE);
    tft.setCursor(tft.width() / 3 - 16, tft.height() - 50);
    tft.setTextSize(1);
    tft.print("Designed by Gabriel Rytov");
    tft.setCursor(tft.width() / 3 + 15, tft.height() - 35);
    tft.print("Made in Israel");
    tft.setCursor((tft.width() / 2) - 38, tft.height() - 20);
    tft.print(F("Version: "));
    tft.println(version);
    tft.setCursor(tft.width() / 2, 250);
    tft.setTextSize(2);
    printCenter("Loading...");
    drawLoading(tft.width() / 2, tft.height() / 2 + 100);
    tft.fillScreen(BLACK);
}
