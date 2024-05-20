#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rename_col(CDATAFRAME *cdf, char *col_name, char *new_title){
    lnode *actual_node;
    char *title;
    int nb_col;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title;
        if(strcmp(col_name,title) == 0){
            ((COLUMN*)actual_node->data)->title = new_title;
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }

}

bool check_valuea(CDATAFRAME *cdf, void *value){
    lnode *actual_node;
    char *title;
    int nb_col;
    char column_type;
// i will check if the sizes or okay
    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        column_type = ((COLUMN*)actual_node->data)->column_type;
        if(sizeof(column_type) == sizeof(value)){

        }

        actual_node = get_next_node(cdf->lst, actual_node);
    }



}

void display_col_name(CDATAFRAME *cdf){
    lnode *actual_node;
    char *col_name;
    int nb_col;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);

    for(int i = 0; i<nb_col; i++){
        col_name = ((COLUMN*)actual_node->data)->title;
        printf("%s \n", col_name);
        actual_node = get_next_node(cdf->lst, actual_node);
    }
}


void display_nb_rows(CDATAFRAME *cdf,char *col_name){
    lnode *actual_node;
    char *title;
    int nb_col;
    int nb_row;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title;
        if(strcmp(col_name,title) == 0){
            nb_row = (((COLUMN*)actual_node->data)->size);

        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    printf("There is %d rows.", nb_row);

}


int equals_to(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value == (((COLUMN*)actual_node->data)->column_type)){
            counter += nb_occurrences((COLUMN*)actual_node, value, type_of_value);
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;

}

int greater_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value >= (((COLUMN*)actual_node->data)->column_type)){
            counter += nb_occurrences((COLUMN*)actual_node, value, type_of_value);
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;
}

int less_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value){
    lnode *actual_node;
    char *title;
    int nb_col;
    int counter = 0;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        if(type_of_value <= (((COLUMN*)actual_node->data)->column_type)){
            counter += nb_occurrences((COLUMN*)actual_node, value, type_of_value);
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }
    return counter;
}

bool check_value(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value) {
    lnode *actual_node;
    int nb_col;
    bool exists = false;

    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);

    for(int i = 0; i < nb_col; i++) {
        if(type_of_value <= ((COLUMN*)actual_node->data)->column_type) {
            int size_col = ((COLUMN*)actual_node->data)->size;
            for(int j = 0; j < size_col; j++) {
                COL_TYPE *checker = ((COLUMN*)actual_node->data)->data[j];
                // Assuming COL_TYPE is an actual type and not a pointer
                // Compare the values pointed to by checker and value
                if (memcmp(checker, value, sizeof(COL_TYPE)) == 0) {
                    exists = true;
                    break;  // No need to continue searching if the value is found
                }
            }
        }
        actual_node = get_next_node(cdf->lst, actual_node);
    }

    return exists;
}

COL_TYPE* access_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb) {
    lnode *actual_node;
    actual_node = get_first_node(cdf->lst);
    int current_col = 0;


    while (actual_node != NULL && current_col <= col_nb) {
        if (current_col == col_nb) {

            void* value = value_at_index((COLUMN*)actual_node->data, row_nb);
            return (COL_TYPE*)value;
        }

        actual_node = get_next_node(cdf->lst, actual_node);
        current_col++;
    }


    return NULL;
}

void replace_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb, COL_TYPE new_val){
    COL_TYPE *value = access_cdataframe(cdf,row_nb, col_nb);
    *value = new_val;

}



