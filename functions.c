
//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to functions (not for user)

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//rename a given column
void rename_col(CDATAFRAME *cdf, char *col_name, char *new_title){
    lnode *actual_node;
    char *title;
    int nb_col;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title;
        if(strcmp(col_name,title) == 0){ //check if we are in the good colum,
            ((COLUMN*)actual_node->data)->title = new_title; //change the title
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }

}

//display the columns' names
void display_col_name(CDATAFRAME *cdf){
    lnode *actual_node;
    char *col_name;
    int nb_col;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);

    for(int i = 0; i<nb_col; i++){
        col_name = ((COLUMN*)actual_node->data)->title; // for each column it acces to the title then print it
        printf("%s \n", col_name);
        actual_node = get_next_node(cdf->lst, actual_node);
    }
}

//display the number of rows of a column
void display_nb_rows(CDATAFRAME *cdf,char *col_name){
    lnode *actual_node;
    char *title;
    int nb_col;
    int nb_row;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title;
        if(strcmp(col_name,title) == 0){// check if we are in the good column
            nb_row = (((COLUMN*)actual_node->data)->size); // we access to the logical size of the column which is the number of rows

        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    printf("There is %d rows.", nb_row);

}

// tells the user how many variables are equal to the one he gaves
int equals_to(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value == (((COLUMN*)actual_node->data)->column_type)){// check if the column we are in has the same type as the value. If yes, it will search the value in the column, if not it will do nothing.
            counter += nb_occurrences((COLUMN*)actual_node, value, type_of_value);// we use the nb_occurrences function to know how many time the value appears in it. After that, we add it to counter which will represent how many times the value appeaars in all the cdataframe.
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;

}

// Gives the number of values grater than the given one. It works like the previous one
int greater_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value >= (((COLUMN*)actual_node->data)->column_type)){
            counter += values_greater_than((COLUMN*)actual_node, value, type_of_value);
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;
}

// gives the number that are less are equal to the given one . Works like the previous one.
int less_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value <= (((COLUMN*)actual_node->data)->column_type)){
            counter += values_lower_than((COLUMN*)actual_node, value, type_of_value);
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;
}


// Check if a value exists in the cdatframe. Return True if the value exists, False if it does not exist
bool check_value(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value) {
    lnode *actual_node;
    int nb_col;
    bool exists = false;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);

    for(int i = 0; i < nb_col; i++) {
        if(type_of_value <= ((COLUMN*)actual_node->data)->column_type) { // check if the column as the same datatype as the given value to not search in columns that does not have the same datatype.
            int size_col = ((COLUMN*)actual_node->data)->size; // gets the number of rows to iterate through the coluimn
            for(int j = 0; j < size_col; j++) {
                COL_TYPE *checker = ((COLUMN*)actual_node->data)->data[j];
                // Compare the values pointed to by checker and value
                int equal = 1 ;
                switch(((COLUMN*)actual_node->data)->column_type){

                    case INT :
                        if ((int*)checker == (int*)value ) {
                            exists = true;
                            break;  // No need to continue searching if the value is found
                        }
                    case FLOAT :
                        if ((float*)checker == (float*)value )  {
                            exists = true;
                            break;  // No need to continue searching if the value is found
                        }
                    case CHAR :
                        if ((char*)checker == (char*)value )  {
                            exists = true;
                            break;  // No need to continue searching if the value is found
                        }
                    case UINT :
                        if ((unsigned int*)checker == (unsigned int *)value )  {
                            exists = true;
                            break;  // No need to continue searching if the value is found
                        }
                    case DOUBLE :
                        if ((double*)checker == (double*)value )  {
                            exists = true;
                            break;  // No need to continue searching if the value is found
                        }

                }

            }
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }

    return exists;
}

//Access to the data in the given index
COL_TYPE* access_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb) {
    lnode *actual_node;
    actual_node = get_first_node(cdf->lst);
    int current_col = 0;


    while (actual_node != NULL && current_col <= col_nb) {
        if (current_col == col_nb) {// checks if we are in the good column

            void* value = value_at_index((COLUMN*)actual_node->data, row_nb);  // use the value_at_index function to access the wanted data/
            return (COL_TYPE*)value;
        }

        actual_node = get_next_node(cdf->lst, actual_node);
        current_col++;
    }


    return NULL;
}

//replace a value in the cdataframe
void replace_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb, COL_TYPE new_val){
    COL_TYPE *value = access_cdataframe(cdf,row_nb, col_nb); //use the access_cdataframe to the right value
    *value = new_val;

}



