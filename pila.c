#define CAPACIDAD_INICIAL 20
#define FACTOR 2

#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>

// Función para uso interno
bool __pila_redimensionar(pila_t *pila, size_t capacidad_nueva);

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t *pila_crear(void){

    pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL) return NULL;
    
    pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }

    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = 0;
    
    return pila;
}

void pila_destruir(pila_t *pila){

    if(pila == NULL) return;

    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){

    if(pila == NULL) return false;

    return pila->cantidad == 0;
}

void *pila_ver_tope(const pila_t *pila){

    if(pila == NULL) return NULL;
    if(pila_esta_vacia(pila)) return NULL;

    return pila->datos[pila->cantidad - 1];
}

bool pila_apilar(pila_t *pila, void *valor){

    if(pila == NULL) return false;

    if(pila->cantidad == pila->capacidad){
        if(!__pila_redimensionar(pila, pila->capacidad * FACTOR)){
            return false;
        }
    }

    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;

    return true;
}

void *pila_desapilar(pila_t *pila){

    if(pila == NULL) return NULL;
    if(pila_esta_vacia(pila)) return NULL;

    void *tope = pila_ver_tope(pila);

    if(pila->cantidad <= pila->capacidad / (FACTOR*FACTOR) && CAPACIDAD_INICIAL <= pila->capacidad / FACTOR){
        __pila_redimensionar(pila, pila->capacidad / FACTOR);
    }

    pila->cantidad--;

    return tope;
}

bool __pila_redimensionar(pila_t *pila, size_t capacidad_nueva) {
    void **datos_nuevo = realloc(pila->datos, capacidad_nueva * sizeof(void*));

    // Cuando capacidad_nueva es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (capacidad_nueva > 0 && datos_nuevo == NULL) {
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = capacidad_nueva;

    return true;
}