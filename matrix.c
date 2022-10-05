#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

struct matrix{

    struct matrix* right;
    struct matrix* below;
    int line;
    int column;
    float info;

};



int matrix_create(Matrix** m){

    int k, l;/*Dimensão da matriz. Coloquei k e l ao invés de m e n, pois
    o programa estava considerando que eu estava redeclarando 'm'*/

    int i, j;
    float valor;

    /*Digite o numero de linhas e colunas <m x n> desejado para a matriz respectivamente:*/
    scanf("%d", &k);
    scanf("%d", &l);

    /*Criação do nó cabeça e dos nós folha*/
    int a, b;

    *m = (Matrix*)malloc(sizeof(Matrix*));
    (*m)->right = NULL;
    (*m)->below = NULL;
    (*m)->line = -1;
    (*m)->column = -1;

    Matrix* aux = *m;
    for (a = 1; a <= k; a++){


        Matrix* novo = (Matrix*)malloc(sizeof(Matrix));
        novo->right = novo;
        novo->below = *m;
        novo->line = a;
        novo->column = -1;
        aux->below = novo;
        aux = novo;


    }

    Matrix* aux1 = *m;
    for (b = 1; b <= l; b++){

        Matrix*novo = (Matrix*)malloc(sizeof(Matrix));
        novo->right = *m; /*Aponta para si mesmo*/
        novo->below = novo; /*Aponta para o nó cabeça*/ /*Depois será apontado para o elemento da coluna*/
        novo->line = -1; /*Linha do nó folha*/
        novo->column = b; /*Coluna onde serão inseridos os elementos*/

        aux1->right = novo; /*Auxiliar que aponta para o nó folha*/
        aux1 = novo;

    }

    /*Digite a tripla com as cordenadas x e y e o valor do elemento nesta mesma ordem, ou 0 para encerrar a leitura de valores:*/
    scanf("%d", &i);


    while (i != 0){

        if (i != 0){

            scanf("%d %f", &j, &valor);
            matrix_setelem(*m, i, j, valor);

        }

        /*Digite a tripla com as cordenadas x e y e o valor do elemento nesta mesma ordem, ou 0 para encerrar a leitura de valores:*/
        scanf("%d", &i);


    }

    if(*m != NULL){

        return 0;
    }else{

        return 1;
    }

}

int matrix_destroy (Matrix* m){

    /*Caso a matriz não aponte para NULL a memória alocada para a sua criação será destruída, senão, a operação não será realizada*/
    if(m != NULL){

        Matrix* p = m;
        Matrix* q = m;
        p = p->right;
        q = q->below;

        do{





            Matrix* t = p;
            p = p->right;
            free(t);



        }while(p != m);

        do{





            Matrix* t = q;
            q = q->below;
            free(t);



        }while(q != m);


        free(m);
        m = NULL;



        return 0;
    }else{

        return 1;
    }


}

int matrix_print( const Matrix* m){

    /*Serão impressas as componentes da matrix em ordem crescente em relação a cada linha*/
    const Matrix* p = m;
    const Matrix* q = m;

    if(p != NULL){


        do{


            if((q->line != -1) && (q->column != -1))
            printf("\n%d %d %0.1f\n", q->line, q->column, q->info);

            q = q->below->right;

        }while(q != m);


        printf("\n%d\n", 0);

        return 0;


    }else if(p == NULL){

        printf("Matriz vazia!");
        return 1;

    }


}

int matrix_add( const Matrix* m, const Matrix* n, Matrix** r ){

    const Matrix* p = m;

    const Matrix* q = n;


    /*Algoritmo para se calcular as dimensões das matrizes A e B*/
    int mx = 0, my = 0, nx = 0, ny = 0;

    do{

        if( mx < p->line){

            mx = p->line;
        }

        if( my < p->column){

            my = p->column;
        }

        p = p->right->below;

    }while(p != m);

    do{

        if( nx < q->line){

            nx = q->line;
        }

        if( ny < q->column){

            ny = q->column;
        }

        q = q->right->below;

    }while(q != n);

    /*Se as matrizes tiverem as mesmas dimensões a operação soma será realizada, senão, será o caso de matriz indefinida*/
    if ((mx == nx) && (my == ny)){


        /*Criação do nó cabeça da matriz C*/
        int a, b;

        *r = (Matrix*)malloc(sizeof(Matrix*));
        (*r)->right = NULL;
        (*r)->below = NULL;
        (*r)->line = -1;
        (*r)->column = -1;

        Matrix* aux = *r;//(Matrix*)malloc(sizeof(Matrix));
        for (a = 1; a <= mx; a++){


            Matrix* novo = (Matrix*)malloc(sizeof(Matrix));
            novo->right = novo;
            novo->below = *r;
            novo->line = a;
            novo->column = -1;
            aux->below = novo;
            aux = novo;


        }

        Matrix* aux1 = *r;
        for (b = 1; b <= my; b++){

            Matrix*novo = (Matrix*)malloc(sizeof(Matrix));
            novo->right = *r; /*Aponta para si mesmo*/
            novo->below = novo; /*Aponta para o nó cabeça*/ /*Depois será apontado para o elemento da coluna*/
            novo->line = -1; /*Linha do nó folha*/
            novo->column = b; /*Coluna onde serão inseridos os elementos*/

            aux1->right = novo; /*Auxiliar que aponta para o nó folha*/
            aux1 = novo;

        }

        /*Operação adição entre as matrizes A e B, sendo o resultado colocado na matriz C*/
        int i, j;


        for (i = 1; i <= mx; i++){

            for (j = 1; j <= my; j++){

                float g;

                float h;
                float elem;

                matrix_getelem(m, i, j, &g);
                matrix_getelem(n, i, j, &h);

                elem = g + h;

                matrix_setelem(*r, i, j, elem);





            }


        }


        return 0;

    }else{

        printf("\nMatriz indefinida!\n");

        return 1;

    }


}

int matrix_multiply( const Matrix* m, const Matrix* n, Matrix** r ){

    const Matrix* p = m;

    const Matrix* q = n;

    /*Algoritmo para se calcular as dimensões das matrizes A e B*/
    int mx = 0, my = 0, nx = 0, ny = 0;

    do{

        if( mx < p->line){

            mx = p->line;
        }

        if( my < p->column){

            my = p->column;
        }

        p = p->right->below;

    }while(p != m);

    do{

        if( nx < q->line){

            nx = q->line;
        }

        if( ny < q->column){

            ny = q->column;
        }

        q = q->right->below;

    }while(q != n);

    /*Caso o numero de colunas da matriz A seja igual ao número de linhas da matriz B a operação de multiplicação
    entre ambas as matrizes será realizada, caso contrário será o caso de operação de multiplicação entre matrizes que
    não satisfaz a condição de existência*/
    if (my == nx){

        /*Criação do nó cabeça da matriz C*/
        int a, b;

        *r = (Matrix*)malloc(sizeof(Matrix*));
        (*r)->right = NULL;
        (*r)->below = NULL;
        (*r)->line = -1;
        (*r)->column = -1;

        /*Criação dos nós folha da matriz C*/
        Matrix* aux = *r;
        for (a = 1; a <= mx; a++){


            Matrix* novo = (Matrix*)malloc(sizeof(Matrix));
            novo->right = novo;
            novo->below = *r;
            novo->line = a;
            novo->column = -1;
            aux->below = novo;
            aux = novo;


        }

        Matrix* aux1 = *r;
        for (b = 1; b <= my; b++){

            Matrix*novo = (Matrix*)malloc(sizeof(Matrix));
            novo->right = *r; /*Aponta para si mesmo*/
            novo->below = novo; /*Aponta para o nó cabeça*/ /*Depois será apontado para o elemento da coluna*/
            novo->line = -1; /*Linha do nó folha*/
            novo->column = b; /*Coluna onde serão inseridos os elementos*/

            aux1->right = novo; /*Auxiliar que aponta para o nó folha*/
            aux1 = novo;

        }


        /*Inicio do algoritmo para a realização da operação multiplicação entre as matrizes A e B*/
        int i, j;

        float v[mx][my];

        for (i = 1; i <= mx; i++){

            for (j = 1; j <= my; j++){

                float elem;

                matrix_getelem(m, i, j, &elem);
                v[i-1][j-1] = elem;
            }
        }

        float v1[nx][ny];

        for (i = 1; i <= nx; i++){

            for (j = 1; j <= ny; j++){

                float elem;
                matrix_getelem(n, i, j, &elem);
                v1[(i-1)][(j-1)]= elem;
            }
        }


        int linha, coluna;

        for (linha = 0; linha < mx; linha++){

            for (coluna = 0; coluna < ny; coluna++){

                float soma = 0;

                for (i = 0; i < mx; i++){

                    soma = soma + v[linha][i]*v1[i][coluna];
                }
                matrix_setelem(*r, linha+1, coluna+1, soma);
            }
        }
        /*Fim do algoritmo para a realização da operação multiplicação entre as matrizes A e B*/




        return 0;
    } else{/*Caso a operação multiplicação entre as matrizes A e B não satisfaça a condição de exixtência*/

        printf("\nO produto entre as matrizes dadas nao existe, pois nao obedece a condicao de existencia entre elas!\n");

        return 1;

    }


}

int matrix_transpose( const Matrix* m, Matrix** r ){

    const Matrix* w = m;

    /*Algoritmo para se calcular a dimensão da matriz A*/
    int contax = 0, contay = 0;
    int i, j;

    do{

        if( contax < w->line){

            contax = w->line;
        }

        if( contay < w->column){

            contay = w->column;
        }

        w = w->right->below;

    }while(w != m);


    /*Criação do nó cabeça da matriz C*/
    int a, b;

    *r = (Matrix*)malloc(sizeof(Matrix*));
    (*r)->right = NULL;
    (*r)->below = NULL;
    (*r)->line = -1;
    (*r)->column = -1;

    /*Criação dos nós folha da matriz C*/
    Matrix* aux = *r;
    for (a = 1; a <= contay; a++){


        Matrix* novo = (Matrix*)malloc(sizeof(Matrix));
        novo->right = novo;
        novo->below = *r;
        novo->line = a;
        novo->column = -1;
        aux->below = novo;
        aux = novo;


    }

    Matrix* aux1 = *r;
    for (b = 1; b <= contax; b++){

        Matrix*novo = (Matrix*)malloc(sizeof(Matrix));
        novo->right = *r; /*Aponta para si mesmo*/
        novo->below = novo; /*Aponta para o nó cabeça*/ /*Depois será apontado para o elemento da coluna*/
        novo->line = -1; /*Linha do nó folha*/
        novo->column = b; /*Coluna onde serão inseridos os elementos*/

        aux1->right = novo; /*Auxiliar que aponta para o nó folha*/
        aux1 = novo;

    }

    /*Operação de transposição da matriz A com os resultados sendo alocados na matriz C*/
    for (i = 1; i <= contax; i++){

        for (j = 1; j<=contay; j++){

            float elem;

            matrix_getelem(m, i, j, &elem);

            matrix_setelem(*r, j, i, elem);




        }


    }

    /*Caso a matriz C não seja mais vazia, a operação transposição foi realizada*/
    if(*r != NULL){

        return 0;

    }else{

        return 1;
    }




}

int matrix_getelem(const Matrix* m, int x, int y, float* elem){

    const Matrix* p = m;

    float k = 0;


    /*Caso seja encontrada uma componente nas coordenadas x e y, a variável sinalizadora signal receberá 1 como valor*/
    int signal = 0;

    do{

        if((p->line == x)&&(p->column == y)){

            signal = 1;


            *elem = p->info;



        }
        p = p->right->below;

    }while(p != m);



    /*No caso de ser encontrada a componente, a operação terá tido sucesso, senão, a variável elem receberá um valor nulo*/
    if (signal != 1){

        *elem = k;


        return 1;

    } else{

        return 0;

    }



}

int matrix_setelem(Matrix* m, int x, int y, float elem){

    Matrix* p = m;
    Matrix* q = m;
    Matrix* w = m;

    int contax = 0, contay = 0;
    int signal;

    /*Algoritmo para calcular a dimensão da matriz A*/
     do{

        if( contax < w->line){

            contax = w->line;
        }

        if( contay < w->column){

            contay = w->column;
        }

        w = w->right->below;

    }while(w != m);

    /*Caso as coordendas dadas como parâmetro não extrapolem as dimensões da matriz, e que o valor dado seja diferente de nulo,
    a operação ocorrerá*/

    if (((x >= 1)&&(x <= contax))&&((y >= 1)&&(y <= contay))&&(elem != 0)){


        do{


            if((p->line == x) && (p->column == y)){

                signal = 1;
                printf("\nEssa posicao da matriz ja se encontrava preenchida, esse novo valor substiuira o valor anterior.\n");
                p->info = elem;
            }

            p = p->right->below;

        }while(p != m);



        /*Criação do nó folha contendo o valor do novo elemento para ser adicionado à matriz A*/
        if(signal != 1){

            do{

                if(p->column == y){


                    Matrix* aux;
                    Matrix* prox = (Matrix*)malloc(sizeof(Matrix));
                    prox->line = x;
                    prox->column = y;
                    prox->info = elem;
                    prox->right = prox;

                    prox->below = p->below;
                    p->below = prox;

                }

                p = p->right;


            }while(p != m);


        }

        return 0;


    /*Caso as coordenadas dadas extrapolem o valor das dimensões da matriz A, será retornada uma mensagem de erro*/
    }else if(((x < 1)||(x > contax))||((y < 1)||(y >contay))){

        printf("\nEssas coordenadas ultrapassam as dimensoes da matriz, o elemento nao sera adicionado.\n");

        return 1;
    }


}
