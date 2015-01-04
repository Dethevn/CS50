/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE; 

int main(void)
{
    // ready only, hard coded
    FILE* file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
        
    // get file size to create proper loop & reset file pointer to beginning
    fseek(file, 0, SEEK_END);
    int eof = ftell(file);   
    fseek(file, 0, SEEK_SET);
    
    // two JPEG cases, see above main for BYTE typedef
    BYTE jpeg[4] = {0xff, 0xd8, 0xff, 0xe0};
    BYTE jpeg1[4] = {0xff, 0xd8, 0xff, 0xe1};   
    
    // int to keep track of jpegs
    int counter = 0;
    
    // BUFFER to hold each 512 block
    BYTE buffer[512];
    
    // string to hold file name for each jpg, 015.jpg + null = 8
    char *title = (char *) malloc(8);
    FILE* img = NULL;
   
    for (int i = 0; i < eof; i+= 512)
    {  
        // tests to ensure there is still data to read from file
        if (fread(&buffer, 512*sizeof(BYTE), 1, file) == 1)
        {
            // compare first 4 bytes of temp to jpeg pattern to locate start of jpeg
            if (memcmp(jpeg, buffer, sizeof(jpeg)) == 0 || memcmp(jpeg1, buffer, sizeof(jpeg1)) == 0)
            {
                // if img is open, start new image as new start identified
                if (img != NULL)
                {
                    fclose(img);
                    counter++;
                    sprintf(title, "%03d.jpg", counter);
                    img = fopen(title, "w"); 
                }
                // for the first image as there is garbage before first jpeg
                else
                {
                    sprintf(title, "%03d.jpg", counter);
                    img = fopen(title, "w");
                }
            }      
            
            // write to buffer as long as a file is open
            if (img != NULL)
                fwrite(&buffer, 512*sizeof(BYTE), 1, img); 
        }
        else
            break;
    } 
    fclose(img);
    fclose(file);
    free(title);
       
    return 0;
}
