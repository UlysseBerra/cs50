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
    for (int i = 0; i < (int)round(sizeof(file) / 512); i = i + 512)
    {
        // check if file is jpeg
        fread(bytes, sizeof(BYTE), 3, file);

        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
        {
            printf("Yes, possibly\n");
        }
        else
        {
            printf("No\n");
        }
    }

    // close file and free memory

    fclose(file);
    free(bytes);



}