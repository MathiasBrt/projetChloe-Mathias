
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

object sfs_eval( object input ) {
	eval:
	if(input->type==SFS_PAIR){
		if(input->this.pair.car->type==SFS_SYMBOL){
			if (strncmp(input->this.pair.car->this.symbol,"quote",5)==0){
				input = input->cadr;
				goto eval;
			}
			if(strncmp(input->this.pair.car->this.symbol,"and",3)==0)
			{
				
				object et_logique=make_object(SFS_BOOLEAN);
				
				if(predicat(input->cadr)  == 0) 
				{
					printf("Faux\n");
					et_logique->this.boolean= 0;
					return et_logique;
				}
				if(predicat(input->caddr)  == 1)
				{
					printf( "Vrai\n");
					et_logique->this.boolean = 1;
					return et_logique;
				}

				else 
				{
					et_logique->this.boolean = 0;
					return et_logique;
				}	
			}

			if(strncmp(input->this.pair.car->this.symbol,"or",2)==0)
			{
				
				object et_logique=make_object(SFS_BOOLEAN);
				
				if(predicat(input->cadr) == 1) 
				{
					printf("Vrai\n");
					et_logique->this.boolean= 1;
					return et_logique;
				}
				if(predicat(input->caddr)  == 0)
				{
					printf( "Faux\n");
					et_logique->this.boolean = 0;
					return et_logique;
				}

				else 
				{
					et_logique->this.boolean = 1;
					return et_logique;
				}	


			}	

			if(!strcmp(input->this.pair.car->this.symbol,"if")){ /* lecture d'un if */
				if (input->this.pair.cdr->type==SFS_NIL){
					WARNING_MSG("Pas de prédicat");
					return input;
				}
				if (input->cddr->type==SFS_NIL){
					WARNING_MSG("Pas de conséquence");
					return input;
				}
				if (predicat(input->cadr)){
					input = input->caddr;
					goto eval;
				}
				else if (!predicat(input->cadr)){
					if(input->cdddr->type==SFS_NIL){
						WARNING_MSG("Pas d'alternative");
						return input;
					}
					input = input->cadddr;
					goto eval;
				}
			}
		}
		return input;
	}
    return input;
}

BOOL predicat(object input){
	input=sfs_eval(input);
	if (input->type==SFS_BOOLEAN && input->this.boolean==0) return 0;
	else return 1;
}

