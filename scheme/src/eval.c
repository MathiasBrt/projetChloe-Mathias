
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
#include "print.h"

object toplevel;

object sfs_eval( object input, object env_courant ) {

	
    object p=creer_env();
	

  eval:
    /*Dans le cas s'une paire*/
    if(input->type==SFS_PAIR){
	if(input->this.pair.car->type==SFS_PAIR)
	    {
		input->this.pair.car=sfs_eval(input->this.pair.car,env_courant);
	    }

	if(input->this.pair.car->type==SFS_COMPOUND)
	    {
		env_courant=ajout_tete_env(env_courant);
		object p=input->this.pair.car->this.compound.parms;
		object q=input->this.pair.cdr;
		object agregat=association(env_courant,input->this.pair.car);

		do
		    {
			env_courant=ajout_queue_var(env_courant,p->this.pair.car,sfs_eval(q->this.pair.car,env_courant));
			p=p->this.pair.cdr;
			q=q->this.pair.cdr;
		    }while(q->this.pair.car->type==SFS_NUMBER || q->this.pair.car->type==SFS_PAIR);

		object resultat = sfs_eval(agregat->this.compound.body,env_courant);
		env_courant=env_courant->env_suiv;
			

		return resultat;
	    }

	/*Test si le car est un symbol*/
	if(input->this.pair.car->type==SFS_SYMBOL)
	    {
		/*Recherche dans l'environnement courant*/
		p=recherche(env_courant,input->this.pair.car->this.symbol);
				
		if(p==NULL) return input; /*Renvoie l'entrée si le symbol n'existe pas*/

		/* Teste si le cdr est une primitive */
		if(p->this.pair.cdr->type==SFS_PRIMITIVE)
		    {
			object (*prim)(object,object); /* Pointeur de fonction */
			prim = p->this.pair.cdr->this.primitive; /* Association de la fonction */
			return prim(input, env_courant);
		    }
		/* Teste si le cdr est un agregat */
		if(p->this.pair.cdr->type==SFS_COMPOUND){
		    input->this.pair.car=association(env_courant,input->this.pair.car);
		    goto eval;
		}

		/* Test de la gestion de casse => Forme écrite obligatoirement en minuscule */
		if(!strcmp(input->this.pair.car->this.symbol,"IF") || !strcmp(input->this.pair.car->this.symbol,"AND") || !strcmp(input->this.pair.car->this.symbol,"DEFINE") || !strcmp(input->this.pair.car->this.symbol,"OR") || !strcmp(input->this.pair.car->this.symbol,"SET!") || !strcmp(input->this.pair.car->this.symbol,"QUOTE"))
		    {
			WARNING_MSG("La forme est certainement en majuscule !");
			return input;

		    }

		/* Forme quote, elle n'évalue pas la l'expression, elle renvoie les arguments  */

		if (strcmp(input->this.pair.car->this.symbol,"quote")==0)
		{


			if (input->this.pair.cdr->type != SFS_NIL)
			{
					
				input = input->cadr;
				return input;

			} 			

			else WARNING_MSG (" Rien à recopier");
		}	

		/* forme begin */
		if(strcmp(input->this.pair.car->this.symbol,"begin")==0)
		{
			object resultat;

			while(input->this.pair.cdr->type!=SFS_NIL)
			{
				input=input->this.pair.cdr;
				resultat=sfs_eval(input->this.pair.car,env_courant);

					
			} return resultat;
	 	}
			
		/* forme let */
		if(strcmp(input->this.pair.car->this.symbol,"let")==0){
			
		    if(input->this.pair.cdr->type==SFS_NIL)
			{
			    WARNING_MSG("Erreur de syntaxe du let");
			    return input;
			}
				
		    input=input->this.pair.cdr;
		    env_courant=ajout_tete_env(env_courant);
		    object cons_var = make_object(SFS_PAIR);
		    cons_var->this.pair.car=make_object(SFS_SYMBOL);
		    cons_var->this.pair.cdr=make_object(SFS_PAIR);
				
				
		    if(input->this.pair.car->type!=SFS_PAIR)
			{
			    WARNING_MSG("Erreur de syntaxe du let");
			    return input;
			}
				
		    object circulation = input->this.pair.car;
		
				
		    while(circulation->type!=SFS_NIL)
				
			{
			    strcpy(cons_var->this.pair.car->this.symbol,"define");
					
			    if(circulation->this.pair.car->this.pair.cdr->this.pair.car->type!=SFS_NUMBER && circulation->this.pair.car->this.pair.cdr->this.pair.car->type!=SFS_SYMBOL)
	
				{
				    WARNING_MSG("Erreur de syntaxe du let!");
				    return input;
				} 

			    if(circulation->this.pair.car->this.pair.cdr->this.pair.car->type==SFS_SYMBOL)
				{
				    printf("%d",circulation->this.pair.car->this.pair.cdr->this.pair.car->type);
				    printf("%s",circulation->this.pair.car->this.pair.cdr->this.pair.car->this.symbol);
						
				    p=recherche(env_courant,circulation->this.pair.car->this.pair.cdr->this.pair.car->this.symbol);
						
				    if (p==NULL) WARNING_MSG("La variable n'est pas définie ! ");

				    else
					{
						
					    circulation->this.pair.car->this.pair.cdr->this.pair.car=p->this.pair.cdr;
					
					}	

				}
					
			    cons_var->this.pair.cdr=circulation->this.pair.car;
			    sfs_eval(cons_var,env_courant);
			    circulation=circulation->this.pair.cdr;
			}


		    WARNING_MSG("Bonjour!");
		    input->this.pair.car->type=SFS_SYMBOL;
		    strcpy(input->this.pair.car->this.symbol,"begin");
		    circulation = sfs_eval(input,env_courant);
		    env_courant=env_courant->env_suiv;
				
		    return circulation; 
		}


		/* Forme lambda */
		if(strcmp(input->this.pair.car->this.symbol,"lambda")==0)
		    {
			object agregat=make_object(SFS_COMPOUND);
			input=input->this.pair.cdr;


			if(input->this.pair.car->type==SFS_PAIR)
			    {
				agregat->this.compound.parms=input->this.pair.car;
			    }

			else 

			    {
				WARNING_MSG("Attention, la syntaxe des paramètres de fonction ne sont pas corrects");

				return nil;
			    }

			if(input->this.pair.cdr->type==SFS_PAIR)

			    {
				agregat->this.compound.body=input->cadr;
			    }

			else
			    {
				WARNING_MSG("Attention, la syntaxe de la fonction n'est pas correct");

				return nil;
			    }

			agregat->this.compound.env=env_courant;

			return agregat;
		    }
		/* forme and */
		if(strcmp(input->this.pair.car->this.symbol,"and")==0)
		    {
				
			object et_logique=make_object(SFS_BOOLEAN);
				
			/* Si premier test faux, on renvoie faux */
			if(predicat(input->cadr,env_courant)  == 0) 
			    {
			
				et_logique->this.boolean= 0;
				return et_logique;
			    }

			/* Si deuxième test vrai, on renvoie vrai*/
			if(predicat(input->caddr,env_courant)  == 1)
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
			if(predicat(input->cadr,env_courant) == 1) 
			    {
					
				et_logique->this.boolean= 1;
				return et_logique;
			    }

			/* Si deuxème test faux, on renvoie faux*/
			if(predicat(input->caddr,env_courant)  == 0)
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
			    if(sfs_eval(input->cadr->this.pair.car,env_courant)->this.boolean==1)
				{
						
				    input = input->caddr;
				    goto eval; 
				}
			    if(!predicat(sfs_eval(input->cadr->this.pair.car,env_courant),env_courant))
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
		    if (predicat(input->cadr,env_courant)){
			input = input->caddr;
			goto eval;
		    }

		    else if (!predicat(input->cadr,env_courant)){
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
			if(input->this.pair.cdr->type!=SFS_NIL){
			    if(input->cadr->type==SFS_SYMBOL){
				p=recherche_env(env_courant,input->cadr->this.symbol);
				if(p==NULL)
				    {
					if(input->caddr->type==SFS_NIL)
					    {
						WARNING_MSG("La variable ne peut pas prendre la valeur ()");
						return input;
					    }
					else
					    {
						env_courant=ajout_queue_var(env_courant,input->cadr,sfs_eval(input->caddr,env_courant));
						return sfs_eval(input->cadr,env_courant);
								
					    }
				    }
				else {
				    WARNING_MSG("Pour changer la valeur de la variable, utilisez set!");
				    return input;
				}
			    }
			    else if(input->cadr->type==SFS_PAIR){
				if(input->caadr->type==SFS_SYMBOL){
				    /* Vérifications syntaxiques */
				    if(input->cdadr->type!=SFS_PAIR){
					WARNING_MSG("Déclaration implicite de fonction sans paramètres");
					return input;
				    }
				    if(input->cddr->type!=SFS_PAIR){
					WARNING_MSG("Déclaration implicite de fonction sans corps");
					return input;
				    }
				    /* On va transformer l'arbre pour faire apparaitre une structure analogue à lambda */
				    p=recherche_env(env_courant,input->caadr->this.symbol);
				    if(p==NULL){
					object cons_lambda = make_object(SFS_PAIR);
					cons_lambda->this.pair.car=make_object(SFS_SYMBOL);
					strcpy(cons_lambda->this.pair.car->this.symbol,"lambda");
					cons_lambda->this.pair.cdr=make_object(SFS_PAIR);
					cons_lambda->cddr=make_object(SFS_PAIR);
					cons_lambda->cadr=input->cdadr;
					cons_lambda->caddr=input->caddr;
					ajout_queue_var(env_courant,input->caadr,sfs_eval(cons_lambda,env_courant));
					input=input->caadr;
					goto eval;
								
				    }
				    else{
					WARNING_MSG("Pour changer la valeur de la variable, utilisez set!");
					return input;
				    }
				}
				else{
				    WARNING_MSG("Argument de define invalide");
				    return input;
				}
			    }
			    else{
				WARNING_MSG("Argument de define invalide");
				return input;
			    }
			}
		    }

		/* forme set! */
		if(!strcmp(input->this.pair.car->this.symbol,"set!"))
		    {
			object p=creer_env();
			p=recherche_env(env_courant,input->cadr->this.symbol); /*idem : une var peut être dans 2 env*/
			if(p==NULL) WARNING_MSG("La variable n'est pas définie");
			else 
			    {
				p->this.pair.cdr=sfs_eval(input->caddr,env_courant);
				return env_courant;
			    }
			return env_courant;

		    }
			
		
		return input;
	    }
    }
    /*Renvoie la valeur de la variable, si elle existe*/
    if(input->type==SFS_SYMBOL){
	p=recherche(env_courant,input->this.symbol);
	if (p==NULL) {
	    WARNING_MSG("Variable non liée");
	    return input;
	}
	return p->this.pair.cdr;
    }
    return input;
}

BOOL predicat(object input, object env_courant){
    input=sfs_eval(input,env_courant);
    if (input->type==SFS_BOOLEAN && input->this.boolean==0) return 0;
    else return 1;
}

