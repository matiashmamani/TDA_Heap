#define VOLUMEN 10000

#include "heap.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intcmp(const void *a, const void *b){

    if(*(int*)a > *(int*)b) return 1;

    if(*(int*)a < *(int*)b) return -1;

    // *a == *b
    return 0;
}

static void prueba_heap_vacia(void) {

    printf("1. INICIO DE PRUEBAS CON HEAP VACIO\n");
    heap_t *heap = heap_crear(intcmp);
    print_test("- Crear heap vacío", heap);
    print_test("- Heap esta vacío", heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", !heap_cantidad(heap));
    print_test("- Ver máximo del heap vacio devuelve NULL", !heap_ver_max(heap));
    print_test("- Desencolar en heap vacio devuelve NULL", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
    print_test("- Destruir heap vacío", true);
}

static void prueba_heap_elementos_estaticos(void) {

    int vec_int[] = {3, -5, -3, 2, 8, 1, 10, -9, 0, 2};
    int n_int = 10;
    int *p_int;
    
    printf("3. INICIO DE PRUEBAS CON HEAP DE ELEMENTOS ESTATICOS\n");
    heap_t *heap = heap_crear(intcmp);
    print_test("- Crear heap", heap);

    bool ok = true;
    bool ok_ver_max = true;
    int max = 0;
    for(int i = 0; i < n_int; i++){
        ok &= heap_encolar(heap, &vec_int[i]);
        if(vec_int[i] > max) max = vec_int[i];
        p_int = heap_ver_max(heap);
        ok_ver_max &= (*p_int == max);
    }

    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento del heap es el máximo en cada encolado", ok_ver_max);
    print_test("- Heap no esta vacío", !heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", heap_cantidad(heap) == n_int);

    ok = true;
    for(int i = 0; i < n_int; i++){
        p_int = heap_ver_max(heap);
        ok &= (p_int == heap_desencolar(heap));
    }

    print_test("- Se pudieron desencolar todos los elementos y mantienen invariante de heap", ok);
    print_test("- Heap quedó vacío después de desencolar todo", heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", !heap_cantidad(heap));
    print_test("- Ver máximo de heap devuelve NULL después de desencolar todo", !heap_ver_max(heap));
    print_test("- Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));
    
    for(int i = 0; i < n_int; i++){
        heap_encolar(heap, &vec_int[i]);
    }

    print_test("- Heap se llenó de vuelta", !heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("- Destruir heap (con NULL)", true);
}

static void prueba_heap_elementos_dinamicos(void){

    int **vec_int;
    size_t n_int  = 3;
    int *p_int;

    vec_int = malloc(n_int * sizeof(int*));
    for(int i = 0; i < n_int; i++){
        vec_int[i] = malloc(sizeof(int));
        *(vec_int[i]) = i;
    }

    printf("4. INICIO DE PRUEBAS CON HEAP DE ELEMENTOS DINAMICOS\n");
    heap_t *heap = heap_crear_arr((void**)vec_int, n_int, intcmp);
    print_test("- Crear heap", heap);
    print_test("- Heap no esta vacío", !heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", heap_cantidad(heap) == n_int);
    p_int = heap_ver_max(heap);
    print_test("- El primer elemento del heap es el máximo", *p_int == 2);
    heap_destruir(heap, free);
    print_test("- Destruir heap (con free())", true);
    free(vec_int);
}

static void prueba_heap_volumen(void) {

    printf("7. INICIO DE PRUEBAS DE VOLUMEN\n");
    heap_t *heap = heap_crear(intcmp);
    print_test("- Crear heap", heap);
    
    bool ok = true;
    bool ok_ver_max = true;
    int *p_int;
    int vec_int[VOLUMEN];
    int max = 0;
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        ok &= heap_encolar(heap, &vec_int[i]);
        if(vec_int[i] > max) max = vec_int[i];
        p_int = heap_ver_max(heap);
        ok_ver_max &= (*p_int == max);
    } 
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento del heap es correcto en cada encolado", ok_ver_max);
    print_test("- Heap no esta vacío", !heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", heap_cantidad(heap) == VOLUMEN);

    ok = true;
    p_int = NULL;
    for(int i = 0; i < VOLUMEN; i++){
        p_int = heap_ver_max(heap);
        ok &= (p_int == heap_desencolar(heap));
    }
    print_test("- Se pudieron desencolar todos los elementos y se mantiene el invariante de heap", ok);
    print_test("- Heap quedó vacío después de desencolar todo", heap_esta_vacio(heap));
    print_test("- Ver máximo del heap devuelve NULL después de desencolar todo", !heap_ver_max(heap));
    print_test("- Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));
    
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        heap_encolar(heap, &vec_int[i]);
    }
    print_test("- Heap se llenó de vuelta", !heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("- Destruir heap", true);
}


static void prueba_heap_sort(void) {

    int vec_desord[] = {3, -5, -3, 2, 8, 1, 10, -9, 0, 2};
    int vec_ord[] = {-9, -5, -3, 0, 1, 2, 2, 3, 8, 10};
    int **vec_int;
    size_t n_int = 10;

    vec_int = malloc(n_int * sizeof(int*));
    for(size_t i = 0; i < n_int; i++){
        vec_int[i] = malloc(sizeof(int));
        *(vec_int[i]) = vec_desord[i];
    }

    printf("8. INICIO DE PRUEBAS HEAP SORT\n");
    print_test("- Vector dinámico creado. Todos los elementos están desordenados", true);
    
    heap_sort((void**)vec_int, n_int, intcmp);

    bool ok = true;
    for(int i = 0; i < n_int; i++){
        ok &= (*(vec_int[i]) == vec_ord[i]);
    }
    print_test("- Los elementos quedaron perfectamente ordenados luego de aplicar heapsort", ok);
        
    for(size_t i = 0; i < n_int; i++){
        free(vec_int[i]);
    }
    free(vec_int);
    print_test("- Vector dinámico destruido", true);
}

int nullcmp(const void *a, const void *b){
    return 0;
}

static void prueba_heap_valor_null(void) {

    void **vec_null;
    int n_null = 4;

    // Creo vector de NULLs
    vec_null = malloc((size_t)n_null * sizeof(void*));
    for(int i = 0; i < n_null; i++){
        vec_null[i] = NULL;
    }
 
    printf("2. INICIO DE PRUEBAS CON VALOR NULL\n");
    heap_t *heap = heap_crear(nullcmp);
    print_test("- Crear heap", heap);

    bool ok = true;
    bool ok_ver_max = true;
    void **p_null;
    for(int i = 0; i < n_null; i++){
        ok &= heap_encolar(heap, &vec_null[i]);
        p_null = heap_ver_max(heap);
        ok_ver_max &= (*p_null == NULL);
    }
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- Ver max es NULL en cada encolada", ok_ver_max);
    print_test("- heap no esta vacío", !heap_esta_vacio(heap));

    ok = true;
    p_null = NULL;
    for(int i = n_null - 1; i >= 0; i--){
        p_null = heap_desencolar(heap);
        ok &= (*p_null == vec_null[i]);
    }
    print_test("- Se pudieron desencolar todos los elementos", ok);
    print_test("- heap quedó vacío después de desencolar todo", heap_esta_vacio(heap));
    print_test("- Ver max de heap devuelve NULL después de desencolar todo", !heap_ver_max(heap));
    print_test("- Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
    
    // Destruyo vector de NULLs
    free(vec_null);
}

void pila_destruir_wrapper(void *pila){
    pila_destruir((pila_t*)pila);
}

static void prueba_heap_funcion_destruir(void){

    printf("6. INICIO DE PRUEBAS CON FUNCION DESTRUIR (PILA_DESTRUIR)\n");
    heap_t* heap = heap_crear(nullcmp);
    size_t largo = 10;
    pila_t *pila = NULL;

    /* Inserta 'largo' parejas en el heap */
    bool ok = true;
    for(unsigned i = 0; i < largo; i++) {
        pila = pila_crear();
        ok = heap_encolar(heap, pila);
        if(!ok) break;
    }

    print_test("- Se pudieron almacenar varias pilas", ok);
    print_test("- La cantidad de pilas almacenadas es correcta", heap_cantidad(heap) == largo);
    print_test("- Destruir con funcion de destruccion pila_destruir", true);

    /* Destruye el heap con funcion pila_destruir */
    heap_destruir(heap, pila_destruir_wrapper);
}

static void prueba_heap_crear_arr(void) {

    int **vec_int;
    size_t n_int  = 3;
    int *p_int;

    vec_int = malloc(n_int * sizeof(int*));
    for(int i = 0; i < n_int; i++){
        vec_int[i] = malloc(sizeof(int));
        *(vec_int[i]) = i;
    }

    printf("5. INICIO DE PRUEBAS CON HEAP CREADO DESDE ARREGLO\n");
    heap_t *heap = heap_crear_arr((void**)vec_int, n_int, intcmp);
    print_test("- Crear heap desde arreglo", heap);
    print_test("- Heap no esta vacío", !heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", heap_cantidad(heap) == n_int);

    bool ok = true;
    for(int i = 0; i < n_int; i++){
        p_int = heap_ver_max(heap);
        ok &= (p_int == heap_desencolar(heap));
        free(p_int);
    }

    print_test("- Se pudieron desencolar todos los elementos y mantienen invariante de heap", ok);
    print_test("- Heap quedó vacío después de desencolar todo", heap_esta_vacio(heap));
    print_test("- La cantidad de elementos del heap es correcta", !heap_cantidad(heap));
    print_test("- Ver máximo de heap devuelve NULL después de desencolar todo", !heap_ver_max(heap));
    print_test("- Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));
    heap_destruir(heap, free);
    print_test("- Destruir heap (con free)", true);
    free(vec_int);
}

void pruebas_heap_estudiante() {
    prueba_heap_vacia();
    prueba_heap_valor_null();
    prueba_heap_elementos_estaticos();
    prueba_heap_elementos_dinamicos();
    prueba_heap_crear_arr();
    prueba_heap_funcion_destruir();
    prueba_heap_volumen();
    prueba_heap_sort();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif