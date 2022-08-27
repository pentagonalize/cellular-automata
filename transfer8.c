#include <stdlib.h>
#include "cells8.h"

double polyEval(double *pc, int pclen, double x){
    // largest exponent at end of array
    double ret=0;
    ret = pc[pclen-1];
    for(int i = pclen-2; i>=0 ; i--){
      ret = pc[i] + x * ret;
    }
    return ret;
}

void transferArrayGen(int *transferArray, double *pc, int pclen){
    // generate transfer array based on polynomial probability distribution
    for(int i=0; i<512; i++){
        int b = floor(1/polyEval(pc, pclen, i));
        if(b){
            transferArray[i] = rand()% b ? 0 : 1;
        }
        else{
            transferArray[i] = 0;
        }
    }
}

void randomArrayGen(int *transferArray){
    // r
    for(int i=0; i<512; i++){
        transferArray[i] = rand()%rand() < rand() ? 1 : 0;
    }
}

struct transferTree {
    // tree parent
    struct transferTree *prev;
    // 0:leaf, 1:AND, 2:OR, 3:NAND, 4:NOR, 5:NOT, 6:IF, 7:XOR
    int operation;
    // 0-8, indicating to which adjacent cell. -1 if not leaf
    int data;
    // tree children. Handled by parsing of tree
    struct transferTree *left;
    struct transferTree *right;
};
typedef struct transferTree transferTree;

int height(transferTree *t){
    // returns height of binary transferTree (unused)
    if(t == NULL){
        return 0;
    }
    else if(t->left == NULL && t->right == NULL){
        return 1;
    }
    else{
        if(height(t->left)>height(t->right)){
            return(height(t->left));
        }
        else{
            return(height(t->right));
        }
    }
}

int size(transferTree *t){
    // returns # of nodes in transferTree
    if(t == NULL){
        return 0;
    }
    else if(t->operation > 0){
        switch(t->operation){
            case 1:
                return (1+size(t->left)+size(t->right));
                break;
            case 2:
                return (1+size(t->left)+size(t->right));
                break;
            case 3:
                return (1+size(t->left)+size(t->right));
                break;
            case 4:
                return (1+size(t->left)+size(t->right));
                break;
            case 5:
                return (1+size(t->right));
                break;
            case 6:
                return (1+size(t->left)+size(t->right));
                break;
            case 7:
                return (1+size(t->left)+size(t->right));
                break;
        }
    }
    else{
        return 1;
    }
}

void printTransferTreeHelp(transferTree *t){
    // helper for printTransferTree
    if(t){
        if(t->operation > 0){
            printf("(");
            switch(t->operation){
                case 1:
                    printf("and ");
                    break;
                case 2:
                    printf("or ");
                    break;
                case 3:
                    printf("nand ");
                    break;
                case 4:
                    printf("nor ");
                    break;
                case 5:
                    printf("not ");
                    break;
                case 6:
                    printf("if ");
                    break;
                case 7:
                    printf("xor ");
                    break;
            }
            printTransferTreeHelp(t->left);
            printf(" ");
            if(t->right){
                printTransferTreeHelp(t->right);
            }
            printf(")");
        }
        else{
            printf("%d",t->data);
            // if(t->left != NULL || t->right != NULL){
            //     printf("IM LEAF BUT HAVE CHIDLREN\n");
            // }
        }
    }
}

void printTransferTree(transferTree *t){
    // utility function for printing transfer tree operations (not very pretty atm)
    // see struct for meaning of #'s
    printTransferTreeHelp(t);
    printf("\n");
}

void printPointers(transferTree *t){
    // returns # of nodes in transferTree
    if(t){
        // printTransferTree(t);
        printf("(t: %d, ", t );
        printf("t->prev %d)\n", t->prev);
        // for some reason, leaf children are not null?
        if(t->operation != 0 && t->left){
            // printf("going left\n");
            // printTransferTree(t->left);
            printPointers(t->left);
            if(t->right){
                // printf("going right\n");
                // printTransferTree(t->right);
                printPointers(t->right);
            }
        }
        else{
            // printf("null childre %d\n", t);
        }
    }
}

transferTree *treeIndex(transferTree *t, int i){
    // This is supposed to traverse the tree left to right, then up to down, and return the ith node
    // Used when randomly selecting a node from which to do crossover
    if(i == 0){
        return t;
    }
    else if(size(t->left)<i){
        return treeIndex(t->right, i-size(t->left)-1);
    }
    else{
        return treeIndex(t->left, i-1);
    }
}

void freeTransferTree(transferTree *t){
    // free a transferTree
    if(t){
        if(t->operation != 0 && t->left){
            freeTransferTree(t->left);
        }
        if(t->operation != 0 && t->right){
            freeTransferTree(t->right);
        }
        free(t);
    }
}

int transferTreeEval(transferTree *t, int cn, int cne, int ce, int cse, int cs, int csw, int cw, int cnw, int c){
    // can i just cast as char?
    // 0:leaf, 1:AND, 2:OR, 3:NAND, 4:NOR, 5:NOT, 6:IF, 7:XOR
    if(t->operation == 0){
        switch(t->data){
            case 0:
                return c;
            case 1:
                return cnw;
            case 2:
                return cw;
            case 3:
                return csw;
            case 4:
                return cs;
            case 5:
                return cse;
            case 6:
                return ce;
            case 7:
                return cne;
            case 8:
                return cn;
            default:
                return 0;
        }
    }
    else if(t->operation == 1){
        // and
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        return (l & r);
    }
    else if(t->operation == 2){
        // or
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        return (l | r);
    }
    else if(t->operation == 3){
        // nand
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        if(l & r){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(t->operation == 4){
        // nor
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        if(l | r){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(t->operation == 5){
        // not
        // only left should be not null
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        if(l){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(t->operation == 6){
         // if
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        if(r){
            return 1;
        }
        else{
            if(l==0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    else if(t->operation == 7){
        // xor
        int l = transferTreeEval(t->left, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        int r = transferTreeEval(t->right, cn, cne, ce, cse, cs, csw, cw, cnw, c);
        return (l^r);
    }
    else{
        return 0;
    }
}

void parseTransferTree(transferTree *t, int *transferArray){
    // Generate a transfer array based on transfer tree
    // see updateCell8 in cells8.c for more details
    for(int i=0;i<512;i++){
        transferArray[i] = transferTreeEval(t, (i>>8)&1, (i>>7)&1, (i>>6)&1, (i>>5)&1, (i>>4)&1, (i>>3)&1, (i>>2)&1, (i>>1)&1, i&1);
    }
}

transferTree *randomTransferTreeGen(int depth){
    // generates a random transfertree of maximum height depth
    if(depth > 0){
        transferTree *t = malloc(sizeof(transferTree));
        t->prev = NULL;
        // choose a random operation
        int operation = rand()%8;
        t->operation = operation;

        if(operation == 0){
            // if leaf, set leaf value
            t->data = rand()%9;
        }
        else{
            // not leaf, set leaf to -1, create subtree
            t->data = -1;
            if(operation == 5){
                // operation is not, only do left subtree
                t->left = randomTransferTreeGen(depth-1);
                t->left->prev = t;
                t->right = NULL;
            }
            else{
                t->left = randomTransferTreeGen(depth-1);
                t->left->prev = t;
                t->right = randomTransferTreeGen(depth-1);
                t->right->prev = t;
            }
        }
        return t;
    }
    else{
        transferTree *t = malloc(sizeof(transferTree));
        t->operation = 0;
        t->prev = NULL;
        t->data = rand()%9;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
}

transferTree *copyTransferTree(transferTree *src){
    // copies a transferTree and returns pointer to it
    if(src == NULL){
        return NULL;
    }
    else{
        transferTree *t = malloc(sizeof(transferTree));
        t->prev = NULL;
        t->operation = src->operation;
        t->data = src->data;
        // again for some reason children nodes are nonNull
        if(t->operation != 0 && src->left){
            // printf("op: %d\n",t->operation);
            t->left = copyTransferTree(src->left);
            t->left->prev = t;
            t->right = NULL;
            if(src->right){
                // printf("op: %d, rightnotnull\n", t->operation);
                t->right = copyTransferTree(src->right);
                t->right->prev = t;
            }
        }
        // printf("tee\n");
        // printTransferTree(t);
        // printf("teend\n");
        return t;
    }
}

int isLeftChildOf(transferTree *t_child, transferTree *t_parent){
    // printf("t_child: %d, t_child->prev: %d, t_parent: %d, t_parent->left: %d\n",t_child, t_child->prev, t_parent, (t_child->prev)->left);
    if(t_child->prev == t_parent){
        // printf("correct parent\n");
        if(t_parent->left == t_child){
            // printf("correct side\n");
            return 1;
        }
    }
    return 0;
}

int isRightChildOf(transferTree *t_child, transferTree *t_parent){
    // printf("t_child: %d, t_child->prev: %d, t_parent: %d, t_parent->right %d\n",t_child, t_child->prev, t_parent, (t_child->prev)->right);
    if(t_child->prev == t_parent){
        // printf("correct parent\n");
        if(t_parent->right == t_child){
            // printf("correct side\n");
            return 1;
        }
    }
    return 0;
}

transferTree *crossoverTransferTrees(transferTree *t1, transferTree *t2){
    // Performs crossover of parents t1 and t2 to return new transferTree t
    int t1_size = size(t1);
    int t2_size = size(t2);
    transferTree *t = malloc(sizeof(transferTree));
    if(rand()%2==0){
        // printf("root t1\n");
        t = copyTransferTree(t1);
        // printf("done copying\n");
        // select a random node from t1, and assign a random node from t2 as its left subtree
        // printf("printingtree\n");
        transferTree *dst = treeIndex(t,rand()%t1_size);
        transferTree *src = treeIndex(t2,rand()%t2_size);
        // printf("dst: "); printTransferTree(dst);
        // printf("src: "); printTransferTree(src);
        // printf("t pointers:\n");
        // printPointers(t);
        if(dst == NULL){
            return t;
        }
        else if(dst->prev == NULL){
            freeTransferTree(t);
            t = copyTransferTree(src);
        }
        else if(isLeftChildOf(dst, dst->prev)){
            // dst is the left child of its parent
            // printf("ball_left\n");
            dst->prev->left = copyTransferTree(src);
            // printf("dst->prev->left: %d\n", dst->prev->left);
            // printf("dst: %d\n", dst);
            freeTransferTree(dst);
        }
        else if(isRightChildOf(dst, dst->prev)){
            // dst is the right child of its parent
            // printf("ball_right\n");
            dst->prev->right = copyTransferTree(src);
            // printf("dst->prev->right: %d\n", dst->prev->right);
            // printf("dst: %d\n", dst);
            freeTransferTree(dst);
        }
        else{
            // printf("bad child\n");
            // other default behavior is ok too
            freeTransferTree(dst->left);
            freeTransferTree(dst->right);
            dst->left = NULL;
            dst->right = NULL;
        }
    }
    else{
        // printf("root t2\n");
        t = copyTransferTree(t2);
        // printf("done copying\n");
        // select a random node from t2, and assign a random node from t1 as its left subtree
        transferTree *dst = treeIndex(t,rand()%t2_size);
        transferTree *src = treeIndex(t1,rand()%t1_size);

        // printf("dst: "); printTransferTree(dst);
        // printf("src: "); printTransferTree(src);
        if(dst == NULL){
            return t;
        }
        else if(dst->prev == NULL){
            freeTransferTree(t);
            t = copyTransferTree(src);
        }
        else if(isLeftChildOf(dst, dst->prev)){
            // t1 is the left child of its parent
            // printf("ball_left\n");
            dst->prev->left = copyTransferTree(src);
            freeTransferTree(dst);
        }
        else if(isRightChildOf(dst, dst->prev)){
            // t1 is the right child of its parent
            // printf("ball_right\n");
            dst->prev->right = copyTransferTree(src);
            freeTransferTree(dst);
        }
        else{
            // printf("bad child\n");
            // some error happened. Just cut off the tree at the dst point?
            // other default behavior is ok too
            freeTransferTree(dst->left);
            freeTransferTree(dst->right);
            dst->left = NULL;
            dst->right = NULL;
        }
    }
    return t;
}

void mutate(transferTree *t, double p){
    if(t != NULL){
        if(rand()/RAND_MAX < p){
            // there is a problem if we switch from a binary to a unary operator
            if(t->operation == 0){
                t->data = rand()%8;
            }
            else{
                if(t->operation == 5){
                    mutate(t->left, p);
                }
                else{
                    int choices[6] = {1,2,3,4,6,7};
                    t->operation = choices[rand()%6];
                    mutate(t->left, p);
                    mutate(t->right, p);
                }
            }
        }
    }
}
