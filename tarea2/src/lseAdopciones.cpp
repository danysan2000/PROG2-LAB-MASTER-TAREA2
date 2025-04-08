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
    TLSEAdopciones tlseadop = new rep_lseadopciones ;
	tlseadop->prs = NULL;
   	tlseadop->per = NULL;
   	tlseadop->fechaAdop = NULL ;
return tlseadop;
}


bool esVaciaTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	return lseAdopciones == NULL;
}

void imprimirTLSEAdopciones(TLSEAdopciones lseAdopciones)
{
	
	TLSEAdopciones aux1 = lseAdopciones ;
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
	TLSEAdopciones  axAdop = lseAdopciones, axAdop2;

	if ( axAdop == NULL ) return;

	// axData1 = axAdop->data;
	while( axAdop != NULL  )
	{
		liberarTFecha(axAdop->fechaAdop );
		liberarTPerro(axAdop->per);
		liberarTPersona(axAdop->prs);
		axAdop2 = axAdop->sig;
		delete axAdop;
		axAdop = axAdop2;
	}
}

#define CODIGO_PERSONA_PERRO (ciTPersona(ax_data->prs)==ciTPersona(persona)) && (idTPerro(ax_data->per)==idTPerro(perro))

void insertarTLSEAdopciones(TLSEAdopciones &lseAdopciones, TFecha fecha, TPersona persona, TPerro perro)
{
	TLSEAdopciones ax1 = lseAdopciones;
	TLSEAdopciones ax1_sel; // registro selecionado.
	int res_fecha; 		// resultado comparacion fechas
	int ctl; // control switch
						//
	// step 1. Verificar que key( persona->ci, perro->id ) no exista.
	if ( existeAdopcionTLSEAdopciones( ax1, ciTPersona(persona) , idTPerro(perro) ) ) 
	   return ; // existe.

	ctl = 0;
	while( ax1 != NULL ) //Busco donde insertar
	{

		switch( ctl )
		{
			case 1:
				res_fecha = compararTFechas( fecha , ax1->fechaAdop );
				if ( res_fecha == 0 ) { flg = 2; } // al final del conjunto fechas iguales ;
				if ( res_fecha < 0 ) { flg = 0; ax_data_sel = ax_data; } // insertar aca
				break;
			case 2: // fechas iguales.
				res_fecha = compararTFechas( fecha , ax_data->fechaAdop );
				if ( res_fecha != 0 )  // al final del conjunto fechas iguales ;
				break;
			case 0;

		}
			ax_data = ax_data->sig;
	}
		if (aux_data != NULL) return; // ya existe.
	

	// step 2. Insertar En la Lista ordenada de menor a mayor por fecha.
	//     Considerar el tema de la Fecha va despues de la ultima fecha igual 
		res_fecha = compararTFechas( fecha , ax_data->fechaAdop );
	// Inserto en donde esta ax_data apuntando.
	    // Situaciones: ax_data es NULL , porque no hay nada en la lista o porque es el ultimo.
		// Si no es ultimo hay que insertar a partir de este.
	// primero si es ax_data == NULL 
	{
			ax_data->prs = copiarTPersona(persona);
			ax_data->per = copiarTPerro(perro);
		// Inserto apartir de esta posicion.
		// Considerando la fecha si es igual

}

bool existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro)
{
	return false;
}

void removerAdopcionTLSEAdopciones(TLSEAdopciones &lseAdopciones, int ciPersona, int idPerro)
{
	TLSEAdopciones ax1;
	// check si existe.
	if ( !existeAdopcionTLSEAdopciones(TLSEAdopciones lseAdopciones, int ciPersona, int idPerro))
		return ; // no existe
	ax1 = lseAdopciones;

}

