#include "RepairTree.h"
#include "Globals.h"
#include "GraphUtils.h"

void Repair_Tree(std::vector<Edge> &Er, std::vector<EdgeStatus> &Status, std::vector<Edge> &Marked) {
    for (int i = 0; i < (int)Er.size(); i++) {
        Status[i] = NONE;
        Marked[i] = Edge(-1,-1,-1);
    }

    for (int i = 0; i < (int)Er.size(); i++) {
        Edge &E = Er[i];
        int ru = findRoot(E.u), rv = findRoot(E.v);
        if (ru != rv) {
            Edge MaxW = findMaxEdgeOnPath(E.u,E.v);
            if (MaxW.w == INF) {
                Status[i] = RPL;
                Marked[i] = MaxW;
                for (int j = 0; j < (int)Ex.size(); j++) {
                    if ((Ex[j].u == MaxW.u && Ex[j].v == MaxW.v && fabs(Ex[j].w - MaxW.w)<1e-9) ||
                        (Ex[j].v == MaxW.u && Ex[j].u == MaxW.v && fabs(Ex[j].w - MaxW.w)<1e-9)) {
                        Ex[j].replacedId = i;
                        break;
                    }
                }
            }
        }
    }
}
