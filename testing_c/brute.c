#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 9000002

void swap(char **operand1, char **operand2) {
    char *p = *operand1;
    *operand1 = *operand2;
    *operand2 = p;
}

int min(int operand1, int operand2) {
    return operand1 < operand2 ? operand1 : operand2;
}

int main(void) {
    int strings_number;
    scanf("%d ", &strings_number);

    char **strings = malloc(strings_number * sizeof(char *));

    for (int i = 0; i < strings_number; ++i) {
        strings[i] = calloc(STRING_SIZE, sizeof(char));
        fgets(strings[i], STRING_SIZE, stdin);
        strings[i][strlen(strings[i]) - 1] = '\0'; //убираю \n в конце
        char *p = realloc(strings[i], (strlen(strings[i]) + 1)* sizeof(char));
        if (p != NULL) {
            strings[i] = p;
        }
    }

    for (int i = 0; i < strings_number; ++i) {
        for (int j = i + 1; j < strings_number; ++j) {
            if (strcmp(strings[i], strings[j]) > 0) {
                swap(strings + i, strings + j);
            }
        }
    }

    for (int i = 0; i < strings_number; ++i) {
        puts(strings[i]);
    }

    for (int i = 0; i < strings_number; ++i) {
        free(strings[i]);
    }

    free(strings);
    return 0;
}