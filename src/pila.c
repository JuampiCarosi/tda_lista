#include "pila.h"

#include "lista.h"

struct _nodo {
  void *elemento;
  struct nodo *siguiente;
};

struct _pila_t {
  nodo_t *nodo_inicio;
  nodo_t *nodo_fin;
  size_t cantidad;
};

pila_t *pila_crear() { return (pila_t *)lista_crear(); }

pila_t *pila_apilar(pila_t *pila, void *elemento) {
  if (!pila || !elemento) return NULL;
  return (pila_t *)lista_insertar((lista_t *)pila, elemento);
}

void *pila_desapilar(pila_t *pila) {
  if (!pila) return NULL;
  return lista_quitar((lista_t *)pila);
}

void *pila_tope(pila_t *pila) {
  if (!pila) return NULL;
  return pila->nodo_fin->elemento;
}

size_t pila_tamanio(pila_t *pila) {
  if (!pila) return 0;
  return pila->cantidad;
}

bool pila_vacia(pila_t *pila) {
  if (!pila) return true;
  return pila->cantidad == 0;
}

void pila_destruir(pila_t *pila) {
  if (!pila) return;
  lista_destruir((lista_t *)pila);
}
