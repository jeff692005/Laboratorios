#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANO 6

int encontrarDiag(int matriz[TAMANO][TAMANO], int x, int y) {
    int max = 0;
    int count = 0;
    
    while (x < TAMANO && y < TAMANO) {
        if (matriz[x][y] == 1) {
            count++;
            if (count > max) {
                max = count;
            }
        } else {
            count = 0;
        }
        x++;
        y++;
    }
    
    return max;
}

int encontrardiaglarga(int matriz[TAMANO][TAMANO]) {
    int max = 0;

    for (int i = 0; i < TAMANO; i++) {
        int diag_max = encontrarDiag(matriz, 0, i);
        if (diag_max > max) {
            max = diag_max;
        }
    }

    for (int i = 1; i < TAMANO; i++) {
        int diag_max = encontrarDiag(matriz, i, 0);
        if (diag_max > max) {
            max = diag_max;
        }
    }

    return max;
}

void MatrizRand(int matriz[TAMANO][TAMANO]) {
    srand(time(NULL));
    
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            matriz[i][j] = rand() % 2;
        }
    }
}

void imprimirMatriz(int matriz[TAMANO][TAMANO]) {
    printf("La matriz corresponde a:\n");
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matriz[TAMANO][TAMANO];

    MatrizRand(matriz);

    imprimirMatriz(matriz);

    int diaglarga = encontrardiaglarga(matriz);

    printf("La secuencia de 1s más grande es: %d\n", diaglarga);

    return 0;
}