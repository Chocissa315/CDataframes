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

    int x = 1 ;

    char* value = (char*)value_at_index(mycol, x) ;

    char buffer[100];

    convert_value(mycol, x, buffer, 100);

    if (value) {
        printf("%s / %c \n", buffer, *value);

    }
    else{
        printf("it didn't work out, the value was |%s| \n", buffer);
    }

    printf("The number of 'C' present in the column is : %d", nb_occurrences(mycol, &c, CHAR));

    char nul = ' ' ;

    printf("\n the number is : %d ", values_greater_than(mycol, &nul, CHAR));

    delete_column(&mycol);





    return 0;
}
