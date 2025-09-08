#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "string.h"




int main() {
    char  str1[] = "2345";
    char* str2   = (char*) calloc(100, 1);


    size_t  size = 50;
    size_t* ptr  = &size;

    my_getline(&(str2), ptr, stdin);

    //strncpy(str2, str1, 4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%d\n", my_atoi(str1));
    //printf("%c\n", *strrchr(str2, 'a'));
}


void my_strcpy(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    char c = 0;

    for (size_t copied_el = 0; c = *(str + copied_el); copied_el++) {
        *(dest + copied_el) = c;
    }
}

void my_strncpy(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    char c = 0;

    for (size_t copied_el = 0; copied_el < n && c = *(str + copied_el); copied_el++) {
        *(dest + copied_el) = c;
    }

    while (copied_el++ < n) {
        *(dest + copied_el) = '\0';
    }
}

char* my_strcat(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    char c = 0;

    while (*dest++);

    for (size_t i = dest; c = *(str + i); i++) {
        *i  = c;
    }

    return dest;
}

char* my_strncat(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    char c = 0;

    while (*dest++);

    for (size_t i = dest; c = *(str + i) && (i-dest) < n; i++) {
        *i  = c;
    }

    return dest;
}

int my_strcmp(const char* str1, const char* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    char c1    = 0;
    char c2    = 0;
    int  delta = 0;

    while (c1 = *str1++ && *str2++) {

        delta = c1 - c2;

        if (delta != 0) {
            return delta;
        }
    }

    return 0;
}

int my_strncmp(const char* str1, const char* str2, size_t n) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    char   c1         = 0;
    char   c2         = 0;
    int    delta      = 0;
    size_t checked_el = 0;

    for (checked_el < n && c1 = *str1++ && c2 = *str2++) {

        delta = c1 - c2;

        if (delta != 0) {
            return delta;
        }
    }

    return 0;
}

char* my_strchr(const char* str, int c) {
    assert(str != nullptr);

    while (*str++) {

        if (*str == c) {
            return (char*) str;
        }
    }

    return nullptr;
}

char* my_strrchr(const char* str, int c) {
    assert(str != nullptr);

    char* res = nullptr;

    while (*str++) {

        if (*str == c) {
            res = (char*) str;
        }
    }

    return (char*) res;
}

size_t my_strspn(const char* str, const char* usable_symbols) {
    assert(str     != nullptr);
    assert(usable_symbols != nullptr);

    size_t valid_len = 0;
    bool   is_valid     = false;

    while (str[valid_len] != '\0') {

        for (size_t j = 0; usable_symbols[j] != '\0'; j++) {

            if (str[valid_len] == usable_symbols[j]) {
                is_valid = 1;
            }
        }

        if (!is_valid) return valid_len;

        valid_len++;
    }

    return valid_len;
}

size_t my_strcspn(const char* str, const char* banned_symbols) {
    assert(str         != nullptr);
    assert(banned_symbols != nullptr);

    size_t valid_len = 0;

    while (str[valid_len] != '\0') {

        for (size_t j = 0; banned_symbols[j] != '\0'; j++) {

            if (str[valid_len] == banned_symbols[j]) {
                return valid_len;
            }
        }
        valid_len++;
    }

    return valid_len;
}

char* my_fgets(char* s, int n, FILE* iop) {
    char* cs = s;
    char c = 0;

    while (--n > 0 && (c = fgetc(iop)) != EOF) {
        *cs++ = c;
        if (c == '\n') break;
    }

    *cs = '\0';

    return (c == EOF && cs == s) ? nullptr : s;
}

int my_puts(char* str) {
    assert(str != nullptr);

    while (*str++) {

        if (fputc(*str, stdout) == -1) return -1;
    }

    fputc('\n', stdout);

    return 0;
}

char* my_strdup(char* s) {
    assert(s != nullptr);

    char* pointer = nullptr;

    pointer = (char*) calloc(strlen(s)+1, sizeof(char));

    if (pointer != nullptr) {
        my_strcpy(pointer, s);
    }

    return pointer;
}

static bool IsDigit(char c) return ((c >= '0') && (c <= '9')) ? true : false;
static size_t BoolToDigit(char c) return c - '0';

int my_atoi(const char* str) {
    assert(str != nullptr);

    bool is_negative = false;
    int  res         = 0;
    char digit       = 0;

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        is_negative = true;
        str++;
    }

    while (*str != '\0') {
        digit = *str;

        if (IsDigit(digit)) {
            res = res * 10 + BoolToDigit(digit);
        } else {
            return 0;
        }

        str++;
    }

    return (is_negative) ? -res : res;
}

ssize_t my_getline(char** lineptr, size_t* n, FILE* stream) {
    assert(lineptr != nullptr);
    assert(stream  != nullptr);
    assert(n       != nullptr);

    char   c       = 0;
    char** buf_adr = *lineptr;
    size_t filled  = 0;

    if (buf_adr == nullptr) {

        if (!(buf_adr = (char*) calloc(DEFAULT_BUFF, 1))) *n = 100;
        else return 0;
    }

    while ((c = fgetc(stream)) != '\n') {

        if (c == EOF) return -1;

        if (filled == *n) {

            if (!(buf_adr = (char*) realloc(buf_adr, MEMORY_MULTIPLICATION*filled))) *n *= MEMORY_MULTIPLICATION;
            else return 0;
        }

        (buf_adr)[filled] = c;
        filled++;
    }

    buf_adr[filled]   = '\n';
    buf_adr[filled+1] = '\0';

    return filled;

}

size_t my_strlen(const char* s) {
    size_t len = 0;

    while (*s++) {
        len++;
    }

    return len;
}

char* strstr(const char* haystack, const char* needle) {
    size_t needle_length = strlen(needle);

    while (*haystack++) {

        if (!my_strncmp(haystack, needle, needle_length)) return haystack;
    }

    return nullptr;
}


