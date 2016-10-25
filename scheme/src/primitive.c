#include "primitive.h"
#include "eval.h"
#include "environnement.h"

extern object toplevel;

object add(object input)
			{
				object p=creer_env();
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=0;
				while(input->this.pair.cdr->type!=SFS_NIL)
				{
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					if(input->this.pair.car->type==SFS_NUMBER)
					{
						resultat->this.number.this.integer+=input->this.pair.car->this.number.this.integer;
					}
					else if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer+=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
				}
return resultat;
}

object mult(object input)
{				
				object p=creer_env();
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=1;
				while(input->this.pair.cdr->type!=SFS_NIL)
				{
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					if(input->this.pair.car->type==SFS_NUMBER)
					{
						resultat->this.number.this.integer*=input->this.pair.car->this.number.this.integer;
					}
					if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer*=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
				}return resultat;
			

}

object divi(object input)
{
				object p=creer_env();
				
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=1;	
				if(input->this.pair.cdr->type!=SFS_NIL)
				{
					if(input->cadr->type==SFS_PAIR){
						input->cadr=sfs_eval(input->cadr);
					}
					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number.this.integer !=0){
						resultat->this.number.this.integer=input->cadr->this.number.this.integer;
						input=input->this.pair.cdr;
					}
					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number.this.integer ==0)
					{
					ERROR_MSG("Division par 0 impossible");

					}
					if(input->cadr->type==SFS_SYMBOL){
						p=recherche(toplevel,input->cadr->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						input=input->this.pair.cdr;
					}
				}
				while(input->this.pair.cdr->type!=SFS_NIL)
				{
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					if(input->this.pair.car->type==SFS_NUMBER)
					{
						resultat->this.number.this.integer/=input->this.pair.car->this.number.this.integer;
					}
					if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer/=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
				}return resultat;
}

object sous(object input)
			{
				object p=creer_env();
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=0;
				if(input->this.pair.cdr->type!=SFS_NIL)
				{
					if(input->cadr->type==SFS_PAIR){
						input->cadr=sfs_eval(input->cadr);
					}
					if(input->cadr->type==SFS_NUMBER){
						resultat->this.number.this.integer=input->cadr->this.number.this.integer;
						input=input->this.pair.cdr;
					}
					if(input->cadr->type==SFS_SYMBOL){
						p=recherche(toplevel,input->cadr->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						input=input->this.pair.cdr;
					}
				}
				while(input->this.pair.cdr->type!=SFS_NIL)
				{
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					if(input->this.pair.car->type==SFS_NUMBER)
					{
						resultat->this.number.this.integer-=input->this.pair.car->this.number.this.integer;
					}
					if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							resultat->this.number.this.integer-=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
				}return resultat;
			}
object egal(object input)

{
	object p=creer_env();
	object resultat=make_object(SFS_BOOLEAN);

	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}
				
	if(input->cadr->type==SFS_SYMBOL)
	{
		p=recherche(toplevel,input->cadr->this.symbol);
		if(p->this.pair.cdr->type==SFS_NUMBER)
		{
			if(p->this.pair.cdr->this.number.this.integer==input->caddr->this.number.this.integer)
			{
				resultat->this.boolean=1;	
			}
			else 
			{
				resultat->this.boolean=0;
				return resultat;
			}
		}
		else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						
	}

		if(input->cadr->type==SFS_NUMBER)
		{
			if(input->cadr->this.number.this.integer==input->caddr->this.number.this.integer)
			{
				resultat->this.boolean=1;
				
			}
			else 
			{
				resultat->this.boolean=0;
				return resultat;
			}

		}

	while(input->cddr->type!=SFS_NIL)
	{
		input=input->this.pair.cdr;

		if(input->this.pair.car->type==SFS_PAIR)
		{
			input->this.pair.car=sfs_eval(input->this.pair.car);
		}
				
		if(input->this.pair.car->type==SFS_SYMBOL)
		{
			p=recherche(toplevel,input->this.pair.car->this.symbol);
			if(p->this.pair.cdr->type==SFS_NUMBER)
			{
				if(p->this.pair.cdr->this.number.this.integer==input->cadr->this.number.this.integer)
				{
					resultat->this.boolean=1;	
				}
				else 
				{
					resultat->this.boolean=0;
					return resultat;
				}
			}
			else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						
		}

		if(input->this.pair.car->type==SFS_NUMBER)
		{
			if(input->this.pair.car->this.number.this.integer==input->cadr->this.number.this.integer)
			{
				resultat->this.boolean=1;
				
			}
			else 
			{
				resultat->this.boolean=0;
				return resultat;
			}

		}
	}return resultat;
			
}

object inf(object input)

{
				object p=creer_env();
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=0;
}

object sup(object input)

{
				object p=creer_env();
				object resultat=make_object(SFS_NUMBER);
				resultat->this.number.this.integer=0;

}