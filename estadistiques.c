/*
 * estadistiques.c
 * ----------------
 * Llig nombres (enters o decimals) de l'entrada estàndard o de la línia
 * d'ordres i en mostra: quantitat, mínim, màxim, suma i mitjana.
 *
 * Ús:
 *   ./estadistiques 4 8 6
 *   echo "4 8 6" | ./estadistiques
 *   ./estadistiques < notes.txt
 *   ./estadistiques --versio
 *
 * Codis d'eixida:
 *   0  tot correcte
 *   1  no s'ha llegit cap nombre
 *   2  hi ha algun valor que no és un nombre
 *
 * Material de la pràctica «GitHub Actions: compilar un programa en C».
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSIO "1.0.0"

struct estadistiques {
    int quantitat;
    double minim;
    double maxim;
    double suma;
};

/* Afig un valor a l'acumulador. */
static void afegir(struct estadistiques *e, double valor)
{
    if (e->quantitat == 0 || valor < e->minim) {
        e->minim = valor;
    }
    if (e->quantitat == 0 || valor > e->maxim) {
        e->maxim = valor;
    }
    e->suma += valor;
    e->quantitat++;
}

/* Converteix un text en nombre. Torna 1 si és vàlid, 0 si no. */
static int llegir_nombre(const char *text, double *valor)
{
    char *final = NULL;
    *valor = strtod(text, &final);
    return final != text && *final == '\0';
}

static void mostrar(const struct estadistiques *e)
{
    printf("Quantitat: %d\n", e->quantitat);
    printf("Minim:     %.2f\n", e->minim);
    printf("Maxim:     %.2f\n", e->maxim);
    printf("Suma:      %.2f\n", e->suma);
    printf("Mitjana:   %.2f\n", e->suma / e->quantitat);
}

int main(int argc, char *argv[])
{
    struct estadistiques e = {0, 0.0, 0.0, 0.0};
    double valor;

    if (argc == 2 && strcmp(argv[1], "--versio") == 0) {
        printf("estadistiques %s\n", VERSIO);
        return 0;
    }

    if (argc > 1) {
        /* Valors passats com a arguments. */
        for (int i = 1; i < argc; i++) {
            if (!llegir_nombre(argv[i], &valor)) {
                fprintf(stderr, "Error: '%s' no es un nombre\n", argv[i]);
                return 2;
            }
            afegir(&e, valor);
        }
    } else {
        /* Valors llegits de l'entrada estàndard. */
        char paraula[64];
        while (scanf("%63s", paraula) == 1) {
            if (!llegir_nombre(paraula, &valor)) {
                fprintf(stderr, "Error: '%s' no es un nombre\n", paraula);
                return 2;
            }
            afegir(&e, valor);
        }
    }

    if (e.quantitat == 0) {
        fprintf(stderr, "Error: no s'ha llegit cap nombre\n");
        return 1;
    }

    mostrar(&e);
    return 0;
}
