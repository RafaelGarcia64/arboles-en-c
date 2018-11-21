#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int valor;
    struct nodo* izdo;
    struct nodo* drcho;
} Nodo;

typedef Nodo arbol;

Nodo* CrearNodo(int valor){
    Nodo* nuevoNodo = (Nodo *) malloc (sizeof(Nodo)); 
}