#include <stdlib.h>

struct cell {
    int x;
    int y;
    int state;
    int nextState;
};
typedef struct cell cell;

int updateState(int neighbors, int *ruleset){
    return ruleset[neighbors];
}

void updateCell8(cell *c, cell *cn, cell *cne, cell *ce, cell *cse, cell *cs, cell *csw, cell *cw, cell *cnw, int *ruleset){
    int northState = cn->state;
    int northEastState = cne->state;
    int eastState = ce->state;
    int southEastState = cse->state;
    int southState = cs->state;
    int southWestState = csw->state;
    int westState = cw->state;
    int northWestState = cnw->state;

    int neighbors =  256 * northState 
                    + 128 *northEastState 
                    + 64 * eastState 
                    + 32 * southEastState 
                    + 16 * southState 
                    + 8 * southWestState 
                    + 4 * westState 
                    + 2 * northWestState
                    + c->state;
    c->nextState = updateState(neighbors, ruleset);
}

