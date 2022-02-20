#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

struct noBst* alocarNovoNo ( int val ) {
    struct noBst* novoNo = ( struct noBst* ) malloc ( sizeof ( struct noBst ) );
    novoNo -> esq = NULL;
    novoNo -> dir = NULL;
    novoNo -> val = val;
    return novoNo;
}

void inserir ( struct noBst** raiz, int val, int* tamanho ) {
    if ( *raiz == NULL ) *raiz = alocarNovoNo ( val );
    else if ( ( *raiz ) -> val > val ) inserir ( &( *raiz ) -> esq, val, tamanho );
    else inserir ( &( *raiz ) -> dir, val, tamanho );

    if ( ( *raiz ) -> dir == NULL && ( *raiz ) -> esq == NULL ) ( *tamanho )++;
}

bool buscar ( struct noBst* raiz, int val ) {
    if ( raiz == NULL ) return false;
    if ( raiz -> val == val ) return raiz;
    if ( raiz -> val > val ) return buscar ( raiz -> esq, val );
    return buscar ( raiz -> dir, val );
}

int max ( struct noBst* raiz ) {
    if ( raiz == NULL ) return 0;
    if ( raiz -> dir == NULL ) return raiz -> val;
    return max ( raiz -> dir );
}

int min ( struct noBst* raiz ) {
    if ( raiz == NULL ) return 0;
    if ( raiz -> esq == NULL ) return raiz -> val;
    return min ( raiz -> esq );
}

int altura ( struct noBst* raiz ) {
    if ( raiz == NULL || ( raiz -> esq == NULL && raiz -> dir == NULL ) ) return 0;

    int esq = altura ( raiz -> esq );
    int dir = altura ( raiz -> dir );

    if ( esq > dir ) return esq + 1;
    else return dir + 1;
}

void emOrdem ( struct noBst* raiz ) {
    if ( raiz == NULL ) return;

    emOrdem ( raiz -> esq );
    printf ( "%d ", raiz -> val );
    emOrdem ( raiz -> dir );
}

void preOrdem ( struct noBst* raiz ) {
    if ( raiz == NULL ) return;

    printf ( "%d ", raiz -> val );
    preOrdem ( raiz -> esq );
    preOrdem ( raiz -> dir );
}

void posOrdem ( struct noBst* raiz ) {
    if ( raiz == NULL ) return;

    posOrdem ( raiz -> esq );
    posOrdem ( raiz -> dir );
    printf ( "%d ", raiz -> val );
}

struct noBst* remover ( struct noBst* raiz, int val, int* tamanho ) {
    //Está faltando diminuir o tamanho da árvore
    if ( raiz == NULL ) return raiz;

    if ( raiz -> val > val ) raiz -> esq = remover ( raiz -> esq, val, tamanho );
    else if ( raiz -> val < val ) raiz -> dir = remover ( raiz -> dir, val, tamanho );
    else {
        struct noBst* aux = NULL;
        if ( raiz -> esq == NULL ) {
            aux = raiz -> dir;
            free ( raiz );
            return aux;
        }
        else if ( raiz -> dir == NULL ) {
            aux = raiz -> esq;
            free ( raiz );
            return aux;
        }

        aux = raiz -> dir;
        while ( aux -> esq != NULL ) aux = aux -> esq;

        raiz -> val = aux -> val;
        raiz -> dir = remover ( raiz -> dir, aux -> val, tamanho );
    }
    return raiz;
}

#endif // BST_H
