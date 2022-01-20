#include "defs.h"

/*
  Function:     main
  Purpose:      main function for the client that will send/recieve data
  return:       0
*/
int main(){
  int choice = -1, clientSocket;
  char buffer[MAX_BUFF], bookId[MAX_BUFF];

  //setting up the client socket 
  setupClientSocket(&clientSocket);

  while (1) {

   clientMenu(&choice);
   strcpy(buffer,"");
   strcpy(bookId,"");

   switch(choice) {

      case 1:   // Print books
        //sends the REQ_RET_BOOK request type
        strcat(buffer, "0");
        sendData(clientSocket,buffer);

        //recieves the formatted book list string
        rcvData(clientSocket,buffer);
        printf("%s", buffer);
        break;

      case 2:   // Check out a book
        //appends the REQ_CHECK_OUT request type
        strcat(buffer,"2 ");

        //appends the book ID
        printf("Enter the book ID: ");
        fgets(bookId, sizeof(bookId), stdin);
        strcat(buffer,bookId);

        //sends the buffer to the server
        sendData(clientSocket,buffer);

        //recieves the message
        rcvData(clientSocket,buffer);
        printf("%s",buffer);
        break;

      case 3:   // Check in a book
        //appends the REQ_CHECK_IN request type
        strcat(buffer,"1 ");

        //appends the book ID
        printf("Enter the book ID: ");
        fgets(bookId, sizeof(bookId), stdin);
        strcat(buffer,bookId);
        
        //sends the buffer to the server
        sendData(clientSocket,buffer);

        //recieves the message
        rcvData(clientSocket,buffer);
        printf("%s",buffer);
        break;

      case 0:   // Close everything
        //sends the REQ_CLOSE reques type to the server then closes the client program
        strcat(buffer,"3");
        printf("We will close our server and get you out of here then.\n");
        sendData(clientSocket, buffer);
        return 0;

      default:
        printf("ERROR:  invalid option\n");
    }
  }
  return 0;
}

/*
  Function:     clientMenu
  Purpose:      implements a menu for the user to interact with
  in-out:       choice           
  return:       nothing
*/
void clientMenu(int* choice){
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  //main menu
  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

