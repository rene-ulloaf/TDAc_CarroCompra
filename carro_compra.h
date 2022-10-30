#ifndef CARRO_COMPRA_H_INCLUDED
#define CARRO_COMPRA_H_INCLUDED

#include "estructuras.h"

//#define _RUTA "C:\\carro_compra\\"
#define _RUTA ""
//#define _RUTA_CARRO_COMPRA "C:\\carro_compra\\carro_compra\\"
#define _RUTA_CARRO_COMPRA ""
//#define _RUTA_COMPRA "C:\\carro_compra\\compras\\"
#define _RUTA_COMPRA ""
//#define _DIM_RUTA 17
#define _DIM_RUTA 0
//#define _DIM_RUTA_CARRO_COMPRA 27
#define _DIM_RUTA_CARRO_COMPRA 0
//#define _DIM_RUTA_COMPRA 26
#define _DIM_RUTA_COMPRA 0

void VolverMenuCarroCompra(char *, char *, ListaProd *, ListaCarroCompra *);
ListaCarroCompra * ObtenerCC(ListaCarroCompra *, char *);
void SelProductos(ListaProd *, ListaCarroCompra *, int, int);
ListaCarroCompra * AgregarProdCarroCompra(ListaProd *, ListaCarroCompra *, short *, char *);
void BuscarProductosCC(ListaProd *, ListaCarroCompra *, int, int);
int MostrarProductosCC(ListaCarroCompra *, int, int);
void ModificarProductosCC(ListaProd *, ListaCarroCompra *);
void EliminarProductoCC(ListaProd *, ListaCarroCompra *);
void ComprarProductosCC(ListaProd *, ListaCarroCompra *, char *);
void CompraProductos(ListaProd *, ListaCarroCompra *);
void GuardarProdCCArch(ListaCarroCompra *, char *);
void GuardarProdCompradoArch(ListaCarroCompra *, char *);
void eliminarArchCC(char *);
short valIngCarroCompra(char *, char *, int, char *);
short ValidaCompraCC(ListaProd *, ListaCarroCompra *, char *);

#endif // CARRO_COMPRA_H_INCLUDED
