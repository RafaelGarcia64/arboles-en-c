#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int valor;
    struct nodo *izdo;
    struct nodo *drcho;
} Nodo;

typedef Nodo arbol;

Nodo *CrearNodo(int valor)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->izdo = nuevoNodo->drcho = NULL;
    return nuevoNodo;
}

void DestruirNodo(Nodo *nodo)
{
    nodo->izdo = nodo->drcho = NULL;
    free(nodo);
}
void Insertar(Nodo **arbol, int valor)
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

int Existe(Nodo *arbol, int valor)
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

void DeterminarExistencia(Nodo *arbol, int valor)
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

void Preorden(Nodo *arbol)
{

    if (arbol == NULL)
    {
        printf(" - ");
    }
    else
    {
        printf("( %d ", arbol->valor);
        Preorden(arbol->izdo);
        Preorden(arbol->drcho);
        printf(" )");
    }
}

void Inorden(Nodo *arbol)
{
    if (arbol == NULL)
    {
        printf(" - ");
    }
    else
    {
        printf("( ");
        Inorden(arbol->izdo);
        printf(" %d ", arbol->valor);
        Inorden(arbol->drcho);
        printf(" )");
    }
}

void Postorden(Nodo *arbol)
{

    if (arbol == NULL)
    {
        printf(" - ");
    }
    else
    {
        printf("( ");
        Postorden(arbol->izdo);
        Postorden(arbol->drcho);
        printf(" %d )", arbol->valor);
    }
}

int main(void)
{
    Nodo *arbol = NULL;
    Insertar(&arbol, 5);    Postorden(arbol); printf("\n");
    Insertar(&arbol, 10);   Postorden(arbol); printf("\n");
    Insertar(&arbol, 4);    Postorden(arbol); printf("\n");
    Insertar(&arbol, 9);    Postorden(arbol); printf("\n");
    Insertar(&arbol, 15);   Postorden(arbol); printf("\n");
    //DeterminarExistencia(arbol, 10);
    //DeterminarExistencia(arbol, 3);
    //DeterminarExistencia(arbol, 9);
}
