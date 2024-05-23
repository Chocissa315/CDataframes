//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to cdataframes

#include "cdataframe.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creates cdataframe
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    char *title = "cdataframe";
    COLUMN *dat;
    lnode *ptemp;
    CDATAFRAME *cdf = malloc(sizeof(CDATAFRAME)); // allocate enough size for the cdataframe
    list *liste = NULL;

    title = malloc(sizeof(char)*strlen("cdataframe")+1);
    strcpy(title, "cdataframe");


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


// deletes cdataframes
void delete_cdataframe(CDATAFRAME **cdf){

    /*  **cdf points to the list so the list is given by *cdf sà it will use it with lst_delete_list that takes as parameter a list*/
    if(*cdf != NULL){ /*e verify if the list is yet empty*/
        lst_delete_list((*cdf)->lst); /* we use the lst_delete_list function to delete entirely the list*/
        free(*cdf); /* We free the memory to be sure that we left nothing */
        *cdf = NULL; /*we point to NULL to says that the cdataframe is totally empty */

    }

}


// gets the number of columns in the cdataframe
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


// delete a column with a given name
void delete_col(CDATAFRAME *cdf, char *col_name){

    lnode *actual_node;
    char *title;
    int nb_col;
    nb_col = get_cdataframe_cols_size(cdf); //we take the number of columns to not iterate when is not useful.
    actual_node = get_first_node(cdf->lst); // we take the first to have the possibility to acces all nodes.
    for(int i = 0; i < nb_col; i++){
        title = ((COLUMN*)actual_node->data)->title; // takes the title of the actual node/column
        if(strcmp(col_name,title) == 0){ //when strcmp = 0 then the two strings are equal and it means that we are in the good column.
            delete_column((COLUMN**)actual_node->data);

        }
        actual_node = get_next_node(cdf->lst, actual_node);


    }


}

// display the cdataframe by columns
void display_cdataframe(CDATAFRAME *cdf) {
    int nb_col, j;
    COLUMN *column;
    lnode *actual_node;
    ENUM_TYPE coltype;
    j = 0;


    actual_node = get_first_node(cdf->lst); // we take the first to have the possibility to acces all nodes.
    nb_col = get_cdataframe_cols_size(cdf); //we take the number of columns to not iterate when is not useful.

    for (int i = 0; i < nb_col; i++) {
        column = (COLUMN *)actual_node->data ;

        printf("Column : %s\n", column->title);
        print_col(column);
        printf("*******************\n\n");
        actual_node = get_next_node(cdf->lst, actual_node) ;

    }

}
// allow us to access a column with a given name (we did'nt use it for get_col_size because it was made after but is basically the reasonning and does not really change the run time).
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


// add a value to a specific column
int enter_value_at_col(CDATAFRAME * cdf,char* col_name, void* value, ENUM_TYPE type_of_data){

    lnode * col = get_col_from_name(cdf, col_name); // we get the column with the previous function

    if (col == NULL){
        return 0;
    }


    if(type_of_data!= ((COLUMN*)col->data)->column_type){ // we compare the data type : if it is not the same then we return 0 to say it did not work, else we return 1)
        return 0 ;
    }

    insert_value(((COLUMN*)col->data), value, type_of_data); // use the insert value function to add the value to the column

    return 1;
}


// allow us to hard fill a specific column
int hard_filling_of_column(CDATAFRAME * cdf, char * col_name, int nb_of_values){

    lnode * col = get_col_from_name(cdf, col_name);

    if (col == NULL){
        return 0;
    }

    switch (((COLUMN*)col->data)->column_type){ // we use the switch case to handle any possible case and avoid a maximum of errors. For all the cases we use the same reasonning as the UINT case.

        void *  val ;
        case NULLVAL :
            insert_value(col->data, NULL, NULLVAL) ;

        case UINT :
            val = (unsigned int *)malloc(sizeof(unsigned int*)); // allocate place for the given value
            for (int i = 0  ; i < nb_of_values ; i++){
                printf("\nEnter value at index [%d] : \n", i); // tells the user the index of where the value will be assigned
                scanf("%d", (unsigned int *)val);
                insert_value(col->data, val, UINT) ; // insert the value
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


//Prints all the cdataframe without a limit. It use the same reasonning as the other display cdataframe
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


// prints a given number of lines of a given column.

void print_lines_of_col_up_to(CDATAFRAME *cdf, char* col_name, unsigned int max_lines){
    COLUMN * col = get_col_from_name(cdf, col_name)->data;

    //copy of print_col, but with limitations on the number :

    if (max_lines > col->size){ // check if it is possible to print the number of lines we wanted
        printf("\nError, couldn't print [%d] lines, there is only [%d] of them, "
               "printing all the lines : \n", max_lines, col->size);

        max_lines = col->size ; // in this case it put the numbers of lines to the maximum numbers of lines available in the given column

    }
    max_lines -- ;
    switch (col->column_type) { // for all the other cases we use the same reasonning

        case INT :
            for (int i = 0 ; i< max_lines ; i ++ ){

                if (col->data[i] == NULL){ //print NULL if there is no value
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


// Allow us to print the columns we want
void print_cols_by_name(CDATAFRAME * cdf, char ** list_of_names_cols_to_print, int nb_of_cols_to_print){

    COLUMN * temp ;
    for (int i = 0 ; i < nb_of_cols_to_print ; i++){

        temp = ((COLUMN*)get_col_from_name(cdf, list_of_names_cols_to_print[i])->data); // using the get col from name function it will print each of them
        print_col(temp);

    }

}


//adds a line in the cdataframe
void add_line(CDATAFRAME* cdf){

    int size = get_cdataframe_cols_size(cdf);

    lnode * actual_node = cdf->lst->head ;
    void * temp ;

    if(actual_node == NULL){
        size = 1 ; // check if the column is NULL
    }

    for (int i =0 ; i<size ; i++){

        printf("Enter a value for column '%s' : \n", ((COLUMN*)actual_node->data)->title); // tells the user what is the column where the value will be added
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

//delete a line with its index

int delete_line(CDATAFRAME *cdf, int index_line){

    int size = get_cdataframe_cols_size(cdf);
    lnode * actual_node = cdf->lst->head ; //access to the first column
    for (int i = 0 ; i < size ; i++){

        if (((COLUMN*)actual_node->data)->size <= index_line){ //if the logical size of the column is less than the index, we cannot delete it so we do nothing
            return 0 ;
        }
        ((COLUMN*)actual_node->data)->data[index_line] = NULL ; // else it access to the wanted line and delete the value in it

        actual_node = actual_node->next ;

    }
    return 1 ;
}


//Add columns to the cdataframe
void add_col(CDATAFRAME * cdf, ENUM_TYPE type, char* title){

    COLUMN * col = create_column(type, title); //use the create column function

    lnode * node = lst_create_lnode(col); // creates a node

    lst_insert_tail(cdf->lst, node) ; // then it isert it to the tail like this we are sure it add the column to the end of the cdataframe.

}




