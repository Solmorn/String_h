#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "main.h"




int main() {
    char str1[] = "aaadedcba";
    char str2[30] = "aa";
    //strncpy(str2, str1, 4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%d\n", my_strspn(str1, str2));
    //printf("%c\n", *strrchr(str2, 'a'));
}


void my_strcpy(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str != nullptr);

    size_t i = 0;
    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
}

void my_strncpy(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str != nullptr);

    size_t ready = 0;

    for (size_t i = 0; i < n && str[i] != '\0'; i++) {
        dest[i] = str[i];
        ready++;
    }

    if (ready < n) {

        for (size_t i = ready; i < n; i++) {
            dest[i] = '\0';
            ready++;
        }
    }
}

char* my_strcat(char* dest, const char* str) {
    assert(dest != nullptr);
    assert(str != nullptr);

    size_t pointer = 0;

    while (dest[pointer] != '\0') pointer++;

    for (size_t i = pointer; str[i-pointer] != '\0'; i++) {
        dest[i]  = str[i-pointer];
    }

    return dest;
}

char* my_strncat(char* dest, const char* str, size_t n) {
    assert(dest != nullptr);
    assert(str != nullptr);

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

        if (str1[i] < str2[i]) {
            return -1;
        }

        if (str1[i] > str2[i]) {
            return 1;
        }
    }

    return 0;
}

int my_strncmp(const char* str1, const char* str2, size_t n) {
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    for (size_t i = 0; i < n && (str1[i] != '\0' || str2[i] != '\0'); i++) {

        if (str1[i] < str2[i]) {
            return -1;
        }

        if (str1[i] > str2[i]) {
            return 1;
        }
    }

    return 0;
}

char* my_strchr(char* str, int c) { //костыль
    assert(str != nullptr);

    for (size_t i = 0; str[i] != '\0'; i++) {

        if (str[i] == c) {
            return &str[i];
        }
    }

    return nullptr;
}

char* my_strrchr(char* str, int c) { //костыль
    assert(str != nullptr);

    char* res = nullptr;

    for (size_t i = 0; str[i] != '\0'; i++) {

        if (str[i] == c) {
            res = &str[i];
        }
    }

    return res;
}

size_t my_strspn(const char* str, const char* allowed) {
    assert(str != nullptr);
    assert(allowed != nullptr);

    size_t accepted_len = 0;

    while (str[accepted_len] != '\0') {

        for (size_t j = 0; allowed[j] != '\0'; j++) {

            if (str[accepted_len] != allowed[j]) {
                return accepted_len;
            }
        }
        accepted_len++;
    }

    return accepted_len;
}

size_t my_strcspn(const char* str, const char* not_allowed) {
    assert(str != nullptr);
    assert(not_allowed != nullptr);

    size_t accepted_len = 0;

    while (str[accepted_len] != '\0') {

        for (size_t j = 0; allowed[j] != '\0'; j++) {

            if (str[accepted_len] == not_allowed[j]) {
                return accepted_len;
            }
        }
        accepted_len++;
    }

    return accepted_len;
}

char* my_fgets(char *s, int n, FILE *iop) {
    int c = 0;
    char *cs = s;

    while (--n > 0 && (c = fgetc(iop)) != EOF) {

        if ((*cs++ = c) == '\n' ) {
            break;
        }
    }
    *cs = '\0';

    return (c == EOF && cs == s) ? NULL : s;
}

int my_puts(char *s) {
    int c = 0;

    while (c = *s++) {
        fputc(c, stdin);
    }
    fputc('\n', stdin);

    return 0;
}

char *my_strdup(char *s) {
    char *pointer = nullptr;

    pointer = (char *) malloc(strlen(s)+1); //поставить каллок?
    if (pointer != NULL) {
        strcpy(pointer, s);
    }

    return pointer;
}

