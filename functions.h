//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to functions (not for user)

#define _FUNCTIONS_H_
#include "cdataframe.h"
#include <stdbool.h>

void rename_col(CDATAFRAME *cdf, char *col_name, char *new_title); // did

bool check_value(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value); //did

COL_TYPE* access_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb); //dud
void replace_cdataframe(CDATAFRAME *cdf, int row_nb, int col_nb, COL_TYPE new_val);

void display_col_name(CDATAFRAME *cdf);

void display_nb_rows(CDATAFRAME *cdf,char *col_name); //did

int equals_to(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value); //did
int greater_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value); //did
int less_than(CDATAFRAME *cdf, void *value, ENUM_TYPE type_of_value); //dud


