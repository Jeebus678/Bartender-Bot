#ifndef PARSER_H_
#define PARSER_H_
#include <SD.h>
#include <stdio.h>

class parser
{
public:
    // Struct for storing SD variables
    typedef struct Ingridient
    {
        char liquor[30];
        char portion[2];
    } Ingridient;

    struct Drink
    {
        char name[30];
        Ingridient ingridients[8];
    };

    // Definitions (delimiters below)
    File file;
    Drink cocktail;
    unsigned int fileSize;
    unsigned int pos = 0;
    char buffer[100];
    char readByte;
    const char newArray = '{';
    const char newElement = ';';
    const char divider = ',';
    const char endLine = '}';
    const char newLine = '$';

    // Functions 
    void clearBuffer();
    void setFile(const char *filename);
    void getRecipe(const char *name);
    char *bufferString(unsigned int position, char delimiter);
    void parse(char *name);
};

#endif