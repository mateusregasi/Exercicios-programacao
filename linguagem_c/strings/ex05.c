#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char entradas[1000][100];
    int num_entradas = 0;

    // Tu pode ler uma frase por vez, não precisa reservar um espaço de memória para todas as frases
    while (1) {
        if (scanf("%s", entradas[num_entradas]) == EOF) {
            break;
        }
        num_entradas++;
    }

    for (int i = 0; i < num_entradas; i++) {
        bool a = false, b = false, c = false, d = false, e = false;
        char *aux[5];
        char *token = strtok(entradas[i], "-");
        int j = 0;
        while (token != NULL) {
            aux[j++] = token;
            token = strtok(NULL, "-");
        }

        if (aux[0][0] == 'c' || aux[0][strlen(aux[0]) - 1] == 'c') {
            a = true;
        }
        if (strchr(aux[1], 'o') != NULL || aux[1][strlen(aux[1]) - 1] == 'o') {
            b = true;
        }
        if (strchr(aux[2], 'b') != NULL || aux[2][strlen(aux[2]) - 1] == 'b') {
            c = true;
        }
        if (strchr(aux[3], 'o') != NULL || aux[3][strlen(aux[3]) - 1] == 'o') {
            d = true;
        }
        if (strchr(aux[4], 'l') != NULL || aux[4][strlen(aux[4]) - 1] == 'l') {
            e = true;
        }

        if (a && b && c && d && e) {
            printf("GRACE HOPPER\n");
        } else {
            printf("BUG\n");
        }
    }

    return 0;
}