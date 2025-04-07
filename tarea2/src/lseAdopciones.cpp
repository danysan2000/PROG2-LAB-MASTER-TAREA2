#include "../include/lseAdopciones.h"

typedef struct rep_lsedata *TLSEData;

struct rep_lsedata 
{
    TPersona	prs; // Persona
    TPerro      per; // Perro
    TFecha      fechaAdop; // Fecha de Adoption.
	TLSEData	sig;						   // 
};	

struct rep_lseadopciones 
{
	/*
    TPersona	prs; // Persona
    TPerro      per; // Perro
    TFecha      fechaAdop; // Fecha de Adoption
	*/
	TLSEData data;
	struct {
		TLSEData primero;
		TLSEData ultimo;
		int cnt_reg;
	} ctrl;						// control lista 
};

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

TLSEAdopciones crearTLSEAdopcionesVacia()
{
    TLSEAdopciones tlseadop = new rep_lseadopciones ;
	/*
	tlseadop->prs = NULL;
   	tlseadop->per = NULL;
   	tlseadop->fechaAdop = NULL ;
	*/
	tlseadop->data = NULL;
	tlseadop->ctrl.primero = tlseadop->ctrl.ultimo =  NULL;
	tlseadop->ctrl.cnt_reg = 0;
	return tlseadop;
}


bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	return lseAdopciones->ctrl.cnt_reg == 0;
}

void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	
	TLSEAdopciones auxlse = lseAdopciones ;
	TLSEData ax1;
	if( auxlse == NULL  ) return;
	ax1 = auxlse->data;
	while( ax1 != NULL )
	{		
		printf("---------------------------\n");
		printf("Adopcion en fecha "); imprimirTFecha(ax1->fechaAdop );
		printf("Adoptante:\n");
		printf("Persona %s %s\n", nombreTPersona( ax1->prs), apellidoTPersona( ax1->prs ));
		printf("CI: %d\n", ciTPersona( ax1->prs)); 
		printf("Adoptado:\n");
		printf("Perro %d\n", idTPerro( ax1->per ));
		printf("Nombre: %s\n", nombreTPerro( ax1->per));
		printf("Fecha de ingreso: " ); imprimirTFecha( fechaIngresoTPerro( ax1->per ));
		printf("---------------------------\n");
	}
}

void liberarTLSEAdopciones(TLSEAdopciones &lseAdopciones)
{
	TLSEAdopciones  axAdop = lseAdopciones;
	TLSEData axData1, axData2;

	if ( axAdop == NULL ) return;

	axData1 = axAdop->data;
	while( axData1 != NULL  )
	{
		liberarTFecha(axData1->fechaAdop );
		liberarTPerro(axData1->per);
		liberarTPersona(axData1->prs);
		axData2 = axData1->sig;
		delete axData1;
		axData1 = axData2;
	}
	delete axAdop;
}

void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro)
{
	TLSEAdopciones ax1 = lseAdopciones;
	TLSEData ax_data;
	int res_fecha;
	// step 1. Verificar que key( persona->ci, perro->id ) no exista.
	if( ax1->ctrl.cnt_reg )
	{ //comienza la busqueda
		int aux_cant_reg = ax1->ctrl.cnt_reg;
		ax_data = ax1->ctrl.primero;
		for ( ; aux_cant_reg ; aux_cant_reg-- )
		{
			if((ciTPersona(ax_data->prs)==ciTPersona(persona)) && (idTPerro(ax_data->per)==idTPerro(perro)))
				return;
			ax_data = ax_data->sig;
		}
	}
	//OK. no existe en la lista.

	// step 2. Insertar En la Lista ordenada de menor a mayor por fecha.
	//     Considerar el tema de la Fecha va despues de la ultima fecha igual 
	ax_data = ax1->ctrl.primero;
	while( ax_data != NULL ) // Busco posicion en la lista para insertar.
	{
		res_fecha = compararTFechas( fecha , ax_data->fechaAdop );
	}
	// Inserto en donde esta ax_data apuntando.
	    // Situaciones: ax_data es NULL , porque no hay nada en la lista o porque es el ultimo.
		// Si no es ultimo hay que insertar a partir de este.
	// primero si es ax_data == NULL 
	if( ax_data == NULL)
	{
		if( ax1->ctrl.primero == NULL ) // Lista vacia.
		{
			ax_data = new rep_lsedata;
			ax1->ctrl.primero = ax1->ctrl.ultimo = ax_data;
			ax1->ctrl.cnt_reg++;
			ax_data->prs = copiarTPersona(persona);
			ax_data->per = copiarTPerro(perro);

		}
	}
	else
	{ // Inserto apartir de esta posicion.

	}
}

bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro)
{
	return false;
}

void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro)
{

}

