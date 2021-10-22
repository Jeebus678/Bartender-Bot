// Basic SD card parser
//
// Function Architechture:
// Once the parse() function is called it passes the name parameter to
// lexer(). It scans through the file, looking for an item with a
// matching name (so $_name_ for example). lexer() also calls on
// bufferString() multiple times, which reads starting from a position
// until a delimiter from the SD card.

#include "parser.h"
#include <SD.h>
#include <stdio.h>

parser Parser;

void parser::clearBuffer()
{
    for (unsigned int erase = 0; erase < sizeof(buffer); erase++)
    {
        buffer[erase] = '\0';
    }
}

void parser::clearCocktail()
{
    unsigned int ingrIterate = 0;
    Parser.cocktail.name[0] = '\0';
    while (Parser.cocktail.ingridients[ingrIterate].liquor[0] != '\0')
    {
        Parser.cocktail.ingridients[ingrIterate].liquor[0] = '\0';
        Parser.cocktail.ingridients[ingrIterate].portion = 0;
        ingrIterate++;
    }
}

void parser::close()
{
    file.close();
}

void parser::setFile(const char *filename)
{
    file = SD.open(filename, FILE_READ);
}

bool parser::seekChar(int position, char delimiter)
{ // Will set and return the position of the next desired delimiter
    int i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == delimiter)
        {
            file.seek(position + i + 1);
            return true;
        }
        i++;
    }
    return false;
}

char *parser::bufferString(unsigned int position, char delimiter)
{ // Get any string from a starting position until a specified delimiter
    clearBuffer();
    file.seek(position + 1);
    for (unsigned int n = file.position();; n++) // Iterate forward infinitely
    {
        file.seek(n);
        readByte = file.peek();
        if (readByte == delimiter) // If delimiter detected
        {
            file.seek(position);
            file.read(buffer, n - position);
            return buffer;
        }
    }
}

void parser::lexer(const char *name)
{ // Split up the buffer string into according sub strings
    if (file)
    {
        fileSize = file.size();
        pos = 0;
        for (unsigned int i = pos; i <= fileSize; i++) // Loop through entire file
        {
            file.seek(i);
            readByte = file.peek();
            if (readByte == newLine) // Stop at every new line
            {
                pos = file.position();
                bufferString(pos + 1, newArray);
                if (strcmp(buffer, name) == 0) // Does the name match the input parameter?
                {
                    bufferString(pos + 1, endLine);
                    seekChar(pos, newArray);
                    bufferString(pos + 1, endArray);
                    strcpy(Parser.recipe, buffer);
                    bufferString(pos + 1, endLine);
                    Serial.println(buffer);
                    if (seekChar(pos, newRequire))
                    { // If '[' is a char in the buffer
                        bufferString(file.position() + 1, endRequire);
                        strcpy(Parser.required, buffer);
                        Serial.println(Parser.required);
                        bufferString(pos + 1, endLine);
                    }
                    if (seekChar(pos, newGarnish))
                    { // If '(' is a char in the buffer
                        bufferString(file.position() + 1, endGarnish);
                        strcpy(Parser.garnish, buffer);
                        Serial.println(Parser.garnish);
                        bufferString(pos + 1, endLine);
                    }
                }
            }
        }
        // file.close();
    }
    else
        Serial.println("Error: Failed to open file.");
}

void parser::getRecipe(char *name)
{
    char *p;
    uint8_t n = 0;
    uint8_t iter = 0;
    bool recipeString = false;
    lexer(name); // Stores input name into buffer
    clearCocktail();
    for (p = strtok(recipe, ",;{}"); p != NULL; p = strtok(NULL, ",;{}"))
    {
        if (recipeString == false) // If name is not read
        {
            strcpy(Parser.cocktail.name, p);
            recipeString = true;
        }
        else if (recipeString == true) // If name is read
        {
            if ((iter % 2) == 0) // Evens are liquor names
            {
                strcpy(Parser.cocktail.ingridients[n].liquor, p);
                iter++;
            }
            else if ((iter % 2) == 1) // Odds are portion sizes
            {
                Parser.cocktail.ingridients[n].portion = atoi(p);
                iter++;
                n++; // Iterate through ingridients[8]
            }
        }
    }
    // Used for troubleshooting- comment out when not needed
    // Serial.println(Parser.cocktail.name);
    // unsigned int i = 0;
    // while (Parser.cocktail.ingridients[i].liquor[0] != '\0')
    // {
    //     Serial.println(Parser.cocktail.ingridients[i].liquor);
    //     Serial.println(Parser.cocktail.ingridients[i].portion);
    //     i++;
    // }
}
