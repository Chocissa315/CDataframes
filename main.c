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
    COLUMN *col1 = create_column(CHAR, "Type of potatoes : ");

    COLUMN *col2 = create_column(INT, "Number of Potatoes sold : ");

    COLUMN *col3 = create_column(INT, "Amount of money made with this type : ");

    //now we need to link the columns created to the cdataframe by using a list :

    list * liste = lst_create_list() ;

    //we create nodds linked to the columns

    lnode * node1 = lst_create_lnode(col1);

    lnode * node2 = lst_create_lnode(col2);

    lnode * node3 = lst_create_lnode(col3);

    lst_insert_head(liste, node1);
    lst_insert_after(liste, node2, node1);
    lst_insert_tail(liste, node3);

    //we now have the list of three columns, we can go through it, delete, add, move nodes inside it thanks to the
    // various functions contained in the list.h file. We also can do the same operations directly on the column,
    // to be able to modify and move values

    //we can now hard fill the data inside the table by using the following function :

    int nb_potatoe = 35 ;
    int money_potatoes = 150;
    insert_value(col1, "Regular Potatoes" );
    insert_value(col2, &nb_potatoe);
    insert_value(col3, &money_potatoes);

    //now if we use the function display_CDataframe(), we will see the first ro filled with the datas of the regular
    // potatoes sold during the day.


    //Now that we created the three colunmns, we can fill the using the following function :




    return 0;
}
