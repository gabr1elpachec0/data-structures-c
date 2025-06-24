#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} Queue;

Queue* create_queue();
int size(Queue* queue);
bool is_empty(Queue* queue);
int peek(Queue* queue, bool* status);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue, bool* status);
void destroy_queue(Queue* queue);

int main() {
    Queue* queue = create_queue();

    if (is_empty(queue)) printf("Queue is empty.\n"); 

    enqueue(queue, 8);
    enqueue(queue, 9);
    enqueue(queue, 4);

    if (!is_empty(queue)) printf("Queue is not empty.\n");

    printf("Queue size: %d.\n", queue->size);

    bool status = false;
    int value = 0;

    value = peek(queue, &status);
    if (status) {
        printf("Peek successfull.\n");
        printf("Peek value: %d.\n", value);   
    }

    value = dequeue(queue, &status);
    if (status) {
        printf("Dequeue successfull.\n");
        printf("Element dequeued: %d.\n", value);
    }

    value = peek(queue, &status);
    if (status) {
        printf("Peek successfull.\n");
        printf("Peek value: %d.\n", value);   
    }

    destroy_queue(queue);

    return 0;
}

Queue* create_queue() {
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

int size(Queue* queue) {
    return queue->size;
}

bool is_empty(Queue* queue) {
    return queue->size == 0;
}

int peek(Queue* queue, bool* status) {
    if (is_empty(queue)) {
        *status = false;
        return NULL;
    }
    *status = true;
    return queue->head->value;
}

void enqueue(Queue* queue, int value) {
    Node* new_node = malloc(sizeof(Node));

    new_node->value = value;
    new_node->next = NULL;

    if (is_empty(queue)) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    queue->size++;
}

int dequeue(Queue* queue, bool* status) {
    if (is_empty(queue)) {
        *status = false;
        return NULL;
    }
    int value = queue->head->value;

    Node* old_head = queue->head;

    if (queue->size == 1) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }

    free(old_head);
    
    queue->size--;

    return value;
}

void destroy_queue(Queue* queue) {
    Node* current_node = queue->head;

    while (current_node != NULL) {
        Node* temp = current_node;
        current_node = current_node->next;
        free(temp);
    }

    free(queue);
}