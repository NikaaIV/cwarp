# cwarp.h

**cwarp** is a lightweight, zero-dependency, single-header C library designed to make non-linear control flow readable, explicit, and safe—particularly useful for retry loops and centralized resource cleanup (preventing memory leaks).

## Why cwarp?

In standard C, raw `goto` statements can easily become confusing because the same keyword is used both to jump backward (creating loops) and to jump forward (handling errors). **cwarp** separates these two intents into clear, self-documenting primitives:

- **Backward jumps (`checkpoint` / `go_back`):** Clearly mark retry blocks or state-machine loops.
- **Forward jumps (`skip_to` / `skip_point`):** Implement the Centralized Resource Cleanup pattern to safely free allocated memory and close files when an error occurs, preventing memory leaks.

## Features

- **Zero Dependencies:** Pure standard C preprocessor macros, no external headers required.
- **Header-Only:** Just drop `cwarp.h` into your project or install it system-wide.
- **Namespace Safe:** Automatically prefixes generated labels (`cwarp_cp_` and `cwarp_sp_`) to prevent label collisions.
- **Memory-Leak Tested:** Verified with Valgrind (`0 errors from 0 contexts`).

## Installation

### Option 1: System-Wide Installation (Linux / macOS)
Install `cwarp.h` into `/usr/local/include` so you can include it anywhere using `<cwarp.h>`:

```bash
git clone https://github.com/NikaaIV/cwarp.git
cd cwarp
sudo make install
```

To uninstall:
```bash
sudo make uninstall
```

### Option 2: Local Project Include
Simply copy `cwarp.h` into your project directory and include it with quotes:

```c
#include "cwarp.h"
```

## Quick Example (visible in the file examples > example.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <cwarp.h>

int main(void) {
    char *buffer = malloc(64 * sizeof(char));
    if (buffer == NULL) {
        skip_to(cleanup);
    }

    int attempts = 0;

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

    printf("This is getting skipped\n");

    skip_point(cleanup);
    free(buffer);
    printf("Memory freed successfully. Zero memory leaks!\n");
    return 0;
}
```

## Building the Example

```bash
clang -Wall -Wextra -g example.c -o example
./example
```

## License

This project is licensed under the MIT License.
