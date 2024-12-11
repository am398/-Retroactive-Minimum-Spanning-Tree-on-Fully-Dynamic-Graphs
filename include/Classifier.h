#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "Edge.h"
#include <vector>

enum EdgeStatus {
    NONE,
    DEL,
    INS,
    RPL
};

void Classify_Edges(std::vector<Edge> &CE, std::vector<EdgeStatus> &Status, std::vector<Edge> &Marked);

#endif
