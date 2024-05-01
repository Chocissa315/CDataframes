#include "Column.h"
#include <stdio.h>
#include <stdlib.h>


void test(){

    printf("the test is working");

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


int insert_value(COLUMN *col, void *value, ENUM_TYPE type_of_data){

    if (type_of_data == col->column_type) {

        if (col->size >= col->max_size) {

            if (col->max_size == 0) {
            //this is the case where the list is empty and hence not yet initialized

                switch (col->column_type) {

                    case INT :
                        col->data[col->size] = (int*) malloc (sizeof(int));

                        *((int*)col->data[col->size])= *((int*)value);

                        col->size +=1 ;
                        col->max_size += 1;
                        break;

                    case CHAR :
                        col->data[col->size] = (char*) malloc (sizeof(char));

                        *((char*)col->data[col->size])= *((char*)value);

                        col->size +=1 ;
                        col->max_size += 1 ;
                        break ;

                    case FLOAT :
                        col->data[col->size] = (float*) malloc (sizeof(float));

                        *((float*)col->data[col->size])= *((float*)value);

                        col->size +=1 ;
                        col->max_size += 1 ;
                        break ;

                    case DOUBLE :
                        col->data[col->size] = (double*) malloc (sizeof(double));

                        *((double*)col->data[col->size])= *((double*)value);

                        col->size +=1 ;
                        col->max_size += 1 ;
                        break ;

                    case STRING :
                        col->data[col->size] = (char**) malloc (sizeof(char*));

                        *((char**)col->data[col->size])= *((char**)value);

                        col->size +=1 ;
                        col->max_size += 1 ;
                        break ;

                    case STRUCTURE :
                        col->data[col->size] =  malloc (1);

                        //*col->data[col->size] = *(value);

                        col->size +=1 ;
                        col->max_size += 1 ;
                        break ;

                }



            }
            else{
                //case where we need to extend the size but there's already a space allocated : use realloc
                //do we need to code this part ?

                switch (col->column_type) {

                    case INT :
                        col->data = realloc(col->data, (col->max_size+ 3)*sizeof (int ));

                        *((int*)col->data[col->size])= *((int*)value);

                        break ;

                    case CHAR :
                        col->data = realloc(col->data, (col->max_size+ 3)*sizeof (char ));

                        *((char*)col->data[col->size])= *((char*)value);

                        break ;

                    case FLOAT :
                        col->data = realloc(col->data, (col->max_size+ 3)*sizeof (float ));

                        *((float *)col->data[col->size])= *((float *)value);

                        break ;

                    case DOUBLE:
                        col->data = realloc(col->data, (col->max_size+ 3)*sizeof (double ));

                        *((double*)col->data[col->size])= *((double*)value);

                        break ;

                    case STRING:
                        col->data = realloc(col->data, (col->max_size+ 3)*sizeof (char* ));

                        *((char**)col->data[col->size])= *((char**)value);

                        break;

                    case STRUCTURE :
                        //col->data = realloc(col->data, (col->max_size+ 3)*sizeof ());
                        break ;
                }

                col->size += 1 ;

                col->max_size +=3;

            }




        }

        else {
            col->data[col->size] = value;

            col->size += 1;
        }

        return 1;

    }
    else{

        return 0 ;

    }
}

void delete_column(COLUMN **col){

    free((*col)->data);

    free((*col)->title);

    free((*col)->index);

    free(*col);


}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){

    char buffer[100];

    

}

