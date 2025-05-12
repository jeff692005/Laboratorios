#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TAMANO 100

bool binario(int valor) {
    return valor == 0 || valor == 1;
}

bool leer_matriz(const char* nombre_archivo, int matriz[MAX_TAMANO][MAX_TAMANO], int* tamano) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return false;
    }

    int filas = 0;
    int columnas_esperadas = -1;
    char linea[1024];

    printf("La matriz utilizada corresponde a:\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        int col = 0;
        char* token = strtok(linea, " \t\n\r");

        while (token != NULL) {
            int valor = atoi(token);

            if (!binario(valor)) {
                printf("Error: La matriz contiene valores no binarios (valor: %d en fila %d).\n", valor, filas + 1);
                fclose(archivo);
                return false;
            }

            matriz[filas][col++] = valor;
            token = strtok(NULL, " \t\n\r");
        }

        if (col == 0) continue;

        if (columnas_esperadas == -1) {
            columnas_esperadas = col;
        } else if (col != columnas_esperadas) {
            printf("Error: La matriz no es cuadrada");
            fclose(archivo);
            return false;
        }



        for (int i = 0; i < col; i++) {
            printf("%d", matriz[filas][i]);
            if (i < col - 1) printf(" ");
        }
        printf("\n");

        filas++;
    }

    fclose(archivo);

    if (filas != columnas_esperadas) {
        printf("Error: La matriz no es cuadrada");
        return false;
    }

    *tamano = filas;
    return true;
}


int diag_larga(int matriz[MAX_TAMANO][MAX_TAMANO], int tamano) {
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

int vert_larga(int matriz[MAX_TAMANO][MAX_TAMANO], int tamano) {
    int max_longitud = 0;

    for (int col = 0; col < tamano; col++) {
        int longitud_actual = 0;
        for (int fila = 0; fila < tamano; fila++) {
            if (matriz[fila][col] == 1) {
                longitud_actual++;
                if (longitud_actual > max_longitud) max_longitud = longitud_actual;
            } else {
                longitud_actual = 0;
            }
        }
    }

    return max_longitud;
}

// Programa principal
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre_del_archivo>\n", argv[0]);
        return 1;
    }

    int matriz[MAX_TAMANO][MAX_TAMANO];
    int tamano;

    if (!leer_matriz(argv[1], matriz, &tamano)) {
        return 1;
    }

    int diagonal_inversa = diag_larga(matriz, tamano);
    int vertical = vert_larga(matriz, tamano);

    int max_total = (diagonal_inversa > vertical) ? diagonal_inversa : vertical;

    printf("La secuencia de 1s más grande es: %d\n", max_total);

    return 0;
}
