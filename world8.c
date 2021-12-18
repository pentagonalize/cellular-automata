#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <time.h>
#include "cells8.c"

int world_width = 200;
int world_height = 200;
cell ***cellArray;

int world_x_origin = 0;
int world_y_origin = 0;
int cell_size = 20;

int ruleset[512]; 
int temp[512] = {0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,1};
const char *loadinRuleset = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001010111110110011000111010101001000111111110111110101101110110110110001010111111111111111111111111111101011110010011011011110000101001101110110111101110000000111111011111001101101110011010110101111110000111110101101110001011111111110111111111110011111011101111111111110001011111010110001100111101111001111110001111101111110111111111110010101111111111001111011111111111";

void randomRuleset(){
    for(int i=0; i<512; i++){
        ruleset[i] = rand()%6 ? 1 : 0;
        if(i < 324 ){
            if(i%2 == 0){
                ruleset[i] = 0;
            }
        }
    }
    ruleset[1] = 0;
    ruleset[496] = 0;
    ruleset[510] = 1;
}

cell *newCell(int x, int y, int state){
    cell *myCell = malloc(sizeof(cell));
    myCell->x = x;
    myCell->y = y;
    myCell->state = state;
    myCell->nextState = state;
    return myCell;
}

void drawCell(cell *c, int cell_size, int x_origin, int y_origin){
    int x_ind = c->x;
    int y_ind = c->y;
    c->state = c->nextState;
    if(c->state == 1){
        // glColor3ub(rand()%255, rand()%255, rand()%255 );
        glColor3ub(0, 0, 0); 
    }
    else{
        glColor3ub(255, 255, 255);
    }
    
    glBegin(GL_POLYGON);
    glVertex3f(x_origin + x_ind * cell_size, y_origin + y_ind * cell_size, 0);
    glVertex3f(x_origin + (x_ind + 1) * cell_size, y_origin + y_ind * cell_size, 0);
    glVertex3f(x_origin + (x_ind + 1) * cell_size, y_origin + (y_ind + 1) * cell_size,0);
    glVertex3f(x_origin + x_ind * cell_size, y_origin + (y_ind + 1) * cell_size, 0);
    glEnd();
}

void reInitializeCells(){
    for(int i=0; i<world_width; i++){
        for(int j=0; j<world_height; j++){
            cellArray[i][j] = newCell(i,j,rand()%2);
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0; i<world_width;i++){
        for(int j=0; j<world_height; j++){
            drawCell(cellArray[i][j], cell_size, world_x_origin, world_y_origin);
        }
    }
    glFlush();
    usleep(50000);
    for(int i=0; i<world_width;i++){
        for(int j=0; j<world_height; j++){
            updateCell8(cellArray[i][j]
                , cellArray[i][(j+1)%world_height]
                , cellArray[(i+1)%world_width][(j+1)%world_height]
                , cellArray[(i+1)%world_width][j]
                , cellArray[(i+1)%world_width][(j+world_height-1)%world_height]
                , cellArray[i][(j+world_height-1)%world_height]
                , cellArray[(i+world_width-1)%world_width][(j+world_height-1)%world_height]
                , cellArray[(i+world_width-1)%world_width][j]
                , cellArray[(i+world_width-1)%world_width][(j+1)%world_height]
                , ruleset);
        }
    }
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'q'){
        exit(0);
    }
    if(key == 'u'){
        randomRuleset();
        for(int i=0;i<512;i++){
            printf("%d", ruleset[i]);
        }
        printf("\n");
        reInitializeCells();
    }
}
int main(int argc, char *argv[])
{   
    srand(time(NULL));

    for(int i=0;i<512;i++){
        temp[i]=loadinRuleset[i]-48;
        // printf("%c",loadinRuleset[i]);
        // printf("%d",temp[i]);
    }

    for(int i=0;i<512;i++){
        ruleset[i] = temp[i];
    }
    cellArray = malloc(world_width*world_height*sizeof(cell));
    for(int i=0; i<world_width; i++){
        cellArray[i] = malloc(world_height*sizeof(cell));
        for(int j=0; j<world_height; j++){
            cellArray[i][j] = newCell(i,j,rand()%2);
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000 * 2 * world_height / world_width);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Dawna Linsdell");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0.f, world_width * cell_size, 0.f, world_height * cell_size, 0.f, 2.f);
    glViewport(0, 0, world_width, world_height);
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glClear(GL_COLOR_BUFFER_BIT);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}









