
#include "../include/abbPersonas.h"


//static TABBPersonas CtlTree( TABBPersonas &abbPersonas ,  int fun );

// ? cabezal ? ( rep_abbPersonas ) 
//
// NO SE PUEDE AGREGAR CABEZAL 

/* struct rep_abbPersonasNodo {

};
*/

struct rep_abbPersonas {
	int  key;        // KEY: ci de Persona(para no tener que estar accediendo a persona cada vez que se usa)
	TPersona per;  // Dato 
	TABBPersonas  left, right;
};

TABBPersonas crearTABBPersonasVacio()
{
	// retorno Null 
    return NULL;
}

// Prototype
static void insABB (int key, TPersona dato, TABBPersonas &t);

void insertarTPersonaTABBPersonas(TABBPersonas &abbPersonas, TPersona persona)
{
	int key;
	key = ciTPersona(persona);
	insABB( key , persona , abbPersonas );
}

static void insABB (int key, TPersona dato, TABBPersonas & t)
{
	if (t == NULL)
	{
		t = new rep_abbPersonas; 
		t->key = key;
		t->per = dato;
		t->left = t->right = NULL;
	}
	else if ( key  < t->key)
		insABB (key , dato, t->left);
	else if ( key > t->key)
		insABB ( key , dato, t->right);
}

void imprimirTABBPersonas(TABBPersonas abbPersonas)
{

}

static void liberarTABB_postOrden (TABBPersonas &t);

void liberarTABBPersonas(TABBPersonas &abbPersonas)
{
	// recorrer todo el arbol
	liberarTABB_postOrden ( abbPersonas);
}

static void liberarTABB_postOrden (TABBPersonas &t)
{
	if (t != NULL)
	{
		liberarTABB_postOrden(t->left);
		liberarTABB_postOrden(t->right);
		// P(t->item);
		liberarTPersona( t->per );
		delete t;
	}
}

bool existeTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona)
{
    return false;
}

TPersona obtenerTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona){
    return NULL;
}

nat alturaTABBPersonas(TABBPersonas abbPersonas){
    return 0;
}

TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas){
    return NULL;
}

void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona){

}

int cantidadTABBPersonas(TABBPersonas abbPersonas){
    return 0;
}

TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n){
    return NULL;
}

TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio){
    return NULL;
}

//----------------------------------------------------------------------
//Funciones staticas auxiliares.
// Idea es  centralizar el manejo del Tree en una funcion.
//----------------------------------------------------------------------

// CtlTree:
//  Retorna status
//  fun: 
/*
static int CtlTree( TABBPersonas &abbPersonas ,  int fun )
{
	TABBPersonas ax1 = abbPersonas;
	int status;
	return status
}
*/
//- Copiando codigo.

/*
Typedef NodoAB * AB;
struct NodoAB{
T item;
AB left, right;
}

// 
void preOrden (AB t){
if (t != NULL){
P(t -> item);
preOrden(t -> left);
preOrden(t -> right);
}
}

void enOrden (AB t){
if (t != NULL){
enOrden(t -> left);
P(t -> item);
enOrden(t -> right);
}
}

void postOrden (AB t){
if (t != NULL){
postOrden(t -> left);
postOrden(t -> right);
P(t -> item);
}
}

// Cantidad de Nodos.
cantNodos (()) = 0
cantNodos ((izq,a,der)) =
1 + cantNodos(izq) + cantNodos(der)
int cantNodos (AB t){
if (t == NULL) return 0;
else
return 1 + cantNodos(t -> left)
+ cantNodos(t -> right);
}

// *
Espejo
espejo (()) = ()
espejo ((izq,a,der)) =
(espejo(der),a,espejo(izq))
// 
AB espejo (AB t){
if (t == NULL) return NULL;
else
{ AB rt = new NodoAB;
rt -> item = t -> item;
rt -> left = espejo (t -> right);
rt -> right = espejo (t -> left);
return rt;
}
}


Hojas de un árbol
hojas (()) = []
hojas (((),a,())) = [a] hojas
hojas ((izq,a,der)) =
hojas(izq) ++ hojas(der),
Si izq() o der()
// 

Lista hojas (AB t){
Lista p;
if (t == NULL) return NULL;
else
if ((t -> left == NULL)
&& (t -> right == NULL))
{ p = new nodoLista;
p -> info = t -> item;
p -> sig = NULL;
return p;
}
else return Concat(hojas(t -> left),
hojas(t -> right));
} // Nota: Concat es aquí una función (no un proced.
  //

Arbol binario de búsqueda (ABB)
// ojo con el desbalanceo.

typedef NodoABB* ABB;
struct NodoABB {
Ord key;
T info;
ABB left, right;
}

// Buscar iterativo

ABB buscarIterativo(Ord x, ABB t){
while ((t != NULL) && (t -> key != x)){
if (t -> key > x)
t = t -> left;
else t = t -> right;
}
return t;
}


// Buscar recursivo
//
ABB buscarRecursivo(Ord x, ABB t){
ABB res;
if (t == NULL)
res = NULL;
else
if (x == t -> key)
res = t;
else
if (x < t -> key)
res = buscarRecursivo (x,t -> left);
else
res = buscarRecursivo (x,t -> right);
return res;
}


// La función Miembro
bool miembro (Ord x, ABB t){
if (t == NULL) return false;
else
if (x == t -> key)
return true;
else
return (miembro(x,t -> left)
|| miembro(x,t -> right));
}

// ¿Es eficiente la función miembro?
// ¿Podría optimizarse?


// Siempre se agrega (eventualmente) un elemento como
//una hoja?
// void insABB (Ord clave, T dato, ABB & t)

// Inserción en un ABB
void insABB (Ord clave, T dato, ABB & t)
{
	if (t == NULL)
	{
		t = new NodoABB ;
		t->key = clave;
		t->info = dato;
		t->left = t->right = NULL;
	}
	else if (clave < t->key)
		insABB (clave, dato, t->left);
	else if (clave > t->key)
		insABB (clave, dato, t->right);
}


//Eliminación en un ABB
//

void elimABB (Ord clave, ABB & t){
if (t!=NULL){
if (clave < t->key)
elimABB(…);
else if (clave > t->key)
elimABB(…);
else { \\ clave == t->key
if (t->right == NULL){
ABB aBorrar = t;
t = t->left;
delete aBorrar;
}
else if (t->left == NULL){
…
}
else {
ABB min_t_der = minimo(t->right);
t->key = …
t->info = …
elimABB(t->key,t->right);
}
}
}
}

\\ retorna un puntero al nodo con el mínimo de t; NULL si es vacío.
ABB minimo (ABB t){
if (t==NULL) return NULL;
else{
while(t->left!=NULL){
t = t->left;
}
return t;
}
}

//Compare esta versión de aplanar con la que se obtiene usando la
//concatenación de listas.

// Ejercicio: Aplanar eficientemente un ABB
//
Lista aplanar (ABB t)
{
	Lista l = NULL;
	aplanarEnLista (t, l);
	return l;
}

void aplanarEnLista (ABB t, Lista & l)
{
	if ( t!= NULL)
	{
		aplanarEnLista(t->right,l);
		insComienzo(t->dato,l);
		aplanarEnLista(t->left,l);
	}
}

*/

