#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "estructuras.h"

#define max_sku 10
#define max_nom_prod 100
#define max_stock 9

#define max_nom_usuario 25
#define max_pass 6

void MenuPrincipal(char *);
short InicioSesion(char *, char *);
void MenuAdministrador(ListaProd *, short);
void MenuComprador(ListaProd *, ListaCarroCompra *, char *);

#endif // MAIN_H_INCLUDED
