#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int nData;
	struct Node* next;
}Node;

typedef struct Stack {
	Node* top;
}Stack;

void InitializeStack(Stack* stack);
void Push(Stack* stack, int nData);
int Pop(Stack* stack);


int main(void) {
	Stack* s = (Stack*)malloc(sizeof(Stack));
	Push(s, 1);
	Push(s, 2);
	Push(s, 3);
	printf("%d\n", Pop(s));
	return 0;
}

void InitializeStack(Stack* stack) {
	stack->top = NULL;
}

void Push(Stack* stack, int nData) {
	Node* new_top = (Node*)malloc(sizeof(Node));

	new_top->nData = nData;
	new_top->next = stack->top;

	stack->top = new_top;
}

int Pop(Stack* stack) {
	Node* new_top = (Node*)malloc(sizeof(Node));
	int ret = stack->top->nData;
	new_top = stack->top->next;
	stack->top = new_top;

	return ret;
}
