#include <math.h>
#include "helpers.h"

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
