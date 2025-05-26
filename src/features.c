#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count);

void dimension(char* filename) {
    unsigned char* data;
    int width, height, channels;
    read_image_data(filename, &data, &width, &height, &channels);
    
    printf("dimension: %s: %d x %d\n", filename, width, height);
    free_image_data(data);
}

void tenth_pixel (char *filename){
    unsigned char* data;
    int width, height, channels;
    int R, G, B;

    read_image_data(filename, &data, &width, &height, &channels);

    R=data[27];
    G=data[28];
    B=data[29];

    printf("tenth pixel: R=%d, G=%d, B=%d\n", R, G, B);
    free_image_data(data);
}
void first_pixel(char* filename) {
    unsigned char* data;
    int width, height, channels;
    int R, G, B;
    read_image_data(filename, &data, &width, &height, &channels);
    R = data[0];
    G = data[1];
    B = data[2];
    printf("first_pixel: %d %d %d",  R, G, B);
    free_image_data(data);
}

void print_pixel(char *filename, int x, int y) {
    unsigned char* data;
    int width, height, channels;
    int R, G, B;

    read_image_data(filename, &data, &width, &height, &channels);

    pixelRGB* pixel = get_pixel(data, width, height, channels, x, y);
    if (pixel != NULL) {
        printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    }

    free_image_data(data);
}