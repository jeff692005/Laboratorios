#include <stdio.h>

void printBi(unsigned int n) {
    if (n > 1) {
        printBi(n / 2);
    }
    printf("%d", n % 2);
}

int main() {
    unsigned int n;

    printf("Introdusca un número entero positivo: ");
    scanf("%u", &n);

    printf("En binario %u es: ", n);
    printBi(n);
    printf("\n");

    return 0;
}