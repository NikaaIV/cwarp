#include <stdio.h>
#include <stdlib.h>
#include "cwarp.h"

int main(void) {
    char *buffer = NULL;
    int attempts = 0;

    buffer = malloc(64 * sizeof(char));
    if (buffer == NULL) {
        skip_to(cleanup);
    }

    // 1. Backward jump (Retry loop)
    checkpoint(retry_block);
    attempts++;
    printf("Connection attempt %d...\n", attempts);

    if (attempts < 3) {
        go_back(retry_block);
    }

    // 2. Forward jump (Centralized memory cleanup)
    int simulated_error = 1;
    if (simulated_error) {
        printf("ERROR DETECTED: jumping to cleanup.\n");
        skip_to(cleanup);
    }

    printf("This is getting skipped.\n");

    skip_point(cleanup);
    free(buffer);
    printf("Memory freed successfully. Zero memory leak!\n");
    return 0;
}
