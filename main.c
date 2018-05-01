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

	#if 0
	//// Test delete node ////
	PrintInfoGraph(graph);
	
	Node *node = graph->Head->next;
	graph = DeleteNodeSave(graph, node);

	PrintInfoGraph(graph);

	graph = RestoringNode(graph, node);

	PrintInfoGraph(graph);

	#endif

	ColoringGraph(graph);

	free(Matrix);

	return 0;
}