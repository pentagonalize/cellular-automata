#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef CELLHEADER
#define CELLHEADER

typedef unsigned int uint;

typedef struct {
    int x;
    int y;
    int state;
    int nextState;
} cell;

struct world;
typedef struct {
    void *data;     // where is the data
    int width, height,
        x_origin, y_origin,
        cell_size;
    cell ***cellArray;
    int transferArray[512];
} world;

int updateState(int neighbors, int *transferArray);
void reInitializeCells(world *wrld);
void randomizetransferArray(world *wrld);
void transferArrayGen(int *transferArray, double *pc, int pclen);
void updateCell8(cell *c, cell *cn, cell *cne, cell *ce, cell *cse, cell *cs, cell *csw, cell *cw, cell *cnw, int *transferArray);
cell *newCell(int x, int y, int state);
void drawCell(world *wrld, int i, int j);

#endif
