#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node *next;
};

void list(struct node *);

int main()
{
	struct node *head, *node2;
	
	int num;
	head = malloc(sizeof(struct node));
	if (head == NULL) {
    	return 0;
	}	
    
    num=10;
	head->val = num;
	head->next = NULL;
	
	node2 = malloc(sizeof(struct node));
	if (node2 == NULL) {
    	return 0;
	}	
    num=20;
	node2 ->val = num;
	node2 ->next = NULL;
	
	head->next = node2;
	
	
	list(head);
	return 0;

}

void list(struct node *head)
{
	struct node* current = head;
    while (current->next != NULL) {
    	printf("-%d-",current->val);
        current = current->next;
    }
    printf("-%d-",current->val);
}
