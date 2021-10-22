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

void parser::closeFile()
{
    file.close();
}

void parser::setFile(const char *filename)
{
    file = SD.open(filename, FILE_READ);
}

bool parser::seekChar(int position, char delimiter)
{ // Will set and return the position of the next desired delimiter
    int bufferPos = 0;
    while (buffer[bufferPos] != '\0')
    {
        if (buffer[bufferPos] == delimiter)
        {
            file.seek(position + bufferPos + 1);
            return true;
        }
        bufferPos++;
    }
    return false;
}

char *parser::bufferStringFromFile(unsigned int position, char delimiter)
{ // Get any string from a starting position until a specified delimiter
    clearBuffer();
    file.seek(position + 1);
    for (unsigned int filePos = file.position();; filePos++) // Iterate forward infinitely
    {
        file.seek(filePos);
        readByte = file.peek();
        if (readByte == delimiter) // If delimiter detected
        {
            file.seek(position);
            file.read(buffer, filePos - position);
            return buffer;
        }
    }
}

void parser::lexBufferToCocktail(const char *name)
{ // Split up the buffer string into according sub strings
    if (file)
    {
        fileSize = file.size();
        savePos = 0;
        for (unsigned int filePos = savePos; filePos <= fileSize; filePos++) // Loop through entire file
        {
            file.seek(filePos);
            readByte = file.peek();
            if (readByte == newLine) // Stop at every new line
            {
                savePos = file.position();
                bufferStringFromFile(savePos + 1, newArray);
                if (strcmp(buffer, name) == 0) 
                {
                    bufferStringFromFile(savePos + 1, endLine);
                    seekChar(savePos, newArray);
                    bufferStringFromFile(savePos + 1, endArray);
                    strcpy(Parser.recipe, buffer);
                    bufferStringFromFile(savePos + 1, endLine);
                    Serial.println(buffer);
                    if (seekChar(savePos, newRequire))
                    { // If '[' is a char in the buffer
                        bufferStringFromFile(file.position() + 1, endRequire);
                        strcpy(Parser.required, buffer);
                        Serial.println(Parser.required);
                        bufferStringFromFile(savePos + 1, endLine);
                    }
                    if (seekChar(savePos, newGarnish))
                    { // If '(' is a char in the buffer
                        bufferStringFromFile(file.position() + 1, endGarnish);
                        strcpy(Parser.garnish, buffer);
                        Serial.println(Parser.garnish);
                        bufferStringFromFile(savePos + 1, endLine);
                    }
                }
            }
        }
    }
    else
        Serial.println("Error: Failed to open file.");
}

void parser::getRecipe(char *name)
{
    char *token;
    uint8_t ingrIter = 0;
    uint8_t elements = 0;
    bool recipeString = false;
    lexBufferToCocktail(name); // Stores input name into buffer
    clearCocktail();
    for (token = strtok(recipe, ",;{}"); token != NULL; token = strtok(NULL, ",;{}"))
    {
        if (recipeString == false) // If name is not read
        {
            strcpy(Parser.cocktail.name, token);
            recipeString = true;
        }
        else if (recipeString == true) // If name is read
        {
            if ((elements % 2) == 0) // Evens are liquor names
            {
                strcpy(Parser.cocktail.ingridients[ingrIter].liquor, token);
                elements++;
            }
            else if ((elements % 2) == 1) // Odds are portion sizes
            {
                Parser.cocktail.ingridients[ingrIter].portion = atoi(token);
                elements++;
                ingrIter++; // Iterate through ingridients[8]
            }
        }
    }
    // Used for troubleshooting- comment out when not needed
    // Serial.println(Parser.cocktail.name);
    // ingrIter = 0;
    // while (Parser.cocktail.ingridients[ingrIter].liquor[0] != '\0')
    // {
    //     Serial.println(Parser.cocktail.ingridients[ingrIter].liquor);
    //     Serial.println(Parser.cocktail.ingridients[ingrIter].portion);
    //     ingrIter++;
    // }
}
