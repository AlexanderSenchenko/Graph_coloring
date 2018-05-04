#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
	struct Node *Head;
	int number;
} Graph;

typedef struct Node
{
	struct Node *next;		// Следущий по индексу узелу
	struct Node *parent;	// Предыдущий по индексу узелу
	struct HashT *Contact;	// Список связей
	int index;				// Номер узла
	int color;				// Цвет
	int number;				// Колличество звязей
	int status;				// Проверка на посещаемость
} Node;

typedef struct HashT
{
	struct Node *node;
	struct HashT *next;
	struct HashT *parent;
} HashT;

void GetMatrix(int **Matrix, int *line, int *column);
int GetIndex(int line, int i, int j);
void PrintMatrix(int *Matrix, int line, int column);

Graph *CreateGraph(int *Matrix, int line, int column);
Node *CreateNode(int index, int num_contact);
HashT *CreateNodeHashT();

Graph *DeleteNodeSave(Graph *graph, Node *node);
void DeleteNodeList(Node *Head, Node *node);

Graph *RestoringNode(Graph *graph, Node *node);
void RestoringContact(Node *node);
HashT *SortListNode(HashT *NodeCont);

void PrintInfoGraph(Graph *graph);
void RebootGraph(Graph *graph);

void GraphImageCreation(Graph *graph);

#endif