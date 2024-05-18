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


    }


    // I  have to go through the list and found the node having the same name as the column then delete t=it
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






