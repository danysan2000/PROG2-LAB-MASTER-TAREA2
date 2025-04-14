#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
    int altura;  // Para calcular el factor de equilibrio
} Nodo;

// Función auxiliar para obtener la altura de un nodo
int altura(Nodo *n) {
    if (n == NULL) return 0;
    return n->altura;
}

// Función auxiliar para obtener el máximo de dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Crear un nuevo nodo
Nodo* nuevoNodo(int dato) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->altura = 1;  // Nuevo nodo es añadido como hoja
    return nodo;
}

// Rotación simple a derecha
Nodo* rotarDerecha(Nodo *y) {
    Nodo *x = y->izq;
    Nodo *T2 = x->der;

    // Realizar rotación
    x->der = y;
    y->izq = T2;

    // Actualizar alturas
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;  // Nueva raíz
}

// Rotación simple a izquierda
Nodo* rotarIzquierda(Nodo *x) {
    Nodo *y = x->der;
    Nodo *T2 = y->izq;

    // Realizar rotación
    y->izq = x;
    x->der = T2;

    // Actualizar alturas
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;  // Nueva raíz
}

// Obtener el factor de equilibrio de un nodo
int obtenerEquilibrio(Nodo *n) {
    if (n == NULL) return 0;
    return altura(n->izq) - altura(n->der);
}

// Función para insertar un nodo en el árbol AVL
Nodo* insertarAVL(Nodo* nodo, int dato) {
    // 1. Inserción normal en ABB
    if (nodo == NULL) return nuevoNodo(dato);

    if (dato < nodo->dato)
        nodo->izq = insertarAVL(nodo->izq, dato);
    else if (dato > nodo->dato)
        nodo->der = insertarAVL(nodo->der, dato);
    else  // No se permiten duplicados
        return nodo;

    // 2. Actualizar altura del nodo actual
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    // 3. Obtener el factor de equilibrio
    int equilibrio = obtenerEquilibrio(nodo);

    // 4. Realizar rotaciones si el nodo está desbalanceado

    // Caso izquierda-izquierda
    if (equilibrio > 1 && dato < nodo->izq->dato)
        return rotarDerecha(nodo);

    // Caso derecha-derecha
    if (equilibrio < -1 && dato > nodo->der->dato)
        return rotarIzquierda(nodo);

    // Caso izquierda-derecha
    if (equilibrio > 1 && dato > nodo->izq->dato) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    // Caso derecha-izquierda
    if (equilibrio < -1 && dato < nodo->der->dato) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    // Si ya está balanceado, devolver el nodo sin cambios
    return nodo;
}

