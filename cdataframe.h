//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to cdataframes

#include "Column.h"
#include "list.h"


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
void add_col(CDATAFRAME * cdf, ENUM_TYPE type, char* title);
void display_cdataframe(CDATAFRAME *cdf);






 //void rename_cols(CDATAFRAME *cdf, char *col_name, char* newname);







