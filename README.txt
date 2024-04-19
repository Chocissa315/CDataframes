CD DATAFRAME PROJECT :

Link to the Github repository :
https://github.com/Chocissa315/CDataframes.git

The project consist in creating a new library similar to the Pandas library on python (specifically the type called
"Dataframes"), but on the language C because no such library exist in C. The idea of the library is to allow the user to
store data into a table, and give the user numerous type of functions that will allow him to access, add, suppress,
modify, etc. data. Similarly to excel, we want to be able to process with big amounts of data, of different types, and
accessing them by columns.

To create this project, several methods of various difficulties were possible. We decided to stick to the basic
functions, but to try to create a CDataframe that would be able to process with any type of data (thanks to the void*
command we just learned about and several structs that will allow us to take as input the type of data we want to store
in the column, and create the column depending on the type chosen by the user).

The columns will therefore be lists of pointers, each one pointing to a value assigned by the user. The pointers are
defined as void pointers to be able to enter the address of any type of data when creating the column and adding values.

For the structure of the CDataframe itself, we decided to go with the double-linked list.

The idea is to make the dataframe a structure containing only the head and the tail of the list of columns.
Each column will be associated to a node type containing three information :
- first the pointer to the column associated, to be able to access the column and the data stored inside it
- then the pointer to the next node, to be able to go through the list from the beginning to the end
- and finally the pointer to the previous node, to be able to go through the list in the other direction.

The bidirectional allows us to ensure a better access, allowing us to go through the list in both directions, but
also a lot of flexibility : we can change direction and move to the next or the previous node (and therefore column)
whenever we need it.
Moreover, this type of structure allows us to be more free while manipulating the columns, and has better flexibility.