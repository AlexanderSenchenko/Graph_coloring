#include "graph.h"

void GetMatrix(int **Matrix, int *line, int *column)
{
	FILE *stream = fopen("Matrix.txt", "r");
	if (!stream) {
		return;
	}

	char *str = NULL;
	size_t len = 0;
	int count, index;

	while (getline(&str, &len, stream) != -1) {
		count = 0;
		for (int i = 0; str[i] != 0; i++) {
			if (str[i] == ' ') {
				count++;
			}
		}
		count++;

		if (count > *column) {
			*column = count;
		}
		(*line)++;
	}

	fseek(stream, 0, SEEK_SET);

	*Matrix = malloc(sizeof(int) * *line * *column);
	for (int i = 0; i < *line; i++) {
		for (int j = 0; j < *column; j++) {
			index = GetIndex(*line, i, j);
			fscanf(stream, "%d", &(*Matrix)[index]);
		}
	}

	free(str);
	fclose(stream);
}

int GetIndex(int line, int i, int j)
{
	return line * i + j;
}

void PrintMatrix(int *Matrix, int line, int column)
{
	int index;
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			index = GetIndex(line, i, j);
			printf("%d ", Matrix[index]);
		}
		printf("\n");
	}
}

Graph *CreateGraph(int *Matrix, int line, int column)
{
	Graph *graph = malloc(sizeof(Graph));
	Node **ArrNode = malloc(sizeof(ArrNode) * line);

	graph->number = line;

	for (int i = 0; i < line; i++) {
		int num_contact = 0;

		for (int j = 0; j < column; j++) {
			if (Matrix[GetIndex(line, i, j)] == 1)
				num_contact++;
		}

		ArrNode[i] = CreateNode(i, num_contact);
	}

	free(ArrNode);

	return graph;
}

Node *CreateNode(int index, int num_contact)
{
	Node *node = malloc(sizeof(Node));
	node->Contact = malloc(sizeof(Node) * num_contact);
	node->index = index;
	node->color = -1;
	node->number = num_contact;
	node->status = 1;

	return node;
}

void ColoringGraph()
{
	
}

void GraphImageCreation(int *Matrix, int line, int column)
{
	FILE *out = fopen("graph.gv", "w");
	if (out == NULL) {
		return;
	}

	int index, value;
	char elem = '"';
	char *colors[6] = {"red", "lawngreen", "deeppink", "cyan", "indigo", "purple"};

	fprintf(out, "digraph HelloGraph {\n");

	fprintf(out, "\tnode [shape=%ccircle%c, ", elem, elem);
	fprintf(out, "style=%cfilled%c, ", elem, elem);
	fprintf(out, "margin=%c0.01%c];\n", elem, elem);

	fprintf(out, "\tedge [dir=%cnone%c];\n\n", elem, elem);

	for (int i = 0; i < line; i++) {
		fprintf(out, "\t%cNode %d%c [fillcolor=%c%s%c]\n", elem, i, elem, elem, colors[i], elem);
	}
	fprintf(out, "\n");

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			index = GetIndex(line, i, j);
			value = Matrix[index];
			if (i < j && value > 0) {
				fprintf(out, "\t%cNode %d%c -> ", elem, i, elem);
				fprintf(out, "%cNode %d%c;\n", elem, j, elem);
			}
		}
	}
	fprintf(out, "}\n");
	fclose(out);
}
