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
int world_index;


int main(int argc, char *argv[])
{   
    t1 = malloc(sizeof(transferTree));
    t2 = malloc(sizeof(transferTree));

    t1 = randomTransferTreeGen(4);
    t2 = randomTransferTreeGen(4);

    printTransferTree(t1);
    printTransferTree(t2);

    transferTree *t3 = crossoverTransferTrees(t1, t2);
    printTransferTree(t3);

    transferTree *t4 = crossoverTransferTrees(t1, t3);
    printTransferTree(t4);

    for(int i=0; i<100; i++){
        t4 = crossoverTransferTrees(t1, t3);
        printTransferTree(t4);
    }

    return 0;
}
