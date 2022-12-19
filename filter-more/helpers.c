#include "helpers.h"
#include <math.h>

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
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];                }
                }

                // Calculate Sobel operator
                int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
                int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
                int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));            // Cap at 255
                if (red > 255)
                {
                    red = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }            // Assign new values to pixels
                image[i][j].rgbtRed = red;
                image[i][j].rgbtGreen = green;
                image[i][j].rgbtBlue = blue;
            }
            // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
                image[i][j].rgbtRed = red;
            }            // Assign new values to pixels
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    return;
}
