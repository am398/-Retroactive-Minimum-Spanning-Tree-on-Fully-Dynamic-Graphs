#include "RootedTree.h"
#include "GraphUtils.h"
#include "Globals.h"
#include "RootedVertex.h"
#include <queue>

int findHighestDegreeVertex() {
    int max_deg = -1;
    int vertex = 0;
    for (int i = 0; i < V; i++) {
        if (RootedT[i].parent == -1) {
            int deg = (int)adjEx[i].size();
            if (deg > max_deg) {
                max_deg = deg;
                vertex = i;
            }
        }
    }
    return vertex;
}

void bfsFromRoot(int root) {
    RootedT[root].parent = root;
    RootedT[root].root = root;
    std::queue<int>q;
    for (auto &nbr : adjEx[root]) {
        int v = nbr.first;
        int eidx = nbr.second;
        if (RootedT[v].parent == -1) {
            RootedT[v].parent = root;
            RootedT[v].root = root;
            RootedT[v].maxE = Ex[eidx];
            q.push(v);
        }
    }

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto &nbr : adjEx[cur]) {
            int nxt = nbr.first;
            int eidx = nbr.second;
            if (RootedT[nxt].parent == -1) {
                RootedT[nxt].parent = cur;
                RootedT[nxt].root = RootedT[cur].root;
                // update maxE
                double curMax = RootedT[cur].maxE.w;
                if (Ex[eidx].w > curMax) {
                    RootedT[nxt].maxE = Ex[eidx];
                } else {
                    RootedT[nxt].maxE = RootedT[cur].maxE;
                }
                q.push(nxt);
            }
        }
    }
}

void Create_Tree() {
    for (int i = 0; i < V; i++) {
        RootedT[i].parent = -1;
        RootedT[i].root = -1;
        RootedT[i].maxE = Edge(-1,-1,-1);
    }

    bool allAssigned = false;
    while(!allAssigned) {
        allAssigned = true;
        for (int i = 0; i < V; i++) {
            if (RootedT[i].parent == -1) {
                int r = findHighestDegreeVertex();
                RootedT[r].parent = r;
                RootedT[r].root = r;
                bfsFromRoot(r);
                break;
            }
        }
        for (int i = 0; i < V; i++) {
            if (RootedT[i].parent == -1) {
                allAssigned = false;
                break;
            }
        }
    }
}
