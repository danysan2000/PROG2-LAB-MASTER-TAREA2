#include "../include/ldePerros.h"

typedef struct rep_nodo_perros *TLDEPerrosNodo;

struct rep_nodo_perros {   // Nodo de la lista DE.
	TPerro per;
	struct rep_nodo_perros *ant;  // nodo anterior.
	struct rep_nodo_perros *sig;  // nodo siguiente.
};


struct rep_tldeperros {    // cabezal de la lista DE.
	struct rep_nodo_perros *prm; // Inicio.
	struct rep_nodo_perros *ult; // Final.
	nat cant_nodos;        // cantindad de nodos en rep_Nodo_perros
};

TLDEPerros crearTLDEPerrosVacia()
{
	TLDEPerros ax1;  // auxiliar 
	ax1 = new struct rep_tldeperros;
	ax1->prm = NULL;
	ax1->ult = NULL;
	ax1->cant_nodos = 0;
   	return  ax1;
}

void insertarTLDEPerros(TLDEPerros &ldePerros, TPerro perro)
{
	// ldePerros nunca se cambia , no se toca.
	TLDEPerros  ax1_cab; // auxiliar
	TLDEPerrosNodo ax1_new, ax1;
	nat ax_edad;    // auxiliar
	if ( ldePerros == NULL ) return ; // No se creo la ListaVacia.
    if ( existePerroTLDEPerros( ldePerros,  idTPerro(perro)) ) return ; // el perro ya existe.

	ax1_cab      = ldePerros;					// reg cabezal

	ax1_new      = new struct rep_nodo_perros;
	ax1_new->per = perro;
	ax1_new->sig = NULL;
	ax1_new->ant = NULL;
	ax1_cab->cant_nodos++;
	ax_edad      = edadTPerro(perro);

	ax1 = ax1_cab->prm; // primero
	while( ax1 != NULL &&  !( ax_edad <= edadTPerro(ax1->per) )) // busco ubicacion.
			ax1 = ax1->sig;
	// insertar aca.
	if ( ax1 == NULL ) // insertar despues del ultimo o antes 
	{
		//analizando distintas situaciones.
		if ( ax1_cab->prm == NULL ) // la lista esta vacia
		{
			ax1_cab->prm = ax1_cab->ult = ax1_new;
		}
		else // es el ultimo inserto ? antes o despues ? -> despues
		{
			ax1_new->ant      = ax1_cab->ult;
			ax1_cab->ult->sig = ax1_new;
			ax1_cab->ult      = ax1_new;
		}
	}
	else
	{
		ax1_new->ant = ax1->ant; // (1)
		ax1_new->sig = ax1;      // (2)
		if( ax1->ant != NULL )
		{
			ax1->ant->sig = ax1_new;
			ax1->ant      = ax1_new;
		}
		else
		{
			ax1->ant     = ax1_new;
			ax1_cab->prm = ax1_new;
		}
	}
}

void liberarTLDEPerros(TLDEPerros &ldePerros)
{
	TLDEPerros ax1_cab = ldePerros;
	TLDEPerrosNodo ax1,ax2;
	if ( ldePerros == NULL ) return ; // No se creo la ListaVacia.
	if ( ax1_cab->cant_nodos )
	{	 
		ax1 = ax1_cab->prm;
		while ( ax1 != NULL )
		{
			liberarTPerro( ax1->per);
			ax2 = ax1->sig;
			delete ax1;
			ax1 = ax2;
		}
	}
	delete 	ax1_cab;
	ldePerros = NULL;
}

void imprimirTLDEPerros(TLDEPerros ldePerros)
{
	TLDEPerros ax1_cab = ldePerros;
	TLDEPerrosNodo ax1;
	printf("LDE Perros:\n");
	if ( ax1_cab == NULL ) return;
	ax1 = ax1_cab->prm;
	while( ax1 != NULL )
	{
		imprimirTPerro( ax1->per);
		ax1 = ax1->sig;
	}
}

void imprimirInvertidoTLDEPerros(TLDEPerros ldePerros)
{
	TLDEPerros ax1_cab = ldePerros;
	TLDEPerrosNodo ax1;
	printf("LDE Perros:\n");
	ax1 = ax1_cab->ult;
	while ( ax1 != NULL )
	{
		imprimirTPerro( ax1->per);
		ax1 = ax1->ant;
	}
}


nat cantidadTLDEPerros(TLDEPerros ldePerros)
{
    return ldePerros->cant_nodos;
}


static TLDEPerrosNodo recording_idPerro;

TPerro removerPerroTLDEPerros(TLDEPerros &ldePerros, int id)
{
	// Por las especificaciones de la letra:
	// no se debe borrar el objeto TPerro 
	// solo se desconecta el Nodo  de la lista y se libera la memoria del
	// espacio solo de la lista.
	//
	TLDEPerros ax1_cab = ldePerros;
	TLDEPerrosNodo ax1;
	TPerro retorno;
	int aux_cond;
	if ( !existePerroTLDEPerros( ldePerros,  id) ) return NULL ;
	// El id existe -- en recording_idPerro tengo el nodo a remover de la lista.
	//
	ax1 = recording_idPerro;
	// aux_cond valores 0,1,2,3 representando las 4 posibles situaciones de los punteros
	// ->sig y ->ant
	aux_cond =  ( ax1->sig == NULL ) * 1 + ( ax1->ant == NULL ) * 2 ;
	switch( aux_cond )
	{
		case 0:   // sig != NULL Y ant != NULL  <-- ni primero ni ultimo
			ax1->ant->sig = ax1->sig;  // [1]
			ax1->sig->ant = ax1->ant;  // [2]
			break;
		case 1:  // sig == NULL Y ant != NULL  <-- ultimo
			
			break;
		case 2:  // sig  != NULL Y ant == NULL  <-- primero

			break;
		case 3:  // sig == NULL Y ant == NULL   <-- solo un registro.
			ax1_cab->cant_nodos = 0;
			break;
	}
	retorno = ax1->per;
	delete ax1;
    return retorno;
}

TPerro obtenerPrimeroTLDEPerros(TLDEPerros ldePerros)
{
    return ldePerros->prm->per;
}

TPerro obtenerUltimoTLDEPerros(TLDEPerros ldePerros)
{
    return ldePerros->ult->per;
}

TPerro obtenerNesimoTLDEPerros(TLDEPerros ldePerros, int n)
{
	TLDEPerrosNodo ax1;
	int tope = n-1;
	ax1 = ldePerros->prm; // primero
	if( n < 0 || ( (nat) n > ldePerros->cant_nodos) ) return NULL;
	for( ; tope  ; tope--)
		ax1 = ax1->sig;
    return ax1->per;
}


bool existePerroTLDEPerros(TLDEPerros ldePerros, int id)
{
	TLDEPerros  ax1_cab;
	TLDEPerrosNodo ax1;
	ax1_cab = ldePerros;
	ax1 = ax1_cab->prm;
	while( ax1 != NULL && ( id != idTPerro(ax1->per) ) )
		ax1 = ax1->sig;
    return ( recording_idPerro = ax1);
}

