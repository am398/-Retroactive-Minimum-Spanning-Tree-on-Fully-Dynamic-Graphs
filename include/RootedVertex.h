#ifndef ROOTEDVERTEX_H
#define ROOTEDVERTEX_H

#include "Edge.h"

struct RootedVertex {
    int parent;
    int root;
    Edge maxE;
    RootedVertex() {
        parent = -1;
        root = -1;
        maxE = Edge(-1,-1,-1);
    }
};

#endif
