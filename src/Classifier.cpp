#include "Classifier.h"
#include "GraphUtils.h"
#include "Globals.h"

void Classify_Edges(std::vector<Edge> &CE, std::vector<EdgeStatus> &Status, std::vector<Edge> &Marked) {
    for (int i = 0; i < (int)CE.size(); i++) {
        Status[i] = NONE;
        Marked[i] = Edge(-1,-1,-1);
    }

    for (int i = 0; i < (int)CE.size(); i++) {
        Edge &E = CE[i];
        if (E.w > 1e14) {
            // deletion
            Status[i] = DEL;
        } else {
            // insertion
            int u = E.u, v = E.v;
            int ru = findRoot(u), rv = findRoot(v);
            if (ru != rv) {
                Status[i] = INS;
            } else {
                // same component
                Edge MaxW = findMaxEdgeOnPath(u,v);
                if (MaxW.w > E.w && MaxW.w >= 0) {
                    int x = MaxW.replacedId;
                    if (x == -1 || (x>=0 && x<(int)CE.size() && CE[x].w > E.w)) {
                        Marked[i] = MaxW;
                        Status[i] = RPL;
                        // Set MaxW replacedId in Ex
                        for (int j = 0; j < (int)Ex.size(); j++) {
                            if ((Ex[j].u == MaxW.u && Ex[j].v == MaxW.v && fabs(Ex[j].w - MaxW.w)<1e-9) ||
                                (Ex[j].v == MaxW.u && Ex[j].u == MaxW.v && fabs(Ex[j].w - MaxW.w)<1e-9)) {
                                Ex[j].replacedId = i;
                                break;
                            }
                        }
                    }
                }
                // else Status remains NONE
            }
        }
    }
}
