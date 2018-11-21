#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int valor;
    struct nodo *izdo;
    struct nodo *drcho;
} Nodo;

typedef Nodo arbol;

Nodo* CrearNodo(int valor)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->izdo = nuevoNodo->drcho = NULL;
    return nuevoNodo;
}

void DestruirNodo(Nodo* nodo)
{
    nodo->izdo = nodo->drcho = NULL;
    free(nodo);
}
void Insertar(Nodo** arbol, int valor)
{

    if (*arbol == NULL)
    {
        *arbol = CrearNodo(valor);
    }
    else
    {
        int valorRaiz = (*arbol)->valor;
        if (valor < valorRaiz)
        {
            Insertar(&(*arbol)->izdo, valor);
        }
        else
        {
            Insertar(&(*arbol)->drcho, valor);
        }
    }
}

int Existe(Nodo* arbol, int valor)
{
    if (arbol == NULL)
    {
        return 0;
    }
    else if (arbol->valor == valor)
    {
        return 1;
    }
    else if (valor < arbol->valor)
    {
        return Existe(arbol->izdo, valor);
    }
    else
    {
        return Existe(arbol->drcho, valor);
    }
}

void DeterminarExistencia(Nodo* arbol, int valor)
{

    if (Existe(arbol, valor))
    {
        printf("El nodo %d existe en el arbol.\n", valor);
    }
    else
    {
        printf("El nodo %d No existe en el arbol.\n", valor);
    }
}

int main(void)
{
    Nodo* arbol = NULL;
    Insertar(&arbol, 5);
    Insertar(&arbol, 10);
    Insertar(&arbol, 4);
    Insertar(&arbol, 9);
    Insertar(&arbol, 15);
    DeterminarExistencia(arbol,10);
    DeterminarExistencia(arbol,3);
    DeterminarExistencia(arbol,9);
}
