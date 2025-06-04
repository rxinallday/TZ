#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool bracket_check(char str[]) {
    int schetchik = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '(') {
            schetchik++;
        }
        else if (str[i] == ')') {
            schetchik--;
            if (schetchik < 0) {
                return false;
            }
        }
        i++;
    }

    return schetchik == 0;
}

int bracket_check_with_index(char str[], int* error_idx) {
    int schetchik = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '(') {
            schetchik++;
        }
        else if (str[i] == ')') {
            schetchik--;
            if (schetchik < 0) {
                *error_idx = i;
                return 0;
            }
        }
        i++;
    }

    if (schetchik != 0) {
        *error_idx = strlen(str);
        return 0;
    }

    return 1;
}

int advanced_bracket_check(char str[], int* error_idx, char* error_type) {
    char stek[1000];
    int top = -1;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            top++;
            stek[top] = str[i];
        }
        else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            if (top < 0) {
                *error_idx = i;
                *error_type = str[i];
                return 0;
            }

            char ozhidaem;
            if (str[i] == ')') ozhidaem = '(';
            else if (str[i] == ']') ozhidaem = '[';
            else ozhidaem = '{';

            if (stek[top] != ozhidaem) {
                *error_idx = i;
                *error_type = str[i];
                return 0;
            }
            top--;
        }
        i++;
    }

    if (top >= 0) {
        *error_idx = strlen(str);
        *error_type = stek[top];
        return 0;
    }

    return 1;
}

int main() {
    char test1[] = "2 + 1 + (3 * 4)";
    char test2[] = "2 + 1 - (";
    char test3[] = "{[()]}";
    char test4[] = "{[(])}";

    printf("Test 1: %s\n", bracket_check(test1) ? "true" : "false");
    printf("Test 2: %s\n", bracket_check(test2) ? "true" : "false");

    int err_idx;
    char err_type;

    printf("Advanced test 3: %s\n", advanced_bracket_check(test3, &err_idx, &err_type) ? "true" : "false");

    if (!advanced_bracket_check(test4, &err_idx, &err_type)) {
        printf("Error at index %d, bracket type: %c\n", err_idx, err_type);
    }

    return 0;
}