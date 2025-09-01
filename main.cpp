#include <stdio.h>
#include <stdlib.h>


void strcpy(char* dest, const char* str);
void strncpy(char* dest, const char* str, size_t n);
char* strcat(char* dest, const char* str);
char* strncat(char* dest, const char* str, size_t n);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t n);
const char* strchr(const char* str, const int c);
const char* strrchr(const char* str, const int c);
int my_getchar(void);


int main() {
    char str1[] = "aaaaaa";
    char str2[] = "bbabb";
    // strncpy(str2, str1, 5);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", strcat(str2, str1));
    printf("%c\n", *strrchr(str2, 'a'));
}


void strcpy(char* dest, const char* str) {
    size_t size = sizeof(str)/sizeof(str[0]);
    for (size_t i = 0; i < size + 2; i++) {
        dest[i] = str[i];
    }
}


void strncpy(char* dest, const char* str, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = str[i];
    }
}

char* strcat(char* dest, const char* str) {
    size_t size_dest = sizeof(dest)/sizeof(dest[0]);
    size_t size_str = sizeof(str)/sizeof(str[0]);
    char* res = (char *)malloc(size_dest + size_str + 1);
    for (size_t i = 0; i < size_dest; i++) {
        res[i]  = dest[i];
    }
    for (size_t i = 0; i < size_str + 1; i++) {
        res[i + size_dest]  = str[i];
    }
    return res;
}

char* strncat(char* dest, const char* str, size_t n) {
    size_t size_dest = sizeof(dest)/sizeof(dest[0]);
    char* res = (char *)malloc(size_dest + n + 1);
    for (size_t i = 0; i < size_dest; i++) {
        res[i]  = dest[i];
    }
    for (size_t i = 0; i < n + 1; i++) {
        res[i + size_dest]  = str[i];
    }
    return res;
}

int strcmp(const char* str1, const char* str2) {
    size_t size_str1 = sizeof(str1)/sizeof(str1[0]);
    size_t size_str2 = sizeof(str2)/sizeof(str2[0]);
    for (size_t i = 0; i < size_str1 + 1 && i < size_str2 + 1; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}

int strncmp(const char* str1, const char* str2, size_t n) {
    size_t size_str1 = sizeof(str1)/sizeof(str1[0]);
    size_t size_str2 = sizeof(str2)/sizeof(str2[0]);
    for (size_t i = 0; i < n + 1 && i < size_str1 + 1 && i < size_str2 + 1; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}


const char* strchr(const char* str, int c) {
    size_t size_str = sizeof(str)/sizeof(str[0]);
    for (size_t i = 0; i < size_str; i++) {
        if (str[i] == c) {
            return &str[i];
        }
    }
    return nullptr;
}

const char* strrchr(const char* str, int c) {
    size_t size_str = sizeof(str)/sizeof(str[0]);
    for (size_t i = size_str - 1; i >= 0; i--) {
        if (str[i] == c) {
            return &str[i];
        }
    }
    return nullptr;
}

size_t strspn(const char* str, const char* allowed) {
    size_t size_str = sizeof(str)/sizeof(str[0]);
    size_t size_allowed = sizeof(allowed)/sizeof(allowed[0]);
    for (size_t i = 0; i < size_str; i++) {
        for (size_t j = 0; j < size_allowed; j++) {
           if (str[i] != allowed[j]) {
            return i;
        }
        }
    }
    return size_str;
}

size_t strcspn(const char* str, const char* not_allowed) {
    size_t size_str = sizeof(str)/sizeof(str[0]);
    size_t size_not_allowed = sizeof(not_allowed)/sizeof(not_allowed[0]);
    for (size_t i = 0; i < size_str; i++) {
        for (size_t j = 0; j < size_not_allowed; j++) {
           if (str[i] == not_allowed[j]) {
            return i;
        }
        }
    }
    return size_str;
}



int my_getchar(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }

    return (--n >= 0)
        ? (unsigned char) *bufp++
        : EOF;
}

int my_fgetchar(void, FILE* f_adr) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {
        n = read(fileno(f_adr), buf, sizeof buf);
        bufp = buf;
    }

    return (--n >= 0)
        ? (unsigned char) *bufp++
        : EOF;
}

int my_fputc(int c, FILE *f) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = BUFSIZ;

    if (--n < 0) {
        if (write(fileno(f), buf, bufp - buf) != bufp - buf) {
            return EOF;
        }
        bufp = buf;
        n = BUFSIZ - 1;
    }
    *bufp++ = (char)c;
    return (unsigned char)c;
}



char* fgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;
    cs = s;
    while (--n > 0 && (c = my_fgetc(iop)) != EOF)
        if ((*cs++ = c) == '\n' )
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}


int my_puts(char *s) {
    int c;
    while (c = *s++)
    my_fputc(c, stdin);
    return ferror(stdin) ? EOF : 0;
}

char *strdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
    strcpy(p, s);
    return p;
}

int getline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c = my_fgetc()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == 'n'; {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void aaaaaa() {
    printf("AAAAAAAAAA");
}
