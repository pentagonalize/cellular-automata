#include <stdlib.h>
#include "cells8.h"


int updateState(int neighbors, int *transferArray){
    // helper function
    // may want other effects? I forget why I made this a separate function
    return transferArray[neighbors];
}

void reInitializeCells(world *wrld){
    // give each cell a random state
    for(int i=0; i<wrld->width; i++){
        for(int j=0; j<wrld->height; j++){
            wrld->cellArray[i][j] = newCell(i,j,rand()%2);
        }
    }
}

void updateCell8(cell *c, cell *cn, cell *cne, cell *ce, cell *cse, cell *cs, cell *csw, cell *cw, cell *cnw, int *transferArray){
    // input cells are in clockwise order, starting from north(directly above)
    int northState = cn->state;
    int northEastState = cne->state;
    int eastState = ce->state;
    int southEastState = cse->state;
    int southState = cs->state;
    int southWestState = csw->state;
    int westState = cw->state;
    int northWestState = cnw->state;
    /*
        each of the neighbor states (0 or 1) are concatenated together into a binary number b,
        where the northern cell's state is in the 2^8th place, the northwestern cell's state is
        in the 2^1th place, while the current cell's state is in the 2^0th place.

        the b-th entry in the transfer array determines the new state of the cell c
    */
    int neighbors =  256 * northState 
                    + 128 *northEastState 
                    + 64 * eastState 
                    + 32 * southEastState 
                    + 16 * southState 
                    + 8 * southWestState 
                    + 4 * westState 
                    + 2 * northWestState
                    + c->state;
    c->nextState = updateState(neighbors, transferArray);
}

cell *newCell(int x, int y, int state){
    // initialze a new cell
    cell *myCell = malloc(sizeof(cell));
    myCell->x = x;
    myCell->y = y;
    myCell->state = state;
    myCell->nextState = state;
    return myCell;
}

void drawCell(world *wrld, int i, int j){
    // determine whether a cell is alive or dead, and then draw it
    cell *c = wrld->cellArray[i][j];
    int x_origin = wrld->x_origin;
    int y_origin = wrld->y_origin;
    int cell_size = wrld->cell_size;
    int x_ind = c->x;
    int y_ind = c->y;
    c->state = c->nextState;
    if(c->state == 1){
        // // fun colors
        // glColor3ub(rand()%255, rand()%255, rand()%255 );
        // alive, we draw a black square
        glColor3ub(0, 0, 0);
    }
    else{
        glColor3ub(255, 255, 255);
    }
    // draw the square
    glBegin(GL_POLYGON);
    glVertex3f(x_origin + x_ind * cell_size, y_origin + y_ind * cell_size, 0);
    glVertex3f(x_origin + (x_ind + 1) * cell_size, y_origin + y_ind * cell_size, 0);
    glVertex3f(x_origin + (x_ind + 1) * cell_size, y_origin + (y_ind + 1) * cell_size,0);
    glVertex3f(x_origin + x_ind * cell_size, y_origin + (y_ind + 1) * cell_size, 0);
    glEnd();
}

void updateWorld(world *wrld){
    // loop through all cells and call updateCell8()
    int w = wrld->width;
    int h = wrld->height;
    for(int i=0; i<w;i++){
        for(int j=0; j<h; j++){
            // Using wlrd->transferArray, determine the next state of each cell
            updateCell8(wrld->cellArray[i][j]
                , wrld->cellArray[i][(j+1)%h]
                , wrld->cellArray[(i+1)%w][(j+1)%h]
                , wrld->cellArray[(i+1)%w][j]
                , wrld->cellArray[(i+1)%w][(j+h-1)%h]
                , wrld->cellArray[i][(j+h-1)%h]
                , wrld->cellArray[(i+w-1)%w][(j+h-1)%h]
                , wrld->cellArray[(i+w-1)%w][j]
                , wrld->cellArray[(i+w-1)%w][(j+1)%h]
                , wrld->transferArray);
        }
    }
}

