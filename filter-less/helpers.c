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
void grayscale(int height, int width, RGBTRIPLE image[height][width])
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
void sepia(int height, int width, RGBTRIPLE image[height][width])
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
void reflect(int height, int width, RGBTRIPLE image[height][width])
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
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // array for storing a temporary copy

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // top left corner
    image[0][0].rgbtBlue = (int) round((temp[0][0].rgbtBlue + temp[0][1].rgbtBlue + temp[1][0].rgbtBlue + temp[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = (int) round((temp[0][0].rgbtGreen + temp[0][1].rgbtGreen + temp[1][0].rgbtGreen + temp[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = (int) round((temp[0][0].rgbtRed + temp[0][1].rgbtRed + temp[1][0].rgbtRed + temp[1][1].rgbtRed) / 4.0);

    // top right corner
    image[0][width - 1].rgbtBlue = (int) round((temp[0][width].rgbtBlue + temp[0][width - 1].rgbtBlue + temp[1][width].rgbtBlue + temp[1][width - 1].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = (int) round((temp[0][width].rgbtGreen + temp[0][width - 1].rgbtGreen + temp[1][width].rgbtGreen + temp[1][width - 1].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = (int) round((temp[0][width].rgbtRed + temp[0][width - 1].rgbtRed + temp[1][width].rgbtRed + temp[1][width - 1].rgbtRed) / 4.0);

    // bottom left corner
    image[height][0].rgbtBlue = (int) round((temp[height][0].rgbtBlue + temp[height][1].rgbtBlue + temp[height - 1][0].rgbtBlue + temp[height - 1][1].rgbtBlue) / 4.0);
    image[height][0].rgbtGreen = (int) round((temp[height][0].rgbtGreen + temp[height][1].rgbtGreen + temp[height - 1][0].rgbtGreen + temp[height - 1][1].rgbtGreen) / 4.0);
    image[height][0].rgbtRed = (int) round((temp[height][0].rgbtRed + temp[height][1].rgbtRed + temp[height - 1][0].rgbtRed + temp[height - 1][1].rgbtRed) / 4.0);

    //Right bottom corner
    image[height][width].rgbtBlue = (int) round((temp[height][width].rgbtBlue + temp[height][width - 1].rgbtBlue + temp[height - 1][width].rgbtBlue + temp[height - 1][width - 1].rgbtBlue) / 4);
    image[height][width].rgbtGreen = (int) round((temp[height][width].rgbtGreen + temp[height][width - 1].rgbtGreen + temp[height - 1][width].rgbtGreen + temp[height - 1][width - 1].rgbtGreen) / 4);
    image[height][width].rgbtRed = (int) round((temp[height][width].rgbtRed + temp[height][width - 1].rgbtRed + temp[height - 1][width].rgbtRed + temp[height - 1][width - 1].rgbtRed) / 4);

    //First row
    for (int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtBlue = (int) round((temp[0][i - 1].rgbtBlue + temp[0][i].rgbtBlue + temp[0][i + 1].rgbtBlue + temp[1][i - 1].rgbtBlue + temp[1][i].rgbtBlue + temp[1][i + 1].rgbtBlue) / 6);
        image[0][i].rgbtGreen = (int) round((temp[0][i - 1].rgbtGreen + temp[0][i].rgbtGreen + temp[0][i + 1].rgbtGreen + temp[1][i - 1].rgbtGreen + temp[1][i].rgbtGreen + temp[1][i + 1].rgbtGreen) / 6);
        image[0][i].rgbtRed = (int) round((temp[0][i - 1].rgbtRed + temp[0][i].rgbtRed + temp[0][i + 1].rgbtRed + temp[1][i - 1].rgbtRed + temp[1][i].rgbtRed + temp[1][i + 1].rgbtRed) / 6);
    }

    //Last row
    for (int i = 1; i < width - 1; i++)
    {
        image[width][i].rgbtBlue = (int) round((temp[width][i - 1].rgbtBlue + temp[width][i].rgbtBlue + temp[width][i + 1].rgbtBlue + temp[width - 1][i - 1].rgbtBlue + temp[width - 1][i].rgbtBlue + temp[width - 1][i + 1].rgbtBlue) / 6);
        image[width][i].rgbtGreen = (int) round((temp[width][i - 1].rgbtGreen + temp[width][i].rgbtGreen + temp[width][i + 1].rgbtGreen + temp[width - 1][i - 1].rgbtGreen + temp[width -1][i].rgbtGreen + temp[width - 1][i + 1].rgbtGreen) / 6);
        image[width][i].rgbtRed = (int) round((temp[width][i - 1].rgbtRed + temp[width][i].rgbtRed + temp[width][i + 1].rgbtRed + temp[width - 1][i - 1].rgbtRed + temp[width - 1][i].rgbtRed + temp[width - 1][i + 1].rgbtRed) / 6);
    }

    //First column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][0].rgbtBlue = (int) round((temp[i - 1][0].rgbtBlue + temp[i][0].rgbtBlue + temp[i + 1][0].rgbtBlue + temp[i - 1][1].rgbtBlue + temp[i][1].rgbtBlue + temp[i + 1][1].rgbtBlue) / 6);
        image[i][0].rgbtGreen = (int) round((temp[i - 1][0].rgbtGreen + temp[i][0].rgbtGreen + temp[i + 1][0].rgbtGreen + temp[i - 1][1].rgbtGreen + temp[i][1].rgbtGreen + temp[i + 1][1].rgbtGreen) / 6);
        image[i][0].rgbtRed = (int) round((temp[i - 1][0].rgbtRed + temp[i][0].rgbtRed + temp[i + 1][0].rgbtRed + temp[i - 1][1].rgbtRed + temp[i][1].rgbtRed + temp[i + 1][1].rgbtRed) / 6);
    }

    //Last column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][width].rgbtBlue = (int) round((temp[i - 1][width].rgbtBlue + temp[i][width].rgbtBlue + temp[i + 1][width].rgbtBlue + temp[i - 1][width - 1].rgbtBlue + temp[i][width - 1].rgbtBlue + temp[i + 1][width - 1].rgbtBlue) / 6);
        image[i][width].rgbtGreen = (int) round((temp[i - 1][width].rgbtGreen + temp[i][width].rgbtGreen + temp[i + 1][width].rgbtGreen + temp[i - 1][width - 1].rgbtGreen + temp[i][width - 1].rgbtGreen + temp[i + 1][width - 1].rgbtGreen) / 6);
        image[i][width].rgbtRed = (int) round((temp[i - 1][width].rgbtRed + temp[i][width].rgbtRed + temp[i + 1][width].rgbtRed + temp[i - 1][width - 1].rgbtRed + temp[i][width - 1].rgbtRed + temp[i + 1][width - 1].rgbtRed) / 6);
    }

    //Rest of cells
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtBlue = (int)(round)((temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue + temp[i][j + 1].rgbtBlue + temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j].rgbtBlue + temp[i + 1][j + 1].rgbtBlue) / 9);
            image[i][j].rgbtGreen = (int)(round)((temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i + 1][j + 1].rgbtGreen) / 9);
            image[i][j].rgbtRed = (int)(round)((temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed + temp[i + 1][j - 1].rgbtRed + temp[i + 1][j].rgbtRed + temp[i + 1][j + 1].rgbtRed) / 9);
        }
    }



    return;
}