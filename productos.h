#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include "estructuras.h"

//#define _RUTA "C:\\carro_compra\\"
#define _RUTA ""
//#define _DIM_RUTA 17
#define _DIM_RUTA 0

void VolverMenuProd(char *, char *, ListaProd *);
void creaUsuario(ListaProd *);
ListaProd * ObtenerProductos(ListaProd *productos);
void MostrarProductos(ListaProd *, int, int);
void VerProductos(ListaProd *, int, int);
void AgregarProducto(ListaProd *);
void ModificarProducto(ListaProd *);
void EliminarProducto(ListaProd *);
void GuardarProdArch(ListaProd *);
short guardaUsuarioArch(char *, char *, char *);
short valIngProd(ListaProd *, char *, char *, char *, char *);
short valModProd(char *, char *, char *, char *);

#endif // PRODUCTOS_H_INCLUDED
