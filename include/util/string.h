#ifndef __RL_UTIL_STRING_H
#define __RL_UTIL_STRING_H

#include <ctype.h>
#include <errno.h>
#include "common.h"

inline int strlen_cp(char* str) {
    int c = 0;
    while (*str != '\0') {
        c++;
        str = str + 1;
    }

    return c;
}

typedef struct char_node {
    char* value;
    struct char_node* next;
} CharNode;


inline CharNode* char_node(char* value) {
    CharNode* n = calloc(1, sizeof(struct char_node));
    n->value = value;
    n->next = NULL;
    return n;
}

static inline void replace_substring(char* str, const char* oldSubstr, const char* newSubstr) {
    int oldSubstrLen = strlen(oldSubstr);
    int newSubstrLen = strlen(newSubstr);
    int strLen = strlen(str);

    if (oldSubstrLen == 0 || strLen == 0) return;

    char* pos = strstr(str, oldSubstr);
    while (pos != NULL) {
        int remainingLen = str + strLen - (pos + oldSubstrLen);
        memmove(pos + newSubstrLen, pos + oldSubstrLen, remainingLen + 1);
        memcpy(pos, newSubstr, newSubstrLen);

        if (pos + newSubstrLen >= str + strLen) break;

        pos = strstr(pos + newSubstrLen, oldSubstr);
        strLen += newSubstrLen - oldSubstrLen;
    }
}

static inline void get_multiline_stats(const char* str, int* lineCount, int* longestLineLength) {
    int lines = 0;
    int maxLen = 0;
    int curLen = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            lines++;

            if (curLen > maxLen) {
                maxLen = curLen;
            }
            curLen = 0;
        } else {
            curLen++;
        }
    }

    if (curLen > 0) {
        lines++;

        if (curLen > maxLen) {
            maxLen = curLen;
        }
    }

    *lineCount = lines;
    *longestLineLength = maxLen;
}

/*
 * Use the function `get_multiline_stats` to create an array with the required dimensions
 */
static inline void split_by(const char* input, const char* separator, char* dest[]) {
    char* inputCopy = strdup(input);
    char* token = strtok(inputCopy, separator);
    int i = 0;

    while (token != NULL) {
        // printf("Token: %s\n", token);
        strcpy(dest[i++], token); 
        token = strtok(NULL, separator);
    }

    free(inputCopy);
}

static inline void trim(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;

    while (isspace(*start)) {
        start++;
    }

    while (end > start && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}

static inline void truncateString(char* str, size_t maxLength) {
    size_t length = strlen(str);
    if (length > maxLength) {
        if (maxLength > 5) {
            str[maxLength - 4] = '.';
            str[maxLength - 3] = '.';
            str[maxLength - 2] = '.';
        }
        
        str[maxLength - 1] = '\0';
    }
}

static inline int equal_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

#ifndef __STDC_LIB_EXT1__
static inline int strcpy_s(char* dest, const char* src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        if (dest != NULL && dest_size > 0) {
            dest[0] = '\0';  // Nullify the destination string
        }
        return EINVAL;  // Invalid argument(s)
    }

    size_t src_length = strlen(src);
    if (src_length + 1 > dest_size) {
        // Source string is too long for the destination buffer
        dest[0] = '\0';  // Nullify the destination string
        return ERANGE;  // Destination buffer is not large enough
    }

    // Copy the source string to the destination
    for (size_t i = 0; i <= src_length; ++i) {
        dest[i] = src[i];
    }

    return 0;  // Success
}
#endif



#endif