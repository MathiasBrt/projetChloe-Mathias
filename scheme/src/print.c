
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"
int premiere_parenthese=0;
#include <stdio.h>

void sfs_print_atom( object o ) {
    switch (o->type){
        case SFS_BOOLEAN:
            /*printf("booleen:  ");*/
            printf("%d",o->this.boolean); break;
        case SFS_CHARACTER:
            /*printf("lettre: ");*/
            printf("%c",o->this.character); break;
        case SFS_NUMBER:
            /*printf("nombre: ");*/
            printf("%d",o->this.number.this.integer); break;
        case SFS_SYMBOL:
            /*printf("symbole: ");*/
            printf("%s",o->this.symbol); break;
        case SFS_STRING:
            /*printf("chaine: ");*/
            printf("%s",o->this.string); break;
        /*case SFS_PAIR:
            printf("pair: ");
            printf("car: %p\ncdr: %p\n",o->this.pair.car,o->this.pair.cdr); break;*/
        case SFS_NIL:
        	printf(")"); break;
            
    }
    return;
}

void sfs_print_pair( object o ) {
    sfs_print(o->this.pair.car);printf(" ");
    sfs_print(o->this.pair.cdr);
    return;
}

void sfs_print( object o ) {
	static int parenthese=0;
	if (!premiere_parenthese && SFS_NIL==o->type) printf("(");
    if ( SFS_PAIR == o->type ) {
    	if (!premiere_parenthese){
    		premiere_parenthese++;
    		printf("( ");
    	} 
    	if (o->this.pair.car->type==SFS_PAIR) {parenthese++; printf("( ");}
        sfs_print_pair( o );
    }
    else {
        sfs_print_atom( o ); 
        if(o->type==SFS_NIL) parenthese--;
        
       
    }
}
