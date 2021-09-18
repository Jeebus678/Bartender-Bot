// Basic SD card parser
//
// Function Architechture:
// Once the parse() function is called it passes the name parameter to
// getRecipeString(). It scans through the file, looking for an item with a
// matching name (so $_name_ for example). getRecipeString() also calls on
// bufferString() multiple times, which reads starting from a position
// until a delimiter from the SD card.

#include <parser.h>
#include <SD.h>
#include <stdio.h>

void parser::clearBuffer()
{
    for (unsigned int erase = 0; erase < sizeof(buffer); erase++)
    {
        buffer[erase] = '\0';
    }
}

void parser::setFile(const char *filename)
{
    file = SD.open(filename, FILE_READ);
}

int parser::seekChar(char *delimiter)
{ // Will set and return the position of the next desired delimiter
    fileSize = file.size();
    for (unsigned int i = file.position(); i <= fileSize; i++)
    {
        file.seek(i);
        readByte = file.peek();
        if (readByte == *delimiter)
        {
            return file.position();
            break;
        }
        else
            continue;
    }
}

char *parser::bufferString(unsigned int position, char delimiter) // Get any string from a starting position until a specified delimiter
{
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

void parser::getRecipeString(const char *name) // Retrieve a cocktail's recipe string
{
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
                if (strcmp(buffer, name) == 0)
                {                                   // Does the name parameter match the buffer string?
                    bufferString(pos + 1, endLine); // If it does, save the drink to the buffer
                    break;
                }
            }
        }
        file.close();
    }
    else
        Serial.println("Error: Failed to open file.");
}

void parser::getRecipe(char *name)
{
    char *p;
    uint8_t n = 0;
    uint8_t iter = 0;
    boolean recipeString = false;
    getRecipeString(name); // Stores input name into buffer
    for (p = strtok(buffer, "{,;"); p != NULL; p = strtok(NULL, "{,;"))
    {
        if (recipeString == false) // If name is not read
        {
            strcpy(cocktail.name, p);
            recipeString = true;
        }
        else if (recipeString == true) // If name is read
        {
            if ((iter % 2) == 0) // Evens are liquor names
            {
                strcpy(cocktail.ingridients[n].liquor, p);
                iter++;
            }
            else if ((iter % 2) == 1) // Odds are portion sizes
            {
                strcpy(cocktail.ingridients[n].portion, p);
                iter++;
                n++; // Iterate through ingridients[8]
            }
        }
    }
    // Used for troubleshooting- comment out when not needed
    Serial.println(cocktail.name);
    for (int i = 0; i < 8; i++)
    {
        Serial.println(cocktail.ingridients[i].liquor);
        Serial.println(cocktail.ingridients[i].portion);
    }
}
