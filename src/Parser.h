#ifndef PARSER_H_
#define PARSER_H_
// #pragma once
#include <SD.h>
#include <stdio.h>
#include "Pump.h"

class parser
{
public:
    // Struct for storing SD variables
    typedef struct Ingridient
    {
        char liquor[30];
        int portion;
    } Ingridient;

    struct Drink
    {
        char name[30];
        char note[30];
        char garnish[30];
        Ingridient ingridients[8];
    };

    // Definitions (delimiters below)
    File file;
    Drink cocktail;
    unsigned int fileSize;
    unsigned int pos = 0;
    char required[30]; 
    char garnish[50]; 
    char recipe[180]; 
    char buffer[250];
    char readByte;
    const char newLine = '$';
    const char newArray = '{';
    const char newElement = ';';
    const char divider = ',';
    const char endArray = '}';
    const char newRequire = '[';
    const char endRequire = ']';
    const char newGarnish = '(';
    const char endGarnish = ')';
    const char endLine = '?';
    char drinksBuffer[30][30]; // Holds list of drink names

    // Functions
    void clearBuffer();
    void clearCocktail();
    void close();
    void setFile(const char *filename);
    bool seekChar(int position, char delimiter);
    char *bufferString(unsigned int position, char delimiter);
    void lexer(const char *name);
    void getRecipe(char *name);

    template <size_t N>
    void getOptions(Pump *(&allPumps)[N]) // Gets all possible cocktails 
    {
        if (file)
        {
            char *p;
            char *o;
            fileSize = file.size();
            pos = 0;
            int posStart;
            int counter = 0;
            int drinkCount = 0;
            int maxMembers = 0;
            for (unsigned int i = pos; i < fileSize; i++) // Loop through entire file
            {
                file.seek(i);
                readByte = file.peek();
                if (readByte == newLine)
                {
                    posStart = file.position();
                }
                else if (readByte == newArray) // Stop at every new array
                {
                    counter = 0;
                    maxMembers = 0;
                    pos = file.position() + 1;
                    bufferString(pos, endArray); // Buffer the rest of the string
                    for (p = strtok(buffer, ";"); p != NULL; p = strtok(NULL, ";"))
                    {
                        maxMembers++;
                        o = strchr(p, ',');
                        *o = '\0'; // Cuts off everything except the ingredient name
                        for (unsigned int n = 0; n < N; n++)
                        {
                            if ((strcmp(allPumps[n]->drink, p) == 0))
                            {
                                counter++;
                                break;
                            }
                        }
                    }
                }
                else if ((readByte == endArray) && (counter == maxMembers))
                {
                    file.seek(posStart + 1);
                    bufferString(file.position(), newArray);
                    strcpy(drinksBuffer[drinkCount], buffer);
                    drinkCount++;
                }
            }
            // file.close();
            return; 
        }
        else
        {
            Serial.println("Error: Failed to open file.");
        }
    }
};

extern parser Parser; 

#endif