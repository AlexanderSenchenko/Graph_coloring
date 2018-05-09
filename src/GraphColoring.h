#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "Graph.h"

void ColoringGraph(Graph *graph);							    // Пользовательское меню
int TwoColor(Graph *graph);									    // Начало покраски в 2 цвета
int TwoColorRun(Node *node);								    // Рекурсивный обход узлв
int TwoColorCheckNode(Node *node, int color);				    // Проверка status и color узла
int TFFColor(Graph *graph, int pow);				            // Проверка узлов на количество связей и продолжение окраски
int TFFColorRun(Graph *graph, Node *node, int color);			// Зпуск проверки смежных узлов
int TFFColorNode(Node *node, int color);
int TFFColorCheckContact(Node *node, int numColor, int color);	// Проверка смежных узлов для окраски узла в свобдный цвет
int NColor(Graph *graph);									    // Начало раскраски в N цветов
int NColorRun(Node *node);                                      // Покраска узла 
int NColorRunContact(Node *node);                               // Обход смежных узлов
int NColorContact(Node *node);                                  // Покраска смежных узлв
int NColorCheckContact(Node *node, int color);                  // Поиск доступного цвета

#endif