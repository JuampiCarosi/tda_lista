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
  void *elemento = malloc(sizeof(int));
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_tamanio(lista) == 1, "La cantidad de elementos es 1");
  void *elemento2 = malloc(sizeof(int));
  lista_insertar(lista, elemento2);
  pa2m_afirmar(lista_tamanio(lista) == 2, "La cantidad de elementos es 2");
  lista_destruir_todo(lista, eliminar_elemento);
}

void listaPrimeroDevuelveElPrimerElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  void *elemento = malloc(sizeof(int));
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_primero(lista) == elemento, "El primer elemento es el insertado");
  lista_destruir_todo(lista, eliminar_elemento);
}

void listaUltimoDevuelveElUltimoElemento() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  void *elemento = malloc(sizeof(int));
  lista_insertar(lista, elemento);
  pa2m_afirmar(lista_ultimo(lista) == elemento, "El ultimo elemento es el insertado");
  lista_destruir_todo(lista, eliminar_elemento);
}

void listaEstaVacia() {
  lista_t *lista = lista_crear();
  if (!lista) return;
  pa2m_afirmar(lista_vacia(lista), "La lista esta vacia");
  void *elemento = malloc(sizeof(int));
  lista_insertar(lista, elemento);
  pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");
  lista_destruir_todo(lista, eliminar_elemento);
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

  pa2m_afirmar(lista_buscar_elemento(lista_insertada, comparador, NULL) == NULL,
               "El buscar elemento NULL devuelve NULL");

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
  pa2m_afirmar(elemento_eliminado == &c, "Se retorna correctamente el nuevo elemento");
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
  pa2m_afirmar(elemento_eliminado == &b, "Se retorna correctamente el nuevo elemento");
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

  pa2m_afirmar(lista_con_cada_elemento(lista_insertada, debe_recorrer_elementos, NULL) == 0,
               "Recorrer una lista con contexto NULL devuelve 0");
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
  lista_destruir_todo(lista_insertada, eliminar_elemento);
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

int main() {
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

  return pa2m_mostrar_reporte();
}
