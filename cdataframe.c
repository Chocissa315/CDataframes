#include "cdataframe.h"
#include "list.h"
#include <stdio.h>



CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    ENUM_TYPE type = *cdftype;
    char title[100];
    void *dat;
    lnode *ptemp;
    list *liste;

    printf("Enter the column's name: ");
    scanf("%s", title);
    liste = lst_create_list();

    for (int i = 0; i < size; i++) {
        dat = create_column(type, title);
        ptemp = lst_create_lnode(dat);
        if (i == 0) {
            lst_insert_head(liste, ptemp);
        } else {
            lst_insert_tail(liste, ptemp);
        }
    }

    return liste;
}



void delete_cdataframe(CDATAFRAME **cdf){

    /* What I can do is go through the Linked list and delete one by one the nodes which represents the cols
     * in theory it can work Avec le go to the next it can work et on vérifie que le node n'est pas null*/

}

int get_cdataframe_cols_size(CDATAFRAME *cdf){


}


/* DUcoup j'ai besoin du last node and maybe the first one and get the next node ?
 * as this I can maybe have the number of columns  and maybe the erase function too idk
 */