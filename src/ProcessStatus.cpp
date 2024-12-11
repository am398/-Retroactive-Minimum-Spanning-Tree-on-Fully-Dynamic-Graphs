#include "ProcessStatus.h"
#include "Globals.h"
#include "GraphUtils.h"
#include "RootedTree.h"

void Process_Status(std::vector<Edge> &Ex, std::vector<Edge> &Er, std::vector<Edge> &CE, 
                    std::vector<EdgeStatus> &Status, std::vector<Edge> &Marked) {
    std::vector<Edge> newCE;

    for (int i = 0; i < (int)CE.size(); i++) {
        Edge &E = CE[i];
        EdgeStatus S = Status[i];
        if (S == DEL) {
            // Mark E as deleted in Ex
            for (int j = 0; j < (int)Ex.size(); j++) {
                if ((Ex[j].u == E.u && Ex[j].v == E.v && fabs(Ex[j].w - E.w)<1e-9) ||
                    (Ex[j].v == E.u && Ex[j].u == E.v && fabs(Ex[j].w - E.w)<1e-9)) {
                    Ex[j].w = INF;
                    break;
                }
            }
        } else if (S == NONE) {
            Er.push_back(E);
        } else if (S == INS) {
            Ex.push_back(E);
        } else if (S == RPL) {
            Edge Erpl = Marked[i];
            int rpl_idx = -1;
            for (int j = 0; j < (int)Ex.size(); j++) {
                if ((Ex[j].u == Erpl.u && Ex[j].v == Erpl.v && fabs(Ex[j].w - Erpl.w)<1e-9) ||
                    (Ex[j].v == Erpl.u && Ex[j].u == Erpl.v && fabs(Ex[j].w - Erpl.w)<1e-9)) {
                    rpl_idx = j;
                    break;
                }
            }
            if (rpl_idx != -1 && Ex[rpl_idx].replacedId == i) {
                Ex.push_back(E);
                Ex[rpl_idx].w = -1; // replaced
            } else {
                newCE.push_back(E);
            }
        }
    }

    // Rebuild adj and update RootedT via BFS
    buildExAdj();
    for (int i = 0; i < V; i++) {
        RootedT[i].parent = -1;
        RootedT[i].root = -1;
        RootedT[i].maxE = Edge(-1,-1,-1);
    }
    Create_Tree();

    if (!newCE.empty()) {
        std::vector<EdgeStatus> newStatus(newCE.size(), NONE);
        std::vector<Edge> newMarked(newCE.size());
        Classify_Edges(newCE, newStatus, newMarked);
        Process_Status(Ex, Er, newCE, newStatus, newMarked);
    }
}
