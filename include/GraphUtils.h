#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include "Edge.h"
#include "RootedVertex.h"
#include <vector>

extern std::vector<Edge> Ex; 
extern std::vector<Edge> Er; 
extern std::vector<Edge> CE; 
extern std::vector<RootedVertex> RootedT;
extern std::vector<std::vector<std::pair<int,int>>> adjEx;

void buildExAdj();
int findRoot(int v);
Edge findMaxEdgeOnPath(int u, int v);

#endif
