#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#include "TDAListaProd.h"
#include "recursos.h"

ListaProd *creaListaProd(){
   ListaProd *Lista = malloc(sizeof(ListaProd));

   if(Lista != NULL){
       Lista->ultimo = 0;
       Lista->inicial = NULL;
   }

   return Lista;
}

NodoProd *creaNodoProd(DatosProd p){
   NodoProd *nuevo = malloc(sizeof(NodoProd));

   if(nuevo != NULL){
     nuevo->sgte = NULL;
     nuevo->elem.nombre = p.nombre;
     nuevo->elem.SKU = p.SKU;
     nuevo->elem.stock = p.stock;
   }

   return nuevo;
}

ListaProd *ingresarProd(DatosProd p, posicionProd pos, ListaProd *L){
    int i;
    NodoProd *nuevo = creaNodoProd(p);
    NodoProd *aux = L->inicial;

    if((pos > L->ultimo+1) || (pos < 0)){
        // y aqui que hago? cual ser?a la mejor alternativa?
        //R: se inserta al final de la lista
        pos = L->ultimo;
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

posicionProd localizarProd(DatosProd p, ListaProd *L){
    posicionProd pos=0,pos_ret=0;
    NodoProd *aux = L->inicial;

    while(aux != NULL){
        pos++;

        if(esIgualProd(p,aux->elem.SKU)){
           pos_ret = pos;
        }

        aux=aux->sgte;
    }

    return pos_ret;
}

ListaProd *modificarProd(posicionProd pos, DatosProd p, ListaProd *L){
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

DatosProd *recuperarProd(posicionProd pos, ListaProd *L){
    int i;
    DatosProd *p;
    NodoProd *aux = L->inicial;

    if(pos == 1){
        p = copiarDatoProd(L->inicial);
    }else{
        for(i=1;i<pos;i++){
            aux = aux->sgte;
        }

        p = copiarDatoProd(aux);
    }

    return p;
}

ListaProd *eliminarProd(ListaProd *L, posicionProd pos){
    int i;
    NodoProd *aux = L->inicial;
    NodoProd *ant = NULL;

    if(L != NULL){
        if((pos > 0) && (pos <= L->ultimo)){
            if(pos == 1){
                if(aux->sgte == NULL){
                    L->inicial = NULL;
                }else{
                    L->inicial = aux->sgte;
                }
            }else{
                for(i=2;i<=pos;i++){
                    ant = aux;
                    aux = aux->sgte;
                }

                ant->sgte = aux->sgte;
            }

            L->ultimo--;
            free(aux);
        }
    }

    return L;
}

DatosProd topeProd(ListaProd *L){
    return L->inicial->elem;
}

int CantidadProd(ListaProd *L){
    return L->ultimo;
}

short esIgualProd(DatosProd p, char *sku){
    short ret = _FALSE;

    if(strcmp(p.SKU,sku) == 0){
        ret = _TRUE;
    }

    return ret;
}

DatosProd *copiarDatoProd(NodoProd *n){
    DatosProd *nuevo = malloc(sizeof(NodoProd));

    nuevo->SKU = n->elem.SKU;
    nuevo->nombre = n->elem.nombre;
    nuevo->stock = n->elem.stock;

    return nuevo;
}

ListaProd *vaciarProductos(ListaProd *L){
    while(L->ultimo > 0){
        L = eliminarProd(L, L->ultimo);
    }

    return L;
}
