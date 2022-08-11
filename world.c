#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <time.h>
#include "cells.c"
#include <limits.h>

int world_width = 200;
int world_height = 200;

int screen_width = 1000;
int screen_height = 1000;

cell ***cellArray;

int world_x_origin = 0;
int world_y_origin = 0;
int cell_size = 20;

unsigned long int update = 562826243;

// 562826243 interesting landscape
// 58969546 perpetual crying
// 862062994 pouring sand
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
        glColor3ub(34, 102, 0); 
        // glColor3ub(0, 0, 0); 
    }
    else{
        // glColor3ub(255, 255, 255);
        glColor3ub(133, 150, 235);

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
    usleep(50000);
    for(int i=0; i<world_width;i++){
        for(int j=0; j<world_height; j++){
            updateCell(cellArray[i][j]
                , cellArray[(i+1)%world_width][j]
                , cellArray[i][(j+1)%world_height]
                , cellArray[(i+world_width-1)%world_width][j]
                , cellArray[i][(j+world_height-1)%world_height]
                , update);
        }
    }
    for(int i=0; i<world_width;i++){
        for(int j=0; j<world_height; j++){
            drawCell(cellArray[i][j], cell_size, world_x_origin, world_y_origin);
        }
    }
    glFlush();
}

void keyPressed (unsigned char key, int x, int y) {  
    if(key == 'q'){
        printf("dawnaballz\n");
        exit(0);
    }
    if(key == 'u'){
        update = rand()%ULONG_MAX;
        printf("%lu\n",update);
        reInitializeCells();
    }
}

void onClick(int button, int state, int x, int y){
    int closest_x_ind = (int)(x * world_width / screen_width);
    int closest_y_ind = world_height-(int)(y * world_height / screen_height);
    if(state == GLUT_DOWN){
        for(int i=closest_x_ind-10; i<closest_x_ind+10;i++){
            for(int j=closest_y_ind-10;j<closest_y_ind+5; j++){
                if(rand()%7 >= 1){
                    cellArray[(i+world_width)%world_width][(j+world_height)%world_height]->state = 1;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{   
    cellArray = malloc(world_width*world_height*sizeof(cell));
    for(int i=0; i<world_width; i++){
        cellArray[i] = malloc(world_height*sizeof(cell));
        for(int j=0; j<world_height; j++){
            cellArray[i][j] = newCell(i,j,rand()%2);
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screen_width, screen_height * 2 * world_height / world_width);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Dawna Linsdell");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0.f, world_width * cell_size, 0.f, world_height * cell_size, 0.f, 2.f);
    glViewport(0, 0, world_width, world_height);
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(display);
    glutMouseFunc(onClick);
    glClear(GL_COLOR_BUFFER_BIT);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}



