#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "main.h"
#include "carro_compra.h"
#include "productos.h"
#include "TDAListaProd.h"
#include "TDAListaCarroCompra.h"
#include "recursos.h"
#include "menu.h"

const short limite = 10;

void VolverMenuCarroCompra(char *msg, char *fx, ListaProd *productos, ListaCarroCompra *carroCompra){
    char vm;

    InicioPrograma();
    printf("\n\n");
    printf("%s\n\n %cDesea volver al Menu? [S/N]. " ,msg ,168);
    fflush(stdin);
    scanf("%s", &vm);

    if(vm == 'S' || vm == 's'){
        MenuComprador(productos, carroCompra, "");
    }else{
        if(strcmp(fx,"sel") == 0){
            SelProductos(productos, carroCompra, 0, 0);
        }

        if(strcmp(fx,"buscar") == 0){
            BuscarProductosCC(productos, carroCompra, 0, 0);
        }

        if(strcmp(fx,"modificar") == 0){
            ModificarProductosCC(productos, carroCompra);
        }

        if(strcmp(fx,"eliminar") == 0){
            EliminarProductoCC(productos, carroCompra);
        }
    }
}

ListaCarroCompra * ObtenerCC(ListaCarroCompra *carroCompra, char *usuario){
    char *sku, *nombre, *stock, aux[1],*ruta;
    FILE *archivo;
    DatosCarroCompra carro;

    ruta = (char *) malloc((_DIM_RUTA_CARRO_COMPRA + 17 + strlen(usuario)) * sizeof(char));

    strcpy(ruta,"");
    strcat(ruta,_RUTA_CARRO_COMPRA);
    strcat(ruta,"carro_compra_");
    strcat(ruta,usuario);
    strcat(ruta,".txt");

    if(ExisteArchivo(ruta)){
        if(PreguntaSINO("Tiene un carro de compra guardado. Quiere subirlo?")){
            archivo = fopen(ruta,"r");

            if(archivo != NULL){
                while(!feof(archivo) && fread(aux,1,1,archivo)){
                    fseek(archivo,-1, SEEK_CUR);

                    sku = (char *) malloc(max_sku * sizeof(char));
                    nombre = (char *) malloc(max_nom_prod * sizeof(char));
                    stock = (char *) malloc(max_stock * sizeof(char));

                    fscanf(archivo,"%s",sku);
                    fscanf(archivo,"%s",nombre);
                    fscanf(archivo,"%s",stock);

                    carro.SKU = sku;
                    carro.nombre = nombre;
                    carro.cantidad = atoi(stock);

                    carroCompra = ingresarCarroCompra(carro,(CantidadCarroCompra(carroCompra)+1),carroCompra);
                }

                fflush(archivo);
                fclose(archivo);
            }
        }else{
            remove(ruta);
        }
    }

    return carroCompra;
}

void SelProductos(ListaProd *productos, ListaCarroCompra *carroCompra, int ini, int fin){
    short ret;
    int cant_prod_cc,cant_prod;
    char sel,*msg;

    cant_prod = CantidadProd(productos);
    cant_prod_cc = CantidadCarroCompra(carroCompra);

    InicioPrograma();
    Titulo("Seleccionar Productos", '*', 5);
    printf("cantidad de productos: %i", cant_prod);
    printf("\ncantidad de productos en Carro Compra: %i\n\n", cant_prod_cc);

    fin = (fin == 0 ? limite : fin);
    MostrarProductos(productos, ini, fin);

    if(cant_prod > 0){
        printf("\n\nSeleccione:\n");

        if(fin > limite){
            printf("\n- [A]nterior");
        }

        if(fin < productos->ultimo){
            printf("\n- [S]iguiente");
        }

        printf("\n- Agregar [P]roducto");
    }

    printf("\n- [V]olver\n");
    printf("\nSeleccion: ");
    fflush(stdin);
    scanf("%c", &sel);

    if((sel == 'A') || (sel == 'a')){
        fin = (ini == 0 ? limite : ini);
        ini = (ini - limite < 0 ? 0 : (ini - limite));
        //fin = ((fin % limite) != 0 ? (fin - (ini % limite)) : (fin - limite));
        SelProductos(productos, carroCompra, ini, fin);
    }else if((sel == 'S') || (sel == 's')){
        ini = (fin % limite != 0 ? (fin - (fin %limite)) : fin);
        fin = ((fin + limite) > productos->ultimo ? productos->ultimo : (fin + limite));
        SelProductos(productos, carroCompra, ini, fin);
    }else if((sel == 'P') || (sel == 'p')){
        msg = (char *) malloc(100 * sizeof(char));

        carroCompra = AgregarProdCarroCompra(productos, carroCompra, &ret, msg);

        if(ret){
            SelProductos(productos, carroCompra, ini, fin);
        }else{
            VolverMenuCarroCompra(msg, "sel", productos, carroCompra);
        }
    }else if((sel == 'V') || (sel == 'v')){
        MenuComprador(productos, carroCompra, "");
    }else{
        VolverMenuCarroCompra("Opcion no valida", "sel", productos, carroCompra);
    }
}

ListaCarroCompra * AgregarProdCarroCompra(ListaProd *productos, ListaCarroCompra *carroCompra, short *ret, char *msg){
    char *sku,cant[max_stock];
    int pos_prod,pos_cc;
    DatosProd producto,*prod;
    DatosCarroCompra prod_carro_compra, *prod_cc;

    sku = (char *) malloc(max_sku * sizeof(char));

    printf("\n\nIngrese el SKU del Producto: ");
    fflush(stdin);
    gets(sku);
    //scanf("%s", sku);
    StrUpper(sku);

    producto.SKU = sku;
    pos_prod = localizarProd(producto, productos);

    if(pos_prod > 0){
        prod = recuperarProd(pos_prod,productos);

        printf("\n\nDatos Producto:\n");
        printf("- sku: %s\n", prod->SKU);
        printf("- nombre: %s\n", prod->nombre);
        printf("- stock: %i\n", prod->stock);

        printf("\n\nIngrese la cantidad: ");
        fflush(stdin);
        scanf("%s", cant);

        if(PreguntaSINO("\n\nSeguro que Desea Agregar el producto?")){
            if(valIngCarroCompra(sku, cant, prod->stock, msg)){
                prod_carro_compra.SKU = prod->SKU;
                prod_carro_compra.nombre = prod->nombre;
                prod_carro_compra.cantidad = atoi(cant);

                pos_cc = localizarCarroCompra(prod_carro_compra, carroCompra);

                if(pos_cc > 0){
                    prod_cc = recuperarCarroCompra(pos_cc, carroCompra);

                    prod_carro_compra.SKU = prod_cc->SKU;
                    prod_carro_compra.nombre = prod_cc->nombre;
                    prod_carro_compra.cantidad = prod_cc->cantidad + atoi(cant);

                    carroCompra = modificarCarroCompra(pos_cc, prod_carro_compra, carroCompra);
                }else{
                    carroCompra = ingresarCarroCompra(prod_carro_compra,(CantidadCarroCompra(carroCompra)+1),carroCompra);
                }

                *ret = _TRUE;
            }else{
                *ret = _FALSE;
            }
        }else{
            *ret = _FALSE;
        }
    }else{
        strcpy(msg,"No existe el producto.");
        *ret = _FALSE;
    }

    return carroCompra;
}

void BuscarProductosCC(ListaProd *productos, ListaCarroCompra *carroCompra, int ini, int fin){
    char sel, *msg;
    int cant_prod_cc;

    msg = (char *) malloc(100 * sizeof(char));
    cant_prod_cc = CantidadCarroCompra(carroCompra);

    InicioPrograma();
    Titulo("Listado de Productos a Carro Compra", '*', 5);
    printf("cantidad de productos en Carro Compra: %i\n\n", cant_prod_cc);

    fin = (fin == 0 ? limite : fin);
    MostrarProductosCC(carroCompra, ini, fin);

    if(cant_prod_cc > 0){
        printf("\n\nSeleccione:\n");

        if(fin > limite){
            printf("\n- [A]nterior");
        }

        if(fin < carroCompra->ultimo){
            printf("\n- [S]iguiente");
        }
    }

    printf("\n- [V]olver\n");
    printf("\nSeleccion: ");
    fflush(stdin);
    scanf("%c", &sel);

    if((sel == 'A') || (sel == 'a')){
        fin = (ini == 0 ? limite : ini);
        ini = (ini - limite < 0 ? 0 : (ini - limite));
        BuscarProductosCC(productos, carroCompra, ini, fin);
    }else if((sel == 'S') || (sel == 's')){
        ini = (fin % limite != 0 ? (fin - (fin %limite)) : fin);
        fin = ((fin + limite) > carroCompra->ultimo ? carroCompra->ultimo : (fin + limite));
        BuscarProductosCC(productos, carroCompra, ini, fin);
    }else if((sel == 'V') || (sel == 'v')){
        MenuComprador(productos, carroCompra, "");
    }else{
        VolverMenuCarroCompra("Opcion no valida", "bus", productos, carroCompra);
    }
}

void ModificarProductosCC(ListaProd *productos, ListaCarroCompra *carroCompra){
    int cant_prod_cc,pos;
    char sku[max_sku], st[max_stock];
    DatosCarroCompra productoCC,*prodCC;

    cant_prod_cc = CantidadCarroCompra(carroCompra);

    InicioPrograma();
    Titulo("Modificar Productos Carro Compra", '*', 5);
    printf("cantidad de productos en Carro Compra: %i", cant_prod_cc);

    printf("\n\nIngrese el SKU del Producto a Modificar: ");
    fflush(stdin);
    gets(sku);

    StrUpper(sku);
    productoCC.SKU = sku;
    pos = localizarCarroCompra(productoCC, carroCompra);

    if(pos > 0){
        prodCC = recuperarCarroCompra(pos,carroCompra);

        printf("\n\nproducto a modificar:\n");
        printf("- sku: %s\n", prodCC->SKU);
        printf("- nombre: %s\n", prodCC->nombre);
        printf("- stock: %i\n", prodCC->cantidad);

        printf("\n\nIngrese la cantidad: ");
        fflush(stdin);
        scanf("%s", st);

        if(PreguntaSINO("\n\nSeguro que Desea Modificar el producto?")){
            if(IsEnTero(st)){
                productoCC.SKU = prodCC->SKU;
                productoCC.nombre = prodCC->nombre;
                productoCC.cantidad = atoi(st);

                modificarCarroCompra(pos,productoCC,carroCompra);
                VolverMenuCarroCompra("Modificado", "modificar", productos, carroCompra);
            }else{
                VolverMenuCarroCompra("la cantidad debe ser numerico", "modificar", productos, carroCompra);
            }
        }else{
            VolverMenuCarroCompra("", "modificar", productos, carroCompra);
        }
    }else{
        VolverMenuCarroCompra("No existe el producto.", "modificar", productos, carroCompra);
    }
}

void EliminarProductoCC(ListaProd *productos, ListaCarroCompra *carroCompra){
    char sku[10];
    int pos,cant_prod_cc;
    DatosCarroCompra productoCC,*prodCC;

    cant_prod_cc = CantidadProd(productos);

    InicioPrograma();
    Titulo("Eliminar Productos", '*', 5);
    printf("cantidad de productos: %i", cant_prod_cc);

    printf("\n\nIngrese el SKU del Producto a Eliminar: ");
    fflush(stdin);
    gets(sku);

    StrUpper(sku);
    productoCC.SKU = sku;
    pos = localizarCarroCompra(productoCC, carroCompra);

    if(pos > 0){
        if(localizarCarroCompra(productoCC, carroCompra) > 0){
            prodCC= recuperarCarroCompra(pos,carroCompra);

            printf("\n\nproducto a Eliminar:\n");
            printf("- sku: %s\n", prodCC->SKU);
            printf("- nombre: %s\n", prodCC->nombre);
            printf("- stock: %i\n", prodCC->cantidad);

            if(PreguntaSINO("\n\nSeguro que Desea Eliminar el producto?")){
                carroCompra = eliminarCarroCompra(carroCompra, pos);
                VolverMenuCarroCompra("Eliminado", "eliminar", productos, carroCompra);
            }else{
                VolverMenuCarroCompra("", "eliminar", productos, carroCompra);
            }
        }else{
            VolverMenuCarroCompra("no existe el producto en el carro de compra", "eliminar", productos, carroCompra);
        }
    }else{
        VolverMenuCarroCompra("No existe el producto.", "eliminar", productos, carroCompra);
    }
}

int MostrarProductosCC(ListaCarroCompra *carroCompra, int ini, int fin){
    int i=0;
    NodoCarroCompra *aux = carroCompra->inicial;

    if(aux == NULL){
        printf("\n\nNo hay productos.\n\n");
    }else{
        for(i=0;i<ini;i++){
            aux = aux->sgte;
        }

        printf("SKU - nombre - stock\n\n");

        for(i=ini;i<fin;i++){
            if(aux != NULL){
                printf("%i.- %s\t\t%s\t\t\t\t%i\n", (i+1), aux->elem.SKU, aux->elem.nombre, aux->elem.cantidad);
                aux = aux->sgte;
            }else{
                break;
            }
        }
    }

    return i;
}

void ComprarProductosCC(ListaProd *productos, ListaCarroCompra *carroCompra, char *usuario){
    int cant_prod_cc = CantidadCarroCompra(carroCompra);
    char *msg;

    msg = (char *) malloc(100 * sizeof(char));

    InicioPrograma();
    Titulo("Comprar Productos Carro Compra", '*', 5);
    printf("cantidad de productos en Carro Compra: %i", cant_prod_cc);

    if(cant_prod_cc > 0){
        if(PreguntaSINO("\n\nSeguro que Desea Comprar los productos?")){
            if(ValidaCompraCC(productos,carroCompra,msg)){
                CompraProductos(productos,carroCompra);
                GuardarProdCompradoArch(carroCompra, usuario);
                carroCompra = vaciarCarroCompra(carroCompra);
                eliminarArchCC(usuario);
                MenuComprador(productos, carroCompra, "Compra realizada.");
            }else{
                MenuComprador(productos, carroCompra, msg);
            }
        }else{
            MenuComprador(productos, carroCompra, "");
        }
    }else{
        MenuComprador(productos, carroCompra, "No existen productos para comprar.");
    }
}

void CompraProductos(ListaProd *productos, ListaCarroCompra *carroCompra){
    int pos;
    NodoCarroCompra *aux = carroCompra->inicial;
    DatosProd producto,*prod;

    while(aux != NULL){
        producto.SKU = aux->elem.SKU;
        pos = localizarProd(producto, productos);
        prod = recuperarProd(pos,productos);

        producto.SKU = aux->elem.SKU;
        producto.nombre = aux->elem.nombre;
        producto.stock = (prod->stock - aux->elem.cantidad);

        productos = modificarProd(pos,producto,productos);
        aux = aux->sgte;
    }
}

void eliminarArchCC(char *user){
    char *ruta;

    ruta = (char *) malloc((_DIM_RUTA_CARRO_COMPRA + 17 + strlen(user)) * sizeof(char));

    strcpy(ruta,"");
    strcat(ruta,_RUTA_CARRO_COMPRA);
    strcat(ruta,"carro_compra_");
    strcat(ruta,user);
    strcat(ruta,".txt");

    if(ExisteArchivo(ruta)){
        remove(ruta);
    }
}

void GuardarProdCompradoArch(ListaCarroCompra *carroCompra, char *usuario){
    char stock[max_stock],*fecha,*ruta=NULL;
    NodoCarroCompra *aux = carroCompra->inicial;
    FILE *archivo;

    ruta = (char *) malloc((_DIM_RUTA_COMPRA + 11 + strlen(usuario)) * sizeof(char));
    fecha = ObtenerFechaFormateada();

    strcpy(ruta,"");
    strcat(ruta,_RUTA_COMPRA);
    strcat(ruta,"compra_");
    strcat(ruta,usuario);
    strcat(ruta,".txt");

    archivo = fopen(ruta,"a");
    if(archivo != NULL){
        while(aux != NULL){
            itoa(aux->elem.cantidad, stock, 10);

            fputs(aux->elem.SKU,archivo);
            fputc('\t',archivo);
            fputs(aux->elem.nombre,archivo);
            fputc('\t',archivo);
            fputs(stock,archivo);
            fputc('\t',archivo);
            fputs(fecha,archivo);
            fputc('\n',archivo);

            aux = aux->sgte;
        }


        fflush(archivo);
        fclose(archivo);
    }
}

void GuardarProdCCArch(ListaCarroCompra *carroCompra, char *usuario){
    char stock[10],*ruta=NULL;
    NodoCarroCompra *aux = carroCompra->inicial;
    FILE *archivo=NULL;

    ruta = (char *) malloc((_DIM_RUTA_CARRO_COMPRA + 17 + strlen(usuario)) * sizeof(char));

    strcpy(ruta,"");
    strcat(ruta,_RUTA_CARRO_COMPRA);
    strcat(ruta,"carro_compra_");
    strcat(ruta,usuario);
    strcat(ruta,".txt");

    if(aux != NULL){
        archivo = fopen(ruta,"w");
    }

    if(archivo != NULL){
        while(aux != NULL){
            itoa(aux->elem.cantidad, stock, 10);

            fputs(aux->elem.SKU,archivo);
            fputc('\t',archivo);
            fputs(aux->elem.nombre,archivo);
            fputc('\t',archivo);
            fputs(stock,archivo);

            if(aux->sgte != NULL){
                fputc('\n',archivo);
            }

            aux = aux->sgte;
        }

        fflush(archivo);
        fclose(archivo);
    }
}

short valIngCarroCompra(char *sku, char *cantidad, int cantProd, char *msg){
    strcpy(msg,"");

    if(strlen(sku) < 1){
        strcpy(msg,"sku es obligatorio.");
        return _FALSE;
    }

    if(strlen(sku) > 10){
        strcpy(msg,"sku debe tener a lo mas 10 digito.");
        return _FALSE;
    }

    if(strlen(cantidad) < 1){
        strcpy(msg,"la cantidad es obligatorio.");
        return _FALSE;
    }

    if(!IsEnTero(cantidad)){
        strcpy(msg,"la cantidad debe ser numerico.");
        return _FALSE;
    }

    if(atoi(cantidad) > cantProd){
        strcpy(msg,"La cantidad de productos es inferior a la solicitada.");
        return _FALSE;
    }

    return _TRUE;
}

short ValidaCompraCC(ListaProd *productos, ListaCarroCompra *carroCompra, char *msg){
    int pos;
    short ret;
    NodoProd *aux = carroCompra->inicial;
    DatosProd producto,*prod;

    while(aux != NULL){
        producto.SKU = aux->elem.SKU;
        pos = localizarProd(producto, productos);

        if(pos > 0){
            prod = recuperarProd(pos,productos);

            if(prod->stock >= aux->elem.stock){
                ret = _TRUE;
            }else{
                ret = _FALSE;
                strcpy(msg,"Producto ");
                strcat(msg, aux->elem.nombre);
                strcat(msg, " con menor stock.");
                break;
            }
        }else{
            ret = _FALSE;
            strcpy(msg,"Producto ");
            strcat(msg, aux->elem.SKU);
            strcat(msg, " no existe en la lista.");
            break;
        }

        aux = aux->sgte;
    }

    return ret;
}
