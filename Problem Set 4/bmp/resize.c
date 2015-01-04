/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int rnum = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Create outfile's headers
    BITMAPFILEHEADER bfout = bf;
    BITMAPINFOHEADER biout = bi;
    
    // update header info for the outfile
    biout.biWidth = bi.biWidth*rnum;
    biout.biHeight = bi.biHeight*rnum;
    
    // determine padding for scanlines
    int opad =  (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int ipad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update image size and bitmap file size.
    biout.biSizeImage = (sizeof(RGBTRIPLE)*abs(biout.biHeight)*biout.biWidth)+opad*abs(biout.biHeight);
    bfout.bfSize = biout.biSizeImage + (sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));
    
    // write outfile's header files
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);

    // temporary storage to iterate correct amount of vertical copies
    RGBTRIPLE tarray[biout.biWidth];
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // index variable for cycling through tarray
        int tind = 0;
        
        // iterate over INFILE's pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)  
        {           
            // temporary storage for pixel to mulitply by rnum
            RGBTRIPLE triple;
            
            // read input file to the temp pixel storage
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // multiply pixel by desired rnum to scale horizontally
            for (int k = 0; k < rnum; k++)
            {
                tarray[tind] = triple;
                tind++;
            }
        }
         
        // skip over padding, if any
        fseek(inptr, ipad, SEEK_CUR);
        
        for (int l = 0; l < rnum; l++)
        {
            // write entire row of pixels at once using tarray, rnum times to scale vertically
            fwrite(&tarray, sizeof(RGBTRIPLE), biout.biWidth, outptr);
            
            // add padding if needed at end of each row of pixels
            for (int k = 0; k < opad; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
