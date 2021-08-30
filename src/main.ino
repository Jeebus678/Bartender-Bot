#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <SD.h>
#include <SPI.h>
#include <Pump.h>
#include <string.h>
using namespace std;

const uint8_t chipSelect = 10; // Sets the SD chip-select pin, enabled on Mega through SOFT-SPI
Sd2Card card;
SdFile root;


void setup()
{
    Serial.begin(9600);
    while (!Serial)
        continue;

    pinMode(SS, OUTPUT); // Required for SD library to function
    while (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("SD initialization failed."); 
  } 
    //   loadCocktail(filename, data, "Americano");
    // Set up all control pins, touch screen, etc.
    // Determine input drinks and their volumes.
    // Determine all the potential drinks based off 
    // input drinks and save them as objects.
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

// const char *filename = "/cocktail.json";

// struct cocktailData
// {
//     char name[25];
//     const char *portions[7][1];
// } data;

// void loadCocktail(const char *filename, cocktailData &data, String drinkName)
// {
    
// }

//---------- Read a struct from file
// Cocktail c[3]; //struct for holding the content from the file

// File fileToRead = SPIFFS.open("/cocktails.txt");

// if (fileToRead)
// {
//   Serial.println("Data from file...");
//   for (int i = 0; i < 3; i++)
//   {
//     fileToRead.read((byte *)&c[i], sizeof(c[i]));
//     Serial.println(c[i].name);
//     int n = 0;
//     while (strlen(c[i].ingridients[n].liquor))
//     {
//       Serial.print(c[i].ingridients[n].liquor);
//       Serial.print(" - ");
//       Serial.print(c[i].ingridients[n].portion);
//       n++;
//     }
//     Serial.println();
//   }
// }

// fileToRead.close();
// }