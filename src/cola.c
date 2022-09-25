#include "cola.h"

#include "lista.h"

struct _nodo {
  void *elemento;
  struct nodo *siguiente;
};

struct _cola_t {
  nodo_t *nodo_inicio;
  nodo_t *nodo_fin;
  size_t cantidad;
};

cola_t *cola_crear() { return (cola_t *)lista_crear(); }

cola_t *cola_encolar(cola_t *cola, void *elemento) {
  if (!cola || !elemento) return NULL;
  return (cola_t *)lista_insertar((lista_t *)cola, elemento);
}

void *cola_desencolar(cola_t *cola) {
  if (!cola || cola->cantidad == 0) return NULL;
  return lista_quitar_de_posicion((lista_t *)cola, 0);
}

void *cola_frente(cola_t *cola) {
  if (!cola || cola->cantidad == 0) return NULL;
  return cola->nodo_inicio->elemento;
}

size_t cola_tamanio(cola_t *cola) {
  if (!cola) return 0;
  return cola->cantidad;
}

bool cola_vacia(cola_t *cola) {
  if (!cola) return true;
  return cola->cantidad == 0;
}

void cola_destruir(cola_t *cola) {
  if (!cola) return;
  lista_destruir((lista_t *)cola);
}
