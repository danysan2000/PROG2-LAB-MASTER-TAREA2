#include "../include/ldePerros.h"

struct rep_nodo_perros {   // Nodo de la lista DE.
	TPerro per;
	struct rep_nodo_perros *ant;  // nodo anterior.
	struct rep_nodo_perros *sig;  // nodo siguiente.

};


struct rep_tldeperros {    // cabezal de la lista DE.
	struct rep_nodo_perros *ini; // Inicio.
	struct rep_nodo_perros *fin; // Final.
	nat cant_nodos;        // cantindad de nodos en rep_Nodo_perros
};

TLDEPerros crearTLDEPerrosVacia()
{
	TLDEPerros ax1;  // auxiliar 
	ax1 = new struct rep_tldeperros;
	ax1->ini = NULL;
	ax1->fin = NULL;
	cant_nodos = 0;
   	return  ax1;
}

void insertarTLDEPerros(TLDEPerros &ldePerros, TPerro perro)
{
	TLDEPerros ax1, ax1_new, ax1_cab; // auxiliar
	nat ax_edad;    // auxiliar
	if ( ldePerros == NULl ) return ; // No se creo la ListaVacia.
    if ( existePerroTLDEPerros( ldePerros,  idTPerro(perro)) ) return ; // el perro ya existe.

	ax1_cab      = ldePerros;					// reg cabezal
	ax1_new      = new struct rep_nodo_perros;
	ax1_new->per = perro;
	ax1_cab->cant_nodos++;
	ax_edad      = edadTPerro(perro);

	ax1 = ax1_cab->prm; // primero
	while( ax1 != NULL &&  !( ax_edad < edadTPerro(ax1->per) )) // busco ubicacion.
			ax1 = ax1->sig;
	// insertar aca.
	if ( ax1 == NULL ) // insertar despues del ultimo
	{

	}
	else
	{
		ax1_new->ant = ax1->ant; // (1)
		ax1_new->sig = ax1; // (2)
		if( ax1->ant != NULL )
			ax1->ant->sig = ax1_new;
		else
		{
			ax1->ant     = ax1_new;
			ax1_cab->prm = ax1_new;
		}
	}
}

void liberarTLDEPerros(TLDEPerros &ldePerros)
{
	if ( ldePerros == NULl ) return ; // No se creo la ListaVacia.

}

void imprimirTLDEPerros(TLDEPerros ldePerros){

}

void imprimirInvertidoTLDEPerros(TLDEPerros ldePerros){

}

nat cantidadTLDEPerros(TLDEPerros ldePerros)
{
    return 0;
}

TPerro removerPerroTLDEPerros(TLDEPerros &ldePerros, int id){
    return NULL;
}

TPerro obtenerPrimeroTLDEPerros(TLDEPerros ldePerros){
    return NULL;
}

TPerro obtenerUltimoTLDEPerros(TLDEPerros ldePerros){
    return NULL;
}

TPerro obtenerNesimoTLDEPerros(TLDEPerros ldePerros, int n){
    return NULL;
}

bool existePerroTLDEPerros(TLDEPerros ldePerros, int id){
    return false;
}

