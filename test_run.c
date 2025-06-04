#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// testing func

bool bracket_check(char str[]) {
    int schetchik = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') schetchik++;
        else if (str[i] == ')') {
            schetchik--;
            if (schetchik < 0) return false;
        }
        i++;
    }
    return schetchik == 0;
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

void test_brackets() {
    printf("Testing validation...\n");

    assert(bracket_check("2 + 1 + (3 * 4)") == true);
    assert(bracket_check("2 + 1 - (") == false);
    assert(bracket_check("()") == true);
    assert(bracket_check(")(") == false);
    assert(bracket_check("") == true);

    int err_idx;
    char err_type;
    assert(advanced_bracket_check("{[()]}", &err_idx, &err_type) == 1);
    assert(advanced_bracket_check("{[(])}", &err_idx, &err_type) == 0);

    printf("Tests passed!\n");
}

typedef struct {
    int64_t vremya;
    char metka;
} zapis_t;

int64_t podschitat_rabochee_vremya(zapis_t* massiv, int razmer, int* oshibka) {
    *oshibka = 0;
    int64_t obshee_vremya = 0;
    int64_t nachalo = -1;
    int otkritih_sesij = 0;

    for (int i = 0; i < razmer - 1; i++) {
        for (int j = 0; j < razmer - i - 1; j++) {
            if (massiv[j].vremya > massiv[j + 1].vremya) {
                zapis_t temp = massiv[j];
                massiv[j] = massiv[j + 1];
                massiv[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < razmer; i++) {
        if (massiv[i].metka == '+') {
            if (otkritih_sesij == 0) {
                nachalo = massiv[i].vremya;
            }
            otkritih_sesij++;
        }
        else if (massiv[i].metka == '-') {
            if (otkritih_sesij > 0) {
                otkritih_sesij--;
                if (otkritih_sesij == 0 && nachalo != -1) {
                    obshee_vremya += massiv[i].vremya - nachalo;
                    nachalo = -1;
                }
            }
            else {
                *oshibka = 1;
            }
        }
    }

    if (otkritih_sesij > 0) {
        *oshibka = 1;
    }

    return obshee_vremya;
}

void test_work_time() {
    printf("Testing work time calculation...\n");

    zapis_t test1[] = { {120, '+'}, {130, '-'} };
    int err;
    int64_t result = podschitat_rabochee_vremya(test1, 2, &err);
    assert(result == 10);
    assert(err == 0);

    zapis_t test2[] = { {100, '+'}, {200, '-'}, {300, '+'}, {400, '-'} };
    result = podschitat_rabochee_vremya(test2, 4, &err);
    assert(result == 200);
    assert(err == 0);

    printf("Work time tests passed!\n");
}

int main() {
    printf("Running all tests...\n\n");

    test_brackets();
    test_work_time();

    printf("\nAll tests passed!\n");
    return 0;
}