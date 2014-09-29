#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void list_sort(struct node **head) {
  int temp;
  struct node *new_node = *head;
  struct node *second_node = new_node->next;
  for(; new_node->next !=NULL; new_node= new_node->next){
      for(second_node = new_node->next; second_node != NULL; second_node= second_node->next){
          if ((new_node->value) < (second_node->value)) {
		temp = new_node->value;
		new_node->value = second_node->value;
		second_node->value = temp;
	}
      }
    }
}

void list_append(const int *val, struct node **head) {
   
	struct node *new_node = malloc(sizeof(struct node));
	new_node->value = val;
	new_node->next = *head;
        *head = new_node;
  
}


void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %d\n", i++, list->value);
        list = list->next;
    }
}

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}
