#include "GraphUtils.h"
#include "Globals.h"
#include <algorithm>
#include <queue>

std::vector<Edge> Ex; 
std::vector<Edge> Er; 
std::vector<Edge> CE; 
std::vector<RootedVertex> RootedT;
std::vector<std::vector<std::pair<int,int>>> adjEx;

void buildExAdj() {
    adjEx.assign(V, {});
    for (int i = 0; i < (int)Ex.size(); i++) {
        Edge &e = Ex[i];
        if (e.u >= 0 && e.v >= 0 && e.w < INF && e.w >=0) {
            adjEx[e.u].push_back({e.v, i});
            adjEx[e.v].push_back({e.u, i});
        }
    }
}

int findRoot(int v) {
    return RootedT[v].root;
}

// Utility function to get path to root
static std::vector<int> getPathToRoot(int x) {
    std::vector<int> path;
    while (x != RootedT[x].parent) {
        path.push_back(x);
        x = RootedT[x].parent;
    }
    path.push_back(x);
    return path;
}

// Finds max weighted edge in path u -> v
Edge findMaxEdgeOnPath(int u, int v) {
    if (RootedT[u].root != RootedT[v].root) {
        return Edge(-1,-1,-1);
    }
    int root = RootedT[u].root;

    std::vector<int> upath = getPathToRoot(u);
    std::vector<int> vpath = getPathToRoot(v);
    std::reverse(upath.begin(), upath.end());
    std::reverse(vpath.begin(), vpath.end());

    int len = (int)std::min(upath.size(), vpath.size());
    int lca = -1;
    for (int i = 0; i < len; i++) {
        if (upath[i] == vpath[i]) lca = upath[i]; else break;
    }

    auto maxOnPath = [&](int start, int end) {
        double mxw = -1;
        Edge mxE(-1,-1,-1);
        int cur = start;
        while (cur != end) {
            int p = RootedT[cur].parent;
            if (p == cur) break;
            // Find edge cur-p
            bool found = false;
            for (auto &nb : adjEx[cur]) {
                if (nb.first == p) {
                    Edge &ed = Ex[nb.second];
                    if (ed.w > mxw) {
                        mxw = ed.w;
                        mxE = ed;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) break;
            cur = p;
        }
        return mxE;
    };

    Edge mxE1 = maxOnPath(u, lca);
    Edge mxE2 = maxOnPath(v, lca);

    if (mxE1.w > mxE2.w) return mxE1;
    return mxE2;
}
