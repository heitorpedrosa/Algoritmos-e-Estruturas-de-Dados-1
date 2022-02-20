#include <stdio.h>
#include <stdbool.h>

void bubbleSort ( int* arr, int n );

void selectionSort ( int* arr, int n );

void insertionSort ( int* arr, int n );

void merge ( int* arr, int size, int* left_arr, int left_size, int* right_arr, int right_size );

void mergeSort ( int* arr, int size );

void quickSort(int* arr, int begin, int end );

int particiona ( int* arr, int begin, int end );

void countingSort ( int* arr, int n );

void swap ( int* arr, int i, int j );

void imprimir ( int* arr, int n );

int main () { return 0; }

void bubbleSort ( int* arr, int n ) {
    bool ordenada;
    int aux;

    do {
        ordenada = true;
        for ( int i = 0; i < ( n - 1 ); i++ ) {
            if ( arr [ i ] > arr [ i + 1 ] ) {
                aux = arr [ i ];
                arr [ i ] = arr [ i + 1 ];
                arr [ i + 1 ] = aux;
                ordenada = false;
            }
        }
        n--;
    } while ( !ordenada );
}

void selectionSort ( int* arr, int n ) {
    int aux;
    for ( int i = 0; i < ( n - 1 ); i++ ) {
        int iMenor = i;
        for ( int j = i + 1; j < n; j++ ) {
            if ( arr [ j ] < arr [ iMenor ] ) iMenor = j;
        }
        if ( i != iMenor ) {
            aux = arr [ i ];
            arr [ i ] = arr [ iMenor ];
            arr [ iMenor ] = aux;
        }
    }
}

void insertionSort ( int* arr, int n ) {
    int aux;
     for ( int i = 1; i < n; i++ ) {
        for ( int j = i; j > 0; j-- ) {
            if ( arr [ j - 1 ] > arr [ j ] ) {
                aux = arr [ j - 1 ];
                arr [ j - 1 ] = arr [ j ];
                arr [ j ] = aux;
            }
            else break;
        }
    }
}

void merge ( int* arr, int size, int* left_arr, int left_size, int* right_arr, int right_size ) {
    int index = 0;
    int left_index = 0;
    int right_index = 0;

     while ( left_index < left_size && right_index < right_size ) {
        if ( left_arr [ left_index ] <= right_arr [ right_index ] ) {
            arr [ index ] = left_arr [ left_index ];
            left_index++;
        } else{
            arr [ index ] = right_arr [ right_index ];
            right_index++;
        }
        index++;
    }

    while ( left_index < left_size ){
        arr [ index ] = left_arr [ left_index ];
        left_index++;
        index++;
    }

    while ( right_index < right_size ){
        arr [ index ] = right_arr [ right_index ];
        right_index++;
        index++;
    }
}

void mergeSort ( int* arr, int size ) {
    if ( size > 1 ) {
        int meio = size / 2;

        int tamV1 = meio;
        int v1 [ tamV1 ];

        for ( int i = 0; i < meio; i++ ){
            v1 [ i ] = arr [ i ];
        }

        int tamV2 = size - meio;
        int v2 [ tamV2 ];

        for ( int i = meio; i < size; i++ ){
            v2 [ i - meio ] = arr [ i ];
        }
        mergeSort ( v1, tamV1 );
        mergeSort ( v2,tamV2 );
        merge ( arr, size, v1, tamV1, v2, tamV2 );
    }
}

void quickSort(int* arr, int begin, int end ) {
    if ( end > begin ) {
        int pivot_index = particiona ( arr, begin, end );

        quickSort ( arr, begin, pivot_index - 1 );
        quickSort ( arr, pivot_index + 1, end );
    }
}

int particiona ( int arr [], int begin, int end ) {
    int pivot_index = begin;
    int pivot = arr [ end ];
    for ( int i = begin; i < end; i++ ) {
        if ( arr [ i ] <= pivot ) {
            swap ( arr, i, pivot_index );
            pivot_index++;
        }
    }
    swap ( arr, pivot_index, end );

    return pivot_index;
}

void countingSort ( int* arr, int n ) {
    int aux [ n ];

    int maior = arr [ 0 ];

    for ( int i = 1; i < n; i++ ) {
        if ( arr [ i ] > maior ) maior = arr [ i ];
    }

    int count [ maior + 1 ];

    for ( int i = 0; i < ( maior + 1 ); i++ ) count [ i ] = 0;

    for ( int i = 0; i < n; i++ ) count [ arr [ i ] ]++;

    for ( int i = 1; i < ( maior + 1 ); i++ ) count [ i ] += count [ i - 1 ];

    for ( int i = n - 1; i >= 0; i-- ) {
        aux [ count [ arr [ i ] ] - 1 ] = arr [ i ];
        count [ arr [ i ] ]--;
    }

    for ( int i = 0; i < n; i++ ) {
        arr [ i ] = aux [ i ];
    }
}

void swap ( int* arr, int i, int j ) {
    int aux = arr [ i ];
    arr [ i ] = arr [ j ];
    arr [ j ] = aux;
}

void imprimir ( int* arr, int n ) {
    for ( int i = 0; i < n; i++ ) printf ( "%d ", arr [ i ] );
    printf ( "\n" );
}
