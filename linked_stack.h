#ifndef ED_H
#define ED_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct no{
    int val;
    struct no *prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar () {
    struct linkedstack* pilha = ( struct linkedstack* ) malloc ( sizeof ( struct linkedstack ) );
    pilha -> topo = NULL;
    pilha -> qtdade = 0;
    return pilha;
}

struct no* alocarNovoNo ( int valor ){
    struct no* novoNo = ( struct no* ) malloc ( sizeof ( struct no ) );
    novoNo -> prox = NULL;
    novoNo -> val = valor;
    return novoNo;
}

bool vazia ( struct linkedstack* pilha ) {
    if ( pilha == NULL || pilha -> qtdade == 0 ) return true;
    return false;
}

void empilhar ( struct linkedstack** pilha, int valor ){
    struct no* aux = alocarNovoNo ( valor );
    if ( ( *pilha ) == NULL ) {
        ( *pilha ) = inicializar ();
        ( *pilha ) -> topo = aux;
    }
    else {
        aux -> prox = ( *pilha ) -> topo;
        ( *pilha ) -> topo = aux;
    }
    ( *pilha ) -> qtdade++;
}

void desempilhar ( struct linkedstack* pilha ) {
    if ( vazia ( pilha ) || pilha -> qtdade == 0 ) {
        return;
    }
    else {
        struct no* aux = pilha -> topo;
        pilha -> topo = pilha -> topo -> prox;
        free ( aux );
        pilha -> qtdade--;
    }
}

int desempilharRetornando ( struct linkedstack* pilha ) {
    if ( vazia ( pilha ) || pilha -> qtdade == 0 ) return INT_MIN;
    int valor = pilha -> topo -> val;
    desempilhar ( pilha );
    return valor;
}

int topo ( struct linkedstack* pilha ){
    if ( vazia ( pilha ) || pilha -> qtdade == 0 ) return INT_MIN;
    return pilha -> topo -> val;
}

void exibirPilha ( struct linkedstack* pilha ) {
    if ( !vazia ( pilha ) ) {
        struct no* aux = pilha -> topo;
        printf ( "_\n" );
        do {
            printf ( "%d\n", aux -> val );
            aux = aux -> prox;
        } while ( aux != NULL );
        printf ( "_" );
    }
    else {
        printf ( "A pilha está vazia!" );
    }
}

#endif // ED_H
