
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
	while( (t != NULL) && (t->key != key) )
	{
		t = ( t->key > key ) ? t->left : t->right;
		/*
		if (t->key > key)
			t = t->left;
		else
		   	t = t->right;
		*/
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

static TABBPersonas  MaxCIP(TABBPersonas  t)
{
	while ( t->right!=NULL)
	   	t = t->right;
	return t;
}

/*
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
*/

TPersona maxCITPersonaTABBPersonas(TABBPersonas abbPersonas)
{
    return MaxCIP(abbPersonas)->per;
}

//---- removerTP_TABBP -----------------
//	……………… …  …

// maximin 
static TABBPersonas maximin( TABBPersonas t)
{
	if (t!=NULL)
		while( t->right!=NULL )
	   		t = t->right;
	return t;
}


static TABBPersonas minimax ( TABBPersonas t)
{
	if (t!=NULL)
		while( t->left != NULL )
			t = t->left;
	return t;
}

void elimTABBP(int clave,  TABBPersonas & t , int status)
{
	if (t==NULL)
		return ;

	if(clave < t->key)
		elimTABBP(clave, t->left, status );
	else if(clave > t->key)
		elimTABBP(clave, t->right, status);
	else
	{
		// ****  clave == t->key **** lo encontro !!!
		TABBPersonas  taux=NULL;
		int cond_op; // variable de condicion de operacion.
		cond_op = ( t->left == NULL ) * 2 + ( t->right == NULL ) * 1 ;
		switch( cond_op)
		{
			case 0:		// 2 nodos ocupados
				//break; misma situacion en 0 y 1
			case 1:		// nodo izq.
				taux   = maximin( t->left);
				liberarTPersona( t->per);
				t->key = taux->key;
				t->per = taux->per;
				elimTABBP(t->key, t->left, 0);
				break;
			case 2:		// nodo der.
				taux = minimax( t->right);
				liberarTPersona(t->per);
				t->key = taux->key;
				t->per = taux->per;
				elimTABBP(t->key, t->right,0);
				break;
			case 3:		// Hoja.
				if( status ) // Importante variable status para diferenciar si estoy buscando la clave o
							 // estoy buscando el maximin o minimax.
					liberarTPersona( t->per);
				delete t;
				t = NULL;
				break;
		}
	}
}

void removerTPersonaTABBPersonas(TABBPersonas &abbPersonas, int ciPersona)
{
	elimTABBP( ciPersona , abbPersonas, 1 );
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

	
static void enesTABBP_enOrden (TABBPersonas t , int n,int & cnt , TABBPersonas &rslt )
{
	if (t == NULL || rslt != NULL ) return;
	
	enesTABBP_enOrden(t->left, n , cnt , rslt );
	if (rslt != NULL ) return;
	
	cnt++;
	if ( cnt == n )
	{
		rslt = t;
		return ;
	}
	enesTABBP_enOrden(t->right, n , cnt , rslt );
}


TPersona obtenerNesimaPersonaTABBPersonas(TABBPersonas abbPersonas, int n)
{
	TABBPersonas rslt = NULL;
	int cnt = 0;
	enesTABBP_enOrden ( abbPersonas ,  n, cnt ,   rslt );
	return rslt->per;
}

//--------- filtradoTABBP
static void filtrado_TABBP( TABBPersonas t, TABBPersonas &tnew,  TFecha fecha, int crit)
{
	char select, cmp_fech;
	if ( t == NULL ) return;
	// filtrado en posOrder.
	filtrado_TABBP( t->left , tnew, fecha, crit );
	filtrado_TABBP( t->right, tnew, fecha, crit );
	// chequeo de condiciones de Fecha.
	// select bool
	cmp_fech = compararTFechas( fechaNacimientoTPersona( t->per) , fecha );
	select  =( (crit < 0  ) &&  (cmp_fech   <  0) ) ||
   			 ( (crit == 0 ) && ( cmp_fech   == 0) ) ||
   			 ( (crit > 0  ) && ( cmp_fech   >  0) );

	// insertar
	if( select )
		//insAbbPersona(int key, TPersona dato, TABBPersonas & tnew)
		insAbbPersona(t->key, copiarTPersona(t->per ), tnew);
}

TABBPersonas filtradoPorFechaDeNacimientoTABBPersonas(TABBPersonas abbPersonas, TFecha fecha, int criterio)
{
	// para esta funcion tengo que recorerlo completo el arbol ya que 
	// la fecha es el criterio de seleccion y el arbol no esta ordenado por fecha .
	TABBPersonas tnew;
	tnew = crearTABBPersonasVacio();
	filtrado_TABBP( abbPersonas,  tnew,  fecha, criterio);
    return tnew;
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

void elimABB (Ord clave, ABB & t)
{
if (t!=NULL)
{
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

