#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <queue>
#include <algorithm>

using namespace std;

void atualizar ( struct noBst* no );
struct noBst* balancear ( struct noBst* no );
struct noBst* rebalancearEsqEsq ( struct noBst* no );
struct noBst* rebalancearEsqDir ( struct noBst* no );
struct noBst* rebalancearDirDir ( struct noBst* no );
struct noBst* rebalancearDirEsq ( struct noBst* no );

struct noBst {
    int val;
    int altura;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

struct noBst* alocarNovoNo ( int val ) {
    struct noBst* novoNo = ( struct noBst* ) malloc ( sizeof ( struct noBst ) );
    novoNo -> esq = NULL;
    novoNo -> dir = NULL;
    novoNo -> val = val;
    novoNo -> altura = 0;
    novoNo -> balanco = 0;
    return novoNo;
}

struct noBst* rotacaoDireita ( struct noBst* arvore ) {
    struct noBst* novaRaiz = arvore -> esq;
    struct noBst* aux = novaRaiz -> dir;

    novaRaiz -> dir = arvore;
    arvore -> esq = aux;

    atualizar ( arvore );
    atualizar ( novaRaiz );

    return novaRaiz;
}

struct noBst* rotacaoEsquerda ( struct noBst* arvore ) {
    struct noBst* novaRaiz = arvore -> dir;
    struct noBst* aux = novaRaiz -> esq;

    novaRaiz -> esq = arvore;
    arvore -> dir = aux;

    atualizar ( arvore );
    atualizar ( novaRaiz );

    return novaRaiz;
}

void inserir ( struct noBst** raiz, int val, int* tamanho ) {
    if ( *raiz == NULL ) *raiz = alocarNovoNo ( val );
    else if ( ( *raiz ) -> val > val ) inserir ( &( *raiz ) -> esq, val, tamanho );
    else inserir ( &( *raiz ) -> dir, val, tamanho );

    atualizar ( *raiz );

    if ( ( *raiz ) -> dir == NULL && ( *raiz ) -> esq == NULL ) ( *tamanho )++;

    balancear( *raiz );
}

void atualizar ( struct noBst* no ) {
    if ( no -> dir == NULL || no -> esq == NULL ) return;
    no -> altura = 1 + max ( no -> esq -> altura, no -> dir -> altura );
    no -> balanco = ( no -> dir -> altura ) - ( no -> esq -> altura );
}

struct noBst* balancear ( struct noBst* no ) {
    if ( no -> balanco > 1 && no -> esq -> balanco >= 0 ) no = rebalancearEsqEsq ( no );
    if ( no -> balanco > 1 && no -> esq -> balanco < 0 ) no = rebalancearEsqDir ( no );
    if ( no -> balanco < -1 && no -> dir -> balanco <= 0 ) no = rebalancearDirDir ( no );
    if ( no -> balanco < -1 && no -> dir -> balanco > 0 ) no = rebalancearDirEsq ( no );
    return no;
}

struct noBst* rebalancearEsqEsq ( struct noBst* no ) {
    return rotacaoDireita ( no );
}

struct noBst* rebalancearEsqDir ( struct noBst* no ) {
    no -> esq = rotacaoEsquerda ( no -> esq );
    return rotacaoDireita ( no );
}

struct noBst* rebalancearDirDir ( struct noBst* no ) {
    return rotacaoEsquerda ( no );
}

struct noBst* rebalancearDirEsq ( struct noBst* no ) {
    no -> dir = rotacaoDireita ( no -> dir );
    return rotacaoEsquerda ( no );
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

struct noBst* remover (struct noBst* raiz, int val, int* tamanho ) {
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

    atualizar ( raiz );
    balancear ( raiz );

    return raiz;
}

void imprimir ( queue <struct noBst*> nosImpressao );

void imprimir ( struct noBst* raiz ) {
    queue <struct noBst*> nosImpressao;
    nosImpressao.push ( raiz );
    imprimir ( nosImpressao );
}

void imprimir ( queue <struct noBst*> nosImpressao ) {

    queue <struct noBst*> nosImpressaoProxNivel;

    while ( !nosImpressao.empty () ) {
        struct noBst* noImpressao = nosImpressao.front ();
        if ( noImpressao != NULL ){
            if ( noImpressao -> esq != NULL ) nosImpressaoProxNivel.push ( noImpressao -> esq );
            else nosImpressaoProxNivel.push ( NULL );

            if ( noImpressao -> dir != NULL ) nosImpressaoProxNivel.push ( noImpressao -> dir );
            else nosImpressaoProxNivel.push ( NULL );
        }
        nosImpressao.pop ();

        if ( noImpressao != NULL ) {
            cout << to_string ( noImpressao -> val ) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if ( !nosImpressaoProxNivel.empty () )
        imprimir ( nosImpressaoProxNivel );
}

#endif // AVL_H
