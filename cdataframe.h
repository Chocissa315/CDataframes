
#include "Column.h"
#include "list.h"

#define _CDATAFRAME_H_


typedef struct CDATAFRAME{

    list *lst;

}CDATAFRAME;

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

/**
* @brief: Column deletion
* param1: Pointer to the CDataframe to delete
*/
void delete_cdataframe(CDATAFRAME **cdf);

/**
* @breif: Delete column by name
* @param1: Pointer to the CDataframe
* @param2: Column name
*/
void delete_col(CDATAFRAME *cdf, char *col_name);

/**
* @brief: Number of columns
* @param1: Point to the CDataframe
* @return: Number of columns in the CDataframe
*/
int get_cdataframe_cols_size(CDATAFRAME *cdf); //did it

lnode* get_col_from_name(CDATAFRAME* cdf, char* col_name);

int enter_value_at_col(CDATAFRAME * cdf,char* col_name, void* value, ENUM_TYPE type_of_data);

int hard_filling_of_column(CDATAFRAME * cdf, char * col_name, int nb_of_values);

void print_all_cdataframe(CDATAFRAME* cdf);

void print_lines_of_col_up_to(CDATAFRAME *cdf, char* col_name, unsigned int max_lines);

void print_cols_by_name(CDATAFRAME * cdf, char ** list_of_names_cols_to_print, int nb_of_cols_to_print);

void add_line(CDATAFRAME* cdf);

int delete_line(CDATAFRAME *cdf, int index_line) ;

/* FUNCTIONS TO FILL
 *


* Fill the CDataframe with the user input
 *
 * We first take the pointer to the dataframe then choose a column to fill
int fill_cdataframe(CDATAFRAME *cdf,char *col_name);

* Hard filling of the dataframe
 *
 */



/* FUNCTIONS TO DISPLAY
 *
 * Display the entire CDataframe
 * For the moment takes only the pointer to the dataframe
 void display_cdataframe(CDATAFRAME *cdf);

 *Display rows according what the users wants
 * The limit will probably be the number of rows the user wants
 void display_rows(CDATAFRAME *cdf, int limit);

 * Display columns acccording what the user wants
 * idea: We can make a list filled by the user of what columns he wants to be displayed then use it in the function
 * void display_cols(CDATAFRAME *cdf);
 *
 */



/* FUNCTIONS OF USUAL OPERATIONS
 *
 * Add a row of values
 * Idea : going through all the columns using the nodes and add to the lists of data inside the column at a certain
 * position (use the function insert_value that we need to code inside the column part)
 *
 *
 * Delete a row of values :
 *
 *idea : we may use the previous function and in some way reverse it
 *
 * Add a column
 * idea : We will use the functions of columns.h
 * to add a column we would maybe just have to create a new column, create a node linked to it, and insert this node
 * into the list of nodes by giving the previous one the address of this new node (instead of the next one) and the next
 * one the address of this node (instead of the previous one)
 *
 * Delete a column
 * idea : same idea as before
 * to ensure the possibility to go through the whole list, we will have to reconnect the node before and the node after
 * by giving them the address of the next/previous one instead of the one we deleted
 *
 * Rename the title of a column in the CDataframe
 */
 void rename_cols(CDATAFRAME *cdf, char *col_name, char* newname);

/* search for a value
 * idea = ??
 * void search_val(CDATAFRAME *cdf, type-of-val val);
 *
 * Access a value in the CDataframe
 *
 * void access_val (CDATAFRAME *cdf, char *row_name, char *col_name);
 *
 * Replace a value
 * idea : we use the previous function but this time we change the given value
 *
 * Display column names
 * idea : ??
 * void display_col_names(CDATAFRAME *cdf);
 *
 */

/* ANALYSIS AND STATISTICS
 *
 * Display the number of rows
 * void number_of_rows(CDATAFRAME *cdf);
 *
 * Display the number of columns
 * void number_of_cols(CDATAFRAME *cdf);
 *
 * Display the number of cells = x
 * idea : ??
 * void cells_equal_to(CDATAFRAME *cdf, type-of_x x);
 *
 * Display the number of cells > x
 * idea : ??
 * void cells_greater(CDATAFRAME *cdf, type-of_x x);
 *
 * Display the number of cells < x
 * idea : ??
 * void cells_less(CDATAFRAME *cdf, type-of_x x);
 *
 *
 */


/**
* @brief: Create a CDataframe from csvfile
* @param1: CSV filename
* @param2: Array of types
* @param3: Size of array in param2
*/
CDATAFRAME* load_from_csv(char *file_name, ENUM_TYPE *dftype, int size);

/**
* @brief: Export into a csvfile
* @param1: Pointer to the CDataframe
* @param2: csv filename where export file, if the file exists,
* it will be overwritten
*/
void save_into_csv(CDATAFRAME *cdf, char *file_name);


