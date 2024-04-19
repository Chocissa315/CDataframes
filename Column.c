#include "Column.h"
#include <stdio.h>


void test(){

    printf("I guess the test is working");

}

COLUMN *create_column(ENUM_TYPE type , char* title){

    //creation of the column
    COLUMN col1;

    //attribution of the parameters of the newly created column
    col1.title = title ;

    col1.size = 0;

    col1.max_size = 0;

    col1.column_type = type ;

    col1.data = NULL ;

    col1.index = NULL ;

    //returning the adress of the newly created column
    return &col1;

}

