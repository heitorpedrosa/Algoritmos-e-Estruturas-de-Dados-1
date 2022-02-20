#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar () {
    struct linkedlist* lista = ( struct linkedlist* ) malloc ( sizeof ( struct linkedlist ) );
    lista -> cabeca = NULL;
    lista -> qtdade = 0;
    return lista;
}

struct no* alocarNovoNo ( int valor ) {
    struct no* novoNo = ( struct no* ) malloc ( sizeof ( struct no ) );
    novoNo -> prox = NULL;
    novoNo -> val = valor;
    return novoNo;
}

void inserirElementoNoFim ( struct linkedlist* lista, int valor ) {
    if ( lista -> qtdade == 0 ) {
        lista -> cabeca = alocarNovoNo ( valor );
        lista -> qtdade++;
    }
    else {
        struct no* aux = lista -> cabeca;
        struct no* novoNo = alocarNovoNo ( valor );
        while ( aux -> prox != NULL ) {
            aux = aux -> prox;
        }
        aux -> prox = novoNo;
        lista -> qtdade++;
    }
}

void inserirElementoNoInicio ( struct linkedlist* lista, int valor ) {
    if ( lista -> qtdade == 0 ) {
        lista -> cabeca = alocarNovoNo ( valor );
        lista -> qtdade++;
    }
    else {
        struct no* aux = alocarNovoNo ( valor );
        aux -> prox = lista -> cabeca;
        lista -> cabeca = aux;
        lista -> qtdade++;
    }
}

void inserirElementoEmPosicao ( struct linkedlist* lista, int valor, int posicao ) {
    struct no* aux1 = alocarNovoNo ( valor );
    if ( posicao == 0 ) {
        aux1 -> prox = lista -> cabeca;
        lista -> cabeca = aux1;
        lista -> qtdade++;
    }
    else {
        struct no* aux2 = lista -> cabeca;
        for ( int i = 0; i < posicao - 1; i++ ) {
            aux2 = aux2 -> prox;
        }
        aux1 -> prox = aux2 -> prox;
        aux2 -> prox = aux1;
        lista -> qtdade++;
    }
}

int obterElementoEmPosicao ( struct linkedlist* lista, int posicao ) {
    if ( posicao >= 0 && posicao < lista -> qtdade ) {
        struct no* aux = lista -> cabeca;
        for ( int i = 0; i < posicao; i++ ) {
            aux = aux -> prox;
        }
        return aux -> val;
    }
    else return INT_MIN;
}

void removerElementoEmPosicao ( struct linkedlist* lista, int posicao ) {
    if ( posicao >= 0 && posicao < lista -> qtdade ) {
        struct no* aux = lista -> cabeca;
        if ( posicao == 0 ) {
            lista -> cabeca = aux -> prox;
            free ( aux );
            lista -> qtdade--;
        }
        else {
            for ( int i = 0; aux -> prox != NULL && i < posicao - 1; i++ ) {
                aux = aux -> prox;
            }
            struct no* proximo = aux -> prox -> prox;
            free ( aux -> prox );
            aux -> prox = proximo;
            lista -> qtdade--;
        }
    }
}

void imprimirLista ( struct linkedlist* lista ) {
    if ( lista -> cabeca != NULL ) {
        struct no* aux = lista -> cabeca;
        printf( "[" );
        do {
            printf ( "%d", aux -> val );
            aux = aux -> prox;
            if ( aux != NULL ) {
                printf ( ", " );
            }
        } while ( aux != NULL );
        printf ( "]" );
    }
    else {
        printf ( "A lista está vazia!" );
    }
}
