#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:     initList
  Purpose:      initalizes the given BookTypeList struct's required fields
  in-out:       list
  return:       nothing
*/
void initList(BookListType*list){
    list->head = NULL;
    list->tail = NULL;
}

/*
  Function:     initBook
  Purpose:      initalizes the given BookType struct's required fields
  in:           id, title, authour, year, status
  out:          book
  return:       nothing
*/
void initBook(int i, char*t, char*a, int y, BookStatusType st,BookType**book){
    BookType *ptr = malloc(sizeof(BookType));

    ptr->id = i;
    strcpy(ptr->title,t);
    strcpy(ptr->author,a);
    ptr->year = y;
    ptr->status = st;

    //sets the book pointer to 'ptr'
    *book = ptr;
}

/*
  Function:     addBook
  Purpose:      adds a book to the book list in appropriate order (ascending order by title)
  in:           book
  in-out:       list
  return:       nothing
*/
void addBook(BookListType*list, BookType*b){
    NodeType *currNode = list->head, *prevNode = NULL, *newNode;
    
    //loops to find the appropriate position
    while (currNode != NULL){
        if (strcmp(currNode->data->title, b->title) > 0){
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    newNode = malloc(sizeof(NodeType));
    newNode->data = b;
    newNode->next = NULL;

    //set the new node to the list's head if its the first element in the list
    if (prevNode == NULL) {
        list->head = newNode;
    }
    else {
        prevNode->next = newNode;
    }

    newNode->next = currNode;

    //set the new node to the list's tail if its the last element in the list
    if (currNode == NULL){
        list->tail = newNode;
    }
}

/*
  Function:     findBook
  Purpose:      find the given book id in the given list, and return it with the out parameter
  in:           list, id
  out:          book
  return:       nothing
*/
int findBook(BookListType *list, int id, BookType **b){
    NodeType *currNode = list->head, *prevNode = NULL;
    
    //loops over the list
     while (currNode != NULL){
        if (currNode->data->id == id){
            *b = currNode->data;
            return C_OK;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    return C_NOK;   
}

/*
  Function:     formatBook
  Purpose:      format's the given books info to a long string
  in:           book
  out:          outStr
  return:       nothing
*/
void formatBook(BookType *b, char *outStr){
    char statusStr[MAX_ARR];
    convertStatus(b->status,statusStr);
    sprintf(outStr, "ID: %-3d| Title: %-37s| Author: %-19s| Year: %-5d| Status: %-13s\n", b->id, b->title, b->author, b->year, statusStr);
}

/*
  Function:     formatBooks
  Purpose:      format's a given book list's info to a long string
  in:           list
  out:          outStr
  return:       nothing
*/
void formatBooks(BookListType *list, char *outStr){
    NodeType *head = list->head, *currNode = list->head,  *tail = list->tail, *prevNode = NULL;
    char bookStr[MAX_ARR];
    strcat(outStr,"BOOKS:\n");

    //iterates over the list to format each's node data (aka it's book)
    while (currNode != NULL){
        formatBook(currNode->data, bookStr);
        strcat(outStr,bookStr);
  
        prevNode = currNode;
        currNode = currNode->next;
    }

    //adds the head & tail to the long string
    formatBook(head->data, bookStr);
    strcat(outStr, "--HEAD: ");
    strcat(outStr,bookStr);
    formatBook(tail->data, bookStr);
    strcat(outStr, "--TAIL: ");
    strcat(outStr,bookStr);
}

/*
  Function:     cleanUpList
  Purpose:      deallocate's up all allocated memory in the given list
  in:           booklist
  return:       nothing
*/
void cleanupList(BookListType *list){
    NodeType *currNode = list->head, *prevNode = NULL;

    //iterates over the list to free the data
    while (currNode != NULL){
        free(currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
        free(prevNode);
    }
}