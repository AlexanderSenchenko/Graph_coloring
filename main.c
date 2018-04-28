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

	free(Matrix);

	return 0;
}