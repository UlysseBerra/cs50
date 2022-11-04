#include "helpers.h"
#include <math.h>

// Swap two values
void swap(BYTE *a, BYTE *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height - 1][width - 1])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // getting pixel's average color
            int avg_color = (int)round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // setting right color
            image[i][j].rgbtRed = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtBlue = avg_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height - 1][width - 1])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // gets the values of each color in the image
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            // gets the sepia value of the pixels
            int sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue);

            int sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);

            int sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);

            if (sepiaRed >= 256)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen >= 256)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue >= 256)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height - 1][width - 1])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - 1 - j].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - 1 - j].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - 1 - j].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height - 1][width - 1])
{
    RGBTRIPLE tmp[height - 1][width - 1]; //array for storing a tmporary copy

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j]; //copying the data in the tmporary filter
        }
    }

    //Left top corner
    image[0][0].rgbtBlue = (int) round((tmp[0][0].rgbtBlue + tmp[0][1].rgbtBlue + tmp[1][0].rgbtBlue + tmp[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = (int) round((tmp[0][0].rgbtGreen + tmp[0][1].rgbtGreen + tmp[1][0].rgbtGreen + tmp[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = (int) round((tmp[0][0].rgbtRed + tmp[0][1].rgbtRed + tmp[1][0].rgbtRed + tmp[1][1].rgbtRed) / 4.0);

    //Right top corner
    image[0][width - 1].rgbtBlue = (int) round((tmp[0][width - 1].rgbtBlue + tmp[0][width - 2].rgbtBlue + tmp[1][width - 1].rgbtBlue + tmp[1][width - 2].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = (int) round((tmp[0][width - 1].rgbtGreen + tmp[0][width - 2].rgbtGreen + tmp[1][width - 1].rgbtGreen + tmp[1][width - 2].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = (int) round((tmp[0][width - 1].rgbtRed + tmp[0][width - 2].rgbtRed + tmp[1][width - 1].rgbtRed + tmp[1][width - 2].rgbtRed) / 4.0);

    //Left bottom corner
    image[height - 1][0].rgbtBlue = (int) round((tmp[height - 1][0].rgbtBlue + tmp[height - 1][1].rgbtBlue + tmp[height - 2][0].rgbtBlue + tmp[height - 2][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = (int) round((tmp[height - 1][0].rgbtGreen + tmp[height - 1][1].rgbtGreen + tmp[height - 2][0].rgbtGreen + tmp[height - 2][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = (int) round((tmp[height - 1][0].rgbtRed + tmp[height - 1][1].rgbtRed + tmp[height - 2][0].rgbtRed + tmp[height - 2][1].rgbtRed) / 4.0);

    //Right bottom corner
    image[height - 1][width - 1].rgbtBlue = (int) round((tmp[height - 1][width - 1].rgbtBlue + tmp[height - 1][width - 2].rgbtBlue + tmp[height - 2][width - 1].rgbtBlue + tmp[height - 2][width - 2].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = (int) round((tmp[height - 1][width - 1].rgbtGreen + tmp[height - 1][width - 2].rgbtGreen + tmp[height - 2][width - 1].rgbtGreen + tmp[height - 2][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = (int) round((tmp[height - 1][width - 1].rgbtRed + tmp[height - 1][width - 2].rgbtRed + tmp[height - 2][width - 1].rgbtRed + tmp[height - 2][width - 2].rgbtRed) / 4.0);

    //First row
    for (int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtBlue = (int) round((tmp[0][i - 1].rgbtBlue + tmp[0][i].rgbtBlue + tmp[0][i + 1].rgbtBlue + tmp[1][i - 1].rgbtBlue + tmp[1][i].rgbtBlue + tmp[1][i + 1].rgbtBlue) / 6.0);
        image[0][i].rgbtGreen = (int) round((tmp[0][i - 1].rgbtGreen + tmp[0][i].rgbtGreen + tmp[0][i + 1].rgbtGreen + tmp[1][i - 1].rgbtGreen + tmp[1][i].rgbtGreen + tmp[1][i + 1].rgbtGreen) / 6.0);
        image[0][i].rgbtRed = (int) round((tmp[0][i - 1].rgbtRed + tmp[0][i].rgbtRed + tmp[0][i + 1].rgbtRed + tmp[1][i - 1].rgbtRed + tmp[1][i].rgbtRed + tmp[1][i + 1].rgbtRed) / 6.0);
    }

    //Last row
    for (int i = 1; i < width - 1; i++)
    {
        image[height - 1][i].rgbtBlue = (int) round((tmp[height - 1][i - 1].rgbtBlue + tmp[height - 1][i].rgbtBlue + tmp[height - 1][i + 1].rgbtBlue + tmp[height - 2][i - 1].rgbtBlue + tmp[height - 2][i].rgbtBlue + tmp[height - 2][i + 1].rgbtBlue) / 6.0);
        image[height - 1][i].rgbtGreen = (int) round((tmp[height - 1][i - 1].rgbtGreen + tmp[height - 1][i].rgbtGreen + tmp[height - 1][i + 1].rgbtGreen + tmp[height - 2][i - 1].rgbtGreen + tmp[height -1][i].rgbtGreen + tmp[height - 2][i + 1].rgbtGreen) / 6.0);
        image[height - 1][i].rgbtRed = (int) round((tmp[height - 1][i - 1].rgbtRed + tmp[height - 1][i].rgbtRed + tmp[height - 1][i + 1].rgbtRed + tmp[height - 2][i - 1].rgbtRed + tmp[height - 2][i].rgbtRed + tmp[height - 2][i + 1].rgbtRed) / 6.0);
    }

    //First column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][0].rgbtBlue = (int) round((tmp[i - 1][0].rgbtBlue + tmp[i][0].rgbtBlue + tmp[i + 1][0].rgbtBlue + tmp[i - 1][1].rgbtBlue + tmp[i][1].rgbtBlue + tmp[i + 1][1].rgbtBlue) / 6.0);
        image[i][0].rgbtGreen = (int) round((tmp[i - 1][0].rgbtGreen + tmp[i][0].rgbtGreen + tmp[i + 1][0].rgbtGreen + tmp[i - 1][1].rgbtGreen + tmp[i][1].rgbtGreen + tmp[i + 1][1].rgbtGreen) / 6.0);
        image[i][0].rgbtRed = (int) round((tmp[i - 1][0].rgbtRed + tmp[i][0].rgbtRed + tmp[i + 1][0].rgbtRed + tmp[i - 1][1].rgbtRed + tmp[i][1].rgbtRed + tmp[i + 1][1].rgbtRed) / 6.0);
    }

    //Last column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][width - 1].rgbtBlue = (int) round((tmp[i - 1][width - 1].rgbtBlue + tmp[i][width - 1].rgbtBlue + tmp[i + 1][width - 1].rgbtBlue + tmp[i - 1][width - 2].rgbtBlue + tmp[i][width - 2].rgbtBlue + tmp[i + 1][width - 2].rgbtBlue) / 6.0);
        image[i][width - 1].rgbtGreen = (int) round((tmp[i - 1][width - 1].rgbtGreen + tmp[i][width - 1].rgbtGreen + tmp[i + 1][width - 1].rgbtGreen + tmp[i - 1][width - 2].rgbtGreen + tmp[i][width - 2].rgbtGreen + tmp[i + 1][width - 2].rgbtGreen) / 6.0);
        image[i][width - 1].rgbtRed = (int) round((tmp[i - 1][width - 1].rgbtRed + tmp[i][width - 1].rgbtRed + tmp[i + 1][width - 1].rgbtRed + tmp[i - 1][width - 2].rgbtRed + tmp[i][width - 2].rgbtRed + tmp[i + 1][width - 2].rgbtRed) / 6.0);
    }

    //Rest of cells
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtBlue = (int)(round)((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 9.0);
            image[i][j].rgbtGreen = (int)(round)((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 9.0);
            image[i][j].rgbtRed = (int)(round)((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 9.0);
        }
    }

    return;
}