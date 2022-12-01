#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFSIZE (50000*sizeof(char))

typedef unsigned int uint;

bool ReadPuzzleInput(const char* name, char* content) {
    char path[64];
    sprintf(path,"Inputs/%s.txt", name);

    FILE *file = fopen(path, "r");
    if (file != 0)
    {
        uint counter = 0;
        while (1)
        {
            char c = fgetc(file);
            if (feof(file))
            {
                content[counter] = '\0';
                break;
            }
            content[counter] = c;
            counter++;
        }
        fclose(file);
        return true;
    }
    else
    {
        printf("File does not exist!\n");
        return false;
    }
}
