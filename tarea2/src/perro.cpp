#include "../include/perro.h"

/* INFO del Modulo
Esta estructura debe contener :
.- un identificador de tipo entero,
.- un nombre de tipo texto,
.- una edad de tipo natural (nat),
.- un indicador de vitalidad de tipo natural,
.- una descripción de tipo texto
.- una fecha de ingreso de tipo TFecha.

Para el nombre utilizaremos un arreglo de caracteres (char) de tamaño 
  MAX_NOMBRE 
y para la descripción utilizaremos un arreglo de caracteres (char) de tamaño 
  MAX_DESCRIPCION.
*/



struct rep_perro
{
    /************ Parte 4.1 ************/
    int     id;
    char    nombre[MAX_NOMBRE];
    nat     edad;
    nat     id_vital;
    char    descr[MAX_DESCRIPCION];
    TFecha  fecha_ing;
};

TPerro crearTPerro( int id, const char nombre[MAX_NOMBRE], nat edad, nat vitalidad, const char descripcion[MAX_DESCRIPCION], TFecha fechaIngreso )
{
    TPerro perro = new rep_perro;

    perro->id = id;
    // me aseguro que los arrays terminen en cero
    perro->nombre[MAX_NOMBRE-1] = '\0';
    strcpy( perro->nombre, nombre);
    perro->edad = edad;
    perro->id_vital = vitalidad;
    perro->descr[MAX_DESCRIPCION-1] = '\0';
    strcpy(  perro->descr , descripcion);
    perro->fecha_ing = fechaIngreso;  // ojo aca: con los punteros y asignacion de memoria
    return perro; 
}

void liberarTPerro(TPerro &perro)
{
    // delete (rep_fecha) perro->fecha_ing;
    liberarTFecha( perro->fecha_ing);
    delete perro;
    perro = NULL;
}

int idTPerro(TPerro perro)
{
    return  perro->id;
}

char* nombreTPerro(TPerro perro)
{
    return perro->nombre; 
}

nat edadTPerro(TPerro perro)
{
    return perro->edad;
}

nat vitalidadTPerro(TPerro perro)
{
    return perro->id_vital;
}

char* descripcionTPerro(TPerro perro)
{
    return perro->descr;
}

TFecha fechaIngresoTPerro(TPerro perro)
{
    return perro->fecha_ing;
}

// Imprime la información del perro 'p' en el siguiente formato:
// Perro <id>
// Nombre: <nombre>
// Edad: <edad> 
// Descripcion: <descripcion>
// Fecha de ingreso: <fecha de ingreso>
// Vitalidad: <vitalidad>
void imprimirTPerro(TPerro perro)
{
   // TFecha aux_fech = perro->fecha_ing;

   printf( "Perro %d\nNombre: %s\nEdad: %d\nDescripcion: %s\nFecha de ingreso: ", 
    perro->id,
    perro->nombre,
    perro->edad,
    perro->descr);
    imprimirTFecha( perro->fecha_ing);
    printf("Vitalidad: %d\n",perro->id_vital);
}

TPerro copiarTPerro(TPerro perro)
{
    TPerro copy_perro = new rep_perro;

    copy_perro->id = perro->id ;
    strcpy( copy_perro->nombre , perro->nombre );
    copy_perro->edad = perro->edad;
    copy_perro->id_vital = perro->id_vital;
    strcpy( copy_perro->descr, perro->descr );
    copy_perro->fecha_ing = copiarTFecha( perro->fecha_ing );

    return copy_perro;
}

void actualizarEdadTPerro(TPerro &perro, nat nuevaEdad)
{
    perro->edad = nuevaEdad;
}

void actualizarVitalidadTPerro(TPerro &perro, nat nuevaVitalidad)
{
    perro->id_vital = nuevaVitalidad;
}
