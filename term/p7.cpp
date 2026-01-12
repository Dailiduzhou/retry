#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Replace(char *str, char *substr, char *newstr) {
    if (!str || !substr || !newstr)
        return NULL;

    size_t len1 = strlen(str);
    size_t len2 = strlen(substr);
    size_t len3 = strlen(newstr);

    if (len2 == 0) {
        char *res = (char *)malloc(len1 + 1);
        if (!res)
            return NULL;
        memcpy(res, str, len1 + 1);
        return res;
    }

    size_t count = 0;
    char *p = str;
    char *found;
    while ((found = strstr(p, substr)) != NULL) {
        count++;
        p = found + len2;
    }

    size_t newlen = len1 + count * (len3 - len2);
    char *res = (char *)malloc(newlen + 1);
    if (!res)
        return NULL;

    char *src = str;
    char *dst = res;
    while ((found = strstr(src, substr)) != NULL) {
        size_t prefix = (size_t)(found - src);
        memcpy(dst, src, prefix);
        dst += prefix;
        memcpy(dst, newstr, len3);
        dst += len3;
        src = found + len2;
    }
    size_t remaining = strlen(src);
    memcpy(dst, src, remaining);
    dst += remaining;
    *dst = '\0';

    return res;
}

int main() {
    char s[] = "abcabcxyzabc";
    char sub[] = "abc";
    char rep[] = "12345";
    char *r = Replace(s, sub, rep);
    if (r) {
        printf("%s\n", r); // 预期: 1234512345xyz12345
        free(r);
    }
    return 0;
}
