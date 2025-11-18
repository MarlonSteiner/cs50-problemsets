#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int magicnumber = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *memory = fopen(argv[1], "r");

    // Check if file was opened properly
    if (memory == NULL)
    {
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[magicnumber];
    FILE *img = NULL;
    int j = 0, counter = 0;
    char image[] = "000.jpg";

    while (fread(&buffer, 1, magicnumber, memory) == magicnumber)
    {
        // Look for start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // If first JPEG
            if (j == 0)
            {
                // Create JPEG file
                sprintf(image, "%03i.jpg", counter);
                img = fopen(image, "w");
                fwrite(&buffer, magicnumber, 1, img);
                j++;
            }
            else
            {
                // Close current file
                fclose(img);

                // Create JPEG file
                sprintf(image, "%03i.jpg", counter += 1);
                img = fopen(image, "w");
                fwrite(&buffer, magicnumber, 1, img);
            }
        }
        else
        {
            if (j > 0)
            {
                fwrite(&buffer, magicnumber, 1, img);
            }
        }
    }
    // Close any remaining files
    fclose(memory);
    fclose(img);
}
