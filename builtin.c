#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// Builtin Functions (全局函数)
// ============================================================================

void print(char *s) {
    if (s) {
        printf("%s", s);
    }
}

void println(char *s) {
    if (s) {
        printf("%s\n", s);
    } else {
        printf("\n");
    }
}

void printInt(int n) {
    printf("%d", n);
}

void printlnInt(int n) {
    printf("%d\n", n);
}

// Reads one line from stdin.
// Note: This mimics Rust's read_line behavior (ish), but returns a new String.
// The spec says "The trailing newline, if any, is not included".
char* getString() {
    char *buffer = NULL;
    size_t buf_size = 0;
    size_t len = 0;
    int c;

    // Allocate initial buffer
    buf_size = 32;
    buffer = (char*)malloc(buf_size);
    if (!buffer) {
        fprintf(stderr, "Error: memory allocation failed in getString\n");
        exit(1);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            break;
        }

        buffer[len++] = (char)c;

        // Resize if needed (leaving room for null terminator)
        if (len + 1 >= buf_size) {
            buf_size *= 2;
            buffer = (char*)realloc(buffer, buf_size);
            if (!buffer) {
                fprintf(stderr, "Error: memory allocation failed in getString\n");
                exit(1);
            }
        }
    }

    buffer[len] = '\0';
    return buffer;
}

// Reads an integer token. Skips leading whitespace.
int getInt() {
    int n;
    int result = scanf("%d", &n);
    if (result != 1) {
        // If we can't read an integer (EOF or bad format), we usually exit or return 0.
        // For a simple compiler runtime, we might exit.
        // Assuming valid input as per typical OJ/Test setups.
        return 0; 
    }
    return n;
}

// In the spec, 'exit' is treated as returning (), but implementation wise it terminates.
// The name is standard C exit, usually provided by stdlib.h.
// However, if the compiler emits a call to a specific wrapper:
void __builtin_exit(int code) {
    exit(code);
}

// ============================================================================
// Builtin Methods (方法)
// The compiler should map `variable.method()` to `method_name(variable)`
// ============================================================================

// --- .to_string() ---

// Available on: u32, usize (Assuming u32/usize map to standard unsigned int/long formats)
// Note: The resulting string must be heap allocated as per `String` semantics in spec.

char* u32_to_string(unsigned int n) {
    // Max chars for 32-bit int is 10 digits + null terminator. 16 is safe.
    char *str = (char*)malloc(16);
    if (!str) exit(1);
    sprintf(str, "%u", n);
    return str;
}

// Assuming usize is handled as unsigned long (64-bit safe)
char* usize_to_string(unsigned long n) {
    // Max chars for 64-bit int is 20 digits. 32 is safe.
    char *str = (char*)malloc(32);
    if (!str) exit(1);
    sprintf(str, "%lu", n);
    return str;
}

// --- .len() ---

// Available on: String, &str
// Spec: "returns the number of bytes"
// Note: Array len is compile-time, so only string len is implemented here.
unsigned long string_len(char *s) {
    if (!s) return 0;
    return (unsigned long)strlen(s);
}

// --- .as_str() / .as_mut_str() ---

// Spec: "Returns a string slice view... no allocation"
// In C, String and &str are both char*, so this is effectively an identity function.
// The compiler might just elide this call, but if a symbol is needed:
char* string_as_str(char *s) {
    return s;
}

// ============================================================================
// String Static Methods & Operations
// ============================================================================

// --- String::from(&str) ---

// Spec: "The result is allocated on the heap."
char* string_from(char *s) {
    if (!s) {
        // Create empty string
        char *empty = (char*)malloc(1);
        if (!empty) exit(1);
        empty[0] = '\0';
        return empty;
    }
    char *dup = strdup(s);
    if (!dup) exit(1);
    return dup;
}

// --- String::append(&mut self, &str) ---

// Spec: "Modifies the String in place."
// Implementation Note: Since `self` is mutable, in C we expect a double pointer (char**)
// so we can update the pointer if realloc moves the memory block.
//
// Compiler usage expectation: 
// let mut s = ...; s.append("foo"); -> string_append(&s, "foo");

void string_append(char **dest_ptr, char *src) {
    if (!dest_ptr || !src) return;
    
    char *dest = *dest_ptr;
    size_t old_len = (dest) ? strlen(dest) : 0;
    size_t src_len = strlen(src);
    size_t new_len = old_len + src_len;

    // Reallocate
    // +1 for null terminator
    char *new_ptr = (char*)realloc(dest, new_len + 1);
    if (!new_ptr) {
        fprintf(stderr, "Error: memory allocation failed in append\n");
        exit(1);
    }

    // If dest was NULL, we need to ensure the start is null-terminated before cat
    if (!dest) {
        new_ptr[0] = '\0';
    }

    strcat(new_ptr, src);
    
    // Update the caller's pointer
    *dest_ptr = new_ptr;
}