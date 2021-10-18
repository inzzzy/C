#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - -
    -           Corrupts Audio File via XOR             -
    - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav <xorKey>\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int16_t xorKey = atoi(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(&header, sizeof(header), 1, input);
    fwrite(&header, sizeof(header), 1, output);

    // Read samples from input file and write updated data to output file
    int16_t buffer;
    int16_t value = 0;   
    int skip = 0;
    int16_t latest;
    int16_t increment = 100;

    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer ^= xorKey;
        latest = buffer;
        fwrite(&buffer, sizeof(buffer), 7, output);
    }
    
    fclose(input);
    fclose(output);
    
    // Turn your volume down before playing !!!
}
