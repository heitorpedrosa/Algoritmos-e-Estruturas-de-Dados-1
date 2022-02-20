#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct no{
    struct no *ant;
    int val;
    struct no *prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar () {
    struct doublylinkedlist* lista = ( struct doublylinkedlist* ) malloc ( sizeof ( struct doublylinkedlist ) );
    lista -> cabeca = NULL;
    lista -> cauda = NULL;
    lista -> qtdade = 0;
    return lista;
}

struct no* alocarNovoNo ( int valor ) {
    struct no* novoNo = ( struct no* ) malloc ( sizeof ( struct no ) );
    novoNo -> ant = NULL;
    novoNo -> prox = NULL;
    novoNo -> val = valor;
    return novoNo;
}

void inserirElementoNoInicio ( struct doublylinkedlist* lista, int valor ) {
    struct no* novoNo = alocarNovoNo ( valor );
    if ( lista -> cabeca == NULL ) {
        lista -> cabeca = novoNo;
        lista -> cauda = novoNo;
        lista -> cabeca -> ant = NULL;
        lista -> cauda -> prox = NULL;
    }
    else {
        lista -> cabeca -> ant = novoNo;
        novoNo -> prox = lista -> cabeca;
        novoNo -> ant = NULL;
        lista -> cabeca = novoNo;
    }
    lista -> qtdade++;
}

void inserirElementoNoFim ( struct doublylinkedlist* lista, int valor ) {
    struct no* novoNo = alocarNovoNo ( valor );
    if ( lista -> cabeca == NULL ) {
        lista -> cabeca = novoNo;
        lista -> cauda = novoNo;
        lista -> cabeca -> ant = NULL;
        lista -> cauda -> prox = NULL;
    }
    else {
        lista -> cauda -> prox = novoNo;
        novoNo -> ant = lista -> cauda;
        lista -> cauda = novoNo;
        lista -> cauda -> prox = NULL;
    }
    lista -> qtdade++;
}

void inserirElementoEmPosicao ( struct doublylinkedlist* lista, int valor, int posicao ) {
    struct no* novoNo = alocarNovoNo ( valor );
    if ( lista -> cabeca == NULL ) {
        lista -> cabeca = novoNo;
        lista -> cauda = novoNo;
        lista -> cabeca -> ant = NULL;
        lista -> cauda -> prox = NULL;
    }
    else {
        if ( posicao == 0 ) {
            lista -> cabeca -> ant = novoNo;
            novoNo -> prox = lista -> cabeca;
            novoNo -> ant = NULL;
            lista -> cabeca = novoNo;
        }
        else if ( posicao == lista -> qtdade ) {
            lista -> cauda -> prox = novoNo;
            novoNo -> ant = lista -> cauda;
            lista -> cauda = novoNo;
            lista -> cauda -> prox = NULL;
        }
        else {
            struct no* aux = lista -> cabeca;
            for ( int i = 0; aux -> prox != NULL && i < posicao - 1; i++ ) {
                aux = aux -> prox;
            }
            novoNo -> prox = aux -> prox;
            novoNo -> ant = aux;
            aux -> prox = novoNo;
            aux -> prox -> ant = novoNo;
        }
    }
    lista -> qtdade++;
}

int obterElementoEmPosicao ( struct doublylinkedlist* lista, int posicao ) {
    if ( posicao >= 0 && posicao < lista -> qtdade ) {
        struct no* aux = lista -> cabeca;
        for ( int i = 0; aux != NULL && i < posicao; i++ ) {
            aux = aux -> prox;
        }
        return aux -> val;
    }
    else return INT_MIN;
}

void removerElementoEmPosicao ( struct doublylinkedlist* lista, int posicao ) {
    if ( lista -> cabeca == lista -> cauda ) {
        lista -> cabeca = NULL;
        lista -> cauda = NULL;
    }
    else {
        if ( posicao == 0 ) {
            lista -> cabeca = lista -> cabeca -> prox;
            lista -> cabeca -> ant = NULL;
        }
        else if ( posicao == lista -> qtdade - 1 ) {
            struct no* aux = lista -> cabeca;
            while ( aux -> prox -> prox != NULL ) {
                aux = aux -> prox;
            }
            lista -> cauda = aux;
            lista -> cauda -> prox = NULL;
            aux -> ant = lista -> cauda;
            aux -> prox = NULL;
        }
        else {
            struct no* aux = lista -> cabeca;
            for ( int i = 0; i < posicao - 1; i++ ) {
                aux = aux -> prox;
            }
            aux -> prox = aux -> prox -> prox;
            aux -> prox -> ant = aux;
        }
    }
    lista -> qtdade--;
}

void imprimirLista ( struct no** cabeca ) {
    if ( ( *cabeca ) != NULL ) {
        struct no* aux = ( *cabeca );
        printf ( "[" );
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
