#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#include "TDAListaCarroCompra.h"
#include "recursos.h"

ListaCarroCompra *creaListaCarroCompra(){
   ListaCarroCompra *Lista = malloc(sizeof(ListaCarroCompra));

   if(Lista != NULL){
       Lista->ultimo = 0;
       Lista->inicial = NULL;
   }

   return Lista;
}

NodoCarroCompra *creaNodoCarroCompra(DatosCarroCompra p){
   NodoCarroCompra *nuevo = malloc(sizeof(NodoCarroCompra));

   if(nuevo != NULL){
     nuevo->sgte = NULL;
     nuevo->elem.nombre = p.nombre;
     nuevo->elem.SKU = p.SKU;
     nuevo->elem.cantidad = p.cantidad;
   }

   return nuevo;
}

ListaCarroCompra *ingresarCarroCompra(DatosCarroCompra p, posicionCC pos, ListaCarroCompra *L){
    int i;
    NodoCarroCompra *nuevo = creaNodoCarroCompra(p);
    NodoCarroCompra *aux = L->inicial;

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

posicionCC localizarCarroCompra(DatosCarroCompra p, ListaCarroCompra *L){
    posicionCC pos=0,pos_ret=0;
    NodoCarroCompra *aux = L->inicial;

    while(aux != NULL){
        pos++;

        if(esIgualCarroCompra(p,aux->elem.SKU)){
           pos_ret = pos;
        }

        aux=aux->sgte;
    }

    return pos_ret;
}

ListaCarroCompra *modificarCarroCompra(posicionCC pos, DatosCarroCompra p, ListaCarroCompra *L){
    int i;
    NodoCarroCompra *aux = L->inicial;

    if((pos < L->ultimo + 1) || (pos > 0)){
        if(pos == 1){
            aux->elem.SKU = p.SKU;
            aux->elem.nombre = p.nombre;
            aux->elem.cantidad = p.cantidad;
        }else{
            for(i=1;i<pos;i++){
                aux = aux->sgte;
            }

            aux->elem.SKU = p.SKU;
            aux->elem.nombre = p.nombre;
            aux->elem.cantidad = p.cantidad;
        }
    }

    return L;
}

DatosCarroCompra *recuperarCarroCompra(posicionCC pos, ListaCarroCompra *L){
    int i;
    DatosCarroCompra *p;
    NodoCarroCompra *aux = L->inicial;

    if((pos>L->ultimo + 1) || (pos < 0)){
        // y aqui que hago? cual ser?a la mejor alternativa? es mejor preguntar antes?
        // se copia el ultimo
        pos = L->ultimo;
    }

    if(pos == 1){
        p = copiarDatoCarroCompra(L->inicial);
    }else{
        for(i=1;i<pos;i++){
            aux = aux->sgte;
        }

        p = copiarDatoCarroCompra(aux);
    }

    return p;
}

ListaCarroCompra *eliminarCarroCompra(ListaCarroCompra *L, posicionCC pos){
    int i;
    NodoCarroCompra *aux = L->inicial;
    NodoCarroCompra *ant=NULL;

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

            free(aux);
            L->ultimo--;
        }
    }

    return L;
}

DatosCarroCompra topeCarroCompra(ListaCarroCompra *L){
    return L->inicial->elem;
}

int CantidadCarroCompra(ListaCarroCompra *L){
    return L->ultimo;
}

short esIgualCarroCompra(DatosCarroCompra p, char *sku){
    short ret = _FALSE;

    if(strcmp(p.SKU,sku) == 0){
        ret = _TRUE;
    }

    return ret;
}

DatosCarroCompra *copiarDatoCarroCompra(NodoCarroCompra *n){
    DatosCarroCompra *nuevo = malloc(sizeof(NodoCarroCompra));

    nuevo->SKU = n->elem.SKU;
    nuevo->nombre = n->elem.nombre;
    nuevo->cantidad = n->elem.cantidad;

    return nuevo;
}

ListaCarroCompra *vaciarCarroCompra(ListaCarroCompra *L){
    while(L->ultimo > 0){
        L = eliminarCarroCompra(L, L->ultimo);
    }

    return L;
}
