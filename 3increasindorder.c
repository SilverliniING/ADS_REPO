#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct QueueNode* newQueueNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

bool isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(struct Queue* queue, int data) {
    struct QueueNode* temp = newQueueNode(data);

    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }

    queue->rear->next = temp;
    queue->rear = temp;
}

int dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return -1;

    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);
    return data;
}
struct StackNode {
    int data;
    struct StackNode* next;
};
struct Stack {
    struct StackNode *top;
};
struct StackNode* newStackNode(int data) {
    struct StackNode* temp = (struct StackNode*)malloc(sizeof(struct StackNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

bool isStackEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

void push(struct Stack* stack, int data) {
    struct StackNode* newNode = newStackNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack* stack) {
    if (isStackEmpty(stack))
        return -1;

    struct StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

bool canArrangeIncreasingOrder(struct Queue* queue, int n) {
    struct Stack* stack = createStack();
    int expected = 1; 

    while (!isEmpty(queue) || expected <= n) {
        if (!isEmpty(queue) && queue->front->data == expected) {
            dequeue(queue);
            expected++;
        } else {
            if (!isStackEmpty(stack) && stack->top->data == expected) {
                pop(stack);
                expected++;
            } else {
                if (!isEmpty(queue)) {
                    int data = dequeue(queue);
                    if (data > expected) {
                        push(stack, data);
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    struct Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 5);
    enqueue(queue, 2);
    enqueue(queue, 4);
    enqueue(queue, 3);

    int n = 5; 

    printf("Queue elements can be arranged in increasing order using a stack: %s\n", 
           canArrangeIncreasingOrder(queue, n) ? "true" : "false");

    return 0;
}
