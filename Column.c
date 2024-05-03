#include "Column.h"
#include <stdio.h>
#include <stdlib.h>


void test(){

    printf("the test is working");

}


COLUMN *create_column(ENUM_TYPE type , char* title){

    //creation of the column
    COLUMN* col1 = (COLUMN*)malloc(sizeof(COLUMN));

    //attribution of the parameters of the newly created column
    (*col1).title = title ;

    (*col1).size = 0;

    (*col1).max_size = 0;

    (*col1).column_type = type ;

    (*col1).data = NULL ;

    (*col1).index = NULL ;

    //returning the adress of the newly created column

    return col1;

}


int insert_value(COLUMN *col, void *value, ENUM_TYPE type_of_data){

    if (type_of_data == col->column_type) {

        if (col->size >= col->max_size) {

            if (col->max_size == 0) {
            //this is the case where the list is empty and hence not yet initialized

                col->data = (COL_TYPE **) malloc (sizeof(COL_TYPE*));

                col->max_size += 1 ;

            }

            else {
                //case where we need to extend the size but there's already a space allocated : use realloc


                col->data = realloc(col->data, (col->max_size+ 3)*sizeof (COL_TYPE* ));


                col->max_size +=3;

            }
        }



        if (value != NULL) {

            switch (col->column_type){

                case INT :
                    col->data[col->size] = (COL_TYPE*) malloc( sizeof(int));

                    *((int *)(col->data[col->size])) = *((int*) value);
                    break ;

                case FLOAT :
                    col->data[col->size] = (COL_TYPE*) malloc( sizeof(float));

                    *((float *)(col->data[col->size])) = *((float*) value);
                    break ;

                case CHAR :
                    col->data[col->size] = (COL_TYPE*) malloc( sizeof(char));

                    *((char *)(col->data[col->size])) = *((char*) value);
                    break ;

                case DOUBLE :
                    col->data[col->size] = (COL_TYPE*) malloc( sizeof(double));

                    *((double *)(col->data[col->size])) = *((double*) value);
                    break ;

                case STRING :
                    col->data[col->size] = (COL_TYPE*) malloc( sizeof(char*));

                    *((char **)(col->data[col->size])) = *((char**) value);
                    break ;

            }




            }

        else{
            (col->data[col->size]) = NULL;
        }

        col->size +=1 ;

        return 1;

    }
    else{

        return 0 ;

    }
}

void delete_column(COLUMN **col){

    free((*col)->data);

    //free((*col)->title);

    free((*col)->index);

    free(*col);


}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){


    switch (col->column_type) {

        case INT :
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        case FLOAT :
            snprintf(str, size, "%f", *((float*)col->data[i]));
            break;
        case CHAR :
            snprintf(str, size, "%c", *((char*)col->data[i]));
            break;
        case DOUBLE :
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            break;
        case STRING :
            snprintf(str, size, "%s", *((char**)col->data[i]));
            break;
        case STRUCTURE :
            //snprintf(str, size, "", *((STRUCT*)col->data[i]));
            break;

    }

}

void print_col(COLUMN* col){

    switch (col->column_type) {

        case INT :
            for (int i = 0 ; i< col->max_size ; i ++ ){

                if (col->data[i] == NULL){
                    printf("[%d] NULL \n",i);
                }
                else {
                    printf("[%d] %d \n", i, *((int *) col->data[i]));
                }

            }
            break ;
        case CHAR :
            //printf("[0] %c \n", col->data[0]->char_value);
            for (int i = 0 ; i < col->size ; i ++ ){
                if (col->data[i] == NULL){
                    printf("[%d] NULL \n",i);
                }
                else {
                    printf("[%d] %c \n", i, (col->data[i]->char_value));
                }

            }
            break ;
        case FLOAT :
            for (int i = 0 ; i< col->max_size ; i ++ ){

                printf("[%d] %f \n", i,  *((float*)col->data[i]));


            }
            break ;
        case DOUBLE :
            for (int i = 0 ; i< col->max_size ; i ++ ){

                printf("[%d] %lf \n", i,  *((double*)col->data[i]));


            }
            break ;
        case STRING :
            for (int i = 0 ; i< col->max_size ; i ++ ){

                printf("[%d] %s \n", i,  *((char**)col->data[i]));


            }
            break ;
        case STRUCTURE :
            for (int i = 0 ; i< col->max_size ; i ++ ){

                //printf("[%d] %STRUCT \n", i,  *((STRUCT*)col->data[i]));


            }
            break ;

    }

}








