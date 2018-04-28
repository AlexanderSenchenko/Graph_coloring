#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "graph.h"

void ColoringGraph(Graph *graph);

int TwoColor(Graph *graph);
int RunColor(Node *node);
int CheckColorNode(Node *node, int color);

#endif