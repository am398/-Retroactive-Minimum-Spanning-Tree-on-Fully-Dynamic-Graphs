#ifndef PROCESSSTATUS_H
#define PROCESSSTATUS_H

#include "Edge.h"
#include "Classifier.h"
#include <vector>

void Process_Status(std::vector<Edge> &Ex, std::vector<Edge> &Er, std::vector<Edge> &CE, 
                    std::vector<EdgeStatus> &Status, std::vector<Edge> &Marked);

#endif
