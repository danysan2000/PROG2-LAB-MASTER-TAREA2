#include "../include/persona.h"

struct rep_persona
{
    int ci;
    char nombre[MAX_NOMBRE_PERSONA];
    char apellido[MAX_APELLIDO_PERSONA];
    TFecha fechaNacimiento;
    //* Perros adoptados arreglo con tope
    struct {
        TPerro perros[MAX_PERROS_PERSONA];
        int tope;
    } perrosAdoptados;
    // lo pongo por las dudas.
    // TPersona sig;
    // TPersona ant; 
};

TPersona crearTPersona(int ci, const char nombre[MAX_NOMBRE_PERSONA], const char apellido[MAX_APELLIDO_PERSONA], nat diaNac, nat mesNac, nat anioNac)
{
    TPersona nueva_Persona = new rep_persona;
    nueva_Persona->ci = ci;
    strncpy( nueva_Persona->nombre, nombre, MAX_NOMBRE_PERSONA);
    strncpy( nueva_Persona->apellido, apellido, MAX_APELLIDO_PERSONA);
    nueva_Persona->fechaNacimiento = crearTFecha( diaNac, mesNac, anioNac );
    nueva_Persona->perrosAdoptados.tope = 0;
return nueva_Persona;
}

void imprimirTPersona(TPersona persona)
{
	int aux;
	printf("Persona %s %s\nCI: %d\n", persona->nombre, persona->apellido, persona->ci );
	printf("Fecha de Nacimiento: "); imprimirTFecha( persona->fechaNacimiento);
	printf("Perros adoptados:\n");
	for( aux=0 ; aux < persona->perrosAdoptados.tope; aux++)
		imprimirTPerro( persona->perrosAdoptados.perros[aux]);
}

void liberarTPersona(TPersona &persona)
{
    TPersona p; 
	int  ax2;  // auxliar loops
	p = persona; // auxliar 
	// libero TFecha
	liberarTFecha( p->fechaNacimiento );
	// libero TPerros. O(n)
	ax2 = p->perrosAdoptados.tope ;
	for( ; ax2 ; ax2--)
		liberarTPerro( p->perrosAdoptados.perros[ax2-1] );
	//
	delete p;
    persona = NULL;
}

int ciTPersona(TPersona persona)
{
	return persona->ci;
}

char* nombreTPersona(TPersona persona)
{
	return persona->nombre;
}

char* apellidoTPersona(TPersona persona)
{
	return persona->apellido;
}

TFecha fechaNacimientoTPersona(TPersona persona)
{
	return persona->fechaNacimiento;
}

void agregarPerroTPersona(TPersona &persona, TPerro perro)
{
    TPerro per;
	int *aux_tope;
	aux_tope = &persona->perrosAdoptados.tope ;
	if ( *aux_tope == MAX_PERROS_PERSONA ) return;
	per = copiarTPerro( perro );
	persona->perrosAdoptados.perros[*aux_tope] = per;
	(*aux_tope)++;
}

bool pertenecePerroTPersona(TPersona persona, int idPerro)
{
	int aux1;
	aux1 = persona->perrosAdoptados.tope;
   	while( 	aux1 &&  idTPerro ( persona->perrosAdoptados.perros[aux1-1]) != idPerro ) aux1--;
    return aux1; // evalua por el valor logico de la expresion.
}

int cantidadPerrosTPersona(TPersona persona)
{
    return persona->perrosAdoptados.tope;
}

TPersona copiarTPersona(TPersona persona)
{
	TPersona p;
    int aux1;
	p = new rep_persona;
	*p = *persona;
    p->fechaNacimiento = copiarTFecha( persona->fechaNacimiento );
    aux1 = persona->perrosAdoptados.tope;
    for ( ; aux1 ; aux1--)
        p->perrosAdoptados.perros[aux1-1] = copiarTPerro( persona->perrosAdoptados.perros[aux1-1] );
return p;
}
