#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t vremya;
    char metka;
} zapis_t;

int64_t podschitat_rabochee_vremya(zapis_t* massiv, int razmer, int* oshibka) {
    *oshibka = 0;
    int64_t obshee_vremya = 0;
    int64_t nachalo = -1;
    int otkritih_sesij = 0;

    // sortiruem po vremeni
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
                printf("Oshibka: minus bez plusa na pozicii %d (vremya: %lld)\n",
                    i, (long long)massiv[i].vremya);
                *oshibka = 1;
            }
        }
    }

    if (otkritih_sesij > 0) {
        printf("Oshibka: nezakritie sesii (ostalos %d otkritih)\n", otkritih_sesij);
        *oshibka = 1;
    }

    return obshee_vremya;
}

int main() {
    zapis_t test1[] = {
        {120, '+'}, {130, '-'}, {140, '+'}, {150, '-'}
    };

    zapis_t test2[] = {
        {190, '-'}, {170, '-'}, {100, '+'}, {110, '+'}, {180, '+'}
    };

    int err;
    int64_t rezultat;

    printf("Test 1:\n");
    rezultat = podschitat_rabochee_vremya(test1, 4, &err);
    printf("Rabochee vremya: %lld\n", (long long)rezultat);
    if (err) printf("Bili oshibki\n");

    printf("\nTest 2:\n");
    rezultat = podschitat_rabochee_vremya(test2, 5, &err);
    printf("Rabochee vremya: %lld\n", (long long)rezultat);
    if (err) printf("Bili oshibki\n");

    return 0;
}