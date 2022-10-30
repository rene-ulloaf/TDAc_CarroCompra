#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "productos.h"
#include "carro_compra.h"
#include "estructuras.h"
#include "TDAListaProd.h"
#include "TDAListaCarroCompra.h"
#include "recursos.h"
#include "menu.h"

char *usuario=NULL, *password=NULL;

int main(){
    MenuPrincipal("");

    return 0;
}

void MenuPrincipal(char *msg){
    char sel, tipo_usuario, *mess;
    ListaProd *lp = NULL;
    ListaCarroCompra *cc = NULL;

    mess = (char *) malloc(100 * sizeof(char));

    InicioPrograma();
    Titulo("Tipo Usuario", '*', 5);

    if(strlen(msg) > 0){
        printf("\n%s\n\n", msg);
    }

    Menu("I", "Iniciar Sesion");
    Menu("S", "Salir");

    printf("Opcion: ");
    fflush(stdin);
    scanf("%c", &sel);

    if((sel == 'I') || (sel == 'i')){
        usuario = (char *) malloc(max_nom_usuario * sizeof(char));
        password = (char *) malloc(max_pass * sizeof(char));

        LimpiaPantalla();
        if(InicioSesion(&tipo_usuario, mess)){
            if(tipo_usuario == 'A' || tipo_usuario == 'a'){
                LimpiaPantalla();
                MenuAdministrador(lp,_FALSE);
            }else if(tipo_usuario == 'C' || tipo_usuario == 'c'){
                LimpiaPantalla();
                MenuComprador(lp, cc, "");
            }else{
                LimpiaPantalla();
                MenuPrincipal( mess);
            }
        }else{
            LimpiaPantalla();
            printf("nombre de usuario y/o password invalidos");
            MenuPrincipal( mess);
        }
    }else if((sel == 'S') || (sel == 's')){
        Salir();
    }else{
        MenuPrincipal("Opcion no permitida");
    }
}

short InicioSesion(char *tipo_usuario, char *msg){
    char *user=NULL,*pass=NULL,aux[1],*user_arch=NULL,*pass_arch=NULL,dir[_DIM_RUTA + 12] = {""};
    short ret=_FALSE;
    FILE *archivo;

    user = (char *) malloc(max_nom_usuario * sizeof(char));
    pass = (char *) malloc(max_pass * sizeof(char));
    user_arch = (char *) malloc(max_nom_usuario * sizeof(char));
    pass_arch = (char *) malloc(max_pass * sizeof(char));

    strcat(dir,"");
    strcat(dir,_RUTA);
    strcat(dir,"usuarios.txt");

    InicioPrograma();
    Titulo("Inicio Sesion", '*', 5);

    printf("\n\nNombre Usuario: ");
    fflush(stdin);
    scanf("%s", user);

    printf("\npassword: ");
    fflush(stdin);
    scanf("%s", pass);

    archivo = fopen(dir,"r");
    if(archivo != NULL){
        while(!feof(archivo) && fread(aux,1,1,archivo)){
            fseek(archivo,-1, SEEK_CUR);

            fscanf(archivo,"%s",user_arch);
            fscanf(archivo,"%s",pass_arch);

            StrUpper(user);
            StrUpper(user_arch);

            if((strcmp(user, user_arch) == 0) && (strcmp(pass, pass_arch) == 0)){
                strcpy(usuario, user_arch);
                strcpy(password, pass_arch);
                fscanf(archivo,"%s",tipo_usuario);

                ret = _TRUE;
                strcpy(msg,"");
                break;
            }else{
                strcpy(msg,"Nombre de usuario y/o contraseña invalidas");
                fscanf(archivo,"%s",tipo_usuario);
            }
        }
    }else{
        ret = _FALSE;
        strcpy(msg,"No existe el Archivo");
    }

    return ret;
}

void MenuAdministrador(ListaProd *productos, short op){
    char sel;

    InicioPrograma();
    Titulo("Menu Administrador", '*', 3);

    if(op){
        printf("\nOpcion no permitida\n\n");
    }

    if(productos == NULL){
        productos = creaListaProd();
        productos = ObtenerProductos(productos);
    }

    Menu("1", "Ver Productos.");
    Menu("2", "Agregar Productos.");
    Menu("3", "Modificar Producto.");
    Menu("4", "Eliminar Productos.");
    Menu("5", "Agregar Usuarios.");
    Menu("6", "Cerrar Sesion.");

    printf("Opcion: ");
    fflush(stdin);
    scanf("%c", &sel);

    if(sel == '1'){
        LimpiaPantalla();
        VerProductos(productos, 0, 0);
    }else if(sel == '2'){
        LimpiaPantalla();
        AgregarProducto(productos);
    }else if(sel == '3'){
        LimpiaPantalla();
        ModificarProducto(productos);
    }else if(sel == '4'){
        LimpiaPantalla();
        EliminarProducto(productos);
    }else if(sel == '5'){
        LimpiaPantalla();
        creaUsuario(productos);
    }else if(sel == '6'){
        LimpiaPantalla();
        GuardarProdArch(productos);
        productos = vaciarProductos(productos);
        MenuPrincipal("");
    }else{
        LimpiaPantalla();
        MenuAdministrador(productos, _FALSE);
    }
}

void MenuComprador(ListaProd *productos, ListaCarroCompra *carroCompra, char *msg){
    char sel;

    InicioPrograma();
    Titulo("Menu Comprador", '*', 3);

    if(strlen(msg) > 0){
        printf("\n%s\n\n", msg);
    }

    if(carroCompra == NULL){
        productos = creaListaProd();
        carroCompra = creaListaCarroCompra();
        productos = ObtenerProductos(productos);
        carroCompra = ObtenerCC(carroCompra, usuario);
        if(carroCompra->ultimo > 0){
            MenuComprador(productos, carroCompra, "Carro Compra Agregado");
        }else{
            MenuComprador(productos, carroCompra, "");
        }
    }else{
        Menu("1", "Seleccionar Productos.");
        Menu("2", "Buscar Productos Carro Compra.");
        Menu("3", "Modificar Producto Carro Compra.");
        Menu("4", "Eliminar Producto Carro Compra.");
        Menu("5", "Comprar.");
        Menu("6", "Cerrar Sesion.");

        printf("Opcion: ");
        fflush(stdin);
        scanf("%c", &sel);

        if(sel == '1'){
            LimpiaPantalla();
            SelProductos(productos, carroCompra, 0, 0);
        }else if(sel == '2'){
            LimpiaPantalla();
            BuscarProductosCC(productos, carroCompra, 0, 0);
        }else if(sel == '3'){
            LimpiaPantalla();
            ModificarProductosCC(productos, carroCompra);
        }else if(sel == '4'){
            LimpiaPantalla();
            EliminarProductoCC(productos, carroCompra);
        }else if(sel == '5'){
            LimpiaPantalla();
            ComprarProductosCC(productos, carroCompra, usuario);
        }else if(sel == '6'){
            LimpiaPantalla();
            GuardarProdCCArch(carroCompra, usuario);
            GuardarProdArch(productos);
            carroCompra = vaciarCarroCompra(carroCompra);
            productos = vaciarProductos(productos);
            MenuPrincipal("");
        }else{
            LimpiaPantalla();
            MenuComprador(productos, carroCompra, "Opcion no permitida");
        }
    }
}
