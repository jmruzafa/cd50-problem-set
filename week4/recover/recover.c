#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

void closeFile(FILE *file);
FILE *createFile(char *filename);

int main(int argc, char *argv[])
{
    /*
    ope memory card
    repat until end of car:
        read 512 bytes into buffer
        if start of new jpeg
            if first jpeg
            ...
            else
        else
            if already found jpeg
            ....    
    close any reamining file
    */
    if (argc <= 1 || argc > 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    //buffer 512 bytes to store what we read from file
    BYTE buffer[512];

    //number of images found
    int imgcount = 0;

    //file name
    char filename[] = "000.jpg";
    
    //output file pointer
    FILE *outptr = NULL; 

    //number of element returns (==bytes)
    size_t n = 512;
      
    while (!feof(inptr))
    {
        //start reading in chunks of 512 bytes
        n = fread(buffer, sizeof(BYTE), 512, inptr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //a new jpeg file has found. check if we have a previous file opened and close it first.
            if (outptr != NULL) 
            {
                closeFile(outptr);
            }
            //format name
            sprintf(filename, "%03i.jpg", imgcount);
            imgcount++;
            // create output file
            outptr = createFile(filename);
        }
        if (outptr != NULL)
        {
            //write into the output file if blocks are complete
            if (n == 512)
            {
                fwrite(buffer, sizeof(BYTE), 512, outptr);
            }
        }         
    }
    // Close any remaining open file
    closeFile(outptr);
    closeFile(inptr);
    //printf("%i\n", imgcount);
}

void closeFile(FILE *file)
{
    //check whether the file is not null and close it
    if (file != 0 || file != NULL)
    {
        fclose(file);
    }
}

FILE *createFile(char *filename)
{
    //create a new file a return the pointer
    FILE *outptr = fopen(filename, "w");
    if (outptr == NULL)
    {
        //if opening the file goes wrong return a NULL pointer
        fprintf(stderr, "Could not create %s.\n", filename);
        return NULL;
    }
    return outptr;
}
