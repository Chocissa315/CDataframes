#include <stdio.h>
#include "Column.h"
#include "sort.h"
#include "functions.h"
#include "list.h"


int main(){



    // Create a column
    COLUMN *col = create_column(INT, "Example Column");

    // Insert values into the column
    int value1 = 10;
    insert_value(col, &value1, INT);

    int value2 = 20;
    insert_value(col, &value2, INT);

    int value3 = 30;
    insert_value(col, &value3, INT);

    // Print the column
    printf("Column Title: %s\n", col->title);
    print_col(col);

    // Test other functions
    printf("\nNumber of occurrences of 20: %d\n", nb_occurrences(col, &value2, INT));
    printf("Value at index 1: %d\n", *(int*)value_at_index(col, 1));
    printf("Number of values greater than 15: %d\n", values_greater_than(col, &value1, INT));
    printf("Number of values lower than 25: %d\n", values_lower_than(col, &value2, INT));
    printf("Number of values equal to 20: %d\n", values_equal_to(col, &value2, INT));


    printf("trying cdataframes functions\n");

    // Create a cdataframe
    ENUM_TYPE cdftype = INT;
    CDATAFRAME *cdf = create_cdataframe(&cdftype, 3);



    // Add a new column
    ENUM_TYPE new_col_type = FLOAT;
    ENUM_TYPE second_type = INT;
    char *new_col_title = "New Column";
    char *sec_title = "Sec col";
    add_col(cdf, new_col_type, new_col_title);
    add_col(cdf,second_type, sec_title);

    //print columns by name
    // Define an array of column names to print
    char *columns_to_print[] = {"New Column", "Sec col", "col3"};
    int num_columns = sizeof(columns_to_print) / sizeof(columns_to_print[0]);
    printf("Printing columns by name:\n");
    print_cols_by_name(cdf, columns_to_print, 3);

    // Enter values into the dataframe
    int value5 = 10;
    char * title;
    title = "Nope";
    enter_value_at_col(cdf, title, &value3, INT);

    float value4 = 3.14;
    enter_value_at_col(cdf, new_col_title, &value4, FLOAT);

    // Display the dataframe
    printf("\nDataFrame:\n");
    display_cdataframe(cdf);

    // Add a line
    printf("\nAdding a line...\n");
   // add_line(cdf);

    // Display the modified dataframe
    printf("\nModified DataFrame:\n");
    display_cdataframe(cdf);

    // Delete a line
    int line_index = 1;
    printf("\nDeleting line at index %d...\n", line_index);
    delete_line(cdf, line_index);

    // Display the dataframe after deletion
    printf("\nDataFrame after deletion:\n");
    display_cdataframe(cdf);

    ENUM_TYPE type = INT; // Change this to the desired data type
    int size = 3; // Change this to the desired number of columns



    // Display the column names
    printf("Column Names:\n");
    display_col_name(cdf);
    printf("\n");

    // Display the number of rows for a specific column
    char *col_name = "bruuuh"; // Change this to the desired column name
    printf("Number of rows in column '%s':\n", col_name);
    display_nb_rows(cdf, col_name);
    printf("\n");

    // Rename a column
    char *new_title = "new_title"; // Change this to the desired new column title
    rename_col(cdf, col_name, new_title);
    printf("Column Names after renaming:\n");
    display_col_name(cdf);
    printf("\n");

    // Check if a value exists in the dataframe
    int value_to_check = 5; // Change this to the desired value
    printf("Checking if value %d exists in the dataframe: %s\n", value_to_check, check_value(cdf, &value_to_check, type) ? "true" : "false");
    printf("\n");

    // Access a specific element in the dataframe
    int row = 0; // Change this to the desired row number
    int col_nb = 0; // Change this to the desired column number
    COL_TYPE *accessed_value = access_cdataframe(cdf, row, col_nb);
    printf("Accessed value at row %d, column %d: %d\n", row, col_nb, *accessed_value);
    printf("\n");

    // Replace a specific element in the dataframe
    COL_TYPE new_value; // Change this to the desired new value
    new_value.int_value = 10;
    replace_cdataframe(cdf, row, col_nb, new_value);
    printf("After replacing the value:\n");
    accessed_value = access_cdataframe(cdf, row, col_nb);
    printf("Accessed value at row %d, column %d: %d\n", row, col_nb, *accessed_value);
    printf("\n");

    // Free memory
    delete_cdataframe(&cdf);



    return 0;
}
