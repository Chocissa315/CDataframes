#include "cdataframe.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    char title[100];
    COLUMN *dat;
    lnode *ptemp;
    CDATAFRAME *cdf = NULL;
    list *liste = NULL;

    printf("Enter the column's name: ");
    scanf("%s", title);

    liste = lst_create_list(); /* Creates the list/dataframe */

    for (int i = 0; i < size; i++) {
        dat = create_column(*cdftype, title); /* Creates a column */
        ptemp = lst_create_lnode(dat); /* Creates a node with the column */
        if (i == 0) {
            lst_insert_head(liste, ptemp); /* If it's the first iteration then we insert a head */
        } else {
            lst_insert_tail(liste, ptemp); /* Each time we need to create a new column, it inserts it as a tail like this we are sure that it will be added to the end of the list*/
        }
    }
    cdf->lst = liste;
    return cdf;
}



void delete_cdataframe(CDATAFRAME **cdf){

    /*  **cdf points to the list so the list is given by *cdf sà it will use it with lst_delete_list that takes as parameter a list*/
    if(*cdf != NULL){ /*e verify if the list is yet empty*/
        lst_delete_list((*cdf)->lst); /* we use the lst_delete_list function to delete entirely the list*/
        free(*cdf); /* We free the memory to be sure that we left nothing */
        *cdf = NULL; /*we point to NULL to says that the cdataframe is totally empty */

    }

}



int get_cdataframe_cols_size(CDATAFRAME *cdf){
    /* For this function we take the first and last node. We set the actual node as the first one and iterate through the list going to the next_node until the actual node equals the last one.
     * While doing this, we increment a counter that begins to one because we begin with the first node. This counter will give us the number of columns. */
    lnode *last_node, *actual_node;
    int count = 1;

    last_node = get_last_node(cdf->lst);
    actual_node = get_first_node(cdf->lst);

    while(actual_node != last_node){
        count += 1;
        actual_node = get_next_node(cdf->lst, actual_node);

    }

    return count;

}



void delete_col(CDATAFRAME *cdf, char *col_name){

    // Works like the delete_cdataframe function
    //   delete_column(&col_name);
    lnode *actual_node;
    char *title;
    int nb_col;
    nb_col = get_cdataframe_cols_size(cdf);
    actual_node = get_first_node(cdf->lst);
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title;
        if(strcmp(col_name,title) == 0){
            delete_column((COLUMN**)actual_node->data);

        }
        actual_node = get_next_node(cdf->lst, actual_node);


    }


    // I  have to go through the list and found the node having the same name as the column then delete t=it
}


void display_cdataframe(CDATAFRAME *cdf){
    int nb_col, j;
    COLUMN *column;
    lnode *actual_node;
    ENUM_TYPE coltype;
    j = 0;

    actual_node = get_first_node(cdf->lst);

    nb_col = get_cdataframe_cols_size(cdf);


    for(int i =0; i < nb_col;i++){
        while(j < i){
            printf("              ");
        }
        column = (COLUMN*)actual_node->data;
        print_col(column);
        actual_node = get_next_node(cdf->lst,actual_node);
    }

}

lnode* get_col_from_name(CDATAFRAME* cdf, char* col_name){

    lnode * actual_node = get_first_node(cdf->lst);
    int size = get_cdataframe_cols_size(cdf);

    int i = 0 ;

    while (i < size){

        if(strcmp(((COLUMN*)actual_node->data)->title, col_name)){

            return actual_node ;

        }

        actual_node = actual_node->next ;
        i++;

    }

    return NULL ;
}

int enter_value_at_col(CDATAFRAME * cdf,char* col_name, void* value, ENUM_TYPE type_of_data){

    lnode * col = get_col_from_name(cdf, col_name);

    if (col == NULL){
        return 0;
    }


    if(type_of_data!= ((COLUMN*)col->data)->column_type){
        return 0 ;
    }

    insert_value(((COLUMN*)col->data), value, type_of_data);

    return 1;
}

int hard_filling_of_column(CDATAFRAME * cdf, char * col_name, int nb_of_values){

    lnode * col = get_col_from_name(cdf, col_name);

    if (col == NULL){
        return 0;
    }

    switch (((COLUMN*)col->data)->column_type){

        void *  val ;
        case NULLVAL :
            insert_value(col->data, NULL, NULLVAL) ;

        case UINT :
            val = (unsigned int *)malloc(sizeof(unsigned int*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%d", (unsigned int *)val);
                insert_value(col->data, val, UINT) ;
            }

        case INT :
            val = (int *)malloc(sizeof(int*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%d", (int *)val);
                insert_value(col->data, val, INT) ;
            }

        case FLOAT :
            val = (float *)malloc(sizeof(float*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%f", (float *)val);
                insert_value(col->data, val, FLOAT) ;
            }

        case DOUBLE :
            val = (double *)malloc(sizeof(double*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%lf", (double *)val);
                insert_value(col->data, val, DOUBLE) ;
            }

        case CHAR :
            val = (char *)malloc(sizeof(char*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%c", (char *)val);
                insert_value(col->data, val, CHAR) ;
            }

        case STRING :
            val = (char*)malloc(sizeof(char*));
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i);
                scanf("%s", (char*)val);
                insert_value(col->data, &val, STRING) ;
            }
    }

    return 1 ;
}


void print_all_cdataframe(CDATAFRAME* cdf){

    lnode * actual_node = cdf->lst ;

    if (actual_node != NULL) {
        while (actual_node->next != NULL) {

            print_col(actual_node->data);
            actual_node = actual_node->next ;
            printf("\n");

        }
    }

}

void print_lines_of_col_up_to(CDATAFRAME *cdf, char* col_name, unsigned int max_lines){
    COLUMN * col = get_col_from_name(cdf, col_name)->data;

    //copy of print_col, but with limitations on the number :

    if (max_lines > col->size){
        printf("\nError, couldn't print [%d] lines, there is only [%d] of them, "
               "printing all the lines : \n", max_lines, col->size);

        max_lines = col->size ;

    }
    max_lines -- ;
    switch (col->column_type) {

        case INT :
            for (int i = 0 ; i< max_lines ; i ++ ){

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
            for (int i = 0 ; i < max_lines ; i ++ ){
                if (col->data[i] == NULL){
                    printf("[%d] NULL \n",i);
                }
                else {
                    printf("[%d] %c \n", i, (col->data[i]->char_value));
                }

            }
            break ;
        case FLOAT :
            for (int i = 0 ; i< max_lines ; i ++ ){

                printf("[%d] %f \n", i,  *((float*)col->data[i]));


            }
            break ;
        case DOUBLE :
            for (int i = 0 ; i< max_lines ; i ++ ){

                printf("[%d] %lf \n", i,  *((double*)col->data[i]));


            }
            break ;
        case STRING :
            for (int i = 0 ; i< max_lines ; i ++ ){

                printf("[%d] %s \n", i,  *((char**)col->data[i]));


            }
        case STRUCTURE :
            for (int i = 0 ; i< max_lines ; i ++ ){

                //printf("[%d] %STRUCT \n", i,  *((STRUCT*)col->data[i]));


            }
            break ;


    }

}

void print_cols_by_name(CDATAFRAME * cdf, char ** list_of_names_cols_to_print, int nb_of_cols_to_print){

    COLUMN * temp ;
    for (int i = 0 ; i < nb_of_cols_to_print ; i++){

        temp = get_col_from_name(cdf, list_of_names_cols_to_print[i]);
        print_col(temp);

    }

}

void add_line(CDATAFRAME* cdf){

    int size = get_cdataframe_cols_size(cdf);

    lnode * actual_node = cdf->lst->head ;
    void * temp ;

    if(actual_node == NULL){
        size = 1 ;
    }

    for (int i =0 ; i<size ; i++){

        printf("Enter a value for column '%s' : \n", ((COLUMN*)actual_node->data)->title);
        switch( ((COLUMN*)actual_node->data)->column_type){

            case UINT :
                temp = (unsigned int*)malloc(sizeof(unsigned int *));
                scanf("%d", (unsigned int*)temp);
                insert_value(actual_node->data, temp, UINT);
                break ;

            case INT :
                temp = (int*)malloc(sizeof(int *));
                scanf("%d", (int*)temp);
                insert_value(actual_node->data, temp, INT);
                break ;

            case CHAR :
                temp = (char*)malloc(sizeof(char*));
                scanf("%c", (char*)temp);
                insert_value(actual_node->data, temp, CHAR);
                break ;

            case FLOAT :
                temp = (float*)malloc(sizeof(float*));
                scanf("%f", (float*)temp);
                insert_value(actual_node->data, temp, FLOAT);
                break ;

            case DOUBLE :
                temp = (double*)malloc(sizeof(double*));
                scanf("%c", (double*)temp);
                insert_value(actual_node->data, temp, DOUBLE);
                break ;

            case STRING :
                temp = (char**)malloc(sizeof(char**));
                scanf("%s", (char*)temp);
                insert_value(actual_node->data, temp, STRING);
                break ;
        }

        actual_node = actual_node->next ;
    }

}

int delete_line(CDATAFRAME *cdf, int index_line){

    int size = get_cdataframe_cols_size(cdf);
    lnode * actual_node = cdf->lst->head ;
    for (int i = 0 ; i < size ; i++){

        if (((COLUMN*)actual_node->data)->size <= index_line){
            return 0 ;
        }
        ((COLUMN*)actual_node->data)->data[index_line] = NULL ;

        actual_node = actual_node->next ;

    }
    return 1 ;
}

void add_col(CDATAFRAME * cdf, ENUM_TYPE type, char* title){

    COLUMN * col = create_column(type, title);

    lnode * node = lst_create_lnode(col);

    lst_insert_tail(cdf->lst, node) ;

}




