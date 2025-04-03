#include "../include/persona.h"

struct rep_persona {
    int ci;
    const char nombre[MAX_NOMBRE_PERSONA];
    const char apellido[MAX_APELLIDO_PERSONA];
    TFecha fechaNacimiento;
};

TPersona crearTPersona(int ci, const char nombre[MAX_NOMBRE_PERSONA], const char apellido[MAX_APELLIDO_PERSONA], nat diaNac, nat mesNac, nat anioNac){
    return NULL;
}

void imprimirTPersona(TPersona persona){

}

void liberarTPersona(TPersona &persona){

}

int ciTPersona(TPersona persona){
    return 0;
}

char* nombreTPersona(TPersona persona){
    return NULL;
}

char* apellidoTPersona(TPersona persona){
    return NULL;
}

TFecha fechaNacimientoTPersona(TPersona persona){
    return NULL;
}

void agregarPerroTPersona(TPersona &persona, TPerro perro){

}

bool pertenecePerroTPersona(TPersona persona, int idPerro){
    return false;
}

int cantidadPerrosTPersona(TPersona persona){
    return 0; 
}

TPersona copiarTPersona(TPersona persona){
    return NULL;
}
