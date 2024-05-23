//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to columns (not for user)

#include "Column.h"
#include <stdio.h>
#include <stdlib.h>

#define REALOC_SIZE  256

void test(){

    printf("the test is working");

}

//function that creates a column, takes as parameter the type of variable the column will contain and its name
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

//function that inserts a value inside a column. Takes as parameter the column, the value, and the type of value
// returns 1 if succed, 0 else
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


                col->data = realloc(col->data, (col->max_size+ REALOC_SIZE)*sizeof (COL_TYPE* ));


                col->max_size +=REALOC_SIZE;

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

//function that deletes a column by freeing the allocated memory linked to it, takes the column as parameter
void delete_column(COLUMN **col){

    free((*col)->data);

    //free((*col)->title);

    free((*col)->index);

    free(*col);


}

// function that converts a value into string in order to be able to print it without knowing its type.
//takes as parameter the column, the index of the value, a buffer to store the converted string, and the max size of the string
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){

    if (col->data + i == NULL){
        str = " ";
    }

    else {
        switch (col->column_type) {

            case INT :
                snprintf(str, size, "%d", *((int *) col->data[i]));
                break;
            case FLOAT :
                snprintf(str, size, "%f", *((float *) col->data[i]));
                break;
            case CHAR :
                snprintf(str, size, "%c", *((char *) col->data[i]));
                break;
            case DOUBLE :
                snprintf(str, size, "%lf", *((double *) col->data[i]));
                break;
            case STRING :
                snprintf(str, size, "%s", *((char **) col->data[i]));
                break;
            case STRUCTURE :
                //snprintf(str, size, "", *((STRUCT*)col->data[i]));
                break;

        }
    }

}

//function that prints a whole column. takes as parameter a pointer to the column
void print_col(COLUMN* col){

    if (col->data == NULL && col!= NULL){
        for (int i = 0 ; i< col->size ; i ++ ){
            printf("[%d] NULL", i);
            return ;
        }
    }

    switch (col->column_type) {

        case INT :
            for (int i = 0 ; i< col->size ; i ++ ){

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
            for (int i = 0 ; i< col->size ; i ++ ){

                printf("[%d] %f \n", i,  *((float*)col->data[i]));


            }
            break ;
        case DOUBLE :
            for (int i = 0 ; i< col->size ; i ++ ){

                printf("[%d] %lf \n", i,  *((double*)col->data[i]));


            }
            break ;
        case STRING :
            for (int i = 0 ; i< col->size ; i ++ ){

                printf("[%d] %s \n", i,  *((char**)col->data[i]));


            }
        case STRUCTURE :
            for (int i = 0 ; i< col->size ; i ++ ){

                //printf("[%d] %STRUCT \n", i,  *((STRUCT*)col->data[i]));


            }
            break ;


    }

}

// function that returns the number of occurences of a value inside a column.
//takes as parameter a pointer to the column, the value to search for, and the type of data that the value is
int nb_occurrences(COLUMN * col, void * value, ENUM_TYPE type_of_data){

    if (type_of_data != col->column_type){

        return -1 ;

    }

    int occurrences = 0 ;

    switch (type_of_data){

        case INT :
            for (int i = 0 ; i < col->size ; i++){

                if (col->data[i]!=NULL) {

                    if (*((int *) (col->data[i])) == *((int *) value)) {

                        occurrences += 1;

                    }
                }
            }
            break ;

        case CHAR :
            for (int i = 0 ; i < col->size ; i++){
                if (col->data[i]!=NULL) {
                    if (*((char *) (col->data[i])) == *((char *) value)) {

                        occurrences += 1;

                    }
                }

            }
            break ;

        case FLOAT :
            for (int i = 0 ; i < col->size ; i++){

                if (col->data[i]!=NULL) {
                    if (*((float *) (col->data[i])) == *((float *) value)) {

                        occurrences += 1;

                    }
                }
            }
            break ;

        case DOUBLE :
            for (int i = 0 ; i < col->size ; i++){

                if (col->data[i]!=NULL) {
                    if (*((double *) (col->data[i])) == *((double *) value)) {

                        occurrences += 1;

                    }
                }
            }
            break ;

        case STRING :
            for (int i = 0 ; i < col->size ; i++){

                if (col->data[i]!=NULL) {
                    if (*((char **) (col->data[i])) == *((char **) value)) {

                        occurrences += 1;

                    }
                }
            }
            break ;

    }


    return occurrences;
}

//function that returns the value at an index inside a column, both given as parameter
void * value_at_index(COLUMN * col, int x){

    if (col->size <= x || x < 0 || col->data[x] == NULL ){

        return NULL ;

    }

    return ((col->data[x])) ;
}

// function that returns the amount of values inside the column greater than a given value as parameter
// also takes as parameter the column and the type of value
int values_greater_than(COLUMN * col, void * x, ENUM_TYPE type_of_data){

    if (x == NULL){

        return 0 ;

    }
    if (type_of_data != col->column_type){

        return -1 ;

    }

    int occurrences = 0 ;

    switch (type_of_data){

        case INT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(int *) col->data[i] > *(int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case CHAR :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char *) col->data[i] > *(char *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case FLOAT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(float *) col->data[i] > *(float *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case DOUBLE :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(double *) col->data[i] > *(double *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case STRING :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char**) col->data[i] > *(char**) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case UINT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(unsigned int *) col->data[i] > *(unsigned int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;
    }

    return occurrences ;
}

// function that returns the amount of values inside the column lower than a given value as parameter
// also takes as parameter the column and the type of value
int values_lower_than(COLUMN * col, void * x, ENUM_TYPE type_of_data){

    if (x == NULL){

        return 0 ;

    }
    if (type_of_data != col->column_type){

        return -1 ;

    }

    int occurrences = 0 ;

    switch (type_of_data){

        case INT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(int *) col->data[i] < *(int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case CHAR :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char *) col->data[i] < *(char *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case FLOAT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(float *) col->data[i] < *(float *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case DOUBLE :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(double *) col->data[i] < *(double *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case STRING :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char**) col->data[i] < *(char**) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case UINT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(unsigned int *) col->data[i] < *(unsigned int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;
    }

    return occurrences ;
}

// function that returns the amount of values inside the column equal to a given value as parameter
// also takes as parameter the column and the type of value
int values_equal_to(COLUMN * col, void * x, ENUM_TYPE type_of_data){

    if (x == NULL){

        return 0 ;

    }
    if (type_of_data != col->column_type){

        return -1 ;

    }

    int occurrences = 0 ;

    switch (type_of_data){

        case INT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(int *) col->data[i] == *(int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case CHAR :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char *) col->data[i] == *(char *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case FLOAT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(float *) col->data[i] == *(float *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case DOUBLE :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(double *) col->data[i] == *(double *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case STRING :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(char**) col->data[i] == *(char**) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;

        case UINT :
            for (int i = 0 ; i < col->size ; i++ ){
                if(col->data[i] != NULL) {

                    if (*(unsigned int *) col->data[i] == *(unsigned int *) x) {

                        occurrences += 1;

                    }
                }


            }
            break ;
    }

    return occurrences ;
}


