#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
	struct Node *Head;		// Указатель на первый узел графа
	int number;				// Колличество узлов в графе
} Graph;

typedef struct Node
{
	struct Node *next;		// Следущий по индексу узелу
	struct Node *parent;	// Предыдущий по индексу узелу
	struct HashT *Contact;	// Список связей
	int index;				// Номер узла
	int color;				// Цвет узла
	int number;				// Колличество связей
	int status;				// Проверка на посещаемость
} Node;

typedef struct HashT
{
	struct Node *node;		// Указатеь на связный узел
	struct HashT *next;		// Следещий связный узел
	struct HashT *parent;	// Предыдущий связный узел
} HashT;

void GetMatrix(int **Matrix, int *line, int *column);	// Чтение матрицы из файла
int GetIndex(int line, int i, int j);					// Возвращает индекс элемента
void PrintMatrix(int *Matrix, int line, int column);	// Вывод матрицы в терминал

Graph *CreateGraph(int *Matrix, int line, int column);	// Инициализация графа
Node *CreateNode(int index, int num_contact);			// Инициализация узла графа
HashT *CreateNodeHashT();								// Инициализация списка смежных узлов

Graph *DeleteNodeSave(Graph *graph, Node *node);		// Удаление из графа узла
void DeleteNodeList(Node *Head, Node *node);			// Удаление удаленного узла из списка смежных узлов всех узлов графа

Graph *RestoringNode(Graph *graph, Node *node);			// Вставка удаленного узла в граф
void RestoringContact(Node *node);						// Вставка удаленного узла в список связей каждого узла, у которых это узел ранее пресутствовал
HashT *SortListNode(HashT *NodeCont);					// Сортирока списка смежных узлов по возрастанию индека

void PrintInfoGraph(Graph *graph);						// Вывод в терминал всей информации о графе
void RebootGraph(Graph *graph);							// Сброс color и status всех узлов графа

void GraphImageCreation(Graph *graph);					// Фрмирование файла для отрисовки графа

#endif