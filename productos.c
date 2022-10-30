#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "productos.h"
#include "estructuras.h"
#include "TDAListaProd.h"
#include "menu.h"
#include "recursos.h"

const short lim = 10;

void VolverMenuProd(char *msg, char *fx, ListaProd *productos){
    char vm;

    InicioPrograma();
    printf("\n\n");
    printf("%s\n\n %cDesea volver al Menu? [S/N]. " ,msg ,168);
    fflush(stdin);
    scanf("%s", &vm);

    if(vm == 'S' || vm == 's'){
        MenuAdministrador(productos, _FALSE);
    }else{
        if(strcmp(fx,"user") == 0){
            creaUsuario(productos);
        }

        if(strcmp(fx,"ver") == 0){
            VerProductos(productos,0 ,0);
        }

        if(strcmp(fx,"agregar") == 0){
            AgregarProducto(productos);
        }

        if(strcmp(fx,"modificar") == 0){
            ModificarProducto(productos);
        }

        if(strcmp(fx,"eliminar") == 0){
            EliminarProducto(productos);
        }
    }
}

void creaUsuario(ListaProd *productos){
    char *user=NULL,*pass=NULL,tipo[1]={""};

    user = (char *) malloc(25 * sizeof(char));
    pass = (char *) malloc(6 * sizeof(char));

    InicioPrograma();
    Titulo("Cracion de Usuarios", '*', 5);

    printf("\n\nIngrese el nombre de usuario (max. 25 digitos): ");
    fflush(stdin);
    //gets(user);
    scanf("%s", user);

    printf("\n\nIngrese el password (max 6 digitos): ");
    fflush(stdin);
    //gets(pass);
    scanf("%s", pass);

    printf("\n\nIndique el tipo de usuario:\n");
    printf("[A]dministrador:\n");
    printf("[C]omprador:\n");
    printf("Seleccion: ");
    fflush(stdin);
    scanf("%s", tipo);

    if(strlen(user) < 1){
        VolverMenuProd("Nombre de usuario es obligatorio.", "user", productos);
    }else if(strlen(user) > 25){
        VolverMenuProd("Nombre de usuario es mayor a 25.", "user", productos);
    }else if(strlen(pass) < 1){
        VolverMenuProd("Password es obligatorio.", "user", productos);
    }else if(strlen(pass) > 6){
        VolverMenuProd("Password es mayor a 6.", "user", productos);
    }else if(!(((strcmp(tipo,"a") == 0) || (strcmp(tipo,"A") == 0)) || ((strcmp(tipo,"c") == 0) || (strcmp(tipo,"C") == 0)))){
        VolverMenuProd("Tipo de usuario no existe.", "user", productos);
    }else{
        if(guardaUsuarioArch(user, pass, tipo)){
           VolverMenuProd("usuario creado correctamente.", "user", productos);
        }else{
            VolverMenuProd("Error al crear el usuario.", "user", productos);
        }
    }
}

ListaProd * ObtenerProductos(ListaProd *productos){
    char *sku, *nombre, *stock, aux[1],dir[_DIM_RUTA + 13] = {""};
    FILE *archivo;
    DatosProd producto;

    strcat(dir,"");
    strcat(dir,_RUTA);
    strcat(dir,"productos.txt");

    archivo = fopen(dir,"r");

    if(archivo != NULL){
        if(ExisteArchivo(dir)){
            while(!feof(archivo) && fread(aux,1,1,archivo)){
                fseek(archivo,-1, SEEK_CUR);

                sku = (char *) malloc(max_sku * sizeof(char));
                nombre = (char *) malloc(max_nom_prod * sizeof(char));
                stock = (char *) malloc(max_stock * sizeof(char));

                fscanf(archivo,"%s",sku);
                fscanf(archivo,"%s",nombre);
                fscanf(archivo,"%s",stock);

                producto.SKU = sku;
                producto.nombre = nombre;
                producto.stock = atoi(stock);

                productos = ingresarProd(producto,(productos->ultimo+1),productos);
            }
        }
    }

    return productos;
}

void MostrarProductos(ListaProd *productos, int ini, int fin){
    int i;
    NodoProd *aux = productos->inicial;

    if(aux == NULL){
        printf("\n\nNo hay productos.");
    }else{
        printf("SKU - nombre - stock\n\n");

        for(i=0;i<ini;i++){
            aux = aux->sgte;
        }

        for(i=ini;i<fin;i++){
            if(aux != NULL){
                printf("%i.- %s\t\t%s\t\t\t\t%i\n", (i+1), aux->elem.SKU, aux->elem.nombre, aux->elem.stock);
                aux = aux->sgte;
            }else{
                break;
            }
        }
    }
}

void VerProductos(ListaProd *productos, int ini, int fin){
    int cant_prod;
    char sel;

    cant_prod = CantidadProd(productos);

    InicioPrograma();
    Titulo("Productos", '*', 5);
    printf("cantidad de productos: %i\n\n", cant_prod);

    fin = (fin == 0 ? lim : fin);
    MostrarProductos(productos, ini, fin);

    if(cant_prod > 0){
        printf("\n\nSeleccione:\n");

        if(fin > lim){
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
        fin = (ini == 0 ? lim : ini);
        ini = (ini - lim < 0 ? 0 : (ini - lim));
        VerProductos(productos, ini, fin);
    }else if((sel == 'S') || (sel == 's')){
        ini = (fin % lim != 0 ? (fin - (fin %lim)) : fin);
        fin = ((fin + lim) > productos->ultimo ? productos->ultimo : (fin + lim));
        VerProductos(productos, ini, fin);
    }else if((sel == 'P') || (sel == 'p')){
        AgregarProducto(productos);
    }else if((sel == 'V') || (sel == 'v')){
        MenuAdministrador(productos, _FALSE);
    }else{
        VolverMenuProd("Opcion no valida.", "ver", productos);
    }
}

void AgregarProducto(ListaProd *productos){
    char *sku=NULL, *nom_prod=NULL, *st=NULL, *msg=NULL;
    int cant_prod;
    DatosProd producto;

    sku = (char *) malloc(max_sku * sizeof(char));
    nom_prod = (char *) malloc(max_nom_prod * sizeof(char));
    st = (char *) malloc(max_stock * sizeof(char));
    msg = (char *) malloc(100 * sizeof(char));
    cant_prod = CantidadProd(productos);

    InicioPrograma();
    Titulo("Ingreso de Productos", '*', 5);
    printf("cantidad de productos: %i", cant_prod);

    printf("\n\nIngrese el SKU del Producto (max. 10 digitos): ");
    fflush(stdin);
    gets(sku);
    //scanf("%s", sku);

    printf("\n\nIngrese el nombre del Producto (max %i digitos): ", max_nom_prod);
    fflush(stdin);
    gets(nom_prod);
    //sscanf("%s", nom_prod);

    printf("\n\nIngrese el stock del Producto: ");
    fflush(stdin);
    scanf("%s", st);

    if(valIngProd(productos,sku,nom_prod,st,msg)){
        QuitaEspacios(nom_prod);
        QuitaEspacios(sku);
        StrUpper(sku);

        producto.nombre = nom_prod;
        producto.SKU = sku;
        producto.stock = atoi(st);

        productos = ingresarProd(producto,(cant_prod+1),productos);

        if(CantidadProd(productos) > cant_prod){
            VolverMenuProd("Ingresado Correctamente.", "agregar", productos);
        }else{
            VolverMenuProd("Error al ingresar el producto.", "agregar", productos);
        }
    }else{
        VolverMenuProd(msg, "agregar", productos);
    }
}

void ModificarProducto(ListaProd *productos){
    char sku[max_sku],nom_prod[max_nom_prod],st[max_stock],*msg;
    int cant_prod,pos;
    DatosProd producto,*prod;

    cant_prod = CantidadProd(productos);
    msg = (char *) malloc(100 * sizeof(char));

    InicioPrograma();
    Titulo("Modificar Productos", '*', 5);
    printf("cantidad de productos: %i", cant_prod);

    printf("\n\nIngrese el SKU del Producto a Modificar: ");
    fflush(stdin);
    gets(sku);
    //scanf("%s", sku);

    StrUpper(sku);
    producto.SKU = sku;
    pos = localizarProd(producto, productos);

    if(pos > 0){
        prod = recuperarProd(pos,productos);

        printf("\n\nproducto a modificar:\n");
        printf("- sku: %s\n", prod->SKU);
        printf("- nombre: %s\n", prod->nombre);
        printf("- stock: %i\n", prod->stock);

        printf("\n\nIngrese el nombre del Producto (max %i digitos): ", max_nom_prod);
        fflush(stdin);
        gets(nom_prod);
        //scanf("%s", nom_prod);
        QuitaEspacios(nom_prod);

        printf("\n\nIngrese el stock del Producto: ");
        fflush(stdin);
        scanf("%s", st);

        if(PreguntaSINO("\n\nSeguro que Desea Modificar el producto?")){
            if(valModProd(sku,nom_prod,st,msg)){
                producto.SKU = sku;
                producto.nombre = nom_prod;
                producto.stock = atoi(st);

                modificarProd(pos,producto,productos);
                VolverMenuProd("Modificado", "modificar", productos);
            }else{
                VolverMenuProd(msg, "modificar", productos);
            }
        }else{
            VolverMenuProd("", "modificar", productos);
        }
    }else{
        VolverMenuProd("No existe el producto.", "modificar", productos);
    }
}

void EliminarProducto(ListaProd *productos){
    char sku[10];
    int pos,cant_prod;
    DatosProd producto,*prod;

    cant_prod = CantidadProd(productos);

    InicioPrograma();
    Titulo("Eliminar Productos", '*', 5);
    printf("cantidad de productos: %i", cant_prod);

    printf("\n\nIngrese el SKU del Producto a Eliminar: ");
    fflush(stdin);
    gets(sku);

    StrUpper(sku);
    producto.SKU = sku;
    pos = localizarProd(producto, productos);

    if(pos > 0){
        if(localizarProd(producto, productos) > 0){
            prod = recuperarProd(pos,productos);

            printf("\n\nproducto a Eliminar:\n");
            printf("- sku: %s\n", prod->SKU);
            printf("- nombre: %s\n", prod->nombre);
            printf("- stock: %i\n", prod->stock);

            if(PreguntaSINO("\n\nSeguro que Desea Eliminar el producto?")){
                productos = eliminarProd(productos, pos);
                VolverMenuProd("Eliminado", "eliminar", productos);
            }
        }else{
            VolverMenuProd("", "eliminar", productos);
        }
    }else{
        VolverMenuProd("No existe el producto.", "eliminar", productos);
    }
}

void GuardarProdArch(ListaProd *productos){
    char stock[10],ruta[_DIM_RUTA + 13] = {""};
    NodoProd *aux = productos->inicial;
    FILE *archivo;

    strcpy(ruta,"");
    strcat(ruta,_RUTA);
    strcat(ruta,"productos.txt");

    archivo = fopen(ruta,"w");
    if(archivo != NULL){
        while(aux != NULL){
            itoa(aux->elem.stock, stock, 10);

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

short guardaUsuarioArch(char *u, char *p, char* t){
    char ruta[_DIM_RUTA + 12] = {""};
    FILE *archivo;

    strcpy(ruta,"");
    strcat(ruta,_RUTA);
    strcat(ruta,"usuarios.txt");

    archivo = fopen(ruta,"a");
    if(archivo != NULL){
        fputs(u,archivo);
        fputc('\t',archivo);
        fputs(p,archivo);
        fputc('\t',archivo);
        StrUpper(t);
        fputs(t,archivo);
        fputc('\n',archivo);

        fflush(archivo);
        fclose(archivo);
    }else{
        return _FALSE;
    }

    return _TRUE;
}

short valIngProd(ListaProd *productos, char *sku, char *nom_prod, char *stock, char *msg){
    NodoProd *aux = productos->inicial;
    DatosProd producto;

    strcpy(msg,"");
    producto.SKU = sku;

    if(strlen(sku) < 1){
        strcpy(msg,"sku es obligatorio.");
        return _FALSE;
    }

    if(strlen(sku) > max_sku){
        strcpy(msg,"sku debe tener a lo mas 10 digito.");
        return _FALSE;
    }

    while(aux != NULL){
        if(localizarProd(producto,productos) > 0){
            strcpy(msg,"SKU ya existe.");
            return _FALSE;
        }
        aux = aux->sgte;
    }

    if(strlen(nom_prod) < 1){
        strcpy(msg,"nombre del producto es obligatorio.");
        return _FALSE;
    }

    if(strlen(nom_prod) > max_nom_prod){
        strcpy(msg,"nombre del producto debe tener a lo mas 100 digito.");
        return _FALSE;
    }

    if(strlen(stock) < 1){
        strcpy(msg,"stock es obligatorio.");
        return _FALSE;
    }

    if(!IsEnTero(stock)){
        strcpy(msg,"stock debe ser numerico.");
        return _FALSE;
    }

    if(atoi(stock) > 99999999){
        strcpy(msg,"stock debe ser menor a 99.999.999.");
        return _FALSE;
    }

    return _TRUE;
}

short valModProd(char *sku, char *nom_prod, char *stock, char *msg){
    strcpy(msg,"");

    if(strlen(sku) < 1){
        strcpy(msg,"sku es obligatorio.");
        return _FALSE;
    }

    if(strlen(sku) > max_sku){
        strcpy(msg,"sku debe tener a lo mas 10 digito.");
        return _FALSE;
    }

    if(strlen(nom_prod) < 1){
        strcpy(msg,"nombre del producto es obligatorio.");
        return _FALSE;
    }

    if(strlen(nom_prod) > max_nom_prod){
        strcpy(msg,"nombre del producto debe tener a lo mas 100 digito.");
        return _FALSE;
    }

    if(strlen(stock) < 1){
        strcpy(msg,"stock es obligatorio.");
        return _FALSE;
    }

    if(!IsEnTero(stock)){
        strcpy(msg,"stock debe ser numerico.");
        return _FALSE;
    }

    if(atoi(stock) > 99999999){
        strcpy(msg,"stock debe ser menor a 99.999.999.");
        return _FALSE;
    }

    return _TRUE;
}
