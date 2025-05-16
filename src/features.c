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

void dimension(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    
    printf("dimension: %d, %d\n", &width, &height);
}