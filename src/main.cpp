#include <bits/stdc++.h>
#include "Globals.h"
#include "GraphUtils.h"
#include "RootedTree.h"
#include "Classifier.h"
#include "ProcessStatus.h"
#include "RepairTree.h"

using namespace std;

void ProcessAllEdges(vector<Edge> &Ex, vector<Edge> &Er, vector<Edge> &CE) {
    // Create Tree
    buildExAdj();
    Create_Tree();

    vector<EdgeStatus> Status(CE.size(), NONE);
    vector<Edge> Marked(CE.size());

    while(!CE.empty()) {
        Classify_Edges(CE, Status, Marked);
        Process_Status(Ex, Er, CE, Status, Marked);
        break; 
    }

    vector<EdgeStatus> StatusR(Er.size(), NONE);
    vector<Edge> MarkedR(Er.size());

    Repair_Tree(Er, StatusR, MarkedR);
    Process_Status(Ex, Er, Er, StatusR, MarkedR);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V;
    int e;
    cin >> e;
    Ex.resize(e);
    for (int i = 0; i < e; i++) {
        int u,v; double w;
        cin >> u >> v >> w;
        Ex[i] = Edge(u,v,w);
    }
    int r;
    cin >> r;
    Er.resize(r);
    for (int i = 0; i < r; i++) {
        int u,v; double w;
        cin >> u >> v >> w;
        Er[i] = Edge(u,v,w);
    }
    int c;
    cin >> c;
    CE.resize(c);
    for (int i = 0; i < c; i++) {
        int u,v; double w;
        cin >> u >> v >> w;
        CE[i] = Edge(u,v,w);
    }

    ProcessAllEdges(Ex, Er, CE);

    cout << "Updated Key Edges:\n";
    for (auto &ed : Ex) {
        if (ed.w >= 0 && ed.w < INF) {
            cout << ed.u << " " << ed.v << " " << ed.w << "\n";
        }
    }

    return 0;
}
