#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int diag_larga(int **matriz, int tamano) {
    int max_longitud = 0;

    for (int col = 0; col < tamano; col++) {
        int fila = 0, c = col, longitud_actual = 0;
        while (fila < tamano && c >= 0) {
            if (matriz[fila][c] == 1) {
                longitud_actual++;
                if (longitud_actual > max_longitud) max_longitud = longitud_actual;
            } else {
                longitud_actual = 0;
            }
            fila++;
            c--;
        }
    }

    for (int fila_start = 1; fila_start < tamano; fila_start++) {
        int fila = fila_start, c = tamano - 1, longitud_actual = 0;
        while (fila < tamano && c >= 0) {
            if (matriz[fila][c] == 1) {
                longitud_actual++;
                if (longitud_actual > max_longitud) max_longitud = longitud_actual;
            } else {
                longitud_actual = 0;
            }
            fila++;
            c--;
        }
    }

    return max_longitud;
}


void ReserM_MD(int ***matriz, int tamano){
    *matriz = (int **)malloc(tamano * sizeof(int *));
    for (int i = 0; i < tamano; i++) {
        (*matriz)[i] = (int *)malloc(tamano * sizeof(int));
    }
}

void llenar_matriz(int **matriz, int tamano) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            matriz[i][j] = rand() % 2;
        }
    }
}


void imprimir_matriz(int **matriz, int tamano){
    printf("Matriz %dx%d:\n", tamano, tamano);
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }
}


void liberar_matriz(int **matriz, int tamano){
    for(int i = 0; i < tamano; i++){
        free(matriz[i]);
    }
    free(matriz);
}


int main(){
    int tamano, diag_mas_larga;
    int **matriz = NULL;

    srand(time(NULL));
    
    printf("Ingrese el tamaño de la matriz deseada:\n");
    scanf("%d", &tamano);

    ReserM_MD(&matriz, tamano);
    llenar_matriz(matriz, tamano);
    imprimir_matriz(matriz, tamano);

    diag_mas_larga = diag_larga(matriz, tamano);
    printf("La secuencia de 1s más grande en diagonales secundarias es: %d\n", diag_mas_larga);

    // Liberar memoria
    liberar_matriz(matriz, tamano);

    return 0;
}
