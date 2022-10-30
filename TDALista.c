#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#include "TDALista.h"
#include "recursos.h"

ListaProd *creaLista(){
   ListaProd *Lista = malloc(sizeof(ListaProd));

   if(Lista != NULL){
       Lista->ultimo = 0;
       Lista->inicial = NULL;
   }

   return Lista;
}

NodoProd *creaNodo(DatosProd p){
   NodoProd *nuevo = malloc(sizeof(NodoProd));

   if(nuevo != NULL){
     nuevo->sgte = NULL;
     nuevo->elem.nombre = p.nombre;
     nuevo->elem.SKU = p.SKU;
     nuevo->elem.stock = p.stock;
   }

   return nuevo;
}

ListaProd *ingresar(DatosProd p, posicion pos, ListaProd *L){
    int i;
    NodoProd *nuevo = creaNodo(p);
    NodoProd *aux = L->inicial;

    if((pos > L->ultimo+1) || (pos < 0)){
        // y aqui que hago? cual ser?a la mejor alternativa?
        //R: se inserta al final de la lista
        nuevo->sgte = L->ultimo;
        L->ultimo++;
    }

    if(pos == 1){
        nuevo->sgte = L->inicial;
        L->inicial = nuevo;
        L->ultimo++;
    }else{
        for(i=2;i<pos;i++){
            aux = aux->sgte;
        }

        nuevo->sgte = aux->sgte;
        aux->sgte = nuevo;
        L->ultimo++;
    }

    return L;
}

posicion localizar(DatosProd p, ListaProd *L){
    posicion pos=0,pos_ret=0;
    NodoProd *aux = L->inicial;

    while(aux != NULL){
        pos++;

        if(esIgual(p,aux->elem.SKU)){
           pos_ret = pos;
        }

        aux=aux->sgte;
    }

    return pos_ret;
}

ListaProd *modificar(posicion pos, DatosProd p, ListaProd *L){
    int i;
    NodoProd *aux = L->inicial;

    if((pos < L->ultimo + 1) || (pos > 0)){
        if(pos == 1){
            aux->elem.SKU = p.SKU;
            aux->elem.nombre = p.nombre;
            aux->elem.stock = p.stock;
        }else{
            for(i=1;i<pos;i++){
                aux = aux->sgte;
            }

            aux->elem.SKU = p.SKU;
            aux->elem.nombre = p.nombre;
            aux->elem.stock = p.stock;
        }
    }

    return L;
}

DatosProd *recuperar(posicion pos, ListaProd *L){
    int i;
    DatosProd *p;
    NodoProd *aux = L->inicial;

    if((pos>L->ultimo + 1) || (pos < 0)){
        // y aqui que hago? cual ser?a la mejor alternativa? es mejor preguntar antes?
        // se copia el ultimo
        p = copiarDato(L->ultimo);
    }

    if(pos == 1){
        p = copiarDato(L->inicial);
    }else{
        for(i=1;i<pos;i++){
            aux = aux->sgte;
        }

        p = copiarDato(aux);
    }

    return p;
}

ListaProd *eliminar(ListaProd *L, posicion pos){
    int i;
    NodoProd *aux = L->inicial;
    NodoProd *ant;

    if(L != NULL){
        if((pos > 0) && (pos <= L->ultimo)){
            if(pos == 1){
                L->inicial->sgte = NULL;
            }else{
                for(i=2;i<=pos;i++){
                    ant = aux;
                    aux = aux->sgte;
                }

                ant->sgte = aux->sgte;
                L->ultimo--;
            }

            free(aux);
        }
    }

    return L;
}

DatosProd tope(ListaProd *L){
    return L->inicial->elem;
}

int CantidadProd(ListaProd *L){
    return L->ultimo;
}

short esIgual(DatosProd p, char *sku){
    short ret = _FALSE;

    if(strcmp(p.SKU,sku) == 0){
        ret = _TRUE;
    }

    return ret;
}

DatosProd *copiarDato(NodoProd *n){
    NodoProd *nuevo = malloc(sizeof(NodoProd));

    nuevo->elem.SKU = n->elem.SKU;
    nuevo->elem.nombre = n->elem.nombre;
    nuevo->elem.stock = n->elem.stock;

    return nuevo;
}
