
#include "../include/abbPersonas.h"


//static TABBPersonas CtlTree( TABBPersonas &abbPersonas ,  int fun );

// ? cabezal ? ( rep_abbPersonas )-->  NO SE PUEDE AGREGAR CABEZAL 
/* struct rep_abbPersonasNodo {
};
*/

struct rep_abbPersonas {
	int  key; // KEY:ci de Persona(para no estar accediendo a persona cada vez que se usa)
	TPersona per;  // Dato 
	TABBPersonas  left, right;
};

TABBPersonas crearTABBPersonasVacio()
{
	// retorno Null 
    return NULL;
}

//---insertar Persona.
//
//----- funcion auxliar
static void insAbbPersona(int key, TPersona dato, TABBPersonas & t)
{
	if (t == NULL)
	{
		t = new rep_abbPersonas; 
		t->key = key;
		t->per = dato;
		t->left = t->right = NULL;
	}
	else if ( key  < t->key)
		insAbbPersona(key , dato, t->left);
	else if ( key > t->key)
		insAbbPersona( key , dato, t->right);
}


void insertarTPersonaTABBPersonas(TABBPersonas &abbPersonas, TPersona persona)
{
	int key;
	key = ciTPersona(persona);
	insAbbPersona( key , persona , abbPersonas );
}


//----- imprimirTABBPersonas ----
//---funcion auxliar.

static void imprimirTABB_PenOrden (TABBPersonas t)
{
	if (t != NULL)
	{
		imprimirTABB_PenOrden(t->left);
		  imprimirTPersona( t->per );
		imprimirTABB_PenOrden(t->right);
	}
}

void imprimirTABBPersonas(TABBPersonas abbPersonas)
{
	imprimirTABB_PenOrden( abbPersonas );
}


//--LiberarTABBPersonas--------
// static void liberarTABB_postOrden (TABBPersonas &t);
// funcion auxliar.

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

void liberarTABBPersonas(TABBPersonas &abbPersonas)
{
	// recorrer todo el arbol
	//if ( abbPersonas == NULL ) return;
	liberarTABB_postOrden ( abbPersonas);
	abbPersonas= NULL;
}

//----- existeTPersona

//----- funcion auxiliar.

static TABBPersonas buscarTABBPersonas(int key , TABBPersonas t)
{
	while( ( t != NULL) && (t->key != key) )
	{
		if (t->key > key)
			t = t->left;
		else
		   	t = t->right;
	}
	return t;
}

bool existeTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona)
{
    return ( buscarTABBPersonas(ciPersona, abbPersonas) );
}

// ---- obteerTPersonaTABBPersonas ---

TPersona obtenerTPersonaTABBPersonas(TABBPersonas abbPersonas, int ciPersona)
{
	TABBPersonas ax1; // auxiliar 
	TPersona res = NULL;
	
    if( (ax1=buscarTABBPersonas(ciPersona, abbPersonas)) )
		res = ax1->per;
    return res;
}

//--- alturaTABBP

static int max(int a, int b )
{
	return ( a > b ? a : b );
}

static nat alturaTABBP( TABBPersonas t )
{
	if (t == NULL)
	   	return 0;
	else
		return ( 1+max( alturaTABBP(t->left),alturaTABBP(t->right)) );
}


nat alturaTABBPersonas(TABBPersonas abbPersonas)
{
    return alturaTABBP( abbPersonas );
}

//------- maxCITPersona
/*
static TABBPersonas  MaxCIP(TABBPersonas & t)
{
	if (t->right==NULL)
	{
		TABBPersonas  max = t;
		t = t->left;
		return max;
	}
	else
	   	return MaxCIP(t->right);
}

*/
static TABBPersonas  MaxCIP(TABBPersonas  t)
{
	if (t==NULL)
	   	return NULL;
	else
	{
	   	TABBPersonas max = t; // inicializamos con la raíz
		TABBPersonas maxRec = MaxCIP(t->left);
		if (maxRec!=NULL && (maxRec->key > max->key) )
			max = maxRec; // se considera el max de t->izq
		maxRec = MaxCIP(t->right);
		if (maxRec!=NULL && ( maxRec->key > max->key) )
			max = maxRec; // se considera el max de t->der
		return max;
	}
}


TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas)
{
    return MaxCIP(abbPersonas)->per;
}

//---- removerTP_TABBP -----------------
//	……………… …  …

static TABBPersonas maximo( TABBPersonas t)
{
	if (t==NULL) return NULL;
	else
	{
		while(t->right!=NULL)
		{
			t = t->right;
		}
		return t;
	}
}


void elimTABBP(int clave,  TABBPersonas & t )
{
	if (t!=NULL)
	{
		if(clave < t->key)
			elimTABBP(clave, t->left );
		else if(clave > t->key)
			elimTABBP(clave, t->right);
		else
	   	{
		   	//  clave == t->key
			//liberarTPersona(t->per);
			if (t->right == NULL)
			{
				TABBPersonas aBorrar = t;
				t = t->left;
				//liberarTPersona(aBorrar->per);
				delete aBorrar;
			}
			else if (t->left == NULL)
			{
				TABBPersonas aBorrar = t;
				t = t->right;
				// liberarTPersona(aBorrar->per);
				delete aBorrar; 
			}
			else
		   	{
				TABBPersonas max_t_izq = maximo(t->left);
				t->key = max_t_izq->key;
				//liberarTPersona(t->per);
				t->per = max_t_izq->per;
				elimTABBP(t->key,t->left);
			}
		}
	}
}

/*
ABB minimo (ABB t)
{
	if (t==NULL) return NULL;
	else
	{
		while(t->left!=NULL)
		{
			t = t->left;
		}
		return t;
	}
}
*/

//---------****************----------------


// Función para encontrar el nodo con la clave máxima en un subárbol
/*
TABBPersonas  TABBPmax(TABBPersonas tmax)
{
    while (tmax->right != NULL)
        tmax = tmax->right;
    return tmax;
}
*/
//void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona)
//void elimABB (Ord clave, ABB & t)

/*
TABBPersonas  elimTABBP(TABBPersonas &t , int key)
{
    if(t == NULL) return t;

    // Búsqueda del nodo a eliminar
    if (key < t->key)
   	{
        t->left = elimTABBP(t->left, key);
    }
   	else if(key > t->key)
   	{
        t->right = elimTABBP(t->right, key);
    }
   	else
   	{
        // Caso 1: Nodo hoja o con un solo hijo
        if (t->left == NULL)
		{
            TABBPersonas taux = t->right;
            //free(t);
			liberarTPersona(t->per);
			delete t;
            return taux;
		}
	   	else if(t->right == NULL)
		{
            TABBPersonas  taux = t->left;
            //free(raiz);
			liberarTPersona( t->per);
			delete t;
            return taux;
        }
        // Caso 2: Nodo con dos hijos -> Reemplazar por el máximo del subárbol izquierdo
        // TABBPersonas  taux = TABBPmax(t->left);
        TABBPersonas  taux = maximo( t->left);  // MaxCIP(t->left);
        t->key = taux->key;  // Copio clave del predecesor.
		t->per = taux->per;   // Copio dato.
        t->left = elimTABBP(t->left, taux->key);  // Elimino  predecesor
    }
    return t;
}
*/
static void borrarNodoCorrectamente(int key, TABBPersonas &t)
{
    if (t == nullptr) return;

    if (key < t->key) {
        borrarNodoCorrectamente(key, t->left);
    } else if (key > t->key) {
        borrarNodoCorrectamente(key, t->right);
    } else {
        // Nodo encontrado
        if (t->left == nullptr) {
            // Caso sin hijo izquierdo (incluye hojas)
            TABBPersonas temp = t->right;
            delete t;
            t = temp;  // Actualiza la referencia correctamente
        } else if (t->right == nullptr) {
            // Caso sin hijo derecho
            TABBPersonas temp = t->left;
            delete t;
            t = temp;  // Actualiza la referencia
        } else {
            // Caso con dos hijos - Estrategia diferente
            // Encontrar predecesor inorder (máximo en subárbol izquierdo)
            TABBPersonas predecesor = t->left;
            while (predecesor->right != nullptr) {
                predecesor = predecesor->right;
            }
            
            // Copiar solo los datos
            t->key = predecesor->key;
            t->per = predecesor->per;
            
            // Borrar el predecesor recursivamente
            borrarNodoCorrectamente(predecesor->key, t->left);
        }
    }
}

void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona)
{
	// elimTABBP( ciPersona , abbPersonas );
	// borrarNodo( ciPersona , abbPersonas );
	// borrarNodoCompleto( ciPersona , abbPersonas );
	borrarNodoCorrectamente( ciPersona , abbPersonas );
}

//----------CantidadTABBP

static int cantTABBP( TABBPersonas t )
{
	if (t == NULL)
	   	return 0;
	else
		return ( 1+cantTABBP(t->left)+cantTABBP(t->right) );
}

int cantidadTABBPersonas(TABBPersonas abbPersonas)
{
    return cantTABBP( abbPersonas );
}

//----- obtenerNesP_TABBP

TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n)
{
//	TPersona res;
//     return res;
	return NULL;
}

//--------- filtradoTABBP

TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio)
{
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

// COPIA
AB copia (AB t){
if (t == NULL) return NULL;
else
{ AB rt = new NodoAB;
rt -> item = t -> item;
rt -> left = copia (t -> left);
rt -> right = copia (t -> right);
return rt;
}
}

PRE: t no tiene elementos repetidos
AB maximo(AB t){
if (t==NULL) return NULL;
else{ AB max = t; // inicializamos con la raíz
AB maxRec = maximo(t->izq);
if (maxRec!=NULL && maxRec->dato > max->dato)
max = maxRec; // se considera el max de t->izq
maxRec = maximo(t->der);
if (maxRec!=NULL && maxRec->dato > max->dato)
max = maxRec; // se considera el max de t->der
return max;
}
}


*/

