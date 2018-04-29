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

	ColoringGraph(graph);

	#if 0	
	//// Test delete node ////
	PrintInfoGraph(graph);
	
	Node *node = DeleteNodeSave(&graph, 0);
	printf("%d\t", node->index);
	if (node->next != NULL)
		printf("%d\t", node->next->index);
	if (node->parent != NULL)
		printf("%d\n", node->parent->index);

	PrintInfoGraph(graph);
	#endif

	free(Matrix);

	return 0;
}