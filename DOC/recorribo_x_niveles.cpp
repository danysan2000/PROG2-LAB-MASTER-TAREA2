#include <stdio.h>
#include <stdlib.h>

// Estructura para un nodo del árbol binario
typedef struct Nodo {
    int dato;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Estructura para la cola (necesaria para el BFS)
typedef struct ColaNodo {
    Nodo* nodoArbol;
    struct ColaNodo* siguiente;
} ColaNodo;

//encabezado -->DAN
typedef struct Cola {
    ColaNodo* frente;
    ColaNodo* final;
} Cola;

// Funciones auxiliares para la cola
Cola* crearCola() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->frente = cola->final = NULL;
    return cola;
}

void encolar(Cola* cola, Nodo* nodoArbol) {
    ColaNodo* nuevoNodo = (ColaNodo*)malloc(sizeof(ColaNodo));
    nuevoNodo->nodoArbol = nodoArbol;
    nuevoNodo->siguiente = NULL;
    
    if (cola->final == NULL) {
        cola->frente = cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
}

Nodo* desencolar(Cola* cola) {
    if (cola->frente == NULL) return NULL;
    
    ColaNodo* temp = cola->frente;
    Nodo* nodoArbol = temp->nodoArbol;
    cola->frente = cola->frente->siguiente;
    
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    
    free(temp);
    return nodoArbol;
}

int colaVacia(Cola* cola) {
    return cola->frente == NULL;
}

// Función para recorrido por niveles (BFS)
void recorridoPorNiveles(Nodo* raiz) {
    if (raiz == NULL) return;
    
    Cola* cola = crearCola();
    encolar(cola, raiz);
    
    while (!colaVacia(cola)) {
        Nodo* nodoActual = desencolar(cola);
        printf("%d ", nodoActual->dato);
        
        if (nodoActual->izquierdo != NULL) {
            encolar(cola, nodoActual->izquierdo);
        }
        
        if (nodoActual->derecho != NULL) {
            encolar(cola, nodoActual->derecho);
        }
    }
    
    free(cola);
}

// Función auxiliar para crear un nuevo nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izquierdo = nuevoNodo->derecho = NULL;
    return nuevoNodo;
}

// Ejemplo de uso
int main() {
    // Crear un árbol binario de ejemplo
    Nodo* raiz = crearNodo(1);
    raiz->izquierdo = crearNodo(2);
    raiz->derecho = crearNodo(3);
    raiz->izquierdo->izquierdo = crearNodo(4);
    raiz->izquierdo->derecho = crearNodo(5);
    raiz->derecho->izquierdo = crearNodo(6);
    raiz->derecho->derecho = crearNodo(7);
    
    printf("Recorrido por niveles (BFS): ");
    recorridoPorNiveles(raiz);
    printf("\n");
    
    return 0;
}


