#include <Arduino.h>
#include <ArduinoJson.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <SD.h>
#include <SPI.h>
#include <Pump.h>
#include <string.h>
using namespace std;


void setup()
{
    Serial.begin(9600);
    while (!Serial)
        continue;
    


    //   loadCocktail(filename, data, "Americano");
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

//

// DynamicJsonDocument doc(bufferSize);
// JsonObject obj;
// obj = getJSonFromFile(&doc, filename);

// JsonObject getJSonFromFile(DynamicJsonDocument *cocktailList, String filename, bool forceCleanONJsonError = true)

const char *filename = "/cocktail.json";

struct cocktailData
{
    char name[25];
    const char *portions[7][1];
} data;

void loadCocktail(const char *filename, cocktailData &data, String drinkName)
{
    File jsonCocktailList = SD.open(filename);
    const size_t bufferSize = JSON_OBJECT_SIZE(1) + 6 * JSON_OBJECT_SIZE(2) + 28 * JSON_OBJECT_SIZE(3) + 11 * JSON_OBJECT_SIZE(4) + 7 * JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(8) + JSON_OBJECT_SIZE(56);
    StaticJsonDocument<bufferSize> doc;
    // DeserializationError error = deserializeJson(doc, filename);
    // if (error)
    // {
    //   Serial.println(F("Failed to read file, using default configuration"));
    //   Serial.println(error.f_str());
    // }

    JsonObject root = doc.as<JsonObject>();
    for (JsonPair kv : root)
    {
        // int i = 0;
        // data.portions[i][0] = ;
        Serial.println(kv.key().c_str());
    }
    jsonCocktailList.close();
}