#include <stdio.h>
#include <stdlib.h>

#include "../include/abbPersonas.h"

// Función para crear un nuevo nodo
/*
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}


// Función para insertar un valor en el ABB
TABBPersonas  insertar(TABBPersonas raiz, int valor)
{
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->valor) {
        raiz->derecha = insertar(raiz->derecha, valor);
    }
    
    return raiz;
}

*/
// Función principal para imprimir el árbol (inorden rotado)
void imprimirArbol(TABBPersonas raiz, int espacio) {
    const int ESPACIO_NIVEL = 4;  // Espacio entre niveles
    
    if (raiz == NULL) {
        return;
    }
    
    // Incrementar la distancia entre niveles
    espacio += ESPACIO_NIVEL;
    
    // Procesar hijo derecho primero
    imprimirArbol(raiz->right, espacio);
    
    // Imprimir el nodo actual después de los espacios
    printf("\n");
    for (int i = ESPACIO_NIVEL; i < espacio; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->key);
    
    // Procesar hijo izquierdo
    imprimirArbol(raiz->left, espacio);
}

// Función wrapper para iniciar la impresión
void mostrarArbol(TABBPersonas raiz) {
    printf("Árbol Binario de Búsqueda (Inorden Rotado):\n");
    imprimirArbol(raiz, 0);
    printf("\n");
}

// Función principal para demostración
int main() {
    TABBPersonas raiz = NULL;
    
    // Insertar valores en el árbol
    raiz = insertar(raiz, 50);
    insertar(raiz, 30);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 70);
    insertar(raiz, 60);
    insertar(raiz, 80);
    
    // Mostrar el árbol
    mostrarArbol(raiz);
    
    return 0;
}
