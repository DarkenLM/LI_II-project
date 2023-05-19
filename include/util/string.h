#ifndef __RL_UTIL_STRING_H
#define __RL_UTIL_STRING_H

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


#endif