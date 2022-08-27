#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <time.h>
#include "cells8.c"
#include "transfer8.c"

// World specs TOROIDAL SPACE
world **wrlds;
int world_width = 300;
int world_height = 300;
cell ***cellArray;
int world_x_origin = 0;
int world_y_origin = 0;
int cell_size = 20;
// Initial transfer array
transferTree **trees;
// Pointers for parent genomes
transferTree *t1;
transferTree *t2;
transferTree *t3;
int world_index;


int main(int argc, char *argv[])
{   
    srand ( time(NULL) );
    printTransferTree(NULL);
    printf("ballz\n");
    // printf("manual tree\n");
    // transferTree *t0;
    // transferTree *tl;
    // transferTree *tr;
    // t0 = malloc(sizeof(transferTree));
    // tl = malloc(sizeof(transferTree));
    // tr = malloc(sizeof(transferTree));

    // t0->operation = 1;
    // t0->data = -1;

    // tl->operation = 0;
    // tl->data = 3;
    // tl->left = NULL;
    // tl->right = NULL;

    // tr->operation = 0;
    // tr->data = 5;
    // tr->left = NULL;
    // tr->right = NULL;

    // t0->right = tl;
    // t0->left = tr;

    // printTransferTree(t0);

    // printf("manual tree done\n");


    t1 = malloc(sizeof(transferTree));
    t2 = malloc(sizeof(transferTree));
    t3 = malloc(sizeof(transferTree));


    // printf("testing tree generation\n");
    // for(int i=0;i<10;i++){
    //     t1 = randomTransferTreeGen(3);
    //     printTransferTree(t1);
    // }
    // printf("tree generation done\n");


    // printf("testing size\n");
    // printf("nothing: %d\n", size(NULL));
    // printf("t0: %d\n", size(t0));
    // for(int i=0;i<8;i++){
    //     printf("new tree\n");
    //     free(t1);
    //     t1 = randomTransferTreeGen(i);
    //     printTransferTree(t1);
    //     printf("%d, %d\n", i, size(t1));
    // }
    // printf("testing size done\n");

    t1 = randomTransferTreeGen(2);
    t2 = randomTransferTreeGen(2);

    printf("t1: ");
    printTransferTree(t1);
    printf("t2: ");
    printTransferTree(t2);


    // printf("T1 POINTERS: \n");
    // printPointers(t1);
    printf("doing t3\n");
    t3 = crossoverTransferTrees(t1, t2);
    // printPointers(t3);
    printf("t3: ");
    printTransferTree(t3);

    printf("spam crossovers\n");
    for(int i=0; i<2000; i++){
        // printf("T1 POINTERS: \n");
        // printPointers(t1);
        printf("t1: ");
        printTransferTree(t1);
        printf("t2: ");
        printTransferTree(t2);
        t3 = crossoverTransferTrees(t1, t2);
        printf("t3: "); printTransferTree(t3); printf("\n");
    }
    printf("spam crossovers\n");
    printf("Hi\n");
    return 0;
}
