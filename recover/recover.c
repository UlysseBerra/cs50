#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check usage
    if (argc != 2)
    {
        printf("This program takes one and only one argument.\n");
        return 1;
    }

    else
    {
        // open input file
        FILE *infile = fopen(argv[1], "r");

        if (!infile || infile == NULL)
        {
            printf("Couldn't open file.");
            return 2;
        }

        // initialise variables
        BYTE buffer[512];
        int count_image = 0;
        FILE *outfile = NULL;
        char filename[8];

        // until end of file is reached
        while (fread(&buffer, 512, 1, infile) == 1)
        {
            // if start of jpg detected (0xff 0xd8 0xff 0xe*)
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                buffer[3] >= 0xe0 &&
                buffer[3] <= 0xef)
            {
                // if not first jpg, close previous file
                if (count_image != 0)
                {
                    fclose(outfile);
                }

                // name and create file
                sprintf(filename, "%03i.jpg", count_image);
                outfile = fopen(filename, "w");

                // increment counter
                count_image++;
            }

            // write to file
            if (count_image != 0)
            {
                fwrite(&buffer, 512, 1, outfile);
            }
        }

        // close files
        fclose(infile);
        fclose(outfile);

        return 0;
    }
}