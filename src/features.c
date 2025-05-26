#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

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
    
    printf("dimension: %d, %d\n", width, height);
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

    printf("tenth_pixel: %d, %d, %d\n", R, G, B);
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
    printf("first_pixel: %d, %d, %d",  R, G, B);
    free_image_data(data);
}

void second_line(char *filename){
    unsigned char* data;
    int i;
    int width, height, channels;
    int R, G, B;
    read_image_data(filename, &data, &width, &height, &channels);

    i=3*width;

    R = data[i];
    G = data[i+1];
    B = data[i+2];

    printf("second_line: %d, %d, %d",  R, G, B);

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

void min_pixel(char *filename) {
    unsigned char* data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    int min_sum = 256 * 3 + 1;
    int min_x = 0, min_y = 0;
    int R, G, B;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            R = data[i];
            G = data[i + 1];
            B = data[i + 2];
            int sum = R + G + B;

            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y,
           data[(min_y * width + min_x) * channels],
           data[(min_y * width + min_x) * channels + 1],
           data[(min_y * width + min_x) * channels + 2]);

    free_image_data(data);
}

void max_component(char *filename, char component) {
    unsigned char *data;
    int width, height, channels;
    read_image_data(filename, &data, &width, &height, &channels);

    int max_val = -1;
    int max_x = 0, max_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            int value;
            if (component == 'R') value = data[i];
            else if (component == 'G') value = data[i + 1];
            else value = data[i + 2];

            if (value > max_val) {
                max_val = value;
                max_x = x;
                max_y = y;
            }
        }
    }

    printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_val);
    free_image_data(data);
}


void min_component(char *filename, char component) {
    unsigned char *data;
    int width, height, channels;
    read_image_data(filename, &data, &width, &height, &channels);

    int min_val = 256;
    int min_x = 0, min_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            int value;
            if (component == 'R') value = data[i];
            else if (component == 'G') value = data[i + 1];
            else value = data[i + 2];

            if (value < min_val) {
                min_val = value;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_val);
    free_image_data(data);
}

void stat_report(char *filename){
    freopen("stat_report.txt", "w", stdout);

    min_pixel(filename);
    printf("\n");

    max_component(filename, 'R');
    printf("\n");

    max_component(filename, 'G');
    printf("\n");

    max_component(filename, 'B');
    printf("\n");

    min_component(filename, 'R');
    printf("\n");

    min_component(filename, 'G');
    printf("\n");

    min_component(filename, 'B');
    printf("\n");

    fflush(stdout);
    fclose(stdout);

    freopen("CON", "w", stdout);    
}



void color_red(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            data[i + 1] = 0; 
            data[i + 2] = 0;   
        }
    }

    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}

void color_green(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            data[i] = 0; 
            data[i + 2] = 0;   
        }
    }

    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}


void color_blue(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            data[i] = 0; 
            data[i + 1] = 0;
        }
    }

    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}
void color_gray(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB* pixel = get_pixel(data, width, height, channels, x, y);
            if (pixel != NULL) {
                unsigned char value = (pixel->R + pixel->G + pixel->B) / 3;
                pixel->R = value;
                pixel->G = value;
                pixel->B = value;
            }
        }
    }

    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}


void color_gray_luminance(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB* pixel = get_pixel(data, width, height, channels, x, y);
            if (pixel != NULL) {
                unsigned char value = (0.21 * pixel->R + 0.72 * pixel->G + 0.07 * pixel->B);
                pixel->R = value;
                pixel->G = value;
                pixel->B = value;
            }
        }
    }

    write_image_data("image_out.bmp", data, width, height);
    free_image_data(data);
}
            


void color_invert(char *filename) {
    unsigned char *data;
    int width, height, channels;

    read_image_data(filename, &data, &width, &height, &channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            int i = (y * width + x) * channels;
            data[i] = 255 - data[i]; 
            data[i + 1] = 255 - data[i + 1];
            data[i + 2] = 255 - data[i + 2];
        }
    }

    write_image_data("image_invert.bmp", data, width, height);
    free_image_data(data);
}




