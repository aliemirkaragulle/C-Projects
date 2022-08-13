#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            pixel = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = pixel;
            image[i][j].rgbtGreen = pixel;
            image[i][j].rgbtBlue = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    int half = width / 2;

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < half; j ++)
        {
            /*
            tmp[0][0].rgbtRed = image[i][j].rgbtRed;
            tmp[0][0].rgbtGreen = image[i][j].rgbtGreen;
            tmp[0][0].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = tmp[0][0].rgbtRed;
            image[i][width - 1 - j].rgbtGreen = tmp[0][0].rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = tmp[0][0].rgbtBlue;
            */

            tmp[0][0] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp[0][0];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

            //copy[i][j] = image[i][j];
        }
    }

    int start = 0;
    int end = width - 1;

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            // 3 Cases In This Problem:

            // Edge
            if (i == start && j == start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                            4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                            4.0);
            }

            if (i == start && j == end)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                            4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                            4.0);
            }

            if (i == end && j == start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                                            4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                            4.0);
            }

            if (i == end && j == end)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                            4.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                                            4.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) /
                                            4.0);
            }

            // Corner
            if (i == start && j < end && j != start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                            copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                            copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            if (i < end && j == end && i != start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                            copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                            copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
            }

            if (i == end && j < end && j != start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                            copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                            copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                            copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
            }

            if (i < end && j == start && i != start)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                            copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                            copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);
            }

            // Inside
            if (i < end && j < end && i != start && i != end && j != start && j != end)
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                            copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                            copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

            //copy[i][j] = image[i][j];
        }
    }

    int start = 0;
    int end = width - 1;

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int gx_red, gx_green, gx_blue;
    int gy_red, gy_green, gy_blue;
    int red, green, blue;

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            // 3 Cases In This Problem:

            // Edge
            if (i == start && j == start)
            {
                gx_red = ((copy[i][j].rgbtRed * gx[1][1]) + (copy[i][j + 1].rgbtRed * gx[1][2]) + (copy[i + 1][j].rgbtRed * gx[2][1]) + (copy[i + 1][j + 1].rgbtRed * gx[2][2]));
                gy_red = ((copy[i][j].rgbtRed * gy[1][1]) + (copy[i][j + 1].rgbtRed * gy[1][2]) + (copy[i + 1][j].rgbtRed * gy[2][1]) + (copy[i + 1][j + 1].rgbtRed * gy[2][2]));

                gx_green = ((copy[i][j].rgbtGreen * gx[1][1]) + (copy[i][j + 1].rgbtGreen * gx[1][2]) + (copy[i + 1][j].rgbtGreen * gx[2][1]) + (copy[i + 1][j + 1].rgbtGreen * gx[2][2]));
                gy_green = ((copy[i][j].rgbtGreen * gy[1][1]) + (copy[i][j + 1].rgbtGreen * gy[1][2]) + (copy[i + 1][j].rgbtGreen * gy[2][1]) + (copy[i + 1][j + 1].rgbtGreen * gy[2][2]));

                gx_blue = ((copy[i][j].rgbtBlue * gx[1][1]) + (copy[i][j + 1].rgbtBlue * gx[1][2]) + (copy[i + 1][j].rgbtBlue * gx[2][1]) + (copy[i + 1][j + 1].rgbtBlue * gx[2][2]));
                gy_blue = ((copy[i][j].rgbtBlue * gy[1][1]) + (copy[i][j + 1].rgbtBlue * gy[1][2]) + (copy[i + 1][j].rgbtBlue * gy[2][1]) + (copy[i + 1][j + 1].rgbtBlue * gy[2][2]));
            }

            if (i == start && j == end)
            {
                gx_red = ((copy[i][j].rgbtRed * gx[1][1]) + (copy[i][j - 1].rgbtRed * gx[1][0]) + (copy[i + 1][j].rgbtRed * gx[2][1]) + (copy[i + 1][j - 1].rgbtRed * gx[2][0]));
                gy_red = ((copy[i][j].rgbtRed * gy[1][1]) + (copy[i][j - 1].rgbtRed * gy[1][0]) + (copy[i + 1][j].rgbtRed * gy[2][1]) + (copy[i + 1][j - 1].rgbtRed * gy[2][0]));

                gx_green = ((copy[i][j].rgbtGreen * gx[1][1]) + (copy[i][j - 1].rgbtGreen * gx[1][0]) + (copy[i + 1][j].rgbtGreen * gx[2][1]) + (copy[i + 1][j - 1].rgbtGreen * gx[2][0]));
                gy_green = ((copy[i][j].rgbtGreen * gy[1][1]) + (copy[i][j - 1].rgbtGreen * gy[1][0]) + (copy[i + 1][j].rgbtGreen * gy[2][1]) + (copy[i + 1][j - 1].rgbtGreen * gy[2][0]));

                gx_blue = ((copy[i][j].rgbtBlue * gx[1][1]) + (copy[i][j - 1].rgbtBlue * gx[1][0]) + (copy[i + 1][j].rgbtBlue * gx[2][1]) + (copy[i + 1][j - 1].rgbtBlue * gx[2][0]));
                gy_blue = ((copy[i][j].rgbtBlue * gy[1][1]) + (copy[i][j - 1].rgbtBlue * gy[1][0]) + (copy[i + 1][j].rgbtBlue * gy[2][1]) + (copy[i + 1][j - 1].rgbtBlue * gy[2][0]));
            }

            if (i == end && j == start)
            {
                gx_red = ((copy[i][j].rgbtRed * gx[1][1]) + (copy[i][j + 1].rgbtRed * gx[1][2]) + (copy[i - 1][j].rgbtRed * gx[0][1]) + (copy[i - 1][j + 1].rgbtRed * gx[0][2]));
                gy_red = ((copy[i][j].rgbtRed * gy[1][1]) + (copy[i][j + 1].rgbtRed * gy[1][2]) + (copy[i - 1][j].rgbtRed * gy[0][1]) + (copy[i - 1][j + 1].rgbtRed * gy[0][2]));

                gx_green = ((copy[i][j].rgbtGreen * gx[1][1]) + (copy[i][j + 1].rgbtGreen * gx[1][2]) + (copy[i - 1][j].rgbtGreen * gx[0][1]) + (copy[i - 1][j + 1].rgbtGreen * gx[0][2]));
                gy_green = ((copy[i][j].rgbtGreen * gy[1][1]) + (copy[i][j + 1].rgbtGreen * gy[1][2]) + (copy[i - 1][j].rgbtGreen * gy[0][1]) + (copy[i - 1][j + 1].rgbtGreen * gy[0][2]));

                gx_blue = ((copy[i][j].rgbtBlue * gx[1][1]) + (copy[i][j + 1].rgbtBlue * gx[1][2]) + (copy[i - 1][j].rgbtBlue * gx[0][1]) + (copy[i - 1][j + 1].rgbtBlue * gx[0][2]));
                gy_blue = ((copy[i][j].rgbtBlue * gy[1][1]) + (copy[i][j + 1].rgbtBlue * gy[1][2]) + (copy[i - 1][j].rgbtBlue * gy[0][1]) + (copy[i - 1][j + 1].rgbtBlue * gy[0][2]));
            }

            if (i == end && j == end)
            {
                gx_red = ((copy[i][j].rgbtRed * gx[1][1]) + (copy[i][j - 1].rgbtRed * gx[1][0]) + (copy[i - 1][j].rgbtRed * gx[0][1]) + (copy[i - 1][j - 1].rgbtRed * gx[0][0]));
                gy_red = ((copy[i][j].rgbtRed * gy[1][1]) + (copy[i][j - 1].rgbtRed * gy[1][0]) + (copy[i - 1][j].rgbtRed * gy[0][1]) + (copy[i - 1][j - 1].rgbtRed * gy[0][0]));

                gx_green = ((copy[i][j].rgbtGreen * gx[1][1]) + (copy[i][j - 1].rgbtGreen * gx[1][0]) + (copy[i - 1][j].rgbtGreen * gx[0][1]) + (copy[i - 1][j - 1].rgbtGreen * gx[0][0]));
                gy_green = ((copy[i][j].rgbtGreen * gy[1][1]) + (copy[i][j - 1].rgbtGreen * gy[1][0]) + (copy[i - 1][j].rgbtGreen * gy[0][1]) + (copy[i - 1][j - 1].rgbtGreen * gy[0][0]));

                gx_blue = ((copy[i][j].rgbtBlue * gx[1][1]) + (copy[i][j - 1].rgbtBlue * gx[1][0]) + (copy[i - 1][j].rgbtBlue * gx[0][1]) + (copy[i - 1][j - 1].rgbtBlue * gx[0][0]));
                gy_blue = ((copy[i][j].rgbtBlue * gy[1][1]) + (copy[i][j - 1].rgbtBlue * gy[1][0]) + (copy[i - 1][j].rgbtBlue * gy[0][1]) + (copy[i - 1][j - 1].rgbtBlue * gy[0][0]));
            }

            // Corner
            if (i == start && j < end && j != start)
            {
                gx_red = (copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j + 1].rgbtRed * gx[2][2]);
                gy_red = (copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j + 1].rgbtRed * gy[2][2]);

                gx_green = (copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j + 1].rgbtGreen * gx[2][2]);
                gy_green = (copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j + 1].rgbtGreen * gy[2][2]);

                gx_blue = (copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j + 1].rgbtBlue * gx[2][2]);
                gy_blue = (copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j + 1].rgbtBlue * gy[2][2]);
            }

            if (i < end && j == end && i != start)
            {
                gx_red = (copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j - 1].rgbtRed * gx[0][0]);
                gy_red = (copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j - 1].rgbtRed * gy[0][0]);

                gx_green = (copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j - 1].rgbtGreen * gx[0][0]);
                gy_green = (copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j - 1].rgbtGreen * gy[0][0]);

                gx_blue = (copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j - 1].rgbtBlue * gx[0][0]);
                gy_blue = (copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j - 1].rgbtBlue * gy[0][0]);
            }

            if (i == end && j < end && j != start)
            {
                gx_red = (copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed * gx[0][2] + copy[i - 1][j - 1].rgbtRed * gx[0][0]);
                gy_red = (copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed * gy[0][2] + copy[i - 1][j - 1].rgbtRed * gy[0][0]);

                gx_green = (copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j + 1].rgbtGreen * gx[0][2] + copy[i - 1][j - 1].rgbtGreen * gx[0][0]);
                gy_green = (copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j + 1].rgbtGreen * gy[0][2] + copy[i - 1][j - 1].rgbtGreen * gy[0][0]);

                gx_blue = (copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue * gx[0][2] + copy[i - 1][j - 1].rgbtBlue * gx[0][0]);
                gy_blue = (copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue * gy[0][2] + copy[i - 1][j - 1].rgbtBlue * gy[0][0]);
            }

            if (i < end && j == start && i != start)
            {
                gx_red = (copy[i][j].rgbtRed * gx[1][1] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j + 1].rgbtRed * gx[2][2] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed * gx[0][2]);
                gy_red = (copy[i][j].rgbtRed * gy[1][1] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j + 1].rgbtRed * gy[2][2] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed * gy[0][2]);

                gx_green = (copy[i][j].rgbtGreen * gx[1][1] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j + 1].rgbtGreen * gx[2][2] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j + 1].rgbtGreen * gx[0][2]);
                gy_green = (copy[i][j].rgbtGreen * gy[1][1] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j + 1].rgbtGreen * gy[2][2] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j + 1].rgbtGreen * gy[0][2]);

                gx_blue = (copy[i][j].rgbtBlue * gx[1][1] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j + 1].rgbtBlue * gx[2][2] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue * gx[0][2]);
                gy_blue = (copy[i][j].rgbtBlue * gy[1][1] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j + 1].rgbtBlue * gy[2][2] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue * gy[0][2]);
            }

            // Inside
            if (i < end && j < end && i != start && i != end && j != start && j != end)
            {
                gx_red = ((copy[i][j].rgbtRed * gx[1][1]) + (copy[i - 1][j - 1].rgbtRed * gx[0][0]) + (copy[i - 1][j].rgbtRed * gx[0][1]) + (copy[i - 1][j + 1].rgbtRed * gx[0][2]) + (copy[i][j - 1].rgbtRed * gx[1][0]) + (copy[i][j + 1].rgbtRed * gx[1][2]) + (copy[i + 1][j - 1].rgbtRed * gx[2][0]) + (copy[i + 1][j].rgbtRed * gx[2][1]) + (copy[i + 1][j + 1].rgbtRed * gx[2][2]));
                gy_red = ((copy[i][j].rgbtRed * gy[1][1]) + (copy[i - 1][j - 1].rgbtRed * gy[0][0]) + (copy[i - 1][j].rgbtRed * gy[0][1]) + (copy[i - 1][j + 1].rgbtRed * gy[0][2]) + (copy[i][j - 1].rgbtRed * gy[1][0]) + (copy[i][j + 1].rgbtRed * gy[1][2]) + (copy[i + 1][j - 1].rgbtRed * gy[2][0]) + (copy[i + 1][j].rgbtRed * gy[2][1]) + (copy[i + 1][j + 1].rgbtRed * gy[2][2]));

                gx_green = ((copy[i][j].rgbtGreen * gx[1][1]) + (copy[i - 1][j - 1].rgbtGreen * gx[0][0]) + (copy[i - 1][j].rgbtGreen * gx[0][1]) + (copy[i - 1][j + 1].rgbtGreen * gx[0][2]) + (copy[i][j - 1].rgbtGreen * gx[1][0]) + (copy[i][j + 1].rgbtGreen * gx[1][2]) + (copy[i + 1][j - 1].rgbtGreen * gx[2][0]) + (copy[i + 1][j].rgbtGreen * gx[2][1]) + (copy[i + 1][j + 1].rgbtGreen * gx[2][2]));
                gy_green = ((copy[i][j].rgbtGreen * gy[1][1]) + (copy[i - 1][j - 1].rgbtGreen * gy[0][0]) + (copy[i - 1][j].rgbtGreen * gy[0][1]) + (copy[i - 1][j + 1].rgbtGreen * gy[0][2]) + (copy[i][j - 1].rgbtGreen * gy[1][0]) + (copy[i][j + 1].rgbtGreen * gy[1][2]) + (copy[i + 1][j - 1].rgbtGreen * gy[2][0]) + (copy[i + 1][j].rgbtGreen * gy[2][1]) + (copy[i + 1][j + 1].rgbtGreen * gy[2][2]));

                gx_blue = ((copy[i][j].rgbtBlue * gx[1][1]) + (copy[i - 1][j - 1].rgbtBlue * gx[0][0]) + (copy[i - 1][j].rgbtBlue * gx[0][1]) + (copy[i - 1][j + 1].rgbtBlue * gx[0][2]) + (copy[i][j - 1].rgbtBlue * gx[1][0]) + (copy[i][j + 1].rgbtBlue * gx[1][2]) + (copy[i + 1][j - 1].rgbtBlue * gx[2][0]) + (copy[i + 1][j].rgbtBlue * gx[2][1]) + (copy[i + 1][j + 1].rgbtBlue * gx[2][2]));
                gy_blue = ((copy[i][j].rgbtBlue * gy[1][1]) + (copy[i - 1][j - 1].rgbtBlue * gy[0][0]) + (copy[i - 1][j].rgbtBlue * gy[0][1]) + (copy[i - 1][j + 1].rgbtBlue * gy[0][2]) + (copy[i][j - 1].rgbtBlue * gy[1][0]) + (copy[i][j + 1].rgbtBlue * gy[1][2]) + (copy[i + 1][j - 1].rgbtBlue * gy[2][0]) + (copy[i + 1][j].rgbtBlue * gy[2][1]) + (copy[i + 1][j + 1].rgbtBlue * gy[2][2]));
            }

            red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }
        }
    }
    return;
}