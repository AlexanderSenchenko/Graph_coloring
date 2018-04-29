#include "GraphColoring.h"

void ColoringGraph(Graph *graph)
{
	#if 1
	if (TwoColor(graph) == 0) {
		PrintInfoGraph(graph);

		GraphImageCreation(graph);
		system("dot -Tpng graph.gv -ograph.png");
	}

	RebootGraph(graph);
	#endif

	// TrheeColor(graph);
}

//////////////////// 2 ////////////////////
int TwoColor(Graph *graph)
{
	Node *node = graph->Head;

	node->color = 0;

	if (RunColor(node) == 1) {
		printf("Error, 2 color\n");
		return 1;
	}

	return 0;
}

int RunColor(Node *node)
{
	if (node->status == 1)
		return 0;

	int nextColor;
	if (node->color == 0) {
		nextColor = 1;
	} else if (node->color == 1) {
		nextColor = 0;
	}
	// printf("ind = %d\n", node->index);

	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		int act = CheckColorNode(contact->node, node->color);
		if (act == 1) {
			return 1;
		} else if (act == 0) {
			contact->node->color = nextColor;
		}
		
		contact = contact->next;
	}

	node->status = 1;

	contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (RunColor(contact->node) == 1)
			return 1;
		contact = contact->next;
	}

	return 0;
}

int CheckColorNode(Node *node, int color)
{
	if (node->color == color) {
		// printf("ind: %d\n", node->index);
		// printf("color: %d\n", node->color);
		return 1;
	}

	if (node->color != -1)
		return 2;

	return 0;
}

//////////////////// 3 ////////////////////
int TrheeColor(Graph *graph)
{
	// Node *node = graph->Head;



	return 0;
}

//////////////////// 4 ////////////////////

//////////////////// 5 ////////////////////