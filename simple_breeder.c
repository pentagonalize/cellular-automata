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
// Pointers for parent genome transferTrees
transferTree *t1;
transferTree *t2;
// Pointers for parent genome transferArrays
int *ta1;
int *ta2;
int world_index;

// Display loop
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int j=0; j<wrlds[0]->height; j++){
        for(int i=0; i<wrlds[0]->width;i++){
            // Determine whether each cell is presently alive or dead, and draw it
            for(int a=0;a<9;a++){
                drawCell(wrlds[a], i, j);
            }
        }
    }
    glFlush();
    // Manually depress the update rate to not kill computer
    usleep(50000);
    // update cell states depending on ruleset
    for(int a=0;a<9;a++){
        updateWorld(wrlds[a]);
    }
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'q'){
        exit(0);
    }
    if(key == 'u'){
        // u for update by crossovering transfer trees
        for(int i=0;i<9;i++){
            freeTransferTree(trees[i]);
            trees[i] = crossoverTransferTrees(t1, t2);
            mutate(trees[i], 0.001);
            parseTransferTree(trees[i], wrlds[i]->transferArray);
            // populate the world with random cells
            reInitializeCells(wrlds[i]);
        }
    }
    if(key == 'f'){
        // set parent 1
        int x_co = ((int)floor(x/world_width))%3;
        int y_co = ((int)floor(y/world_height))%3;
        world_index = x_co*3+y_co;
        printf("world_index: %d\n",world_index);
        freeTransferTree(t1);
        t1 = copyTransferTree(trees[world_index]);
        copyTransferArray(wrlds[world_index]->transferArray, ta1);
    }
    if(key == 'j'){
        // set parent 2
        int x_co = ((int)floor(x/world_width))%3;
        int y_co = ((int)floor(y/world_height))%3;
        world_index = x_co*3+y_co;
        printf("world_index: %d\n",world_index);
        freeTransferTree(t2);
        t2 = copyTransferTree(trees[world_index]);
        copyTransferArray(wrlds[world_index]->transferArray, ta2);
        // for(int i=0;i<512;i++){
        //     printf("%d", ta2[i]);
        // }
        // printf("\n");
    }
    if(key == 'i'){
        // u for update by crossovering transition string
        for(int i=0;i<9;i++){
            crossoverTransitionArray(ta1, ta2, wrlds[i]->transferArray);
            // populate the world with random cells
            reInitializeCells(wrlds[i]);
        }
    }
    printf("%d,%d, %d\n",x,y,world_index);
}

void myMouseFunc(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON) {
		int x_co = ((int)floor(x/world_width))%3;
        int y_co = ((int)floor(y/world_height))%3;
        world_index = x_co*3+y_co;
        printf("%d\n",world_index);
		for(int i=0; i<512; i++){
            printf("%d", wrlds[world_index]->transferArray[i]);
        }
        printf("\n\n");
	}
}

int main(int argc, char *argv[])
{   
    srand(time(NULL));
    trees = malloc(9*sizeof(transferTree));
    t1 = malloc(sizeof(transferTree));
    t2 = malloc(sizeof(transferTree));

    for(int i=0;i<9;i++){
        trees[i] = randomTransferTreeGen(6);
    }

    t1 = copyTransferTree(trees[0]);
    t2 = copyTransferTree(trees[1]);

    // transferArray breeding
    ta1 = malloc(512*sizeof(int));
    ta2 = malloc(512*sizeof(int));

    wrlds = malloc(9*sizeof(world));
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            wrlds[i*3+j] = malloc(sizeof(world));
            wrlds[i*3+j]->width = 100;
            wrlds[i*3+j]->height = 100;
            wrlds[i*3+j]->x_origin = 2000*i;
            wrlds[i*3+j]->y_origin = 2000*j;
            wrlds[i*3+j]->cell_size = 20;
            // generate tranfer array
            parseTransferTree(trees[i*3+j], wrlds[i*3+j]->transferArray);
            // randomly populate the world with cells, equal probability of being live or dead
            wrlds[i*3+j]->cellArray = malloc(wrlds[i*3+j]->width*wrlds[i*3+j]->height*sizeof(cell));
            for(int a=0; a<wrlds[i*3+j]->width; a++){
                wrlds[i*3+j]->cellArray[a] = malloc(wrlds[i*3+j]->height*sizeof(cell));
                for(int b=0; b<wrlds[i*3+j]->height; b++){
                    wrlds[i*3+j]->cellArray[a][b] = newCell(a,b,rand()%2);
                }
            }
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // window dimensions
    glutInitWindowSize(1000, 1000 * 2 * world_height / world_width);
    glutInitWindowPosition(200, 0);
    // dawna linsdell
    glutCreateWindow("Dawna Linsdell");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0.f, world_width * cell_size, 0.f, world_height * cell_size, 0.f, 2.f);
    glViewport(0, 0, world_width, world_height);
    glutKeyboardFunc(keyPressed);
    // display loop
    glutDisplayFunc(display);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(myMouseFunc);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
