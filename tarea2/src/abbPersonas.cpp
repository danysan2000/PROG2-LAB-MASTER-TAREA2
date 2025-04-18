/*
 * Temas interesentes:
 * 		*- control sobre la recursion en la funcion elimTABBP.
 * 		*- Uso de tabla de decision.+ switch. en reemplazo de los if elseif.
 *   No implemente la funcion general de control de grafo-tree.
*/
#include "../include/abbPersonas.h"


//static TABBPersonas CtlTree( TABBPersonas &abbPersonas ,  int fun );
// ? cabezal ? ( rep_abbPersonas )-->  NO SE PUEDE AGREGAR CABEZAL 
/* struct rep_abbPersonasNodo {
};
*/

struct rep_abbPersonas {
	int  key;		// KEY:ci de Persona(para no estar accediendo a persona cada vez que se usa)
	TPersona per;  // Dato 
	TABBPersonas  left, right; // control sobre grafo-tree.
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
	else
		insAbbPersona(key , dato, (key < t->key) ?  t->left : t->right);
/*
	else if ( key  < t->key)
		insAbbPersona(key , dato, t->left);
	else if ( key > t->key)
		insAbbPersona( key , dato, t->right);
*/
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
// funcion auxliar.

static void liberarTABB_postOrden (TABBPersonas &t)
{
	if (t == NULL) return;
	liberarTABB_postOrden(t->left);
	liberarTABB_postOrden(t->right);
	liberarTPersona( t->per );
	delete t;
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
		t = ( t->key > key ) ? t->left : t->right;
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
 Esto sirve si el AB no esta ordenado.
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

//………………………………… removerTP_TABBP ……………………………………………----------------
//………………………………………………………………………………

// maximin 
static TABBPersonas maximin( TABBPersonas t)
{
	if (t!=NULL)
		while( t->right!=NULL )
	   		t = t->right;
	return t;
}

// minimax
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
	return ( t == NULL ) ? 0 : ( 1+cantTABBP(t->left)+cantTABBP(t->right) );
	/*
	if (t == NULL)
	   	return 0;
	else
		return ( 1+cantTABBP(t->left)+cantTABBP(t->right) );
	*/
}

int cantidadTABBPersonas(TABBPersonas abbPersonas)
{
    return cantTABBP( abbPersonas );
}


//----- obtenerNesP_TABBP
//----- funcion auxilar.
	
static void enesTABBP_enOrden (TABBPersonas t , int n,int & cnt , TABBPersonas &rslt )
{
	if (t == NULL || rslt != NULL ) return;
	
	enesTABBP_enOrden(t->left, n , cnt , rslt );
	if (rslt != NULL ) return;
	// raiz en el esquema ( izq; raiz; der)
	cnt++;
	if (cnt==n)
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
	enesTABBP_enOrden ( abbPersonas, n, cnt, rslt );
	return rslt->per;
}


//--------- filtradoTABBP
//
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

