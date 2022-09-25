#include <stdio.h>
#include <stdlib.h>

#include "pa2m.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"

void eliminar_elemento(void *elemento) { free(elemento); }

void listaSeCreaVacia() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Se crea una lista");
  if (!lista) return;
  pa2m_afirmar(lista_primero(lista) == NULL, "El nodo inicio es NULL");
  pa2m_afirmar(lista_ultimo(lista) == NULL, "El nodo fin es NULL");
  pa2m_afirmar(lista_tamanio(lista) == 0, "La cantidad de elementos es 0");
  lista_destruir(lista);
}

void listaTamanio() {
  lista_t *lista = lista_crear();
  char a = 'a';
  lista_insertar(lista, &a);
  pa2m_afirmar(lista_tamanio(lista) == 1, "La cantidad de elementos es 1");
  char b = 'b';
  lista_insertar(lista, &b);
  pa2m_afirmar(lista_tamanio(lista) == 2, "La cantidad de elementos es 2");
  lista_destruir(lista);
}

void listaPrimeroDevuelveElPrimerElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a';
  lista_insertar(lista, &a);
  pa2m_afirmar(lista_primero(lista) == &a, "El primer elemento es el insertado");
  lista_destruir(lista);
}

void listaUltimoDevuelveElUltimoElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a';
  lista_insertar(lista, &a);
  pa2m_afirmar(lista_ultimo(lista) == &a, "El ultimo elemento es el insertado");
  lista_destruir(lista);
}

void listaEstaVacia() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  pa2m_afirmar(lista_vacia(lista), "La lista esta vacia");
  char a = 'a';
  lista_insertar(lista, &a);
  pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");
  lista_destruir(lista);
}

int comparador(void *entero1, void *entero2) {
  if (*(char *)entero1 == *(char *)entero2)
    return 0;
  else if (*(char *)entero1 > *(char *)entero2)
    return 1;
  else
    return -1;
}

void listaBuscarElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c', aux = 'b', aux2 = 'd';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  pa2m_afirmar(lista_buscar_elemento(lista_insertada, comparador, &aux) == &b, "El elemento es encontrado");
  pa2m_afirmar(lista_buscar_elemento(lista_insertada, comparador, &aux2) == NULL, "El elemento no es encontrado");
  lista_destruir(lista);
}

void casosInfeclicesBuscarElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c', aux = 'b';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  pa2m_afirmar(lista_buscar_elemento(lista_insertada, NULL, &aux) == NULL, "El comparador NULL devuelve NULL");
  pa2m_afirmar(lista_buscar_elemento(NULL, comparador, &aux) == NULL, "La lista NULL devuelve NULL");

  lista_destruir(lista);
}

void casosInfelicesObtenerPropiedades() {
  pa2m_afirmar(lista_tamanio(NULL) == 0, "La cantidad de elementos de una lista NULL es 0");
  pa2m_afirmar(lista_vacia(NULL) == true, "La lista NULL esta vacia");
  pa2m_afirmar(lista_primero(NULL) == NULL, "El primer elemento de una lista NULL es NULL");
  pa2m_afirmar(lista_ultimo(NULL) == NULL, "El ultimo elemento de una lista NULL es NULL");
}

void listaSeInsertaUnElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  void *elemento = malloc(sizeof(int));
  lista_t *lista_insertada = lista_insertar(lista, elemento);
  if (!lista_primero(lista_insertada) || !lista_ultimo(lista_insertada)) return;
  pa2m_afirmar(lista_tamanio(lista_insertada) == 1, "La cantidad de elementos es 1");
  pa2m_afirmar(lista_primero(lista_insertada) == elemento,
               "El elemento del nodo inicio es el mismo que el elemento insertado");
  pa2m_afirmar(lista_primero(lista_insertada) == lista_ultimo(lista_insertada),
               "El nodo inicio y el nodo fin son el mismo");

  lista_destruir_todo(lista_insertada, eliminar_elemento);
}

void listaSeInsertanVariosElementos() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  pa2m_afirmar(lista_tamanio(lista_insertada) == 3, "La cantidad de elementos es 3");
  pa2m_afirmar(lista_primero(lista_insertada) == &a,
               "El elemento del nodo inicio es el mismo que el elemento insertado");
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 2) == &c,
               "El elemento del nodo fin es el mismo que el elemento insertado");
  lista_destruir(lista_insertada);
}

void casosInfelicesInsertar() {
  lista_t *lista = lista_crear();
  lista_t *lista_insertada = lista_insertar(lista, NULL);
  pa2m_afirmar(lista_insertada == NULL, "No se puede insertar un elemento NULL");
  lista_destruir(lista);

  void *elemento = malloc(sizeof(int));
  lista_t *lista_null_insertada = lista_insertar(NULL, elemento);
  pa2m_afirmar(lista_null_insertada == NULL, "No se puede insertar un elemento en una lista NULL");
  free(elemento);
}

void listaSeInsertaEnPosicion() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c', d = 'd';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  lista_insertada = lista_insertar_en_posicion(lista_insertada, &d, 1);
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 1) == &d,
               "El elemento se inserta correctamente en posicion 1");
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 2) == &b, "El nodo siguiente al insertado es el mismo");
  pa2m_afirmar(lista_tamanio(lista_insertada) == 4, "La cantidad de elementos es 4");

  char e = 'e';
  lista_insertada = lista_insertar_en_posicion(lista_insertada, &e, 5);
  pa2m_afirmar(lista_ultimo(lista_insertada) == &e,
               "Insertar elemento en posicion mayor a la cantidad de elementos resulta en agrear al final");

  char f = 'f';
  lista_insertada = lista_insertar_en_posicion(lista_insertada, &f, 0);
  pa2m_afirmar(lista_primero(lista_insertada) == &f, "Insertar elemento en posicion 0 resulta en agrear al principio");

  lista_destruir(lista_insertada);
}

void casosInfelicesInsertarPosicion() {
  lista_t *lista = lista_crear();
  lista_t *lista_insertada = lista_insertar_en_posicion(lista, NULL, 0);
  pa2m_afirmar(lista_insertada == NULL, "No se puede insertar un elemento NULL en posicion 0");
  lista_destruir(lista);

  void *elemento = malloc(sizeof(int));
  lista_t *lista_null_insertada = lista_insertar_en_posicion(NULL, elemento, 0);
  pa2m_afirmar(lista_null_insertada == NULL, "No se puede insertar un elemento en una lista NULL en posicion 0");
  free(elemento);

  lista_t *lista2 = lista_crear();
  if (!lista2) return;
  char a = 'a', b = 'b', c = 'c';

  lista_t *lista2_insertada = lista_insertar(lista2, &a);
  lista2_insertada = lista_insertar(lista2_insertada, &b);
  lista2_insertada = lista_insertar(lista2_insertada, &c);

  pa2m_afirmar(lista_elemento_en_posicion(lista2_insertada, 3) == NULL,
               "El elemento en la posicion 'cantidad' es NULL");
  pa2m_afirmar(lista_elemento_en_posicion(lista2_insertada, 4) == NULL,
               "El elemento en la posicion 'cantidad + 1' es NULL");
  lista_destruir(lista2_insertada);
}

void listaElementoEnPosicion() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  pa2m_afirmar(lista_primero(lista_insertada) == &a, "El primer elemento es el mismo que el elemento insertado");
  pa2m_afirmar(lista_ultimo(lista_insertada) == &c, "El ultimo elemento es el mismo que el elemento insertado");

  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 0) == &a,
               "El elemento en la posicion 0 es el mismo que el elemento insertado");
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 1) == &b,
               "El elemento en la posicion 1 es el mismo que el elemento insertado");
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 2) == &c,
               "El elemento en la posicion 2 es el mismo que el elemento insertado");

  lista_destruir(lista_insertada);
}

void casosInfelicesEnPosicion() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_primero(lista) == NULL, "No se puede obtener el primer elemento de una lista vacia");
  pa2m_afirmar(lista_ultimo(lista) == NULL, "No se puede obtener el ultimo elemento de una lista vacia");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "No se puede obtener el elemento 0 de una lista vacia");
  lista_destruir(lista);

  pa2m_afirmar(lista_primero(NULL) == NULL, "No se puede obtener el primer elemento de una lista NULL");
  pa2m_afirmar(lista_ultimo(NULL) == NULL, "No se puede obtener el ultimo elemento de una lista NULL");
  pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL, "No se puede obtener el elemento 0 en una lista NULL ");
}

void listaQuitar() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  void *elemento_eliminado = lista_quitar(lista_insertada);
  pa2m_afirmar(lista_ultimo(lista_insertada) == &b, "El penultimo es el nuevo ultimo");
  pa2m_afirmar(lista_tamanio(lista_insertada) == 2, "La cantidad es 2");
  pa2m_afirmar(elemento_eliminado == &c, "Se retorna correctamente el elemento eliminado");
  lista_destruir(lista);

  lista_t *lista2 = lista_crear();
  if (!lista2) return;
  char d = 'd';

  lista_t *lista2_insertada = lista_insertar(lista2, &d);
  lista_quitar(lista2_insertada);

  pa2m_afirmar(lista_ultimo(lista2_insertada) == NULL,
               "Al eliminar el elemento de una lista de cantidad 1 ultimo es NULL");
  pa2m_afirmar(lista_primero(lista2_insertada) == NULL,
               "Al eliminar el elemento de una lista de cantidad 1 el primero es NULL");
  pa2m_afirmar(lista_tamanio(lista2_insertada) == 0, "La cantidad es 0");
  lista_destruir(lista2_insertada);
}

void casosInfelicesQuitar() {
  pa2m_afirmar(lista_quitar(NULL) == NULL, "Eliminar un elemento de una lista NULL devuelve NULL");

  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_quitar(lista) == NULL, "Eliminar un elemento de una lista vacia devuelve NULL");
  lista_destruir(lista);
}

void listaQuitarElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);

  void *elemento_eliminado = lista_quitar_de_posicion(lista_insertada, 1);
  pa2m_afirmar(lista_elemento_en_posicion(lista_insertada, 1) == &c, "Se borran correctamente los elementos");
  pa2m_afirmar(lista_tamanio(lista_insertada) == 2, "La cantidad es 2");
  pa2m_afirmar(elemento_eliminado == &b, "Se retorna correctamente el elemento eliminado");
  lista_destruir(lista);
}

void casosInfelicesQuitarElemento() {
  pa2m_afirmar(lista_quitar_de_posicion(NULL, 0) == NULL,
               "Eliminar un elemento en posicon 0 de una lista NULL devuelve NULL");

  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL,
               "Eliminar un elemento posicon 0 de una lista vacia devuelve NULL");
  lista_destruir(lista);
}

typedef struct contexto {
  char condicion_de_corte;
  char elementos[4];
  int cantidad;
} contexto_t;

bool debe_recorrer_elementos(void *elemento, void *extra) {
  if (!elemento || !extra) return false;
  char *elemento_char = (char *)elemento;
  contexto_t *contexto = (contexto_t *)extra;

  contexto->elementos[contexto->cantidad] = *elemento_char;
  contexto->cantidad++;
  return (*elemento_char != contexto->condicion_de_corte);
}

bool siempre_true(void *elemento, void *contexto) { return true; }

void listaRecorrerInterno() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  char a = 'a', b = 'b', c = 'c', d = 'd';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);
  lista_insertada = lista_insertar(lista_insertada, &d);

  contexto_t contexto = {.condicion_de_corte = 'c', .elementos = {'z', 'z', 'z', 'z'}, .cantidad = 0};

  size_t iterados = lista_con_cada_elemento(lista_insertada, debe_recorrer_elementos, &contexto);

  bool elementos_correctos = contexto.elementos[0] == 'a' && contexto.elementos[1] == 'b' &&
                             contexto.elementos[2] == 'c' && contexto.elementos[3] == 'z';

  pa2m_afirmar(elementos_correctos, "Se recorren correctamente los elementos correctamente");
  pa2m_afirmar(iterados == 3, "Devuelve la cantidad de elementos iterados");
  lista_destruir(lista_insertada);
}

void casosInfelicesRecorrerInterno() {
  char contexto = 'x';
  pa2m_afirmar(lista_con_cada_elemento(NULL, debe_recorrer_elementos, &contexto) == 0,
               "Recorrer una lista NULL devuelve 0");

  lista_t *lista2 = lista_crear();
  char a = 'a';

  lista_t *lista_insertada = lista_insertar(lista2, &a);
  pa2m_afirmar(lista_con_cada_elemento(lista_insertada, NULL, &a) == 0,
               "Recorrer una lista con funcion NULL devuelve 0");

  lista_destruir(lista_insertada);

  lista_t *lista3 = lista_crear();
  pa2m_afirmar(lista_con_cada_elemento(lista3, debe_recorrer_elementos, &contexto) == 0,
               "Recorrer una lista vacia devuelve 0");
  lista_destruir(lista3);

  lista_t *lista4 = lista_crear();
  char b = 'b', c = 'c';

  lista_t *lista_insertada2 = lista_insertar(lista4, &b);
  lista_insertada2 = lista_insertar(lista_insertada2, &c);
  pa2m_afirmar(lista_con_cada_elemento(lista_insertada2, siempre_true, &contexto) == 0,
               "Recorrer una lista con funcion que devuelve true siempre devuelve 0");
  lista_destruir(lista_insertada2);
}

void listaRecorrerExterno() {
  lista_t *lista = lista_crear();

  if (!lista) return;
  char a = 'a', b = 'b', c = 'c', d = 'd';

  lista_t *lista_insertada = lista_insertar(lista, &a);
  lista_insertada = lista_insertar(lista_insertada, &b);
  lista_insertada = lista_insertar(lista_insertada, &c);
  lista_insertada = lista_insertar(lista_insertada, &d);

  size_t iterados = 0;
  bool iterados_estan_bien = false;
  lista_iterador_t *iterador;
  for (iterador = lista_iterador_crear(lista_insertada); lista_iterador_tiene_siguiente(iterador);
       lista_iterador_avanzar(iterador)) {
    iterados_estan_bien =
        (lista_iterador_elemento_actual(iterador) == lista_elemento_en_posicion(lista_insertada, iterados));
    iterados++;
  }
  lista_iterador_destruir(iterador);
  lista_destruir(lista_insertada);
  pa2m_afirmar(iterados_estan_bien, "Se recorren correctamente los elementos");
  pa2m_afirmar(iterados == 4, "Se recorren la cantidad correcta de elementos");
}

void casosInfelicesRecorrerExterno() {
  lista_iterador_t *iterador = lista_iterador_crear(NULL);
  pa2m_afirmar(!iterador, "Crear un iterador de una lista NULL devuelve NULL");
  lista_iterador_destruir(iterador);

  pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL), "Tiene siguiente de un iterador NULL devuelve false");
  pa2m_afirmar(!lista_iterador_avanzar(NULL), "Avanzar un iterador NULL devuelve false");
}

void pruebas_lista() {
  pa2m_nuevo_grupo("Pruebas de creación de lista");
  listaSeCreaVacia();

  pa2m_nuevo_grupo("Pruebas de inserción de elementos en lista");
  listaSeInsertaUnElemento();
  listaSeInsertanVariosElementos();
  listaSeInsertaEnPosicion();
  casosInfelicesInsertar();
  casosInfelicesInsertarPosicion();

  pa2m_nuevo_grupo("Pruebas de obtención de propiedades en lista");
  listaTamanio();
  listaPrimeroDevuelveElPrimerElemento();
  listaUltimoDevuelveElUltimoElemento();
  listaBuscarElemento();
  listaEstaVacia();
  casosInfelicesObtenerPropiedades();
  casosInfeclicesBuscarElemento();

  pa2m_nuevo_grupo("Pruebas de obtención de elementos en lista");
  listaElementoEnPosicion();
  casosInfelicesEnPosicion();

  pa2m_nuevo_grupo("Pruebas de eliminación de elementos en lista");
  listaQuitar();
  listaQuitarElemento();
  casosInfelicesQuitar();
  casosInfelicesQuitarElemento();

  pa2m_nuevo_grupo("Pruebas de recorrido interno de lista");
  listaRecorrerInterno();
  casosInfelicesRecorrerInterno();

  pa2m_nuevo_grupo("Pruebas de recorrido externo de lista");
  listaRecorrerExterno();
  casosInfelicesRecorrerExterno();
}

void pilaSeCreaVacia() {
  pila_t *pila = pila_crear();
  pa2m_afirmar(pila != NULL, "Se crea una pila");
  if (!pila) return;
  pa2m_afirmar(pila_tope(pila) == NULL, "El nodo tope es NULL");
  pa2m_afirmar(pila_tamanio(pila) == 0, "La cantidad de elementos es 0");
  pila_destruir(pila);
}

void pilaTamanio() {
  pila_t *pila = pila_crear();
  char a = 'a', b = 'b';
  pila_apilar(pila, &a);
  pa2m_afirmar(pila_tamanio(pila) == 1, "La cantidad de elementos es 1");
  pila_apilar(pila, &b);
  pa2m_afirmar(pila_tamanio(pila) == 2, "La cantidad de elementos es 2");
  pila_destruir(pila);
}

void pilaTope() {
  pila_t *pila = pila_crear();
  if (!pila) return;
  char a = 'a';
  pila_apilar(pila, &a);
  pa2m_afirmar(pila_tope(pila) == &a, "El tope es el insertado");
  pila_destruir(pila);
}

void pilaEstaVacia() {
  pila_t *pila = pila_crear();
  if (!pila) return;
  pa2m_afirmar(pila_vacia(pila), "La pila esta vacia");
  char a = 'a';
  pila_apilar(pila, &a);
  pa2m_afirmar(!pila_vacia(pila), "La pila no esta vacia");
  pila_destruir(pila);
}

void pilaSeInsertaUnElemento() {
  pila_t *pila = pila_crear();
  if (!pila) return;
  void *elemento = malloc(sizeof(int));
  pila_t *pila_apilada = pila_apilar(pila, elemento);
  if (!pila_tope(pila_apilada)) return;
  pa2m_afirmar(pila_tamanio(pila_apilada) == 1, "La cantidad de elementos es 1 al apilar");
  pa2m_afirmar(pila_tope(pila_apilada) == elemento, "El elemento del nodo tope es el mismo que el elemento insertado");
  pila_destruir(pila_apilada);
  free(elemento);
}

void pilaDesapilar() {
  pila_t *pila = pila_crear();
  if (!pila) return;
  char a = 'a', b = 'b', c = 'c';

  pila_t *pila_apilada = pila_apilar(pila, &a);
  pila_apilada = pila_apilar(pila_apilada, &b);
  pila_apilada = pila_apilar(pila_apilada, &c);

  void *elemento_eliminado = pila_desapilar(pila_apilada);
  pa2m_afirmar(pila_tope(pila_apilada) == &b, "El penultimo es el nuevo tope");
  pa2m_afirmar(pila_tamanio(pila_apilada) == 2, "La cantidad es 2 al desapilar");
  pa2m_afirmar(elemento_eliminado == &c, "Se retorna correctamente el elemento eliminado");
  pila_destruir(pila);

  pila_t *pila2 = pila_crear();
  if (!pila2) return;
  char d = 'd';

  pila_t *pila2_apilada = pila_apilar(pila2, &d);
  pila_desapilar(pila2_apilada);

  pa2m_afirmar(pila_tope(pila2_apilada) == NULL, "Al eliminar el elemento de una pila de cantidad 1 ultimo es NULL");
  pa2m_afirmar(pila_tamanio(pila2_apilada) == 0, "La cantidad es 0 al desapilar");
  pila_destruir(pila2_apilada);
}

void casosInfelicesPila() {
  pa2m_afirmar(pila_apilar(NULL, NULL) == NULL, "Apilar en una pila NULL devuelve NULL");
  pa2m_afirmar(pila_desapilar(NULL) == NULL, "Desapilar en una pila NULL devuelve NULL");
  pa2m_afirmar(pila_tope(NULL) == NULL, "Tope en una pila NULL devuelve NULL");
  pa2m_afirmar(pila_vacia(NULL), "Vacia en una pila NULL devuelve true");
  pa2m_afirmar(pila_tamanio(NULL) == 0, "Tamanio en una pila NULL devuelve 0");
}

void pruebasPila() {
  pa2m_nuevo_grupo("Pruebas de pila");
  pilaSeCreaVacia();
  pilaTamanio();
  pilaTope();
  pilaEstaVacia();
  pilaSeInsertaUnElemento();
  pilaDesapilar();
  casosInfelicesPila();
}

void colaSeCreaVacia() {
  cola_t *cola = cola_crear();
  pa2m_afirmar(cola != NULL, "Se crea una cola");
  if (!cola) return;
  pa2m_afirmar(cola_frente(cola) == NULL, "El nodo frente es NULL");
  pa2m_afirmar(cola_tamanio(cola) == 0, "La cantidad de elementos es 0");
  cola_destruir(cola);
}

void colaTamanio() {
  cola_t *cola = cola_crear();
  char a = 'a', b = 'b';
  cola_encolar(cola, &a);
  pa2m_afirmar(cola_tamanio(cola) == 1, "La cantidad de elementos es 1");
  cola_encolar(cola, &b);
  pa2m_afirmar(cola_tamanio(cola) == 2, "La cantidad de elementos es 2");
  cola_destruir(cola);
}

void colaFrente() {
  cola_t *cola = cola_crear();
  if (!cola) return;
  char a = 'a';
  cola_encolar(cola, &a);
  pa2m_afirmar(cola_frente(cola) == &a, "El frente es el insertado");
  cola_destruir(cola);
}

void colaEstaVacia() {
  cola_t *cola = cola_crear();
  if (!cola) return;
  pa2m_afirmar(cola_vacia(cola), "La cola esta vacia");
  char a = 'a';
  cola_encolar(cola, &a);
  pa2m_afirmar(!cola_vacia(cola), "La cola no esta vacia");
  cola_destruir(cola);
}
void colaSeInsertaUnElemento() {
  cola_t *cola = cola_crear();
  if (!cola) return;
  void *elemento = malloc(sizeof(int));
  cola_t *cola_encolada = cola_encolar(cola, elemento);
  if (!cola_frente(cola_encolada)) return;
  pa2m_afirmar(cola_tamanio(cola_encolada) == 1, "La cantidad de elementos es 1 al encolar");
  pa2m_afirmar(cola_frente(cola_encolada) == elemento,
               "El elemento del nodo frente es el mismo que el elemento insertado");
  cola_destruir(cola_encolada);
  free(elemento);
}

void colaDesencolar() {
  cola_t *cola = cola_crear();
  if (!cola) return;
  char a = 'a', b = 'b', c = 'c';

  cola_t *cola_encolada = cola_encolar(cola, &a);
  cola_encolada = cola_encolar(cola_encolada, &b);
  cola_encolada = cola_encolar(cola_encolada, &c);

  void *elemento_eliminado = cola_desencolar(cola_encolada);
  pa2m_afirmar(cola_frente(cola_encolada) == &b, "El segundo es el nuevo frente");
  pa2m_afirmar(cola_tamanio(cola_encolada) == 2, "La cantidad es 2 al desencolar");
  pa2m_afirmar(elemento_eliminado == &a, "Se retorna correctamente el elemento eliminado");
  cola_destruir(cola);

  cola_t *cola2 = cola_crear();
  if (!cola2) return;
  char d = 'd';

  cola_t *cola2_encolada = cola_encolar(cola2, &d);
  cola_desencolar(cola2_encolada);

  pa2m_afirmar(cola_frente(cola2_encolada) == NULL, "Al eliminar el elemento de una cola de cantidad 1 frente es NULL");
  pa2m_afirmar(cola_tamanio(cola2_encolada) == 0, "La cantidad es 0 al desencolar");
  cola_destruir(cola2_encolada);
}

void casosInfelicesCola() {
  pa2m_afirmar(cola_encolar(NULL, NULL) == NULL, "Encolar en una cola NULL devuelve NULL");
  pa2m_afirmar(cola_desencolar(NULL) == NULL, "Desencolar en una cola NULL devuelve NULL");
  pa2m_afirmar(cola_frente(NULL) == NULL, "Frente en una cola NULL devuelve NULL");
  pa2m_afirmar(cola_vacia(NULL), "Vacia en una cola NULL devuelve true");
  pa2m_afirmar(cola_tamanio(NULL) == 0, "Tamanio en una cola NULL devuelve 0");
}

void pruebasCola() {
  pa2m_nuevo_grupo("Pruebas de cola");
  colaSeCreaVacia();
  colaTamanio();
  colaFrente();
  colaEstaVacia();
  colaSeInsertaUnElemento();
  colaDesencolar();
  casosInfelicesCola();
}

int main() {
  pruebas_lista();
  pruebasPila();
  pruebasCola();
  return pa2m_mostrar_reporte();
}
