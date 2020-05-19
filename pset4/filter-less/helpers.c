#include "helpers.h"
#include <math.h>

int checkpixvalue(int channel_value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //go through the image
    for (int i = 0; i < height; i++)
    {
        int gray_value;
        for (int j = 0; j < width; j++)
        {
            //calculate the average of the colour channels
            gray_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //assign the grey value to the different channels
            image[i][j].rgbtBlue = gray_value;
            image[i][j].rgbtGreen = gray_value;
            image[i][j].rgbtRed = gray_value;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //sepia formula
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    int sepiared = 0, sepiagreen = 0, sepiablue = 0;
    //go through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //check if the value goes beyond 0xff to set the maximum in that case
            sepiared = checkpixvalue(round(0.393 * image[i][j].rgbtRed  + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
            sepiagreen = checkpixvalue(round(0.349 * image[i][j].rgbtRed  + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            sepiablue = checkpixvalue(round(0.272 * image[i][j].rgbtRed  + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            //assign the grey value to the different channels
            image[i][j].rgbtBlue = sepiablue;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtRed = sepiared;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //temporal var
    RGBTRIPLE tmp;

    int mid;
    //depending if the width is even or odd we calculate a bit different to optimize the calculations
    if (width % 2 == 0)
    {
        mid = (width / 2) - 1;
    }
    else
    {
        mid = width / 2;
    }
    //go through the image
    for (int i = 0; i < height; i++)
    {
        //now we iterate till the mid pixel, not through the whole row
        for (int j = 0; j <= mid; j++)
        {
            //we have to swap values from the pixel that is 'mirroring'
            int mirror = width - j - 1;
            tmp = image[i][j];
            image[i][j] = image[i][mirror];
            image[i][mirror] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float counter;
    int sumblue, sumgreen, sumred;
    int x;
    int y;
    //temporary image to store new values
    RGBTRIPLE imgtemp [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            counter = 0.0;
            sumred = 0;
            sumgreen = 0;
            sumblue = 0;
            
            //now we start iterating through a sub-array around the pixel
            
            for (int h = -1; h <= 1; h++)
            {
                x = i + h;
                for (int w = -1; w <= 1; w ++)
                {
                    y = j + w;

                    if ((x >= 0 && y >= 0) && (x < height && y < width))
                    {
                        sumred += image[x][y].rgbtRed;
                        sumgreen += image[x][y].rgbtGreen;
                        sumblue += image[x][y].rgbtBlue;
                        counter++;
                    }
                }
            }
            imgtemp[i][j].rgbtRed = round(sumred / counter);
            imgtemp[i][j].rgbtGreen = round(sumgreen / counter);
            imgtemp[i][j].rgbtBlue = round(sumblue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imgtemp[i][j].rgbtRed;
            image[i][j].rgbtGreen = imgtemp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imgtemp[i][j].rgbtBlue;
        }
    }
}

int checkpixvalue(int channel_value)
{
    return round(channel_value) > 255 ? 255 : round(channel_value);
}