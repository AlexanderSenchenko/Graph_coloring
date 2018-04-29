#include "Graph.h"

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

int GetIndex(int line, int i, int j) { return line * i + j; }

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

		if (i != 0)
			ArrNode[i - 1]->next = ArrNode[i];

		#if 0
		printf("%d\t", ArrNode[i]->index);
		printf("%p\t", ArrNode[i]);
		printf("%p\n", ArrNode[i]->next);
		#endif
	}

	graph->Head = ArrNode[0];

	Node *node = graph->Head;
	for (int i = 0; i < line; i++) {
		HashT *pcont = NULL;

		for (int j = 0; j < column; j++) {

			if (Matrix[GetIndex(line, i, j)] == 1) {
				HashT *contact = CreateNodeHashT();

				contact->node = ArrNode[j];
				contact->next = NULL;

				if (pcont != NULL)
					pcont->next = contact;
				
				pcont = contact;

				if (node->Contact == NULL) {
					node->Contact = contact;
				}

				contact = contact->next;
			}

		}
		node = node->next;
	}

	free(ArrNode);

	return graph;
}

Node *CreateNode(int index, int num_contact)
{
	Node *node = malloc(sizeof(Node));
	node->next = NULL;
	// node->Contact = malloc(sizeof(Node) * num_contact);
	node->Contact = NULL;
	node->index = index;
	node->color = -1;
	node->number = num_contact;
	node->status = 0;

	return node;
}

HashT *CreateNodeHashT()
{
	HashT *Contact = malloc(sizeof(Contact));
	Contact->node = NULL;
	Contact->next = NULL;

	return Contact;
}

void PrintInfoGraph(Graph *graph)
{
	Node *node = graph->Head;

	printf("Index\tNode\t\tNext\t\tColor\tNumCont\tStatus\n");
	
	for (int i = 0; i < graph->number; i++) {
		printf("%d\t", node->index);
		printf("%p\t", node);
		printf("%p\t", node->next);

		if (i == graph->number - 1)
			printf("\t");

		printf("%d\t", node->color);
		printf("%d\t", node->number);
		printf("%d\n", node->status);

		if (node->Contact != NULL) {
			HashT *contact = node->Contact;

			for (int j = 0; j < node->number; j++) {
				// printf(">ind: %d\t", node->Contact[j]->index);
				printf(">ind: %d\t", contact->node->index);
				// printf("%p\t\t\t", node->Contact[j]);
				// printf("color: %d\n", node->Contact[j]->color);
				printf("color: %d\n", contact->node->color);
				contact = contact->next;
			}
		}

		node = node->next;
	}
}

void RebootGraph(Graph *graph)
{
	Node *node = graph->Head;

	while (node != NULL) {
		node->color = -1;
		node->status = 0;

		node = node->next;
	}
}

void GraphImageCreation(Graph *graph)
{
	// char *file = ;

	FILE *out = fopen("graph.gv", "w");
	if (out == NULL) {
		return;
	}

	Node *node = graph->Head;

	char elem = '"';
	char *colors[6] = {"red", "lawngreen", "deeppink", "cyan", "indigo", "purple"};

	fprintf(out, "digraph HelloGraph {\n");

	fprintf(out, "\tnode [shape=%ccircle%c, ", elem, elem);
	fprintf(out, "style=%cfilled%c, ", elem, elem);
	fprintf(out, "margin=%c0.01%c];\n", elem, elem);

	fprintf(out, "\tedge [dir=%cnone%c];\n\n", elem, elem);

	for (int i = 0; i < graph->number; i++) {
		int ncolor = node->color;
		fprintf(out, "\t%cNode %d%c [fillcolor=%c%s%c]\n", 
								elem, i, elem, elem, colors[ncolor], elem);
		node = node->next;
	}

	fprintf(out, "\n");

	node = graph->Head;

	for (int i = 0; i < graph->number; i++) {
		HashT *contact = node->Contact;
		
		for (int j = 0; j < node->number; j++) {
			int indCont = contact->node->index;
			
			if (i < indCont) {
				fprintf(out, "\t%cNode %d%c -> ", elem, i, elem);
				fprintf(out, "%cNode %d%c;\n", elem, indCont, elem);
			}
			contact = contact->next;
		}
		node = node->next;
	}

	fprintf(out, "}\n");
	
	fclose(out);
}
