#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int id; 
    char name [100];
    int severity; 
    struct node *next; 
} Node; 

typedef struct{
    Node *head; 
} Queue; 

Node *createNode(int id, char name[], int s){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode != NULL){
        newNode->id = id; 
        strcpy(newNode->name, name);
        newNode->severity = s; 
        newNode->next = NULL; 
    }
    return newNode; 
}

int exists(Queue *q, int id){
    Node *temp = q->head; 
    while(temp != NULL){
        if(temp->id == id){
            return 1; 
        }
        temp = temp->next; 
    }
    return 0; 
}

void add(Queue *q, int id, char n[], int s){
    if(exists(q, id)){
        printf("Error: Patient %d already exists.\n", id);
        return;   
    }

    Node *newNode = createNode(id, n, s);
    if (newNode == NULL) {
        return;
    }

    if(q->head == NULL || s > q->head->severity){
        newNode->next = q->head; 
        q->head = newNode; 
    }
    else{
        Node *temp = q->head; 
        while(temp->next != NULL && temp->next->severity >= s){
            temp = temp->next; 
        }
        newNode->next = temp->next; 
        temp->next = newNode; 
    }
    printf("Patient %d Added.\n", id);
}

void treat(Queue *q){
    if(q->head == NULL){
        printf("Queue is empty.\n");
        return; 
    }
    else{
        Node *temp = q->head; 
        printf("Patient %d Treated.\n", temp->id);
        q->head = temp->next;
        free(temp);
    }
}

void remove(Queue *q, int id){
    if(q->head == NULL){
       printf("Error: Patient %d not found.\n", id);
       return; 
    }

    if(q->head->id == id){
        Node *temp = q->head; 
        q->head = temp->next; 
        free(temp);
        printf("Patient %d Removed.\n", id);
        return; 
    }

    Node *current = q->head; 
    while(current->next != NULL && current->next->id != id){
        current = current->next; 
    }

    if(current->next == NULL){
        printf("Error: Patient %d not found.\n", id);
        return;
    }

    Node *temp = current->next; 
    current->next = temp->next; 
    free(temp);
    printf("Patient %d Removed.\n", id);
}

void display(Queue *q){
    if(q->head == NULL){
        printf("Queue is empty.\n");
        return; 
    }

    Node *temp = q->head; 
    while(temp != NULL){
        printf("%s %d\n", temp->name, temp->severity);
        temp = temp->next;
    }
}

void freeAll(Queue *q){
    Node *curr = q->head; 
    while(curr != NULL){
        Node *temp = curr; 
        curr = curr->next; 
        free(temp);
    }
    q->head = NULL;
}

int main(void){
    Queue q; 
    q.head = NULL; 

    char read; 
    while (scanf(" %c", &read) == 1) {

        if (read == 'A') {
            int id, severity;
            char name[101];
            scanf("%d %s %d", &id, name, &severity);
            add(&q, id, name, severity);
        }

        else if (read == 'T') {
            treat(&q);
        }

        else if (read == 'R') {
            int id;
            scanf("%d", &id);
            remove(&q, id);
        }

        else if (read == 'D') {
            display(&q);
        }

        else if (read == 'Q') {
            freeAll(&q);
            break;
        }
    }

    return 0; 
}