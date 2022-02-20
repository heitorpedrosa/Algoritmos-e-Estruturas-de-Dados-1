#ifndef ED_H
#define ED_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct arrayqueue {
    int frente;
    int tras;
    int* elementos;
    int tamanho;
    int qtdade;
};

struct arrayqueue* inicializar ( int tamArray ) {
    struct arrayqueue* fila = ( struct arrayqueue* ) malloc ( sizeof ( struct arrayqueue ) );
    fila -> frente = -1;
    fila -> tras = -1;
    fila -> elementos = ( int* ) calloc ( tamArray, sizeof ( int ) );
    fila -> tamanho = tamArray;
    fila -> qtdade = 0;
    return fila;
}

void enfileirar ( struct arrayqueue** fila, int val ) {
    if ( ( *fila ) == NULL ) {
        ( *fila ) = inicializar ( 10 );
        ( *fila ) -> frente++;
        ( *fila ) -> tras++;
        ( *fila ) -> elementos [ ( *fila ) -> tras ] = val;
        ( *fila ) -> qtdade++;
    }
    else if ( ( *fila ) -> qtdade == 0 ) {
        ( *fila ) -> frente++;
        ( *fila ) -> tras++;
        ( *fila ) -> elementos [ ( *fila ) -> tras ] = val;
        ( *fila ) -> qtdade++;
    }
    else if ( ( ( *fila ) -> tras + 1 ) % ( *fila ) -> tamanho == ( *fila ) -> frente ) return;
    else {
        ( *fila ) -> tras++;
        ( *fila ) -> elementos [ ( *fila ) -> tras ] = val;
        ( *fila ) -> qtdade++;
    }
}

int desenfileirar ( struct arrayqueue* fila ) {
    if ( fila == NULL || fila -> qtdade == 0 ) return INT_MIN;
    else {
        int valor = fila -> elementos [ fila -> frente ];
        fila -> frente++;
        fila -> qtdade--;
        return valor;
    }
}

int frente ( struct arrayqueue* fila ) {
    if ( fila == NULL || fila -> qtdade == 0 ) return INT_MIN;
    else return fila -> elementos [ fila -> frente ];
}

#endif // ED_H
