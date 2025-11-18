#include "helpers.h"
#include <math.h>

typedef uint8_t BYTE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        // Loop over all pixels
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green and blue
            average = round(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5;

            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;

    for (int i = 0; i < height; i++)
    {
        // Loop over all pixels
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaBlue = fmin(255, (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue + 0.5));
            sepiaGreen = fmin(255, (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue + 0.5));
            sepiaRed = fmin(255, (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue + 0.5));

            // Update pixel with sepia values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE bluetmp, greentmp, redtmp;
    for (int i = 0; i < height; i++)
    {
        // Loop over all pixels
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            bluetmp = image[i][j].rgbtBlue;
            greentmp = image[i][j].rgbtGreen;
            redtmp = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = bluetmp;
            image[i][width - 1 - j].rgbtGreen = greentmp;
            image[i][width - 1 - j].rgbtRed = redtmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creare a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Surrounding Blur
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            float counter = 0.0;
            int red = 0, green = 0, blue = 0;
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (k + m < 0 || k + m > (height - 1) || l + n < 0 || l + n > (width - 1))
                    {
                        continue;
                    }
                    blue += image[k + m][l + n].rgbtBlue;
                    green += image[k + m][l + n].rgbtGreen;
                    red += image[k + m][l + n].rgbtRed;
                    counter++;
                }
            }
            // Copy average
            copy[k][l].rgbtBlue = round(blue / counter);
            copy[k][l].rgbtGreen = round(green / counter);
            copy[k][l].rgbtRed = round(red / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
