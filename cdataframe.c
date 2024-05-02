#include "cdataframe.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>


CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    char title[100];
    COLUMN *dat;
    lnode *ptemp;
    list *cdf;

    printf("Enter the column's name: ");
    scanf("%s", title);

    cdf = lst_create_list(); /* Creates the list/datafram */

    for (int i = 0; i < size; i++) {
        dat = create_column(*cdftype, title); /* Creates a column */
        ptemp = lst_create_lnode(dat); /* Creates a node with the column */
        if (i == 0) {
            lst_insert_head(cdf, ptemp); /* If it's the first iteration then we insert a head */
        } else {
            lst_insert_tail(cdf, ptemp); /* Each time we need to create a new column, it inserts it as a tail like this we are sure that it will be added to the end of the list*/
        }
    }

    return cdf;
}



void delete_cdataframe(CDATAFRAME **cdf){

    /*  **cdf points to the list so the list is given by *cdf sà it will use it with lst_delete_list that takes as parameter a list*/
    if(*cdf != NULL){ /*e verify if the list is yet empty*/
        lst_delete_list(*cdf); /* we use the lst_delete_list function to delete entirely the list*/
        free(*cdf); /* We free the memory to be sure that we left nothin */
        *cdf = NULL; /*we point to NULL to says that the cdataframe is totally empty */

    }

}

void delete_col(CDATAFRAME *cdf, char *col_name){
    // Works like the delete_cdataframe function
    lnode *actual_node;

    actual_node = get_first_node(cdf);

    while(actual_node != NULL){

    }

    // I  have to go through the list and found the node having the same name as the column then delete t=it
}

int get_cdataframe_cols_size(CDATAFRAME *cdf){
    /* For this function we take the first and last node. We set the actual node as the first one and iterate through the list going to the next_node until the actual node equals the last one.
     * While doing this, we increment a counter that begins to one because we begin with the first node. This counter will give us the number of columns. */
    lnode *last_node, *actual_node;
    int count = 1;

    last_node = get_last_node(cdf);
    actual_node = get_first_node(cdf);

    while(actual_node != last_node){
        count += 1;
        actual_node = get_next_node(cdf, actual_node);

    }

    return count;

}


