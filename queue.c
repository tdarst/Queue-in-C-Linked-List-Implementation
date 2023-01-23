/* 
 * Code for basic C skills diagnostic.
 * Developed by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 * 
 * @author Darst Trevor
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
    	return NULL;
    }
    
    /* initialize variables */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */

    if (q == NULL) {
    	return;
    }
    
    /* copy the first node on the list and free it and it's value and queue up the next node
       on the list to be freed, rinse and repeat until there's nothing left */
    while(q->head != NULL) {
    	q_remove_head(q, NULL, 0);
    }
    
    /* free memory allocated for q */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
    	return false;
    }
    
    /* allocate memory for the node */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
    	return false;
    }
    
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    
    /* allocate space for string */
    newh->value = malloc((strlen(s)+2)*8);
    
    /* if malloc returns NULL then return false and free newh */
    if (newh->value == NULL) {
      free(newh);
    	return false;
    }
    
    /* copy string */
    strcpy(newh->value, s);
    
    /* if the list is empty then newh is the tail as well */
    if (q->head == NULL) {
    	q->tail = newh;
    }
    
    /* Make the current head the second index of the linked list, make newh the new head and then
       increment the size */
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    
    if (q == NULL) {
    	return false;
    }
    
    list_ele_t *newt;
    /* allocate space for the node */
    newt = malloc(sizeof(list_ele_t));
    
    /* if you can't allocate space for the node return false */
    if (newt == NULL) {
    	return false;
    }
    
    /* allocate space for the string */
    newt->value = malloc((strlen(s)+2)*8);
    
    /* if allocation fails return false and free newt */
    if (newt->value == NULL) {
      free(newt);
    	return false;
    }
    
    /* copy string to newt's value and make sure newt terminates the list */
    strcpy(newt->value, s);
    newt->next = NULL;
    
    /* if list is empty then newt is also the head */
    if (q->head == NULL) {
    	q->head = newt;
    }

    /* otherwise place newt after the current tail and then make newt the new tail
       and increment size of list */
    else {
      q->tail->next = newt;
    }
    
      q->tail = newt;
      q->size++;
    return true;
    
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL) {
    	return false;
    }
    
    list_ele_t *headNode;
    headNode = q->head;
    
    if (sp) {
      size_t length = strlen(headNode->value);
      if (length >= bufsize-1) {
        length = bufsize-1;
      }

      strncpy(sp, headNode->value, length);
      *(sp+length) = '\0';

    }

    q->head = q->head->next

    if (q->head==NULL) {
      q->tail = NULL;
    }

    free(h->value);
    free(h);

    q->size--;
    return true;

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    
    if (q == NULL || q->head == NULL) {
    	return 0;
    }
    
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
    	return;
    }
    
    list_ele_t *presNode, *tempNode, *nextNode;

    presNode = q->head;
    q->tail = q->head;
    nextNode = presNode->next;
    presNode->next = NULL;

    while (nextNode != NULL) {
      tempNode = nextNode->next;
      nextNode->next = presNode;
      presNode = nextNode;
      nextNode = tempNode;

    }

    q->head = presNode;
    
}

