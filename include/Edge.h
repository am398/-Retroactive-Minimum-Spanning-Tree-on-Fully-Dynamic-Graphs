#ifndef EDGE_H
#define EDGE_H

struct Edge {
    int u, v;
    double w;
    int replacedId; // -1 if no replacement

    Edge() : u(-1), v(-1), w(0.0), replacedId(-1) {}
    Edge(int u, int v, double w) : u(u), v(v), w(w), replacedId(-1) {}
};

#endif
