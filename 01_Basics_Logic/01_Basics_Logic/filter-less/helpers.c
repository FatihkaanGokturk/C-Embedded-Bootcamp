#include "helpers.h"
#include <math.h>
#include <string.h>

/**
 * @file helpers.c
 * @brief Implementation of image filter functions (Grayscale, Sepia, Reflect, Blur).
 *
 * This file contains the core functions for processing BMP images
 * as part of the CS50 Filter project. All functions work in-place
 * (except Blur, which uses a temporary array).
 *
 * @author Fatih Kaan GÖKTÜRK
 * @date 3/262026
 * @version 1.0
 */

/**
 * @brief Converts an image to grayscale.
 *
 * @details This function calculates the arithmetic mean of the red, green,
 *          and blue components for each pixel and sets all three color channels
 *          to this average value. The result is a grayscale image.
 *
 * @param[in]  height Height of the image in pixels.
 * @param[in]  width  Width of the image in pixels.
 * @param[in,out] image The RGB image to be processed (modified in place).
 */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float total = image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            int average = round(total / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

/**
 * @brief Applies a sepia tone to the image.
 *
 * @details The function calculates new RGB values for each pixel using the classic
 *          sepia formula and caps them at the maximum value of 255. The calculation
 *          is performed efficiently using pointer arithmetic across all pixels.
 *
 * @param[in]  height Height of the image in pixels.
 * @param[in]  width  Width of the image in pixels.
 * @param[in,out] image The RGB image to be processed (modified in place).
 */
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int total_pixels = height * width;
    RGBTRIPLE *pixel_ptr = &image[0][0];
    for (int i = 0; i < total_pixels; i++) {
        float originalRed   = pixel_ptr->rgbtRed;
        float originalGreen = pixel_ptr->rgbtGreen;
        float originalBlue  = pixel_ptr->rgbtBlue;

        int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
        pixel_ptr->rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;

        int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
        pixel_ptr->rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;

        int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
        pixel_ptr->rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

        pixel_ptr++;
    }
    return;
}

/**
 * @brief Reflects the image horizontally (left-right flip).
 *
 * @details The function symmetrically swaps pixels on the left and right
 *          half of each row. Only the left half is iterated to avoid
 *          double processing.
 *
 * @param[in]  height Height of the image in pixels.
 * @param[in]  width  Width of the image in pixels.
 * @param[in,out] image The RGB image to be processed (modified in place).
 */
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp_pixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp_pixel;
        }
    }
    return;
}

/**
 * @brief Applies a box blur filter (3x3) to the image.
 *
 * @details For each pixel, the average of all neighboring pixels
 *          (including the pixel itself) within a 3x3 window is calculated.
 *          Edge pixels only consider existing neighbors. A temporary
 *          array is used to preserve the original values during calculation.
 *
 * @param[in]  height Height of the image in pixels.
 * @param[in]  width  Width of the image in pixels.
 * @param[in,out] image The RGB image to be processed (modified in place).
 */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int blue = 0, green = 0, red = 0;
            float counter = 0;

            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < height && y >= 0 && y < width) {
                        green += image[x][y].rgbtGreen;
                        blue  += image[x][y].rgbtBlue;
                        red   += image[x][y].rgbtRed;
                        counter++;
                    }
                }
            }

            temp[i][j].rgbtRed   = round(red   / counter);
            temp[i][j].rgbtGreen = round(green / counter);
            temp[i][j].rgbtBlue  = round(blue  / counter);
        }
    }

    // Copy the temporary array back into the original image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
    return;
}