#include "helpers.h"
#include <math.h>

void cap_255(BYTE *num);
void swap(BYTE *a, BYTE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int value =
                round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalred = image[i][j].rgbtRed;
            int originalgreen = image[i][j].rgbtGreen;
            int originalblue = image[i][j].rgbtBlue;

            // Compute sepia values
            // Update pixel with sepia values
            int sepiared = round(.393 * originalred + .769 * originalgreen + .189 * originalblue);
            int sepiagreen = round(.349 * originalred + .686 * originalgreen + .168 * originalblue);
            int sepiablue = round(.272 * originalred + .534 * originalgreen + .131 * originalblue);

            if (sepiared > 255)
            {
                sepiared = 255;
            }
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }

            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap pixels
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // for every pixel
    for (int ii = 0; ii < height; ii++)
    {
        for (int jj = 0; jj < width; jj++)
        {
            // sum of each color
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            // add up number of pixels counted
            int count = 0;

            // for each 3 pix height
            for (int gi = -1; gi <= 1; gi++)
            {
                // for each 3 pix width
                for (int gj = -1; gj <= 1; gj++)
                {
                    // add the values of height and width to find the index number of the
                    // surrounding pixels
                    int ni = gi + ii;
                    int nj = gj + jj;

                    if (ni >= 0 && nj >= 0 && ni < height && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            image[ii][jj].rgbtRed = round((float) sumRed / count);
            image[ii][jj].rgbtGreen = round((float) sumGreen / count);
            image[ii][jj].rgbtBlue = round((float) sumBlue / count);

            // use cap_255 after assigning values; otherwise there is nothing bieng returned
            cap_255(&image[ii][jj].rgbtRed);
            cap_255(&image[ii][jj].rgbtGreen);
            cap_255(&image[ii][jj].rgbtBlue);
        }
    }
    return;
}

// The function grayscale should take an image and turn it into a black-and-white version of the
// same image. The function sepia should take an image and turn it into a sepia version of the same
// image. The reflect function should take an image and reflect it horizontally. Finally, the blur
// function should take an image and turn it into a box-blurred version of the same image.
void cap_255(BYTE *num)
{
    if (*num > 255)
    {
        *num = 255;
    }
}

void swap(BYTE *a, BYTE *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
