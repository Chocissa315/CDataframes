#include <stdio.h>
#include "Column.h"
#include "sort.h"
#include "cdataframe.h"
#include "list.h"

int main(){

    //example of scenario :
    //we are selling potatoes in a market and we want to store the number of potatoes sold and the money it provided
    // for each day
    //we will create a CDataframe to process with this data :

    //to do so we first create a list of what type of data we are going to use
    ENUM_TYPE cdftype[] = {CHAR, INT, INT} ;
    //we ask to create one column char, for the names of the potatoes, one int for the number of potatoes sold,
    // and one int for the money it generated

    CDATAFRAME * table ;
    //we create a variable to store the address of the datadframe we are going to create

    table = create_cdataframe(cdftype, 3);
    //we then use the function to create a CDataframe of length 3 with the types asked


    //now we need to add the new columns in order to be able to fill that table :
    create_column(CHAR, "Type of potatoes : ");

    create_column(INT, "Number of Potatoes sold : ");

    create_column(INT, "Amount of money made with this type : ");

    //Now that we created the three colunmns, we can fill the using the following function :



    return 0;
}
