#include "helpers.h"

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
    // creating copy for reading
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    // making the colors the average of adjacent pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                // top left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i]
                                                 [j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i]
                                                   [j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i]
                                                  [j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                // top right corner
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i]
                                                 [j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i]
                                                   [j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i]
                                                  [j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue) / 4.0);
                }
                // first row
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i]
                                                 [j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i]
                                                 [j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i]
                                                   [j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i]
                                                   [j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i]
                                                  [j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i]
                                                  [j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 6.0);
                }
            }
            else if (i > 0 && i < height - 1)
            {
                // first column
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1]
                                                 [j].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i]
                                                 [j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i - 1]
                                                   [j].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i]
                                                   [j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1]
                                                  [j].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i]
                                                  [j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6.0);
                }
                // last column
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1]
                                                 [j].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i - 1]
                                                   [j].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i]
                                                   [j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1]
                                                  [j].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i]
                                                  [j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 6.0);
                }
                // rest of pixels
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i]
                                                 [j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i + 1]
                                                 [j].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i - 1][j].rgbtRed) / 9.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i]
                                                   [j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i + 1]
                                                   [j].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen) / 9.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i]
                                                  [j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1]
                                                  [j].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue) / 9.0);
                }
            }
            else if (i == height - 1)
            {
                // bottom left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i]
                                                 [j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i]
                                                   [j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i]
                                                  [j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 4.0);
                }
                // bottom right corner
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i]
                                                 [j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i]
                                                   [j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i]
                                                  [j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 4.0);
                }
                // last row
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i]
                                                 [j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i]
                                                   [j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i]
                                                  [j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6.0);
                }
            }
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
