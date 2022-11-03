#include "helpers.h"

// Swap two values
void swap(BYTE *a, BYTE *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
         for (int j = 0; j < width; j++)
        {
            int avg_color = (int)round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtBlue = avg_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiaRed = (int)round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            double sepiaGreen = (int)round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            double sepiaBlue = (int)round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width-j].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width-j].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width-j].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // go through rows
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

        }
    }
    return;
}