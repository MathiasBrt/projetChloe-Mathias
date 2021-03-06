
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

	
	
	object p=creer_env();
	object env_courant=creer_env();
	env_courant=toplevel;

	eval:
	
	 /*Renvoie la valeur de la variable, si elle existe*/
	if(input->type==SFS_SYMBOL){
		p=recherche_env(env_courant,input->this.symbol);
		if (p==NULL) return input;
		return p->this.pair.cdr;
	}
	/*Dans le cas s'une paire*/
	if(input->type==SFS_PAIR){

			/*Test si le car est un symbol*/
			if(input->this.pair.car->type==SFS_SYMBOL)
			{
				/*Recherche dans l'environnement courant*/
				p=recherche_env(env_courant,input->this.pair.car->this.symbol);
				if(p==NULL) return input; /*Renvoie l'entrée si le symbol n'existe pas*/

				/* Test si le cdr est une primitive */
				if(p->this.pair.cdr->type==SFS_PRIMITIVE)
				{

					object (*prim)(object); /* Pointeur de fonction */
					prim = p->this.pair.cdr->this.primitive; /* Association de la fonction */
					return prim(input);
				}

				/* Test de la gestion de casse => Forme écrite obligatoirement en minuscule */
				if(!strcmp(input->this.pair.car->this.symbol,"IF") || !strcmp(input->this.pair.car->this.symbol,"AND") || !strcmp(input->this.pair.car->this.symbol,"DEFINE") || !strcmp(input->this.pair.car->this.symbol,"OR") || !strcmp(input->this.pair.car->this.symbol,"SET!") || !strcmp(input->this.pair.car->this.symbol,"QUOTE"))
				{
					WARNING_MSG("La forme est certainement en majuscule !");
					return input;

				}

				/* Forme quote, elle n'évalue paas la l'expression, elle renvoie les arguments  */
				if (strcmp(input->this.pair.car->this.symbol,"quote")==0){
					if (input->this.pair.cdr->type != SFS_NIL)
					{
					
						input = input->cadr;
						return input;

					} 			

				else WARNING_MSG (" Rien à recopier");
			}	
			/* forme and */
			if(strcmp(input->this.pair.car->this.symbol,"and")==0)
			{
				
				object et_logique=make_object(SFS_BOOLEAN);
				
				/* Si premier test faux, on renvoie faux */
				if(predicat(input->cadr)  == 0) 
				{
			
					et_logique->this.boolean= 0;
					return et_logique;
				}

				/* Si deuxième test vrai, on renvoie vrai*/
				if(predicat(input->caddr)  == 1)
				{
					
					et_logique->this.boolean = 1;
					return et_logique;
				}

				/*Sinon, on renvoie faux*/
				else 
				{
					et_logique->this.boolean = 0;
					return et_logique;
				}	
			}
			
			/* forme or */
			if(strcmp(input->this.pair.car->this.symbol,"or")==0)
			{
				
				object et_logique=make_object(SFS_BOOLEAN);
				
				/* Si premier test vrai, on renvoie vrai */
				if(predicat(input->cadr) == 1) 
				{
					
					et_logique->this.boolean= 1;
					return et_logique;
				}

				/* Si deuxème test faux, on renvoie faux*/
				if(predicat(input->caddr)  == 0)
				{
					
					et_logique->this.boolean = 0;
					return et_logique;
				}

				/*Sinon, on renvoie vrai*/
				else 
				{
					et_logique->this.boolean = 1;
					return et_logique;
				}	


			}	

			/* forme if */
			if(!strcmp(input->this.pair.car->this.symbol,"if")){ /* lecture d'un if */
				
				if(input->cadr->type==SFS_PAIR)

				{
					if(sfs_eval(input->cadr->this.pair.car)->this.boolean==1)
					{
						
						input = input->caddr;
						goto eval; 
					}
					if(!predicat(sfs_eval(input->cadr->this.pair.car)))
					{
						
						input = input->cadddr;
						goto eval;

					}

				}

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

			/* forme define */
			if(!strcmp(input->this.pair.car->this.symbol,"define"))
			{
				object p=creer_env();
				p=recherche_env(env_courant,input->cadr->this.symbol);
				

				if(p==NULL)
				{
					if(input->cadr->type==SFS_PAIR && input->cadr->this.pair.cdr->type==SFS_NIL)
					{
					ajout_queue_var(env_courant,input->cadr->this.pair.car,sfs_eval(input->caddr));
					return env_courant;
					}

					if(input->cadr->type==SFS_PAIR && input->cadr->this.pair.cdr->type!=SFS_NIL)
					{
						WARNING_MSG("Trop d'arguments, indéfinissable");
						return input;

					}

					if(input->caddr->type==SFS_NIL)
					{
						WARNING_MSG("La variable ne peut pas prendre la valeur ()");
						return input;

					}
					else
					{
					ajout_queue_var(env_courant,input->cadr,sfs_eval(input->caddr));
					return env_courant;
					}
				}
				else WARNING_MSG("Pour changer la valeur de la variable, utilisez set!");

			}

			/* forme set! */
			if(!strcmp(input->this.pair.car->this.symbol,"set!"))
			{
				object p=creer_env();
				p=recherche_env(env_courant,input->cadr->this.symbol);
				if(p==NULL) WARNING_MSG("La variable n'est pas définie");
				else 
				{
					p->this.pair.cdr=sfs_eval(input->caddr);
					return env_courant;
				}
				return env_courant;

			}
			
		
		return input;
		}
	}
    return input;
}

BOOL predicat(object input){
	input=sfs_eval(input);
	if (input->type==SFS_BOOLEAN && input->this.boolean==0) return 0;
	else return 1;
}

