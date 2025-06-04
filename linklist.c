#include <stdio.h>
#include <stdlib.h>

typedef struct uzel {
    int dannie;
    struct uzel* sled;
} uzel_t;

typedef struct {
    uzel_t* nachalo;
} spisok_t;

spisok_t* sozdatj_spisok() {
    spisok_t* sp = malloc(sizeof(spisok_t));
    sp->nachalo = NULL;
    return sp;
}

void dobavitj(spisok_t* sp, int znach) {
    uzel_t* noviy = malloc(sizeof(uzel_t));
    noviy->dannie = znach;
    noviy->sled = sp->nachalo;
    sp->nachalo = noviy;
}

void pechatj_priamo(spisok_t* sp) {
    uzel_t* tek = sp->nachalo;
    while (tek != NULL) {
        printf("%d ", tek->dannie);
        tek = tek->sled;
    }
    printf("\n");
}

void pechatj_obratno_rek(uzel_t* uzel) {
    if (uzel == NULL) return;
    pechatj_obratno_rek(uzel->sled);
    printf("%d ", uzel->dannie);
}

void pechatj_obratno(spisok_t* sp) {
    pechatj_obratno_rek(sp->nachalo);
    printf("\n");
}

void udalitj_spisok(spisok_t* sp) {
    uzel_t* tek = sp->nachalo;
    while (tek != NULL) {
        uzel_t* temp = tek;
        tek = tek->sled;
        free(temp);
    }
    free(sp);
}

int main() {
    spisok_t* moi_spisok = sozdatj_spisok();

    dobavitj(moi_spisok, 1);
    dobavitj(moi_spisok, 2);
    dobavitj(moi_spisok, 3);
    dobavitj(moi_spisok, 4);

    printf("Direct: ");
    pechatj_priamo(moi_spisok);

    printf("Reverse: ");
    pechatj_obratno(moi_spisok);

    udalitj_spisok(moi_spisok);
    return 0;
}