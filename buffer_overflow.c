#include <stdio.h>
#include <stdlib.h>

struct buffer {
    int size;
    int start;
    int count;
    int *element;
};

struct node{
	int data;
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

typedef struct buffer buffer_t;


void printList() {
   struct node *ptr = head;
   while(ptr != NULL) {
      printf("Current Items in the buffer overflow list: %d\n",ptr->data);
      ptr = ptr->next;
   }

}

void insertFirst(int data) {
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->data = data;
   link->next = head;
   head = link;
}

void init(buffer_t *buffer, int size) {
    buffer->size = size;
    buffer->start = 0;
    buffer->count = 0;
    buffer->element = malloc(sizeof(buffer->element)*size);

}

int full(buffer_t *buffer) {
    if (buffer->count == buffer->size) {
        return 1;
    } else {
        return 0;
    }
}

int empty(buffer_t *buffer) {
    if (buffer->count == 0) {
        return 1;
    } else {
        return 0;
    }
}

void push(buffer_t *buffer, int data) {
    int index;
    if (full(buffer)) {
        printf("Buffer overflow\n");
        insertFirst(data);
    } else {
        index = buffer->start + buffer->count++;
        if (index >= buffer->size) {
            index = 0;
        }
        buffer->element[index] = data;
    }
}


struct node* deleteFirst() {
   struct node *tempLink = head;


   head = head->next;

   if(head == NULL){
   	   free(head);
      }

   return tempLink;
}

int popqueue(buffer_t *buffer) {
    int element;

    if (empty(buffer)) {
        printf("Buffer underflow\n");
        if(head != NULL){
        	struct node *temp = deleteFirst();
        	element = temp->data;
        }
        return element;
    } else {
       element = buffer->element[buffer->start];
       buffer->start++;
       buffer->count--;
       if (buffer->start == buffer->size) {
           buffer->start = 0;
       }

       return element;
    }
}

int main() {
    buffer_t buffer;
    init(&buffer, 5);
    int data[] = {1,2,3,4,5,6,8,9,10};
    int i;
    for (i = 0; i < 10; i++) {
        printf("push: %d\n", data[i]);
        push(&buffer, data[i]);
    }
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("pop from queue: %d\n", popqueue(&buffer));
    }

    for (i = 0; i < 6; i++) {
        printf("push: %d\n", data[i]);
        push(&buffer, data[i]);
    }
    for (i = 0; i < 6; i++) {
        printf("pop from queue: %d\n", popqueue(&buffer));
    }

    printList();


}

