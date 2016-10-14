
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "object.h"
#include "environnement.h"

object toplevel;

object sfs_eval( object input ) {
	
	object env_courant=creer_env();
	env_courant=toplevel;

	eval:
	
	if(input->type==SFS_PAIR){
		if(input->this.pair.car->type==SFS_SYMBOL){
			if(!strcmp(input->this.pair.car->this.symbol,"IF") || !strcmp(input->this.pair.car->this.symbol,"AND") || !strcmp(input->this.pair.car->this.symbol,"DEFINE") || !strcmp(input->this.pair.car->this.symbol,"OR") || !strcmp(input->this.pair.car->this.symbol,"SET!") || !strcmp(input->this.pair.car->this.symbol,"QUOTE"))
			{
				WARNING_MSG("La forme est certainement en majuscule !");
				return input;

			}

			if (strncmp(input->this.pair.car->this.symbol,"quote",5)==0){
				while (input->this.pair.cdr->type != SFS_NIL)
				{
					
					input = input->cadr;
					
					return input;
				}
			}
			if(strncmp(input->this.pair.car->this.symbol,"and",3)==0)
			{
				
				object et_logique=make_object(SFS_BOOLEAN);
				
				if(predicat(input->cadr)  == 0) 
				{
					
					et_logique->this.boolean= 0;
					return et_logique;
				}
				if(predicat(input->caddr)  == 1)
				{
					
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
					
					et_logique->this.boolean= 1;
					return et_logique;
				}
				if(predicat(input->caddr)  == 0)
				{
					
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

			if(!strcmp(input->this.pair.car->this.symbol,"define"))
			{
				object p=creer_env();
				p=recherche_env(env_courant,input->cadr->this.symbol);
				if(p==NULL)
				{
					ajout_queue_var(env_courant,input->cadr,input->caddr);
					return env_courant;

				}
				else WARNING_MSG("Pour changer la valeur de la variable, utilisez set!");

			}

			if(!strcmp(input->this.pair.car->this.symbol,"set!"))
			{
				object p=creer_env();
				p=recherche_env(env_courant,input->cadr->this.symbol);
				if(p==NULL) WARNING_MSG("La variable n'est pas définie");
				else 
				{
					p->this.pair.cdr=input->caddr;
					return env_courant;
				}
				return env_courant;

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

