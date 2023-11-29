#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

struct Str {
    int size;
    char* s;
};

int min(int a, int b) {
    return a < b ? a : b;
}

int comp(const struct Str *a, const struct Str *b) {
    int len = min(a->size, b->size);

    for (int i = 0; i < len; i++) {
        if (a->s[i] <= 'Z' && b->s[i] >= 'a') return 1;
        if (a->s[i] >= 'a' && b->s[i] <= 'Z') return -1;
        if (a->s[i] < b->s[i]) return -1;
        if (a->s[i] > b->s[i]) return 1;
    }

    if (a->size == b->size) return 0;
    else if (a->size < b->size) return -1;
    else return 1;
}

int main(void) {
    int n;
    scanf("%d\n", &n);
    struct Str *arr = (struct Str *)malloc(n * sizeof(struct Str));

    for (int i = 0; i < n; i++) {
        arr[i].s = (char*)malloc(2 * sizeof(char));
    }

    for (int i = 0; i < n; i++) {
        int cap = 1;
        int last = 0;
        char c;

        c = getchar();
        while (c != '\n') {
            arr[i].s[last] = c;
            last++;
            if (last == cap) {
                cap *= 2;
                arr[i].s = (char*)realloc(arr[i].s, (cap + 1) * sizeof(char));
            }
            c = getchar();
        }

        arr[i].size = last;
        arr[i].s[last] = '\0';
    }

    qsort(arr, n, sizeof(struct Str), (int(*)(const void *, const void *))comp);

    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i].s);
    }

    for (int i = 0; i < n; i++) {
        free(arr[i].s);
    }
    free(arr);
    return 0;
}