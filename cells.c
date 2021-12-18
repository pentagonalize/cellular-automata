#include <stdlib.h>

struct cell {
    int x;
    int y;
    int state;
    int nextState;
};
typedef struct cell cell;

int updateState(int neighbors, unsigned long int update){
    short mask=(1<<neighbors);
    return (update & mask) ? 1 : 0;
}

void updateCell(cell *c, cell *cn, cell *ce, cell *cs, cell *cw, unsigned long int update){
    int northState = cn->state;
    int eastState = ce->state;
    int southState = cs->state;
    int westState = cw->state;

    int neighbors = 16 * northState + 8 * eastState + 4 * southState + 2 * westState + c->state;
    c->nextState = updateState(neighbors, update);
}
