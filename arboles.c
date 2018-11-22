#include <stdio.h>
#include <stdlib.h>

//Definicon de la estructura arbol
typedef struct nodo{
    int valor;
    struct nodo *izdo;
    struct nodo *drcho;
    struct nodo *padre;
} Nodo;

//Definicion de nombre alternativo a la estructura
typedef Nodo arbol;

//Funcion para crear un nodo, funcion creada de forma 
//recursiva para poder usarse en cualquier parte de el arbol
//nodos hijos igualados a nul y preparados para generar una nueva rama
Nodo *CrearNodo(int valor, Nodo *padre){
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->izdo = nuevoNodo->drcho = NULL;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}

//Funcion para destruir un nodo, primero vaciando sus hijos y luego 
//liberando la memoria que usaba el nodo
void DestruirNodo(Nodo *nodo){
    nodo->izdo = nodo->drcho = NULL;
    free(nodo);
}

//Funcion de apoyo creado de forma recursiva un nuevo nodo
//ademas que la funcion evalua en que lugar de el arbol 
//puede ser insertado el nuevo nodo y si un nodo provehido esta vacio
static void InsertarConPadre(Nodo **arbol, Nodo *padre, int valor){
    if (*arbol == NULL){
        *arbol = CrearNodo(valor, padre);
    }
    else{
        int valorRaiz = (*arbol)->valor;
        if (valor < valorRaiz){
            InsertarConPadre(&(*arbol)->izdo, *arbol, valor);
        }else{
            InsertarConPadre(&(*arbol)->drcho, *arbol, valor);
        }
    }
}

//Funcion para agregar un nuevo nodo al arbol
void Insertar(Nodo **arbol, int valor){
    InsertarConPadre(arbol, NULL, valor);
}

//Funcion para recorrer un arbol de forma optima y recursiva
//y devolviendo una respuesta si existe el elemento solicitado
int Existe(Nodo *arbol, int valor){
    if (arbol == NULL){
        return 0;
    }else if (arbol->valor == valor){
        return 1;
    }else if (valor < arbol->valor){
        return Existe(arbol->izdo, valor);
    }else{
        return Existe(arbol->drcho, valor);
    }
}

//Funcion para obtener las ramas de un nodo de forma recursiva
Nodo *Obtener(Nodo *arbol, int valor){
    if (arbol == NULL){
        return NULL;
    }else if (arbol->valor == valor){
        return arbol;
    }else if (valor < arbol->valor){
        return Obtener(arbol->izdo, valor);
    }else{
        return Obtener(arbol->drcho, valor);
    }
}

//Funcion para reemplazar un nodo en un arbol especificado
//la funcion verifica que exista un pdre para el arbol proporcionado
//y si existe padre procede a verificar en donde lo reemplaza y hace
//la accion de reemplazar
static void Reemplazar(Nodo *arbol, Nodo *nuevoNodo){
    if (arbol->padre){
        if (arbol->valor == arbol->padre->izdo->valor){
            arbol->padre->izdo = nuevoNodo;
        }else if (arbol->valor == arbol->padre->drcho->valor){
            arbol->padre->drcho = nuevoNodo;
        }
        if (nuevoNodo){
            nuevoNodo->padre = arbol->padre;
        }
    }
}

//Funcion de apoyo para la funcion de eliminarNodo
//Esta funcion devuelve el menor valor de el arbol
static Nodo *Minimo(Nodo *arbol){
    if (arbol == NULL){
        return NULL;
    }if (arbol->izdo){
        return Minimo(arbol->izdo);
    }else{
        return arbol;
    }
}

//Funcion de apoyo para la funcion en el cual se le proporciona 
//el nodo a eliminar y porcede a eliminarlo y dejar a sus hijos 
//si es que existen 
static void EliminarNodo(Nodo *nodoEliminar){
    if (nodoEliminar->izdo && nodoEliminar->drcho){
        //Tratar elimiar con 2 hijos
        Nodo *minimo = Minimo(nodoEliminar->drcho);
        nodoEliminar->valor = minimo->valor;
        EliminarNodo(minimo);
    }else if (nodoEliminar->izdo){
        //Tratar eliminar con 1 hijo
        Reemplazar(nodoEliminar, nodoEliminar->izdo);
        DestruirNodo(nodoEliminar);
    }else if (nodoEliminar->drcho){
        //Tratar eliminar con 1 hijo
        Reemplazar(nodoEliminar, nodoEliminar->drcho);
        DestruirNodo(nodoEliminar);
    }else{
        //Tratar eliminar con 0 hijos
        Reemplazar(nodoEliminar, NULL);
        DestruirNodo(nodoEliminar);
    }
}

//Funcion en el cual se elimina un nodo a partir de su funcion de apoyo
void Eliminar(Nodo *arbol, int valor){
    if (arbol == NULL){
        return;
    }else if (valor < arbol->valor){
        Eliminar(arbol->izdo, valor);
    }else if (valor > arbol->valor){
        Eliminar(arbol->drcho, valor);
    }else{
        EliminarNodo(arbol);
    }
}

//Funcion en la cual se imprime el arbol en forma de 
//preorden
void Preorden(Nodo *arbol){
    if (arbol == NULL){
        printf(" - ");
    }else{
        printf("( %d ", arbol->valor);
        Preorden(arbol->izdo);
        Preorden(arbol->drcho);
        printf(" )");
    }
}

//Funcion en la cual se imprime el arbol en forma de 
//inorden
void Inorden(Nodo *arbol){
    if (arbol == NULL){
        printf(" - ");
    }else{
        printf("( ");
        Inorden(arbol->izdo);
        printf(" %d ", arbol->valor);
        Inorden(arbol->drcho);
        printf(" )");
    }
}

//Funcion en la cual se imprime el arbol en forma de 
//postorden
void Postorden(Nodo *arbol){
    if (arbol == NULL){
        printf(" - ");
    }else{
        printf("( ");
        Postorden(arbol->izdo);
        Postorden(arbol->drcho);
        printf(" %d )", arbol->valor);
    }
}

//Funcion main con ejemplos de insercion, eliminacion e impresion de datos
int main(void){
    Nodo *arbol = NULL;
    Insertar(&arbol, 5);    Inorden(arbol); printf("\n");
    Insertar(&arbol, 10);   Inorden(arbol); printf("\n");
    Insertar(&arbol, 4);    Inorden(arbol); printf("\n");
    Insertar(&arbol, 9);    Inorden(arbol); printf("\n");
    Insertar(&arbol, 15);   Inorden(arbol); printf("\n");
    Insertar(&arbol, 20);   Inorden(arbol); printf("\n");
    Insertar(&arbol, 2);    Inorden(arbol); printf("\n");
    Eliminar(arbol,4);  Inorden(arbol); printf("\n");
    Eliminar(arbol,15);  Inorden(arbol); printf("\n");
    Eliminar(arbol,5);  Inorden(arbol); printf("\n");
}