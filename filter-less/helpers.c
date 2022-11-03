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
            double sepiaRed = (int)round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen
                                         + 189 * image[i][j].rgbtBlue);
            double sepiaGreen = (int)round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen
                                           + .168 * image[i][j].rgbtBlue);
            double sepiaBlue = (int)round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen
                                          + .131 * image[i][j].rgbtBlue);

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
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy for reading
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // top right corner
    image[0][0].rgbtRed = (int)round((tmp[0][0].rgbtRed + tmp[1][0].rgbtRed + tmp[0][1].rgbtRed + tmp[1][1].rgbtRed)
                                      / 4);
    image[0][0].rgbtGreen = (int)round((tmp[0][0].rgbtGreen + tmp[1][0].rgbtGreen + tmp[0][1].rgbtGreen
                                        + tmp[1][1].rgbtGreen) / 4);
    image[0][0].rgbtBlue = (int)round((tmp[0][0].rgbtBlue + tmp[1][0].rgbtBlue + tmp[0][1].rgbtBlue + tmp[1][1].rgbtBlue)
                                       / 4);

    // bottom right corner
    image[height][0].rgbtRed = (int)round((tmp[height][0].rgbtRed + tmp[height - 1][0].rgbtRed + tmp[height][1].rgbtRed
                                           + tmp[height - 1][1].rgbtRed) / 4);
    image[height][0].rgbtGreen = (int)round((tmp[height][0].rgbtGreen + tmp[height - 1][0].rgbtGreen
                                             + tmp[height][1].rgbtGreen + tmp[height - 1][1].rgbtGreen) / 4);
    image[height][0].rgbtBlue = (int)round((tmp[height][0].rgbtBlue + tmp[height - 1][0].rgbtBlue
                                            + tmp[height][1].rgbtBlue + tmp[height - 1][1].rgbtBlue) / 4);

    // top left corner
    image[0][width].rgbtRed = (int)round((tmp[0][width].rgbtRed + tmp[1][width].rgbtRed + tmp[0][width - 1].rgbtRed
                                          + tmp[1][width - 1].rgbtRed) / 4);
    image[0][width].rgbtGreen = (int)round((tmp[0][width].rgbtGreen + tmp[1][width].rgbtGreen
                                            + tmp[0][width - 1].rgbtGreen + tmp[1][width - 1].rgbtGreen) / 4);
    image[0][width].rgbtBlue = (int)round((tmp[0][width].rgbtBlue + tmp[1][width].rgbtBlue + tmp[0][width - 1].rgbtBlue
                                            + tmp[1][width - 1].rgbtBlue) / 4);

    // bottom left corner
    image[height][width].rgbtRed = (int)round((tmp[height][width].rgbtRed + tmp[height - 1][width].rgbtRed
                                            + tmp[height][width - 1].rgbtRed + tmp[height - 1][width - 1].rgbtRed) / 4);
    image[height][width].rgbtGreen = (int)round((tmp[height][width].rgbtGreen + tmp[height - 1][width].rgbtGreen
                                            + tmp[height][width - 1].rgbtGreen + tmp[height - 1][width - 1].rgbtGreen)
                                            / 4);
    image[height][width].rgbtBlue = (int)round((tmp[height][width].rgbtBlue + tmp[height - 1][width].rgbtBlue
                                            + tmp[height][width - 1].rgbtBlue + tmp[height - 1][width - 1].rgbtBlue)
                                            / 4);

    // first row
    for (int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtRed = (int)round((tmp[0][i - 1].rgbtRed + tmp[0][i].rgbtRed + tmp[0][i + 1].rgbtRed
                                          + tmp[1][i - 1].rgbtRed + tmp[1][i].rgbtRed + tmp[1][i + 1].rgbtRed) / 6);
        image[0][i].rgbtGreen = (int)round((tmp[0][i - 1].rgbtGreen + tmp[0][i].rgbtGreen + tmp[0][i + 1].rgbtGreen
                                            + tmp[1][i - 1].rgbtGreen + tmp[1][i].rgbtGreen + tmp[1][i + 1].rgbtGreen) / 6);
        image[0][i].rgbtBlue = (int)round((tmp[0][i - 1].rgbtBlue + tmp[0][i].rgbtBlue + tmp[0][i + 1].rgbtBlue
                                            + tmp[1][i - 1].rgbtBlue + tmp[1][i].rgbtBlue + tmp[1][i + 1].rgbtBlue) / 6);
    }

    // last row
    for (int i = 1; i < width - 1; i++)
    {
        image[height][i].rgbtRed = (int)round((tmp[height][i - 1].rgbtRed + tmp[height][i].rgbtRed
                                               + tmp[height][i + 1].rgbtRed + tmp[height - 1][i - 1].rgbtRed
                                               + tmp[height - 1][i].rgbtRed + tmp[height - 1][i + 1].rgbtRed) / 6);
        image[height][i].rgbtGreen = (int)round((tmp[height][i - 1].rgbtGreen + tmp[height][i].rgbtGreen
                                                + tmp[height][i + 1].rgbtGreen + tmp[height - 1][i - 1].rgbtGreen
                                                + tmp[height -1][i].rgbtGreen + tmp[height - 1][i + 1].rgbtGreen) / 6);
        image[height][i].rgbtBlue = (int)round((tmp[height][i - 1].rgbtBlue + tmp[height][i].rgbtBlue
                                                + tmp[height][i + 1].rgbtBlue + tmp[height - 1][i - 1].rgbtBlue
                                                + tmp[height - 1][i].rgbtBlue + tmp[height - 1][i + 1].rgbtBlue) / 6);
    }

    // first column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][0].rgbtRed = (int)round((tmp[i - 1][0].rgbtRed + tmp[i][0].rgbtRed + tmp[i + 1][0].rgbtRed
                                            + tmp[i - 1][1].rgbtRed + tmp[i][1].rgbtRed + tmp[i + 1][1].rgbtRed) / 6);
        image[i][0].rgbtGreen = (int)round((tmp[i - 1][0].rgbtGreen + tmp[i][0].rgbtGreen + tmp[i + 1][0].rgbtGreen
                                            + tmp[i - 1][1].rgbtGreen + tmp[i][1].rgbtGreen + tmp[i + 1][1].rgbtGreen) / 6);
        image[i][0].rgbtBlue = (int)round((tmp[i - 1][0].rgbtBlue + tmp[i][0].rgbtBlue + tmp[i + 1][0].rgbtBlue
                                            + tmp[i - 1][1].rgbtBlue + tmp[i][1].rgbtBlue + tmp[i + 1][1].rgbtBlue) / 6);
    }

    // last column
    for (int i = 1; i < height - 1; i ++)
    {
        image[i][width].rgbtRed = (int)round((tmp[i - 1][width].rgbtRed + tmp[i][width].rgbtRed
                                                + tmp[i + 1][width].rgbtRed + tmp[i - 1][width - 1].rgbtRed
                                                + tmp[i][width - 1].rgbtRed + tmp[i + 1][width - 1].rgbtRed) / 6);
        image[i][width].rgbtGreen = (int)round((tmp[i - 1][width].rgbtGreen + tmp[i][width].rgbtGreen
                                                + tmp[i + 1][width].rgbtGreen + tmp[i - 1][width - 1].rgbtGreen
                                                + tmp[i][width - 1].rgbtGreen + tmp[i + 1][width - 1].rgbtGreen) / 6);
        image[i][width].rgbtBlue = (int)round((tmp[i - 1][width].rgbtBlue + tmp[i][width].rgbtBlue
                                                + tmp[i + 1][width].rgbtBlue + tmp[i - 1][width - 1].rgbtBlue
                                                + tmp[i][width - 1].rgbtBlue + tmp[i + 1][width - 1].rgbtBlue) / 6);
    }

    // rest of pixels
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = (int)round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed
                                                + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed
                                                + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed
                                                + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 9);
            image[i][j].rgbtGreen = (int)round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen
                                                + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j - 1].rgbtGreen
                                                + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen
                                                + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen
                                                + tmp[i + 1][j + 1].rgbtGreen) / 9);
            image[i][j].rgbtBlue = (int)round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue
                                                + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j - 1].rgbtBlue
                                                + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue
                                                + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue
                                                + tmp[i + 1][j + 1].rgbtBlue) / 9);
        }
    }

    return;
}