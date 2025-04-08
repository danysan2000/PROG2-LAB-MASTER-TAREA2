
/*
 * Intentona de indexado por hash.
 * Index asociado rep_lseadopciones 
 struct key1 {
 	int cipersona;
	int idperro;
	} key_rep_lseadopciones;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    int id1;
    int id2;
    char data[100]; // otros datos de la estructura
} MyStruct;

typedef struct {
    int key1;
    int key2;
    MyStruct* value;
} HashEntry;

HashEntry* hashTable[TABLE_SIZE];

// Función hash simple para dos enteros
unsigned int hash(int key1, int key2) {
    return (key1 * 31 + key2) % TABLE_SIZE;
}

// Insertar en la tabla hash
void insert(int key1, int key2, MyStruct* value) {
    unsigned int index = hash(key1, key2);
    
    HashEntry* entry = malloc(sizeof(HashEntry));
    entry->key1 = key1;
    entry->key2 = key2;
    entry->value = value;
    
    // Manejo simple de colisiones (sobrescribe)
    hashTable[index] = entry;
}

// Buscar en la tabla hash
MyStruct* search(int key1, int key2) {
    unsigned int index = hash(key1, key2);
    
    if (hashTable[index] != NULL && 
        hashTable[index]->key1 == key1 && 
        hashTable[index]->key2 == key2) {
        return hashTable[index]->value;
    }
    
    return NULL;
}

int main() {
    MyStruct array[] = {
        {1, 100, "Datos 1"},
        {2, 200, "Datos 2"},
        {3, 300, "Datos 3"}
    };
    int arraySize = sizeof(array) / sizeof(array[0]);
    
    // Indexar el array
    for (int i = 0; i < arraySize; i++) {
        insert(array[i].id1, array[i].id2, &array[i]);
    }
    
    // Ejemplo de búsqueda
    MyStruct* result = search(2, 200);
    if (result != NULL) {
        printf("Encontrado: %s\n", result->data);
    } else {
        printf("No encontrado\n");
    }
    
    return 0;
}
*/	
