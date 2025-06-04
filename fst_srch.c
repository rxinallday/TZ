#include <stdio.h>
#include <stdlib.h>

typedef struct uzel {
    int dannie;
    struct uzel* sled;
} uzel_t;

typedef struct {
    uzel_t* nachalo;
    int* kesh;
    int razmer_kesh;
    int schetchik_elem;
} spisok_s_kesh_t;

spisok_s_kesh_t* sozdatj_spisok_s_kesh() {
    spisok_s_kesh_t* sp = malloc(sizeof(spisok_s_kesh_t));
    sp->nachalo = NULL;
    sp->kesh = NULL;
    sp->razmer_kesh = 0;
    sp->schetchik_elem = 0;
    return sp;
}

void perestroitj_kesh(spisok_s_kesh_t* sp) {
    if (sp->kesh) free(sp->kesh);

    sp->kesh = malloc((sp->schetchik_elem + 1) * sizeof(int));
    sp->razmer_kesh = sp->schetchik_elem + 1;

    uzel_t* tek = sp->nachalo;
    int i = 0;
    while (tek != NULL && i < sp->schetchik_elem) {
        sp->kesh[i] = tek->dannie;
        tek = tek->sled;
        i++;
    }

    // sortirovka
    for (int i = 0; i < sp->schetchik_elem - 1; i++) {
        for (int j = 0; j < sp->schetchik_elem - i - 1; j++) {
            if (sp->kesh[j] > sp->kesh[j + 1]) {
                int temp = sp->kesh[j];
                sp->kesh[j] = sp->kesh[j + 1];
                sp->kesh[j + 1] = temp;
            }
        }
    }
}

void dobavitj_s_kesh(spisok_s_kesh_t* sp, int znach) {
    uzel_t* noviy = malloc(sizeof(uzel_t));
    noviy->dannie = znach;
    noviy->sled = sp->nachalo;
    sp->nachalo = noviy;
    sp->schetchik_elem++;
    perestroitj_kesh(sp);
}

int bistriy_poisk(spisok_s_kesh_t* sp, int znach) {
    if (!sp->kesh) return 0;

    int levo = 0;
    int pravo = sp->schetchik_elem - 1;

    while (levo <= pravo) {
        int sered = (levo + pravo) / 2;
        if (sp->kesh[sered] == znach) {
            return 1;
        }
        else if (sp->kesh[sered] < znach) {
            levo = sered + 1;
        }
        else {
            pravo = sered - 1;
        }
    }
    return 0;
}

void udalitj_spisok_s_kesh(spisok_s_kesh_t* sp) {
    uzel_t* tek = sp->nachalo;
    while (tek != NULL) {
        uzel_t* temp = tek;
        tek = tek->sled;
        free(temp);
    }
    if (sp->kesh) free(sp->kesh);
    free(sp);
}

int main() {
    spisok_s_kesh_t* sp = sozdatj_spisok_s_kesh();

    dobavitj_s_kesh(sp, 5);
    dobavitj_s_kesh(sp, 2);
    dobavitj_s_kesh(sp, 8);
    dobavitj_s_kesh(sp, 1);

    printf("Search 5: %s\n", bistriy_poisk(sp, 5) ? "found" : "not found");
    printf("Search 3: %s\n", bistriy_poisk(sp, 3) ? "found" : "not found");
    printf("Search 8: %s\n", bistriy_poisk(sp, 8) ? "found" : "not found");

    udalitj_spisok_s_kesh(sp);
    return 0;
}