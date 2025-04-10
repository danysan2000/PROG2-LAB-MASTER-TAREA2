#include "../include/lseAdopciones.h"



struct rep_lseadopciones 
{
    TPersona		prs;			// Persona
    TPerro			per;			// Perro
    TFecha			fechaAdop;		// Fecha de Adoption
	TLSEAdopciones	sig;							// 
};


TLSEAdopciones crearTLSEAdopcionesVacia()
{
	/*
    TLSEAdopciones tlseadop = new rep_lseadopciones ;
	tlseadop->prs = NULL;
   	tlseadop->per = NULL;
   	tlseadop->fechaAdop = NULL ;
	tlseadop->sig = NULL;
	*/
return NULL;
}


bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	return lseAdopciones == NULL;
}

void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	
	TLSEAdopciones ax1 = lseAdopciones ;
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
		ax1 = ax1->sig;
	}
}

void liberarTLSEAdopciones(TLSEAdopciones &lseAdopciones)
{
	#define axAdop lseAdopciones
	TLSEAdopciones axAdop2;
	while( axAdop  != NULL  )
	{
		liberarTFecha(axAdop->fechaAdop );
		liberarTPerro(axAdop->per);
		liberarTPersona(axAdop->prs);
		axAdop2 = axAdop->sig;
		delete axAdop;
		axAdop = axAdop2;
	}
}


void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro)
{
	TLSEAdopciones ax1 = lseAdopciones;
	TLSEAdopciones ax1_sel, ax1_new; // registro selecionado.
	int res_fecha; 		// resultado comparacion fechas
						
	// step 1. Verificar que key( persona->ci, perro->id ) no exista.
	if ( existeAdopcionTLSEAdopciones( ax1, ciTPersona(persona) , idTPerro(perro) ) ) 
	   return ; // existe.

	// step 2. Insertar En la Lista ordenada de menor a mayor por fecha.
	//     Considerar el tema de la Fecha igual  va despues de la ultima fecha igual 
	ax1_sel = ax1; // el primero seleccionado.
	while( ax1 != NULL ) //Busco donde insertar
	{
		res_fecha = compararTFechas( fecha , ax1->fechaAdop );
		// ax1_sel = ax1;
		if( res_fecha < 0 )
			ax1 = NULL;
		else
		{
			ax1_sel = ax1; // conservo este como anterior para poder insertar.
			ax1 = ax1->sig;	
		}
	}
	// Inserto en donde esta ax1_sel apuntando.
	ax1_new = new rep_lseadopciones ;
	ax1_new->prs = persona ;		// copiarTPersona(persona);
	ax1_new->per = perro ; 			// copiarTPerro(perro);
	ax1_new->fechaAdop = fecha ;	// copiarTFecha( fecha );

	// ojo aca.
	// TENGO QUE DETECTAR CUANDO ES EL PRIMERO.
	if( ax1_sel == NULL )
	{
		lseAdopciones = ax1_sel = ax1_new;
		ax1_new->sig = NULL;
	}
	else
	{
		ax1_new->sig = ax1_sel->sig;
		ax1_sel->sig = ax1_new;
	}
}


#define CODIGO_PERSONA_PERRO(ptr,a,b)  ( (ciTPersona(ptr->prs)== a ) && (idTPerro(ptr->per)==b) )

bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro)
{
	TLSEAdopciones ax1 = lseAdopciones ; // auxiliar
	
	while( ax1 != NULL && !CODIGO_PERSONA_PERRO(ax1,ciPersona, idPerro) )
	   	ax1 = ax1->sig;
	return (ax1 != NULL ); // verdadero existe
}

void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro)
{
	TLSEAdopciones ax1= lseAdopciones, ax1_ant;
	ax1_ant = ax1;
	while( ax1 != NULL && !CODIGO_PERSONA_PERRO(ax1,ciPersona, idPerro) )
	{
		ax1_ant = ax1;
		ax1 = ax1->sig;
	}
	// ajusto punteros.
	if( ax1_ant == ax1 )
		lseAdopciones = ax1->sig;
	else
		ax1_ant->sig = ax1->sig;
	// remuevo ax1
		liberarTFecha(ax1->fechaAdop );
		liberarTPerro(ax1->per);
		liberarTPersona(ax1->prs);
		delete ax1;
	return ;
}

//--------------------------------------------------------------------------------
//Funciones auxiliares. probable no la use.

// prototypes 
/*
static void insComienzo(A e, Lista & l);
static void insOrd(A e, Lista & l);

// static void insComienzo(A e, Lista & l)
static void insComienzo(A e, Lista & l)
{
	Lista nuevo = new nodoLista;
	nuevo->info = e;
	nuevo->sig = l;
	l=nuevo;
}


static void insOrd(A e, Lista & l)
{
	if (l == NULL)
	   	insComienzo(e, l);
	else
	{
	if (e <= l->info)
	   	insComienzo(e, l);
	else
	   	insOrd(e, l->sig);
	}
}

*/
