#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct str_producto{
    char *SKU;
    char *nombre;
    int stock;
} DatosProd;

typedef struct str_nodo{
    DatosProd elem;
    struct str_nodo *sgte;
} NodoProd;

typedef struct str_Lista{
    NodoProd *inicial;
    int ultimo;
} ListaProd;

typedef struct str_carro_compra{
    char *SKU;
    char *nombre;
    int cantidad;
} DatosCarroCompra;

typedef struct str_nodo_carro_compra{
    DatosCarroCompra elem;
    struct str_carro_compra *sgte;
} NodoCarroCompra;

typedef struct str_Lista_carro_compra{
    NodoCarroCompra *inicial;
    int ultimo;
} ListaCarroCompra;

#endif // ESTRUCTURAS_H_INCLUDED
