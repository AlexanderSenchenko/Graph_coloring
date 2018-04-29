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
	Node *parent = NULL;

	graph->number = line;

	for (int i = 0; i < line; i++) {
		int num_contact = 0;

		for (int j = 0; j < column; j++) {
			if (Matrix[GetIndex(line, i, j)] == 1)
				num_contact++;
		}

		ArrNode[i] = CreateNode(i, num_contact);

		if (i != 0)
			parent->next = ArrNode[i];

		ArrNode[i]->parent = parent;

		#if 0
		printf("%d\t", ArrNode[i]->index);
		printf("%p\t", ArrNode[i]);
		printf("%p\n", ArrNode[i]->next);
		#endif
		parent = ArrNode[i];
	}

	graph->Head = ArrNode[0];

	Node *node = graph->Head;
	for (int i = 0; i < line; i++) {
		HashT *parentCont = NULL;

		for (int j = 0; j < column; j++) {

			if (Matrix[GetIndex(line, i, j)] == 1) {
				HashT *contact = CreateNodeHashT();

				contact->node = ArrNode[j];
				contact->next = NULL;
				contact->parent = parentCont;

				if (parentCont != NULL)
					parentCont->next = contact;
				
				parentCont = contact;

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
	node->parent = NULL;
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
	Contact->parent = NULL;

	return Contact;
}

Node *DeleteNodeSave(Graph **graph, int ind)
{
	Node *node = (*graph)->Head;

	while (node->index != ind) {
		node = node->next;
	}

	if (node->parent != NULL) {
		node->parent->next = node->next;
	} else {
		(*graph)->Head = node->next;
	}

	if (node->next != NULL)
		node->next->parent = node->parent;

	(*graph)->number--;

	DeleteNodeList((*graph)->Head, node);

	return node;
}

void DeleteNodeList(Node *Head, Node *node)
{
	Node *head = Head;
	while (head != NULL) {
		HashT *contact = head->Contact;

		for (int i = 0; i < head->number && contact->node->index != node->index; i++) {
			contact = contact->next;
		}

		if (contact != NULL && contact->node->index == node->index) {
			if (contact->parent != NULL) {
				contact->parent->next = contact->next;
			} else {
				head->Contact = contact->next;
			}

			if (contact->next != NULL)
				contact->next->parent = contact->parent;

			head->number--;

			contact->node = NULL;
			contact->next = NULL;
			contact->parent = NULL;
			free(contact);
		}

		head = head->next;
	}
}

Graph *RestoringNode(Graph *graph, Node *node)
{
	if (node->parent != NULL) {
		node->parent->next = node;
	} else {
		graph->Head = node;
	}

	if (node->next != NULL)
		node->next->parent = node;

	graph->number++;

	PrintInfoGraph(graph);

	RestoringContact(graph, node);

	PrintInfoGraph(graph);

	return graph;
}

void RestoringContact(Graph *graph, Node *node)
{
	Node *Head = graph->Head;	
	HashT *contact = node->Contact;

	while (contact != NULL) {
		HashT *restCont = CreateNodeHashT();

		restCont->node = node;

		if (contact->node->Contact->parent != NULL) {
			contact->node->Contact->parent->next = restCont;
		} else {
			contact->node->Contact = restCont;
		}

		if (contact->node->Contact->next != NULL)
			contact->node->Contact->next->parent = restCont;

		contact->node->number++;

		contact = contact->next;
	}
}

void PrintInfoGraph(Graph *graph)
{
	Node *node = graph->Head;

	printf("Numder node = %d\n", graph->number);
	printf("Index\tNode\t\tNext\t\tParent\t\tColor\tNumCont\tStatus\n");
	
	for (int i = 0; i < graph->number && node != NULL; i++) {
		printf("%d\t", node->index);
		printf("%p\t", node);
		printf("%p\t", node->next);
		if (node->next == NULL)
			printf("\t");

		printf("%p\t", node->parent);
		if (node->parent == NULL)
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
