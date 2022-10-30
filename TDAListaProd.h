#ifndef TDALISTAPROD_H_INCLUDED
#define TDALISTAPROD_H_INCLUDED

typedef int posicionProd;

ListaProd *creaListaProd();
NodoProd *creaNodoProd(DatosProd);
ListaProd *ingresarProd(DatosProd, posicionProd, ListaProd *);
posicionProd localizarProd(DatosProd, ListaProd *);
ListaProd *modificarProd(posicionProd, DatosProd, ListaProd *);
DatosProd *recuperarProd(posicionProd, ListaProd *);
ListaProd *eliminarProd(ListaProd *, int);
DatosProd topeProd(ListaProd *);
int CantidadProd(ListaProd *);
short esIgualProd(DatosProd, char *);
DatosProd *copiarDatoProd(NodoProd *);
ListaProd *vaciarProductos(ListaProd *);

#endif // TDALISTAPROD_H_INCLUDED
