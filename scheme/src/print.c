
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"
int premiere_parenthese=0; /* Utilisation d'une variable globale pour la gestion de la première parenthese */
#include <stdio.h>
object toplevel;
#include "environnement.h"

/*
 * Cette fonction est appelée par sfs_print.
 * Elle vérifie le type de l'objet en paramètre et met en forme l'expression à afficher (avec la syntaxe de SCHEME).
 */

void sfs_print_atom( object o ) {
    switch (o->type){
        case SFS_BOOLEAN:
            /*printf("booleen:  ");*/
            (o->this.boolean) ? printf("#t"):printf("#f"); break;
        case SFS_CHARACTER:
            /*printf("lettre: ");*/ 
            if(o->this.character==32) printf("#\\space");
            else if(o->this.character==10) printf("#\\newline");
            else printf("#\\%c",o->this.character); break;
        case SFS_NUMBER:
            /*printf("nombre: ");*/
            if (o->this.number.numtype==NUM_MINFTY) printf("-inf");
            else if (o->this.number.numtype==NUM_PINFTY) printf("+inf");
            else printf("%d",o->this.number.this.integer); break;
        case SFS_SYMBOL:
            /*printf("symbole: ");*/
            printf("%s",o->this.symbol); break;
        case SFS_STRING:
            /*printf("chaine: ");*/
            printf("\"%s\"",o->this.string); break;
        case SFS_NIL:
        	printf(")"); break;

        case SFS_ENVIRONNEMENT :
            affiche_env(o);

        case SFS_PRIMITIVE:
             break;
            
    }
    return;
}


/*
 * Cette fonction est appelée par sfs_print.
 * Elle rappelle sfs_print pour le car de l'objet et pour le cdr.
 * Pour gérer la mise en forme de la sortie, un espace est affiché après chaque car. Si l'on est en bout de paire 
 * (cdr de type SFS_NIL), on se prépare à écrire par-dessus cet espace.
 */

void sfs_print_pair( object o ) {
    sfs_print(o->this.pair.car);
    if (o->this.pair.cdr->type!=SFS_NIL)
    printf(" ");
    sfs_print(o->this.pair.cdr);
    return;
}


/*
 * Cette fonction et sfs_print_pair s'appellent mutuellement.
 * Elle gère l'affichage des parenthèses ouvrantes.
 */

void sfs_print( object o ) {

	if (!premiere_parenthese && SFS_NIL==o->type) printf("(");
  
    if ( SFS_PAIR == o->type ) {
    	if (!premiere_parenthese){
    		premiere_parenthese++;
    		printf("(");
    	} 
        
    	if (o->this.pair.car->type==SFS_PAIR || o->this.pair.car->type==SFS_NIL) printf("(");
        sfs_print_pair( o );

    }

    else {
        sfs_print_atom( o ); 
    }
}
