#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "defs.h"

#define SERVER_IP "127.0.0.1"
#define MY_PORT 60002

int listenSocket;

/*
  Function:     main
  Purpose:      main function for the server that'll send/recieve data
  return:       0
*/
int main(){
  int clientSocket;

  //Library initalization
  LibraryType library, *libraryPtr = &library;
  initLibrary(&libraryPtr,"Carleton");

  //sets up global listening socket
  setupServerSocket(&listenSocket);

  //installs our signal handler
  signal(SIGUSR1, handleSig1);

  //connects to client socket
  printf("Waiting for connection request...\n");
  acceptConnection(listenSocket,&clientSocket);
  printf("...connected.\n");

  //serves the client
  serveOneClient(clientSocket, libraryPtr);
  return 0;
}

/*
  Function:     serveOneClient
  Purpose:      serves a client by taking in a buffer and responding with appropriate data
  in:           client socket, library
  return:       nothing
*/
void serveOneClient(int clientSocket, LibraryType*lib){
  char buffer[MAX_BUFF];
  int choice, bookId;

  while (1){
    //Empties buffer of previous info
    strcpy(buffer,"");
    //recieves buffer from client
    printf("Waiting to recieve message...\n");
    rcvData(clientSocket,buffer);
    printf("...recieved.\n");

    //parses buffer to a choice and bookId (if a bookId isn't needed than it's ignored)
    sscanf(buffer,"%d %d",&choice,&bookId);
    strcpy(buffer,"");

    //formats book list
    if (choice == REQ_RET_BOOKS){
      formatBooks(&lib->books,buffer);
    }

    //checks out book
    else if (choice == REQ_CHECK_OUT){
      if (checkOutBook(lib, bookId) == C_OK){
        sprintf(buffer,"Book with ID %d was successfully checked out.\n",bookId);
      }
      else if (checkOutBook(lib,bookId) == C_BAD_STATUS){
        sprintf(buffer,"ERROR: Book with ID %d couldn't be checked out due to it's current status.\n",bookId);      
      }
      else {
        sprintf(buffer,"ERROR: Book with ID %d couldn't be found in the library.\n",bookId);  
      }
    }

    //checks in book
    else if (choice == REQ_CHECK_IN){
      if (checkInBook(lib, bookId) == C_OK){
        sprintf(buffer,"Book with ID %d was successfully checked in.\n",bookId);
      }
      else if (checkInBook(lib,bookId) == C_BAD_STATUS){
        sprintf(buffer,"ERROR: Book with ID %d couldn't be checked in due to it's current status.\n",bookId);      
      }
      else {
        sprintf(buffer,"ERROR: Book with ID %d couldn't be found in the library.\n",bookId);  
      }
    }

    //close server
    else {
      closeAll(lib);
      exit(-1);
    }

    //sends the buffer back to the client
    sendData(clientSocket,buffer);

  }
}

/*
  Function:     closeAll
  Purpose:      closes the server's listening socket and deallocates the library's allocated info by calling a helper function
  in:           library
  return:       nothing
*/
void closeAll(LibraryType *lib){
  close(listenSocket);
  printf("Server disconnected.\n");
  cleanupLibrary(lib);
}

/*
  Function:     handleSig1
  Purpose:      works as a signal handler that will close the listening socket
  in:           signal
  return:       nothing
*/
void handleSig1(int i){
  close(listenSocket);
  printf("Server disconnected.\n");
  exit(-1);
}

