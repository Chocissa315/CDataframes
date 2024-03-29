#ifndef _CDATAFRAMES_COLUMN_H
#define _CDATAFRAMES_COLUMN_H


/**
* Create a column
* @param1 : Column title
* @return : Pointer to created column
*/

typedef struct{

    int PhysicalSize ;

    char* column_name ;

    void* column_array ;

}COLUMN;

COLUMN *create_column(char *title);

#endif