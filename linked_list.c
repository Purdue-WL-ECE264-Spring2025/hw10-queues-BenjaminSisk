#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { return NULL; }

void insert_at_head(struct linked_list *list, size_t value)
{
   // Create a list_node
  struct list_node * newNode = (struct list_node *) malloc(sizeof(struct list_node)); 
  // Insert the value of the list_node'
  newNode -> value = value;   
  // Make the list_node point to what the head points to
  newNode -> next = list -> head;
  // Make the head point to the list_node
  list -> head = newNode;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  // Create a list_node
  struct list_node * newNode = (struct list_node *) malloc(sizeof(struct list_node)); 
  // Insert the value of the list_node
  newNode -> value = value;   
  // Make the list_node point to NULL
  newNode -> next = NULL;
  // Find the last node
  struct list_node * lastNode;
  lastNode = list -> head;
  if(lastNode != NULL)
  {
    while(lastNode -> next != NULL)
    {
      lastNode = lastNode -> next;
    }
    // Make the last node point to list_node
    lastNode -> next = newNode;
  }
  else
  {
    list -> head = newNode;
  }

}

size_t remove_from_head(struct linked_list *list) 
{ 
  struct list_node * tempPointer;
  
  if((list -> head) != NULL) // If the thing that head points to is not null
  {
    size_t returnVal;
    returnVal = (list -> head -> value);
    // Make the temporary pointer point to what the head points to (which will be deleted)
    tempPointer = list -> head;

    // Make the head point to what the thing it points to points to
    if(tempPointer != NULL)
    {
      list -> head = list -> head -> next;
    }
    else
    {
      list -> head = NULL;
    }
    free(tempPointer);
    return returnVal;
  }
  else
  {
    return __SIZE_MAX__;
  }
}

size_t remove_from_tail(struct linked_list *list) 
{
  // Find the last node and node before that
  struct list_node * penultimate;
  size_t returnVal;
  penultimate = list -> head;
  if((list -> head) != NULL) // If the thing that head points to is not null
  {
    if((list -> head -> next) != NULL) // If the thing that points to the the thing that head points to is not null
    {
      while((penultimate -> next -> next) != NULL) 
      {
        penultimate = penultimate -> next;
      }
      returnVal = (penultimate -> next -> value);
      free(penultimate -> next);
      penultimate -> next = NULL;
    }
    else
    {
      returnVal = (list -> head -> value);
      free(list -> head);
      list -> head = NULL;
    }
    return returnVal; 
  }
  else
  {
    return __SIZE_MAX__;
  }
}

void free_list(struct linked_list list) 
{
  while (remove_from_head(&list) != -1)
  {
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
    //printf("%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
