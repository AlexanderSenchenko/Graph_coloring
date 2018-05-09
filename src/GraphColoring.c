#include "GraphColoring.h"

void ColoringGraph(Graph *graph)
{
	int act;

	system("clear");

	while (act != 7) {
		printf("\n");
		printf("1) Раскарасить граф в 2 цвета\n");
		printf("2) Раскарасить граф в 3 или менее цвета\n");
		printf("3) Раскарасить граф в 4 или менее цвета\n");
		printf("4) Раскарасить граф в 5 или менее цветов\n");
		printf("5) Раскарасить граф\n");
		printf("6) Вывод информации о графе\n");
		printf("7) Выход\n");
		printf("Выберите действие: ");
		scanf("%d", &act);

		switch(act) {
			case 1:
				system("clear");
				RebootGraph(graph);
				if (TwoColor(graph) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 2:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 3) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 3:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 4) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 4:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 5) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 5:
				system("clear");
				RebootGraph(graph);
				if (NColor(graph) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 6:
				system("clear");
				PrintInfoGraph(graph);
				break;
			case 7:
				break;
			default:
				system("clear");
				printf("Ошибка действия\n\n");
		}
	}
}

int TwoColor(Graph *graph)
{
	Node *node = graph->Head;

	node->color = 0;

	if (TwoColorRun(node) == 1) {
		printf("Error, 2 color\n");
		return 1;
	}

	return 0;
}

int TwoColorRun(Node *node)
{
	if (node->status == 1)
		return 0;

	int nextColor;
	if (node->color == 0) {
		nextColor = 1;
	} else if (node->color == 1) {
		nextColor = 0;
	}

	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		int act = TwoColorCheckNode(contact->node, node->color);
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
		if (TwoColorRun(contact->node) == 1)
			return 1;
		contact = contact->next;
	}

	return 0;
}

int TwoColorCheckNode(Node *node, int color)
{
	if (node->color == color)
		return 1;

	if (node->color != -1)
		return 2;

	return 0;
}

int TFFColor(Graph *graph, int color)
{
	Node *node = graph->Head;

	if (node->next == NULL) {
		node->status = 1;
		node->color = 0;
		return 0;
	}

	if (TFFColorRun(graph, node, color) == 1)
		return 1;

	return 0;
}

int TFFColorRun(Graph *graph, Node *node, int color)
{
	int check = 0;
	for (int i = 0; i < graph->number; i++) {
		if (node->number < color && node->status != 1) {
			check = 0;

			graph = DeleteNodeSave(graph, node);

			TFFColor(graph, color);

			graph = RestoringNode(graph, node);

			if (TFFColorCheckContact(node, color, 0) == 1)
				return 1;
		} else {
			check++;
		}
		node = node->next;
	}

	if (check == graph->number) {
		if (TFFColorNode(graph->Head, color) == 1)
			return 1;
	}

	return 0;
}

int TFFColorNode(Node *node, int color)
{
	if (node->status == 1)
		return 0;

	if (TFFColorCheckContact(node, color, 0) == 1)
		return 1;

	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (TFFColorNode(contact->node, color) == 1)
			return 1;

		contact = contact->next;
	}
	
	return 0;
}

int TFFColorCheckContact(Node *node, int numColor, int color)
{
	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (contact->node->color == color) {
			if (TFFColorCheckContact(node, numColor, color + 1) == 1)
				return 1;
		}
		contact = contact->next;
	}

	if (numColor <= color) {
		printf("Error, %d color\n", numColor);
		return 1;
	}

	if (node->color == -1) {
		node->color = color;
		node->status = 1;
	}

	return 0;
}

int NColor(Graph *graph)
{
	Node *node = graph->Head;

	NColorRun(node);

	return 0;
}

int NColorRun(Node *node)
{
	if (node->status == 1)
		return 0;

	if (node->color == -1) {
		int color = NColorCheckContact(node, 0);
		node->color = color;
	}

	NColorRunContact(node);

	node->status = 1;

	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		NColorRun(contact->node);
		contact = contact->next;
	}

	return 0;
}

int NColorRunContact(Node *node)
{
	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		NColorContact(contact->node);
		contact = contact->next;
	}
	return 0;
}

int NColorContact(Node *node)
{
	if (node->color != -1)
		return 0;

	int color = NColorCheckContact(node, 0);

	node->color = color;

	return 0;
}

int NColorCheckContact(Node *node, int color)
{
	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (color == contact->node->color)
			color = NColorCheckContact(node, color + 1);

		contact = contact->next;
	}
	return color;
}