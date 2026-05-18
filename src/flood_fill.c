#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>

#include "util.h"
// a recurisve approach would easily lead to memory overflow issues so we will take the BFS approach.
void flood(image_t* img, int x, int y, pixel_t* target_color) {
    // initial coordinate is out of bounds check
    if (x < 0 || y < 0 || x >= img->w || y >= img->h) return;

    // get the colour of the pixel we are targetting as the start point
    pixel_t startcolour = img->img[y * img->w + x];

    // to prevent an infinite loop, check if the start colour == target colour
    // if so, end the function
    if (startcolour.r == target_color->r && startcolour.g == target_color->g && startcolour.b == target_color->b) {
        return;
    }

    // allocate memory for queue coordinates on the heap to prevent overflow
    int* queuex = malloc(img->w * img->h * sizeof(int));
    int* queuey = malloc(img->w * img->h * sizeof(int));

    // if theres an issue in memory reservation, end the func
    if (queuex == NULL || queuey == NULL) {
        free(queuex);
        free(queuey);
        return;
    }
    // begin the queue process
    int head = 0;
    int tail = 0;

    // colour the starting pixel and push
    img->img[y * img->w + x] = *target_color;
    queuex[tail] = x;
    queuey[tail] = y;
    ++tail;

    // check right,left up and then down in a loop
    // if the colour is equal to the start colour,
    // give it the target colour, otherwise stop. youve hit a wall
    while (head < tail) {
        // while the head is less than the tail, theres still stuff waiting to be examined
        int currentX = queuex[head];
        int currentY = queuey[head];
        ++head;

        // right
        if (currentX + 1 < img->w) {
            int index = currentY * img->w + (currentX + 1);
            if (img->img[index].r == startcolour.r && img->img[index].g == startcolour.g &&
                img->img[index].b == startcolour.b) {
                img->img[index] = *target_color;
                queuex[tail] = currentX + 1;
                queuey[tail] = currentY;
                ++tail;
            }
        }

        // left
        if (currentX - 1 < img->w) {
            int index = currentY * img->w + (currentX - 1);
            if (img->img[index].r == startcolour.r && img->img[index].g == startcolour.g &&
                img->img[index].b == startcolour.b) {
                img->img[index] = *target_color;
                queuex[tail] = currentX - 1;
                queuey[tail] = currentY;
                ++tail;
            }
        }
        // down
        if (currentY - 1 < img->h) {
            int index = (currentY - 1) * img->w + currentX;
            if (img->img[index].r == startcolour.r && img->img[index].g == startcolour.g &&
                img->img[index].b == startcolour.b) {
                img->img[index] = *target_color;
                queuex[tail] = currentX;
                queuey[tail] = currentY - 1;
                ++tail;
            }
        }
        // up
        if (currentY + 1 < img->h) {
            int index = (currentY + 1) * img->w + currentX;
            if (img->img[index].r == startcolour.r && img->img[index].g == startcolour.g &&
                img->img[index].b == startcolour.b) {
                img->img[index] = *target_color;
                queuex[tail] = currentX;
                queuey[tail] = currentY + 1;
                ++tail;
            }
        }
    }
    free(queuex);
    free(queuey);
}
