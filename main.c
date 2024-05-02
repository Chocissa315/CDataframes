#include <stdio.h>
#include "Column.h"
#include "sort.h"
#include "cdataframe.h"
#include "list.h"

int main(){

    COLUMN *mycol = create_column(CHAR, "Column 1");

    char a = 'A', c = 'C';

    insert_value(mycol, &a, CHAR);

    insert_value(mycol, NULL, CHAR);

    insert_value(mycol, &c, CHAR);

    print_col(mycol);

    delete_column(&mycol);







    return 0;
}
