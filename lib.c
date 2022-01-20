#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:     loadBooks
  Purpose:      reads info from the booksData.txt file, convert it's info to a book, and adds said book to the given bookListType
  in-out:       books
  return:       nothing
*/
void loadBooks(BookListType* books){
    FILE *infile; 
    int year, r, id = 0;
    char title[MAX_STR], author[MAX_STR];
    BookStatusType status;
    BookType book, *bookPtr = &book;

    //opens file
    infile = fopen("booksData.txt", "r");
    if (!infile) {
        printf("Error: could not open file\n");
        exit(1);
    }
 
    //interprets every four lines as a new book
    while ((r = fscanf(infile, " %64[^\n] %64[^\n] %d %d\n", title, author, &year, &status)) != EOF) {
        initBook(id, title, author, year, status, &bookPtr);
        addBook(books,bookPtr);
        id++;
    }

    //closes file
    fclose(infile);
}

/*
  Function:     initLibrary
  Purpose:      initalizes the given Library struct's required fields
  in:           name
  in-out:       library
  return:       nothing
*/
void initLibrary(LibraryType **library, char *n){
    LibraryType* ptr = malloc(sizeof(LibraryType));;
    char outStr[MAX_BUFF] = ""; 

    //initalizes the library's book list
    initList(&ptr->books);
    loadBooks(&ptr->books);

    strcpy(ptr->name,n);

    //prints the initial book list
    formatBooks(&ptr->books,outStr);
    printf("%s\n",outStr);

    //sets the library's pointer to 'ptr'
    *library = ptr;
}

/*
  Function:     checkOutBook
  Purpose:      checks out the book with the given bookId
  in:           library, book id
  return:       success/one of the failure flags
*/
int checkOutBook(LibraryType *lib, int bookId){
    BookType book, *bookPtr = &book;

    //determines the status to return
    if (findBook(&lib->books,bookId,&bookPtr) == C_NOK){
        return C_BOOK_NOT_FOUND;
    }
    else if (bookPtr->status == CHECKED_IN){
        bookPtr->status = CHECKED_OUT;
        return C_OK;
    } 
    else {
        return C_BAD_STATUS;
    }
}

/*
  Function:     checkInBook
  Purpose:      checks in the book with the given bookId
  in:           library, book id
  return:       success/one of the failure flags
*/
int checkInBook(LibraryType *lib, int bookId){
    BookType book, *bookPtr = &book;

    //determines the status to return
    if (findBook(&lib->books,bookId,&bookPtr) == C_NOK){
        return C_BOOK_NOT_FOUND;
    }
    else if (bookPtr->status == CHECKED_OUT){
        bookPtr->status = CHECKED_IN;
        return C_OK;
    } 
    else {
        return C_BAD_STATUS;
    }
}

/*
  Function:     cleanUpLibrary
  Purpose:      deallocates all allocated memory in the library
  in:           library
  return:       nothing
*/
void cleanupLibrary(LibraryType *lib){
    cleanupList(&lib->books);
    free(lib);
}