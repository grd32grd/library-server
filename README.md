Program written in C that consists of two processes, one server process that regulates access to a library, and one client process that takes in input and allows the user to modify said library. Library info is read from an external .txt file

## Source Files
server.c
client.c
books.c 
lib.c
connect.c
helper.c
Makefile
booksData.txt

## Header Files
defs.h

## Compilation Instructions
Enter the following below in the command line to start up the compiling/linking process.
make

## Launching Instructions
Enter the following below in the command line to get the server process running.
./server
Then, enter the following below in the command line to get the client process running (must be done in this order)
./client

## Program Instructions
Below is a visual representation of the main menu. Enter one of the following numbers beside the options to get started.

MAIN MENU
  (1) Print books
  (2) Check out a book
  (3) Check in a book
  (0) Exit