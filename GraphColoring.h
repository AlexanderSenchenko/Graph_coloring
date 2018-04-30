#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "Graph.h"

void ColoringGraph(Graph *graph);

int TwoColor(Graph *graph);
int RunTwoColor(Node *node);
int CheckColorNode(Node *node, int color);

int TrheeColor(Graph *graph);
int CheckPow(Graph *graph, int pow);
int RunTrheeColor(Node *node, int numColor);

#endif