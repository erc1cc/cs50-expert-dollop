#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *initialize = fopen(argv[1], "r");
    if (initialize == NULL)
    {
        printf("Unable to read file.\n");
        return 2;
    }

    // creates a buffer of size 512 bytes
    uint8_t buffer[512];

    // image counter
    int counter = 0;


    FILE *img = NULL;

    // while the amount of bytes read is equal to a block of 512 bytes
    while (fread(buffer, 512, 1, initialize) == 1)
    {
        // checks for JPEGs / beginning of a new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // check if img is NULL, or if img is not the first JPEG file declared
            // when the program detects another JPEG, we close the previous JPEG file
            // makes sure fclose is only called if img points to a valid file
            if (img != NULL)
            {
                fclose(img);
            }

            // creates string named filename
            char filename[8];

            // creates file names and writes them to a string called filename
            // filenames: ###.jpg starting at 000.jpg
            sprintf(filename, "%03i.jpg", counter++);

            // creates another file called img in write mode
            img = fopen(filename, "w");

            // if there's an error, we close everything
            if (img == NULL)
            {
                fclose(initialize);
                printf("Unable to create file: %s\n", filename);
                return 3;
            }
        }

        // write current 512 BYTE block to the JPEG file after checking for JPEG
        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    // close everything
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(initialize);
    return 0;
}
