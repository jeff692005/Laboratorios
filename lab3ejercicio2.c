#include <stdio.h>

#define N 3 

int main() {
    int matriz[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        
    };

    int suma_diagonales = 0;

    printf("Sumas de las diagonales:\n");
    for (int i = 0; i < N; i++) {
        int suma_diag = 0;
        for (int j = 0, k = i; j < N - i && k < N; j++, k++) {
            suma_diag += matriz[j][k];
        }
        if (suma_diag != 0) { 
            printf("Diagonal %d : %d\n", i + 1, suma_diag);
        }

        suma_diag = 0;
        for (int j = i, k = 0; j < N && k < N - i; j++, k++) {
            suma_diag += matriz[j][k];
        }
        if (suma_diag != 0) { 
            printf("Diagonal %d : %d\n", i + 1, suma_diag);
        }
    }

    return 0;
}