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
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue) / 4.0);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 6.0);
                }
            }
            else if (i > 0 && i < height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i- 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6.0);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i- 1][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 6.0);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i - 1][j].rgbtRed) / 9.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen+ original[i + 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen) / 9.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue) / 9.0);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 4.0);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6.0);
                }
            }
        }
    }
}