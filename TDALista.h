#ifndef TDASTACK_H_INCLUDED
#define TDASTACK_H_INCLUDED

typedef int posicion;

NodoProd *creaNodo(DatosProd);
ListaProd *creaLista();
ListaProd *ingresar(DatosProd, posicion, ListaProd *);
posicion localizar(DatosProd, ListaProd *);
ListaProd *modificar(posicion, DatosProd, ListaProd *);
DatosProd *recuperar(posicion, ListaProd *);
ListaProd *eliminar(ListaProd *, int);
DatosProd tope(ListaProd *);
int CantidadProd(ListaProd *);
short esIgual(DatosProd, char *);
DatosProd *copiarDato(NodoProd *);

#endif // TDASTACK_H_INCLUDED
