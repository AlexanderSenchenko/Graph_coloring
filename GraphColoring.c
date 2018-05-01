#include "GraphColoring.h"

void ColoringGraph(Graph *graph)
{
	#if 0
	if (TwoColor(graph) == 0) {
		PrintInfoGraph(graph);

		GraphImageCreation(graph);
		system("dot -Tpng graph.gv -ograph.png");
	}

	RebootGraph(graph);
	#endif

	#if 1
	if (TrheeColor(graph) == 0) {
		PrintInfoGraph(graph);

		GraphImageCreation(graph);
		system("dot -Tpng graph.gv -ograph.png");
	}
	#endif
}

//////////////////// 2 ////////////////////
int TwoColor(Graph *graph)
{
	Node *node = graph->Head;

	node->color = 0;

	if (RunTwoColor(node) == 1) {
		printf("Error, 2 color\n");
		return 1;
	}

	return 0;
}

int RunTwoColor(Node *node)
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
		if (RunTwoColor(contact->node) == 1)
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
	int act = CheckPow(graph, 6);
	if (act == 1) {
		// printf("Not available color");
		return 1;
	}

	return 0;
}

int CheckPow(Graph *graph, int pow)
{
	Node *node = graph->Head;
	Node *delNode = NULL;

	if (node->next == NULL) {
		node->status = 1;
		node->color = 0;
		return 0;
	}

	#if 1
	for (int i = 0; i < graph->number; i++) {
		if (node->number < pow && node->status != 1) {
			delNode = node;
			graph = DeleteNodeSave(graph, delNode);

			CheckPow(graph, pow);

			graph = RestoringNode(graph, delNode);

			int act = RunTrheeColor(delNode, pow);
			if (act == 1)
				return 1;
		}

		node = node->next;
	}
	#endif

	return 0;
}

int RunTrheeColor(Node *node, int numColor)
{
	if (node->status == 1)
		return 0;
	
	int act = CheckNColor(node, numColor, 0);

	if (act == 1)
		return 1;

	return 0;
}

int CheckNColor(Node *node, int numColor, int color)
{
	if (node->status == 1)
		return 0;

	HashT *NCont = node->Contact;

	for (int i = 0; i < node->number && node->color == -1; i++) {
		if (NCont->node->color == color) {
			int act = CheckNColor(node, numColor, color + 1);

			if (act == 1)
				return 1;

			// color++;
		}
		NCont = NCont->next;
	}

	if (numColor < color) {
		printf("Not available color");
		return 1;
	}

	if (node->color == -1) {
		node->color = color;
		node->status = 1;
	}

	return 0;
}
//////////////////// 4 ////////////////////

//////////////////// 5 ////////////////////

////////////////// Other //////////////////