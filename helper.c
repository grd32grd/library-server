#include "defs.h"

/*
  Function:     convertStatys
  Purpose:      takes in the BookStatusType and converts it to a suitable string
  in:           status
  out:          statusStr
  return:       nothing
*/
void convertStatus(BookStatusType status, char* statusStr){
    //checks the status to see if it's valid to have a corresponding string
    if (status == 0){
        strcpy(statusStr, "Checked In");
    }
    else if (status == 1){
        strcpy(statusStr, "Checked Out");
    }
    else if (status == 2){
        strcpy(statusStr, "Under Repair");
    }
    else if (status == 3) {
        strcpy(statusStr, "Lost");
    }
    else {
        strcpy(statusStr, "N/A");
    }
}