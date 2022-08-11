#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <time.h>
#include "cells8.c"
#include "transfer8.c"

// World specs TOROIDAL SPACE
world *wrld;
int world_width = 200;
int world_height = 200;
cell ***cellArray;
int world_x_origin = 0;
int world_y_origin = 0;
int cell_size = 20;
// Probability distribution polynomial for transfer array generation
double pc[5] = {.89440000, -.18101600, .00247872, -.00001418, .00000002};
int pclen = 5;
// Initial transfer array
const char *loadintransferArray = "00010101010101010100010101000100010101010100010001010101010101010101010100000101010100010000010100010101010101010101010101010101010101000001000101000000000100010001010101010001010101010101000101000101000101010100010101010000010101010101010101010101010101010101010101010101010100010101000101010101010101000101010100010101010111110111011111111111111111011111111111011111111110111111111011111111011111110111110101111111111111011111111111001101101110111111001011111111111111001001000111111111101111110111100111111111";

// Display loop
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0; i<wrld->width;i++){
        for(int j=0; j<wrld->height; j++){
            // Determine whether each cell is presently alive or dead, and draw it
            drawCell(wrld, i, j);
        }
    }
    glFlush();
    // Manually depress the update rate to not kill computer
    usleep(50000);
    // update cell states depending on ruleset
    updateWorld(wrld);
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'q'){
        exit(0);
    }
    if(key == 'u'){
        // u for update
        // generate and print the new transferArray
        // transferArrayGen(wrld->transferArray, pc, pclen);
        transferTree *t = randomTransferTreeGen(12);
        parseTransferTree(t, wrld->transferArray);
        printTransferTree(t);
        freeTransferTree(t);
        printf("\n");
        for(int i=0;i<512;i++){
            printf("%d", wrld->transferArray[i]);
        }
        printf("\n\n");
        // populate the world with random cells
        reInitializeCells(wrld);
    }
}
int main(int argc, char *argv[])
{   
    srand(time(NULL));
    // initialize world
    wrld = malloc(sizeof(world));
    wrld->width = 200;
    wrld->height = 200;
    wrld->x_origin = 0;
    wrld->y_origin = 0;
    wrld->cell_size = 20;
    // load in default transfer array
    int temp[512];
    for(int i=0;i<512;i++){
        temp[i]=loadintransferArray[i]-48;
    }
    for(int i=0;i<512;i++){
        wrld->transferArray[i] = temp[i];
    }

    transferTree *t = randomTransferTreeGen(4);
    parseTransferTree(t, wrld->transferArray);
    freeTransferTree(t);

    // randomly populate the world with cells, equal probability of being live or dead
    wrld->cellArray = malloc(wrld->width*wrld->height*sizeof(cell));
    for(int i=0; i<wrld->width; i++){
        wrld->cellArray[i] = malloc(wrld->height*sizeof(cell));
        for(int j=0; j<wrld->height; j++){
            wrld->cellArray[i][j] = newCell(i,j,rand()%2);
        }
    }
    /*
        Can we term the 512 bit integer the transition function signature?
        transition string? transition table? transition array. transition number?
        Idea: Characteristic function? for generating transition arrays. A probability
        function p over [0,512], where p(x) is the expected value of the x-th bit of
        the transition array.

        Plan is to use polynomial characteristic functions that way we can use genetic
        programming techniques, since the crossover of two polynomial functions can be
        reasonably defined
    */
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
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
