#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checks
    if (argc != 2)
    {
        printf("Program accepts only one input.\n");
        return 1;
    }

    // Open Memory Card
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Memory Card can not be opened for read mode.\n");
        fclose(file);
        return 1;
    }

    // Block Size
    const int BLOCK_SIZE = 512;

    //JPEG Counter
    int counter = 0;

    // JPEG
    char *filename = malloc((sizeof(char) * 7) + 1);
    sprintf(filename, "%03i.jpg", counter);

    FILE *img = fopen(filename, "w");
    if (!img)
    {
        fclose(img);
        return 1;
    }

    // Buffer
    BYTE buffer[512];

    // Repeating Until the End of the Memory Card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // If Start of a JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] = 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // If First JPEG
            if (counter == 0)
            {
                //Write
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                counter ++;
            }
            else
            {
                // Close the Previous JPEG
                fclose(img);

                // Iterate
                sprintf(filename, "%03i.jpg", counter);
                fopen(filename, "w");
                counter ++;

                //Write
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
        // If Not the Start of a JPEG
        else
        {
            // If a JPEG Has Already Been Found
            if (counter > 0)
            {
                // Write
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }

    // Close Remaining Files
    fclose(file);
    free(filename);
}