#define VOLUMEN 100000

#include "heap.h"
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
    
    printf("2. INICIO DE PRUEBAS CON HEAP DE ELEMENTOS ESTATICOS\n");
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

    printf("3. INICIO DE PRUEBAS CON HEAP DE ELEMENTOS DINAMICOS\n");
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

    printf("4. INICIO DE PRUEBAS DE VOLUMEN\n");
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

    printf("5. INICIO DE PRUEBAS HEAP SORT\n");
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

void pruebas_heap_estudiante() {
    prueba_heap_vacia();
    prueba_heap_elementos_estaticos();
    prueba_heap_elementos_dinamicos();
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