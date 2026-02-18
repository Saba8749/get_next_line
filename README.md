# get_next_line

*This project has been created as part of the 42 curriculum by segribas.*

## Description

The get_next_line project is about programming a function that returns a line read from a file descriptor. The main challenge is handling the buffer efficiently and managing memory properly while reading from different sources (files, stdin, etc.). The function must work regardless of the BUFFER_SIZE value and handle multiple consecutive calls without losing data between reads.

The goal is to understand how file descriptors work, how to read from them efficiently, and how to manage static variables to maintain state between function calls.

## Instructions

### Compilation

The function requires a BUFFER_SIZE to be defined at compilation time. The default value is 42 (defined in the header file), but can be overridden:

```bash
# Standard compilation
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Or use the predefined value in header
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl_test
```

### Testing

Create a test file and run:
```bash
echo -e "Line 1\nLine 2\nLine 3" > test.txt
./gnl_test
```

Test with different BUFFER_SIZE values:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o gnl_test
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c -o gnl_test
```

### Memory Leak Checking

To check for memory leaks using valgrind:

```bash
# Compile with debug flag
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Run with valgrind
valgrind --leak-check=full --show-leak-kinds=all ./gnl_test
```

Expected output: `All heap blocks were freed -- no leaks are possible`

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

### Bonus Usage Example

Here's an example demonstrating reading from multiple files simultaneously:

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    int fd1 = open("test1.txt", O_RDONLY);
    char *line;

    // Read first line from test.txt
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    
    // Switch to test1.txt and read first line
    line = get_next_line(fd1);
    printf("%s", line);
    free(line);
    
    // Continue reading rest of test.txt
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    printf("\nfile finished\n");
    
    // Continue reading rest of test1.txt
    while ((line = get_next_line(fd1)))
    {
        printf("%s", line);
        free(line);
    }
    printf("\nfile finished\n");
    
    close(fd);
    close(fd1);
    return (0);
}
```

**What happens here:**
- Two files are opened simultaneously (fd and fd1)
- We alternate between reading from different files
- Each file descriptor maintains its own position independently
- When we switch from fd to fd1, fd's position is saved in `stash[fd]`
- When we return to fd, it continues exactly where it left off
- This demonstrates that the bonus version can handle multiple file descriptors without mixing their data

## Resources

## For testing with Paco/Francinette 
# https://github.com/Desoroxxx/francinette

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