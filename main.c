#include "graph.h"

int main()
{
	int line = 0;
	int column = 0;
	int *Matrix = NULL;
	struct Graph *graph;

	GetMatrix(&Matrix, &line, &column);
	//PrintMatrix(Matrix, line, column);

	graph = CreateGraph(Matrix, line, column);
	if (graph == NULL) {
		printf("Error\n");
		return 0;
	}
	if (graph->Head == NULL) {
		printf("Error\n");
		return 0;
	}

	// Node *node = graph->FirstNode;
	// while (node != NULL) {
	// 	printf("%p\n", node);
	// 	node = node->next;
	// }

	GraphImageCreation(Matrix, line, column);
	system("dot -Tpng graph.gv -ograph.png");

	free(Matrix);

	return 0;
}