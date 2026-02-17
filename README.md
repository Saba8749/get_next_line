# get_next_line

*This project has been created as part of the 42 curriculum by Saba Gribashvili.*

## Description

The get_next_line project is about programming a function that returns a line read from a file descriptor. The main challenge is handling the buffer efficiently and managing memory properly while reading from different sources (files, stdin, etc.). The function must work regardless of the BUFFER_SIZE value and handle multiple consecutive calls without losing data between reads.

The goal is to understand how file descriptors work, how to read from them efficiently, and how to manage static variables to maintain state between function calls.

## Instructions

### Compilation

The function requires a BUFFER_SIZE to be defined at compilation time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Testing

Create a test file and run the program:
```bash
echo -e "First line\nSecond line\nThird line" > test.txt
./a.out
```

The function can be tested with different BUFFER_SIZE values to ensure it works in all cases:
```bash
cc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c
cc -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
```

## Algorithm Explanation

The algorithm uses a static variable called `stash` to store data between function calls. This is necessary because when reading BUFFER_SIZE bytes, we might read more than one line at a time, so we need to save the extra data for the next call.

### Core Logic

1. **Read into stash**: Read from the file descriptor in chunks of BUFFER_SIZE until a newline is found or EOF is reached. Each read is appended to the stash using string concatenation.

2. **Extract the line**: Once a newline is found (or EOF with remaining data), extract everything up to and including the newline character. This becomes the return value.

3. **Update the stash**: After extracting the line, keep everything after the newline in the stash for the next function call. If nothing remains, free the stash and set it to NULL.

### Why This Approach?

- Using a static variable allows the function to "remember" leftover data between calls without requiring the caller to manage any state
- Reading in fixed chunks (BUFFER_SIZE) is more efficient than reading byte by byte
- The helper functions (strjoin, substr, find_nl) make the code modular and easier to debug

### Edge Cases Handled

- Empty files (returns NULL immediately)
- Files without newlines (returns the entire content)
- Very small BUFFER_SIZE (even 1 byte)
- Very large BUFFER_SIZE
- Reading from stdin (fd = 0)
- Multiple file descriptors simultaneously (bonus)

## Bonus Part

The bonus implementation handles multiple file descriptors at the same time. Instead of using a single static variable, it uses an array of static pointers indexed by the file descriptor number:

```c
static char *stash[OPEN_MAX];
```

This allows each file descriptor to maintain its own independent stash. When `get_next_line(3)` is called, it uses `stash[3]`. When `get_next_line(5)` is called, it uses `stash[5]`. This way, you can alternate between reading from different files without losing your position in any of them.

The core algorithm remains the same, only the storage mechanism changes from a single pointer to an array of pointers.

## Resources

### Documentation
- `man 2 read` - system call documentation
- `man 2 open` - file descriptor documentation
- `man 3 malloc` / `man 3 free` - memory management

### Articles and Tutorials
- 42 Docs: File I/O in C
- Understanding static variables in C
- Buffer overflow prevention techniques

### AI Usage

AI was used to clarify concepts related to file descriptors and static variables.

## Author: segribas | School: 42 Heilbronn
