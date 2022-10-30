#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "recursos.h"

void LimpiaPantalla(){
    /*int i=0;

    for(i=1;i<40;i++){
        printf("\n");
    }*/
    system("cls");
}

void Salir(){
    LimpiaPantalla();
}

short ExisteArchivo(char *direccion){
    int ret;
    FILE *archivo;

    archivo = fopen(direccion,"r");

    if(archivo == NULL){
        ret = _FALSE;
    }else{
        ret = _TRUE;
    }

    if(ret){
        fflush(archivo);
        fclose(archivo);
    }

    return ret;
}

int TamArch(char *direccion){
    int tam;
    FILE *fich;

    fich = fopen(direccion,"r");
    fseek(fich, 0L, SEEK_END);
    tam = ftell(fich);
    fclose(fich);

    return tam;
}

short IsEnTero(char *n){
    int i,cant = strlen(n);
    short ret=_TRUE;

    for(i=0;i<cant;i++){
        if(n[i]<48 || n[i]>57){
            ret = _FALSE;
            break;
        }
    }

    return ret;
}

short ComparaStr(char *str1, char *str2, int desde, int hasta){
    short ret=_TRUE;
    int i;

    for(i=desde;i<hasta;i++){
        if(str1[i] != str2[i]){
            ret = _FALSE;
            break;
        }
    }

    return ret;
}

void StrUpper(char *str){
    short car,i;
    char *cad;

    car = strlen(str);
    cad = (char *) malloc(car * sizeof(char));

    for(i=0;i<car;i++){
        str[i] = toupper(str[i]);
    }
}

void QuitaEspacios(char *str){
    int i,lon;
    lon = strlen(str);

    for(i=0;i<lon;i++){
        if(str[i] == ' '){
            str[i] = '_';
        }
        if(str[i] == -56){
            str[i] = '_';
        }
        if(str[i] == '\"'){
            str[i] = '_';
        }
        if(str[i] == '>'){
            str[i] = '_';
        }
    }
}

short PreguntaSINO(char *msg){
    char *resp,ret=_FALSE;

    resp = (char *) malloc(2 * sizeof(char));

    printf("%s [S/N]: ", msg);
    fflush(stdin);
    scanf("%s", resp);

    if(strlen(resp) == 1){
        if((strcmp(resp,"S") == 0) || (strcmp(resp,"s") == 0)){
            ret = _TRUE;
        }else if((strcmp(resp,"N") == 0) || (strcmp(resp,"n") == 0)){
            ret = _FALSE;
        }else{
            /*resp = NULL;*/
            free(resp);

            printf("respuesta no valida.");
            PreguntaSINO(msg);
        }
    }else{
        free(resp);

        printf("respuesta no valida.");
        PreguntaSINO(msg);
    }

    /*resp = NULL;*/
    free(resp);

    return ret;
}

char * ObtenerFechaFormateada(){
    time_t tiempo = time(0);
    char *f;//[128];
    f = (char *) malloc(sizeof(char)* 128);

    struct tm *tlocal = localtime(&tiempo);
    strftime(f,128,"%d-%m-%Y %H:%M:%S",tlocal);
    //printf("La hora local es: %s\n",asctime(tlocal));
    //printf( "La hora y fecha locales son: %s\n", fec );

    return f;
}
