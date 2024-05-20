//CDATAFRAME Idrissa Barry & Noah Jeandeau file of functions related to columns (not for user)

#ifndef _CDATAFRAMES_COLUMN_H
#define _CDATAFRAMES_COLUMN_H


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/

enum enum_type{

    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE

};
typedef enum enum_type ENUM_TYPE;



union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value ;
    double double_value ;
    char* string_value ;
    void* struct_value ;


};
typedef union column_type COL_TYPE ;



typedef struct{

        char *title;

        unsigned int size; //logical size

        unsigned int max_size; //physical size

        ENUM_TYPE column_type;

        COL_TYPE **data; // array of pointers to stored data

        unsigned long long int *index; // array of integers


}COLUMN;



COLUMN *create_column(ENUM_TYPE type , char *title);


int insert_value(COLUMN *col, void *value, ENUM_TYPE type_of_data);


void delete_column(COLUMN **col);


void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);


void print_col(COLUMN* col);

//In addition to the above functions, we need to implement all the functions that enable the following
//operations to be carried out:
// Return the number of occurrences of a value x (x given as a parameter).
// Return the value present at position x (x given as a parameter).
// Return the number of values that are greater than x (x given as a parameter).
// Return the number of values that are less than x (x given as a parameter).
// Return the number of values which are equal to x (x given as a parameter).

int nb_occurrences(COLUMN * col, void * value, ENUM_TYPE type_of_data);

void* value_at_index(COLUMN * col, int x);

int values_greater_than(COLUMN * col, void * x, ENUM_TYPE type_of_data);

int values_lower_than(COLUMN * col, void* x, ENUM_TYPE type_of_data);

int values_equal_to(COLUMN * col, void * x, ENUM_TYPE type_of_data);

void test();


#endif