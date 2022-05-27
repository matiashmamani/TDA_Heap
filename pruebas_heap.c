#define VOLUMEN 100000
#define POS_PRIMERO 0

#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpiar_entero(void *dato){
    int *p_int;
    p_int = (int*)dato;
    *p_int = 0;
}

int intcmp(const void *a, const void *b){

    if(*(int*)a > *(int*)b) return 1;

    if(*(int*)a < *(int*)b) return -1;

    // *a == *b
    return 0;
}

static void prueba_heap_vacia(void) {

    printf("1. INICIO DE PRUEBAS CON HEAP VACIA\n");
    heap_t *heap = heap_crear(NULL);
    print_test("- Crear heap vacía", heap != NULL);
    print_test("- Heap esta vacía", heap_esta_vacia(heap));
    print_test("- Ver primero de la heap vacia devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("- desencolar en heap vacia devuelve NULL", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
    print_test("- Destruir heap vacía", true);
}

static void prueba_heap_algunos_elementos_estaticos(void) {

    void *p_null = NULL;
    int n_null = 5;
    
    printf("2. INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS ESTATICOS\n");
    printf("HEAP QUE ALMACENA VALORES NULL:\n");
    heap_t *heap = heap_crear(intcmp));
    print_test("- Crear heap", heap != NULL);

    bool ok = true;
    bool ok_ver_max = true;
    for(int i = 0; i < n_null; i++){
        ok &= heap_encolar(heap, p_null);
        ok_ver_max &= (heap_ver_max(heap) == NULL);
    }
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la heap es NULL en cada encolado", ok_ver_max);
    print_test("- Heap no esta vacía", !heap_esta_vacia(heap));

    ok = true;
    for(int i = 0; i < n_null; i++){
        p_null = heap_desencolar(heap);
        ok &= (p_null == NULL);
    }
    print_test("- Se pudieron desencolar todos los elementos y mantienen invariante de heap", ok);
    print_test("- Heap quedó vacía después de desencolar todo", heap_esta_vacia(heap));
    print_test("- Ver primero de heap devuelve NULL después de desencolar todo", heap_ver_max(heap) == NULL);
    print_test("- desencolar en heap vacía devuelve NULL", heap_desencolar(heap) == NULL);
    for(int i = 0; i < n_null; i++){
        heap_encolar(heap, p_null);
    }
    print_test("- Heap se llenó de vuelta", !heap_esta_vacia(heap));
    heap_destruir(heap, NULL);
    print_test("- Destruir heap (con NULL)", true);
}

static void prueba_heap_algunos_elementos_dinamicos(void){

    int **vec_int;
    int n_int  = 3;

    // Creo arreglo de arreglos de enteros
    vec_int = malloc((size_t)n_int * sizeof(int*));
    for(int i = 0; i < n_int; i++){
        vec_int[i] = malloc((size_t)n_int * sizeof(int));
        for(int j = 0; j < n_int; j++){
            vec_int[i][j] = i;
        }
    }

    printf("3. INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS DINAMICOS\n");
    printf("HEAP QUE ALMACENA VECTORES DINAMICOS:\n");
    heap_t *heap = heap_crear();
    print_test("- Crear heap", heap != NULL);

    bool ok = true;
    bool ok_ver_max = true;
    int *p_int;
    for(int i = 0; i < n_int; i++){
        ok &= heap_encolar(heap, vec_int[i]);
        p_int = heap_ver_max(heap);
        ok_ver_max &= (p_int == vec_int[POS_PRIMERO]);
    }
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la heap es correcto en cada encolado", ok_ver_max);
    print_test("- Heap no esta vacía", !heap_esta_vacia(heap));

    heap_destruir(heap, free);
    print_test("- Destruir heap (con free())", true);
    free(vec_int);
}

static void prueba_heap_volumen(void) {

    printf("4. INICIO DE PRUEBAS DE VOLUMEN\n");
    heap_t *heap = heap_crear();
    print_test("- Crear heap", heap != NULL);
    
    bool ok = true;
    bool ok_ver_max = true;
    int *p_int;
    int vec_int[VOLUMEN];
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        ok &= heap_encolar(heap, &vec_int[i]);
        p_int = heap_ver_max(heap);
        ok_ver_max &= (*p_int == vec_int[POS_PRIMERO]);
    } 
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la heap es correcto en cada encolado", ok_ver_max);
    print_test("- Heap no esta vacía", !heap_esta_vacia(heap));

    ok = true;
    p_int = NULL;
    for(int i = 0; i < VOLUMEN; i++){
        p_int = heap_desencolar(heap);
        ok &= (*p_int == vec_int[i]);
    }
    print_test("- Se pudieron desencolar todos los elementos y se mantiene el invariante de heap", ok);
    print_test("- Heap quedó vacía después de desencolar todo", heap_esta_vacia(heap));
    print_test("- Ver primero de la heap devuelve NULL después de desencolar todo", heap_ver_max(heap) == NULL);
    print_test("- desencolar en heap vacía devuelve NULL", heap_desencolar(heap) == NULL);
    
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        heap_encolar(heap, &vec_int[i]);
    }
    print_test("- Heap se llenó de vuelta", !heap_esta_vacia(heap));
    heap_destruir(heap, limpiar_entero);
    print_test("- Destruir heap (con funcion())", true);
}

void pruebas_heap_estudiante() {
    prueba_heap_vacia();
    prueba_heap_algunos_elementos_estaticos();
    prueba_heap_algunos_elementos_dinamicos();
    prueba_heap_volumen();
}