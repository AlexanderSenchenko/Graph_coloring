#include "GraphColoring.h"

int main()
{
	int line = 0;
	int column = 0;
	int *Matrix = NULL;
	struct Graph *graph;

	GetMatrix(&Matrix, &line, &column);

	graph = CreateGraph(Matrix, line, column);
	if (graph == NULL) {
		printf("Error\n");
		return 0;
	}
	if (graph->Head == NULL) {
		printf("Error\n");
		return 0;
	}

	// ColoringGraph(graph);

	#if 1
	//// Test delete node ////
	// PrintInfoGraph(graph);
	
	Node *node = DeleteNodeSave(&graph, 7);

	#if 0
	printf("Del = %d\n", node->index);
	if (node->parent != NULL)
		printf("Par = %d\t", node->parent->index);
	if (node->next != NULL)
		printf("Nex = %d\n", node->next->index);
	#endif

	// PrintInfoGraph(graph);
	graph = RestoringNode(graph, node);

	PrintInfoGraph(graph);

	#endif

	free(Matrix);

	return 0;
}