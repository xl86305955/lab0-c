/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return false;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0; /* Size initialize */
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    while (q->head != NULL) {
        list_ele_t *tmp;
        tmp = q->head;
        free(tmp->value);
        q->head = q->head->next;
        free(tmp);
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
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
    /* What should you do if the q is NULL? */
    /* insertion denied if queue is null*/
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh != NULL) {
        newh->value = strdup(s);
        if (newh->value == NULL) {
            free(newh);
            return false;
        }
        /* If the new node be the first node of queue */
        if (q->head == NULL && q->tail == NULL) {
            newh->next = NULL;
            q->tail = newh;
        } else {
            newh->next = q->head;
        }
        q->head = newh; /* let newh be the new head*/
        q->size += 1;
        return true;
    }
    /* if malloc failed */
    else {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
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
    /* Insertion denied while queue was empty */
    if (q == NULL)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(*newt));
    if (newt != NULL) {
        newt->value = strdup(s);
        if (newt->value == NULL) {
            free(newt);
            return false;
        }
        /* if newt be the first node */
        if (q->head == NULL && q->tail == NULL) {
            q->head = newt;
        } else {
            q->tail->next = newt;
        }
        newt->next = NULL;
        q->tail = newt;
        q->size += 1;
        return true;
    }
    /* Malloc failed */
    else {
        return false;
    }
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
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
    if (q == NULL)
        return false;
    if (q->size == 0)
        return false;
    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp;
    tmp = q->head;
    if (q->size == 1) {
        q->head = NULL;
        q->tail = NULL;
    }
    if (q->head != NULL)
        q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size -= 1;
    return true;

    /* You need to fix up this code. */
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL) {
        return 0;
    } else
        /* You need to write the code for this function */
        /* Remember: It should operate in O(1) time */
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
    if (q == NULL || q->size <= 1)
        return;
    list_ele_t *prev;
    list_ele_t *curr;
    list_ele_t *next;

    prev = NULL;
    curr = q->head;
    next = NULL;
    q->tail = q->head;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = prev;
    /* You need to write the code for this function */
}
