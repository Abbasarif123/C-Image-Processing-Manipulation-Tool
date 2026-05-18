#include "file_io.h"

#include <assert.h>
#include <stdlib.h>

#include "util.h"

/** header file says:
 * Allocate and read the .ppm image from the given input file stream.
 * Return 0 on success, -1 if the input file is in a wrong format.
 */
// to write: fprintf
// to read: fscanf
// everything is defined in the header file
// file will use the pp3 extension, starts with p3, then has the width and height, then the colourss representing the
// pixel data the format is row row row column change row row row the colours will will appear in text the way theyll
// show up in the picture whitespaces are to be ignores along with comments
// use malloc to reserve space for image data
// width stored in w, height in h, the pixel at index(x,y) is stored at pos = (y*w)+x ==(all of this stored in array
// img)
int image_read(image_t* img, FILE* fin) {
    // image read will read from the FILE pointer
    // return -1 if input does not match the correct format
    // validate header as p3
    // read the width and height must be scanned and must be between 0 and 255 (inclusive)
    // allocate memory for the image
    // use a loop to read the values of the image and put them in img.

    // code:
    char magicnum[3];
    // program cant catch a string at all OR first index is not P OR second index is not 3.. return -1
    if (fscanf(fin, "%2s", magicnum) != 1 || magicnum[0] != 'P' || magicnum[1] != '3') {
        return -1;
    }
    // img -> w , is shorthand for (*img).w so im using the arrow syntax since its easier to type
    //
    // in summary (*img).w refers to: follow the address stored in img and look for the w part of it
    int maxval;
    // collect the width height and maxval
    if (fscanf(fin, "%d %d %d", &img->w, &img->h, &maxval) != 3) {
        return -1;
    }
    // check the max val
    if (maxval != 255) {
        return -1;
    }
    // allocate memory dynamically
    // the total size of the image --> width * height *sizeof each pixel
    // img -> img refers to; inside the img(the param) structure, find the member img(struct var). in other words, img
    // -> data (gives me the img data in the object)

    // splint says that i gotta free the memory before i allocate it
    if (img->img != NULL) {
        free(img->img);   // release the old memory
        img->img = NULL;  // clear the pointer to be safe
    }
    img->img = malloc(img->w * img->h * sizeof(pixel_t));
    if (img->img == NULL) {
        return -1;  // return -1 if malloc fails i.e returns null
    }

    // now read the pixel data in row format
    // in R G B
    for (int index = 0; index < (img->w * img->h); index++) {
        if (fscanf(fin, "%d %d %d", &img->img[index].r, &img->img[index].g, &img->img[index].b) != 3) {
            free(img->img);  // free up the memory space allocated for the imaeg if the RGB pixels are not formatted
                             // correctly
            img->img = NULL;
            return -1;
        }
    }

    return 0;  // else its success

    // UNUSED(img);
    // UNUSED(fin);
    // return -1;
}
/** file header says
 * Write the given image to the output file stream.
 */
void image_write(const image_t* img, FILE* fout) {
    // i need to write a file in the correct format
    // first, write the magic num
    //  w h
    //  255
    // pixel data in row format
    fprintf(fout, "P3\n%d %d\n255\n", img->w, img->h);

    // write pixel data
    for (int index = 0; index < img->w * img->h; index++) {
        fprintf(fout, "%d %d %d ", img->img[index].r, img->img[index].g, img->img[index].b);
    }
}

void image_free(image_t* img) {
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = img->h = 0;
    img->img = NULL;
}
