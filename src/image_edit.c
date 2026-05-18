#include "image_edit.h"

#include <stdlib.h>

#include "util.h"
// modify the image

// move pixels left down right up
void rotate_counterclockwise(image_t* img) {
    // logic;
    // the height of the old becomes the width of the new
    // the width of the old becomes the height of the new
    // mathematically how do the pixels transform
    //  the old y index remains the same just now becomes the new x index
    //  the old x index becomes the new y index with the transformation (width-1-x)
    // so in conclusion: (x,y) --> (y, w-1-x)
    int oldwidth = img->w;
    int oldheight = img->h;
    // reserving memory just now height width swapped
    // make this new memory reserve to manipulate
    pixel_t* newpixels = malloc(oldwidth * oldheight * sizeof(pixel_t));
    if (!newpixels) {
        return;
    }

    for (int y = 0; y < oldheight; y++) {
        for (int x = 0; x < oldwidth; x++) {
            // map it counter clockwise
            // the new x is the old y
            // the new y is w-1-x
            int newx = y;
            int newy = oldwidth - 1 - x;
            // the index formula in the doc is (𝑦 × .w) + 𝑥.
            // replace width with height and the new x,y indexes
            // now assign the new calculated indexes in row major format to new pixels and deal with the swap of height
            // and width
            newpixels[newy * oldheight + newx] = img->img[y * oldwidth + x];
            // new array with new indexes = old array with old indexes
            // basically took the new array and at every new index assigned what was at its respective correlative old
            // index
        }
    }
    // now take the new pixel array and replace the old buffer and reassign height and width
    free(img->img);
    img->img = newpixels;
    img->w = oldheight;
    img->h = oldwidth;
}

// move pixles right down left up
void rotate_clockwise(image_t* img) {
    // same thing as counter clockwise just different calculations
    // height width swapped
    // the new y becomes the old x
    // the new x become h-1-y
    //  (x,y) --> (h-1-y, x)
    // the code is the same as before just different transformations

    int oldwidth = img->w;
    int oldheight = img->h;
    pixel_t* newpixels = malloc(oldwidth * oldheight * sizeof(pixel_t));
    if (!newpixels) {
        return;
    }
    for (int y = 0; y < oldheight; y++) {
        for (int x = 0; x < oldwidth; x++) {
            int newx = oldheight - 1 - y;
            int newy = x;

            newpixels[newy * oldheight + newx] = img->img[y * oldwidth + x];
        }
    }
    free(img->img);
    img->img = newpixels;
    img->w = oldheight;
    img->h = oldwidth;
}

void mirror_horizontal(image_t* img) {
    // the width and height remain the same
    //  the y index remains the same
    // x index becomes w-1-x, remember you need to perform swaps
    // so current index gets swapped to the new calculated index
    // only iterate through half the width to swap the pixels
    int width = img->w;
    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w / 2; x++) {
            int newx = width - 1 - x;
            int leftindex = y * img->w + x;
            int rightindex = y * img->w + newx;

            // perform a swap
            pixel_t swaptemp = img->img[leftindex];
            img->img[leftindex] = img->img[rightindex];
            img->img[rightindex] = swaptemp;
        }
    }
}

void mirror_vertical(image_t* img) {
    // same thing as above, but with y
    // newy is height-1-oldy
    // iterate through half the height
    int height = img->h;
    for (int y = 0; y < img->h / 2; y++) {
        for (int x = 0; x < img->w; x++) {
            int newy = height - 1 - y;
            int topindex = y * img->w + x;
            int bottomindex = newy * img->w + x;

            // perform a swap
            pixel_t swaptemp = img->img[topindex];
            img->img[topindex] = img->img[bottomindex];
            img->img[bottomindex] = swaptemp;
        }
    }
}

void resize(image_t* img, int new_width, int new_height) {
    // crop the image to the desired size if u want a smaller image
    // enlarge the image to the desired size if u want a larger image by adding extra blank pixels
    // blank pixel is 0 0 0

    // first make a new target buffer of the new size
    pixel_t* newpixels = malloc(new_height * new_width * sizeof(pixel_t));
    if (!newpixels) {
        return;
    }

    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int newindex = y * new_width + x;  // new index format due to new dimensions
            int oldindex = y * img->w + x;
            // coordinate checking
            //  if the coordinate exists in the image bounds copy it into the new index format (cropping)
            // if it doesnt, that means we're extending the image so give it a rgb of 0 0 0 (extension)
            if (x < img->w && y < img->h) {
                newpixels[newindex] = img->img[oldindex];
            } else {
                newpixels[newindex].r = 0;
                newpixels[newindex].g = 0;
                newpixels[newindex].b = 0;
            }
        }
    }

    free(img->img);
    img->img = newpixels;
    img->w = new_width;
    img->h = new_height;
}
