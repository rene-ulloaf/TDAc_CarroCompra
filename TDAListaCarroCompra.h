#ifndef TDALISTACC_H_INCLUDED
#define TDALISTACC_H_INCLUDED

typedef int posicionCC;

ListaCarroCompra *creaListaCarroCompra();
NodoCarroCompra *creaNodoCarroCompra(DatosCarroCompra);
ListaCarroCompra *ingresarCarroCompra(DatosCarroCompra, posicionCC, ListaCarroCompra *);
posicionCC localizarCarroCompra(DatosCarroCompra, ListaCarroCompra *);
ListaCarroCompra *modificarCarroCompra(posicionCC, DatosCarroCompra, ListaCarroCompra *);
DatosCarroCompra *recuperarCarroCompra(posicionCC, ListaCarroCompra *);
ListaCarroCompra *eliminarCarroCompra(ListaCarroCompra *, int);
DatosCarroCompra topeCarroCompra(ListaCarroCompra *);
int CantidadCarroCompra(ListaCarroCompra *);
short esIgualCarroCompra(DatosCarroCompra, char *);
DatosCarroCompra *copiarDatoCarroCompra(NodoCarroCompra *);
ListaCarroCompra *vaciarCarroCompra(ListaCarroCompra *);

#endif // TDALISTACC_H_INCLUDED
