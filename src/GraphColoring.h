#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "Graph.h"

void ColoringGraph(Graph *graph);							// Пользовательское меню
int TwoColor(Graph *graph);									// Начало покраски в 2 цвета
int TwoColorRun(Node *node);								// Рекурсивный обход узлв
int TwoColorCheckNode(Node *node, int color);				// Проверка status и color узла
int TFFColor(Graph *graph, int color);						// Начало покраски в заданное колличество цветов или меньше
int TFFColorCheckPow(Graph *graph, int pow);				// Проверка узлов на колличество связей и продолжение окраски
int TFFColorRun(Node *node, int numColor);					// Зпуск проверки смежных узлов
int TFFColorCheckNode(Node *node, int numColor, int color);	// Проверка смежных узлов для окраски узла в свобдный цвет
int NColor(Graph *graph);									//
int NColorRun(Node *node);
int NColorCheck(Node *node, int color);

#endif