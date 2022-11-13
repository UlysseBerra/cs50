#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // check usage
    if (argc != 2)
    {
        printf("This program takes one and only one argument.\n");
        return 1;
    }

    // open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    BYTE bytes[3];


    // close file
    fclose(file);
}