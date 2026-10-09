#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int data;
	struct node *next;
}NODE;
NODE *createNode(int data);
void traverseList2(NODE *head);
void traverseList(NODE *head);
void addFront(NODE **head, int data);
void addLast(NODE **head, int data);
void insertNode(NODE **head, int data);
void deleteNode(NODE **head, int data);
int main(){
	NODE *head = NULL;
	insertNode(&head,10); traverseList(head);
	insertNode(&head,20); traverseList(head);
	insertNode(&head,15); traverseList(head);
	insertNode(&head,30); traverseList(head);
	insertNode(&head,40); traverseList(head);
	insertNode(&head,25); traverseList(head);
	insertNode(&head,38); traverseList(head);
	deleteNode(&head,10); traverseList(head);
	deleteNode(&head,30); traverseList(head);
	deleteNode(&head,40); traverseList(head);
	deleteNode(&head,50); traverseList(head);
	
	//traverseList(head);
	
	return 0;
}

void traverseList(NODE *head){
	while(head!=NULL){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

void traverseList2(NODE *head){ //recursive form
	if(head!=NULL){
		printf("%d ", head->data);
		traverseList2(head->next);
	}
	printf("\n");
}

NODE *createNode(int data){
	NODE *newNode=(NODE*) malloc(sizeof(NODE));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
} 

void addFront(NODE **head, int data){
	NODE *newNode = createNode(data);
	newNode->next = *head;
	*head = newNode;
}

void addLast(NODE **head, int data){
	NODE *newNode = createNode(data);
	NODE *tmp;
	if(*head == NULL){
		 *head = newNode;
	}
	else{
		tmp = *head;
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = newNode;	
	}
}

void insertNode(NODE **head, int data){
	NODE *newNode = createNode(data);
	NODE *tmp;
	if(*head == NULL){
		 *head = newNode;
	}
	else{
		tmp = *head;
		while(tmp->next!=NULL && tmp->next->data<data){
			tmp = tmp->next;
		}
		newNode->next = tmp->next;
		tmp->next = newNode;	
	}
}

void deleteNode(NODE **head, int data){
	NODE *tmp;
	NODE *current;
	if((*head)->data ==data){
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		printf("%d silindi\n",data);
	}
	else{
		current = *head;
		while(current->next!=NULL && current->next->data != data){
			current = current->next;
		}
		if(current->next!=NULL){
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
			printf("%d silindi\n",data);
		}
		else{
			printf("Eleman YOK");
		}
	}
}
