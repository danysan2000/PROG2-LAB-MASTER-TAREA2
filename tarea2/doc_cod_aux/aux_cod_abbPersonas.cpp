
// CODIGO AUXILIAR Y DE PRUEBAS EN LA IMPLEMENTACION DE ABBPERSONAS.
//



// Encontrar el mínimo (siempre el nodo más a la izquierda)
Nodo* encontrarMin(Nodo* raiz) {
    if (raiz == NULL) return NULL;  // Árbol vacío
    while (raiz->izq != NULL) {
        raiz = raiz->izq;
    }
    return raiz;
}

// Encontrar el máximo (siempre el nodo más a la derecha)
Nodo* encontrarMax(Nodo* raiz) {
    if (raiz == NULL) return NULL;  // Árbol vacío
    while (raiz->der != NULL) {
        raiz = raiz->der;
    }
    return raiz;
}

// Eliminar un nodo en un ABB
Nodo* eliminarNodo(Nodo* raiz, int key) {
    if (raiz == NULL) return raiz;  // Caso base: árbol vacío

    // Búsqueda de la clave
    if (key < raiz->key) {
        raiz->izq = eliminarNodo(raiz->izq, key);  // Buscar en izquierda
    } else if (key > raiz->key) {
        raiz->der = eliminarNodo(raiz->der, key);  // Buscar en derecha
    } else {
        // Caso 1: Nodo hoja o con un hijo
        if (raiz->izq == NULL) {
            Nodo* temp = raiz->der;
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) {
            Nodo* temp = raiz->izq;
            free(raiz);
            return temp;
        }

        // Caso 2: Nodo con dos hijos
        // Opción A: Reemplazar por el máximo del subárbol izquierdo
        Nodo* temp = encontrarMax(raiz->izq);
        raiz->key = temp->key;  // Copiar la clave
        raiz->izq = eliminarNodo(raiz->izq, temp->key);  // Eliminar el duplicado
    }
    return raiz;
}

// Recorrido inorden para verificar el ABB
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izq);
        printf("%d ", raiz->key);
        inorden(raiz->der);
    }
}

int main() {
    // Crear un ABB de ejemplo
    Nodo* raiz = crearNodo(50);
    raiz->izq = crearNodo(30);
    raiz->der = crearNodo(70);
    raiz->izq->izq = crearNodo(20);
    raiz->izq->der = crearNodo(40);
    raiz->der->izq = crearNodo(60);
    raiz->der->der = crearNodo(80);

    printf("ABB antes de eliminar (Inorden): ");
    inorden(raiz);  // Output: 20 30 40 50 60 70 80

    // Eliminar nodo con key=50 (raíz)
    raiz = eliminarNodo(raiz, 50);

    printf("\nABB después de eliminar 50 (Inorden): ");
    inorden(raiz);  // Output: 20 30 40 60 70 80

    return 0;
}
