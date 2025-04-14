
//------------------Codigo de arbol binario generado por deep

/*
#include <stdio.h>
#include <stdlib.h>

// Definición del nodo del árbol
typedef struct Nodo {
    int valor;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

void hojas(Nodo* raiz) {
    if (raiz == NULL) return;  // Árbol vacío

    if (raiz->izq == NULL && raiz->der == NULL) {
        printf("%d ", raiz->valor);  // Es una hoja
    }
    hojas(raiz->izq);  // Recorrer subárbol izquierdo
    hojas(raiz->der);  // Recorrer subárbol derecho
}

int altura(Nodo* raiz) {
    if (raiz == NULL) return 0;  // Árbol vacío
    
    int alturaIzq = altura(raiz->izq);
    int alturaDer = altura(raiz->der);
    
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);  // max(alturaIzq, alturaDer) + 1
}

int contarNodos(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

int main() {
    // Crear un árbol de ejemplo:
    //        5
    //       / \
    //      3   8
    //     / \
    //    1   4
    Nodo* raiz = crearNodo(5);
    raiz->izq = crearNodo(3);
    raiz->der = crearNodo(8);
    raiz->izq->izq = crearNodo(1);
    raiz->izq->der = crearNodo(4);

    // Ejecutar funciones
    printf("Hojas: ");
    hojas(raiz);  // Output: 1 4 8

    printf("\nAltura: %d", altura(raiz));  // Output: 3

    printf("\nTotal de nodos: %d", contarNodos(raiz));  // Output: 5

    // Liberar memoria (opcional, pero recomendado)
    // ...
    return 0;
}


 * SALIDA ESPERADA
hojas: 1 4 8 
Altura: 3
Total de nodos: 5



//--------------- Fin depp ----------
*/

