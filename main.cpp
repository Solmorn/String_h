#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "main.h"




int main() {
    char str1[] = "2345";
    char str2[] = "aaaaaaaaaa";
    size_t size = 50;
    size_t* ptr = &size;

    my_getline(&str2), ptr, stdin);

    //strncpy(str2, str1, 4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%d\n", my_atoi(str1));
    //printf("%c\n", *strrchr(str2, 'a'));
}


void my_strcpy(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    size_t i = 0;

    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
}

void my_strncpy(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    size_t ready = 0;

    while (ready < n && str[ready] != '\0') {
        dest[ready] = str[ready];
        ready++;
    }

    if (ready < n) {

        while (ready < n) {
            dest[ready] = '\0';
            ready++;
        }
    }
}

char* my_strcat(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    size_t pointer = 0;

    while (dest[pointer] != '\0') pointer++;

    for (size_t i = pointer; str[i-pointer] != '\0'; i++) {
        dest[i]  = str[i-pointer];
    }

    return dest;
}

char* my_strncat(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str  != nullptr);

    size_t pointer = 0;

    while (dest[pointer] != '\0') pointer++;

    for (size_t i = pointer; str[i-pointer] != '\0' && (i-pointer) < n; i++) {
        dest[i]  = str[i-pointer];
    }

    return dest;
}

int my_strcmp(const char* str1, const char* str2) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    for (size_t i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
        char c1 = str1[i];
        char c2 = str2[i];

        if (c1 < c2) {
            return -1;
        }

        if (c1 > c2) {
            return 1;
        }
    }

    return 0;
}

int my_strncmp(const char* str1, const char* str2, size_t n) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    for (size_t i = 0; i < n && (str1[i] != '\0' || str2[i] != '\0'); i++) {//
        char c1 = str1[i];
        char c2 = str2[i];

        if (c1 < c2) {
            return -1;
        }

        if (c1 > c2) {
            return 1;
        }
    }

    return 0;
}

char* my_strchr(const char* str, int c) {
    assert(str != nullptr);

    for (size_t i = 0; str[i] != '\0'; i++) {

        if (str[i] == c) {
            return (char*) str + i;
        }
    }

    return nullptr;
}

char* my_strrchr(const char* str, int c) {
    assert(str != nullptr);

    char* res = nullptr;

    for (size_t i = 0; str[i] != '\0'; i++) {

        if (str[i] == c) {
            res = (char*) str + i;
        }
    }

    return (char*) res;
}

size_t my_strspn(const char* str, const char* allowed) {
    assert(str     != nullptr);
    assert(allowed != nullptr);

    size_t accepted_len = 0;


    while (str[accepted_len] != '\0') {
        bool is_valid = 0;

        for (size_t j = 0; allowed[j] != '\0'; j++) {

            if (str[accepted_len] == allowed[j]) {
                is_valid = 1;
            }
        }

        if (!is_valid) return accepted_len;

        accepted_len++;
    }

    return accepted_len;
}

size_t my_strcspn(const char* str, const char* not_allowed) {
    assert(str         != nullptr);
    assert(not_allowed != nullptr);

    size_t accepted_len = 0;

    while (str[accepted_len] != '\0') {

        for (size_t j = 0; not_allowed[j] != '\0'; j++) {

            if (str[accepted_len] == not_allowed[j]) {
                return accepted_len;
            }
        }
        accepted_len++;
    }

    return accepted_len;
}

char* my_fgets(char* str, int n, FILE* file_adr) {
    assert(str      != nullptr);
    assert(file_adr != nullptr);

    int   c  = 0;
    char *cs = str;

    while (--n > 0 && (c = fgetc(file_adr)) != EOF) {

        if ((*cs++ = c) == '\n' ) {
            break;
        }
    }
    *cs = '\0';

    return (c == EOF && cs == str) ? NULL : str;
}

int my_puts(char* str) {
    assert(str != nullptr);

    for (size_t i = 0; str[i] != '\0'; i++) {
        fputc(str[i], stdin);
    }

    fputc('\n', stdin);

    return 0;
}

char* my_strdup(char* s) {
    assert(s != nullptr);
    char* pointer = nullptr;

    pointer = (char*) calloc(strlen(s)+1, sizeof(s));
    if (pointer != NULL) {
        my_strcpy(pointer, s);
    }

    return pointer;
}

int my_atoi(const char* str) {
    assert(str != nullptr);

    bool is_negative = 0;
    int res = 0;
    const char* allowed = " -0123456789";

    if (strlen(str) != my_strspn(str, allowed)) {
        return 0;
    }

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        is_negative = 1;
        str++;
    }

    while (*str != '\0') {
        char el = *str;

        if ((el >= '0') && (el <= '9')) {
            res = res * 10 + el - '0';
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

    char c = 0;
    size_t filled = 0;

    if (*lineptr == nullptr) {
        *lineptr = (char*) calloc(100, 100);
        *n = 100;
    }

    while ((c = fgetc(stream)) != '\n') {
        printf("%c\n", c);

        printf("AAA1AAAAA\n");

        if (c == EOF) return -1;
        printf("AAA2AAAAA\n");

        //if (filled == *n) {
        //    *lineptr = (char*) realloc(*lineptr, 2*filled);
        //    *n *= 2;
        //}
        printf("AAAA3AAAA\n");

        (*lineptr)[filled] = c;
        filled++;

        printf("AAAA3fthtttAAAA\n");
    }

    (*lineptr)[filled]   = '\n';
    (*lineptr)[filled+1] = '\0';

    return filled;

}


