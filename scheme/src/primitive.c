#include "primitive.h"
#include "eval.h"
#include "environnement.h"
#include "basic.h"

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
				object resultat=make_object(SFS_BOOLEAN);
				resultat->this.boolean=TRUE;
				object operande1=make_object(SFS_NUMBER);
				object operande2=make_object(SFS_NUMBER);
				
				
				if(input->this.pair.cdr->type!=SFS_NIL){
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					else if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							operande1->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
					else if(input->this.pair.car->type==SFS_NUMBER){
						operande1->this.number.this.integer=input->this.pair.car->this.number.this.integer;
					}
					else ERROR_MSG("Pas de nombre à comparer");
				}
				
				while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){

					if(input->this.pair.cdr->type!=SFS_NIL){
						input=input->this.pair.cdr;
						if(input->this.pair.car->type==SFS_PAIR){
							input->this.pair.car=sfs_eval(input->this.pair.car);
						}
						else if(input->this.pair.car->type==SFS_SYMBOL){
							p=recherche(toplevel,input->this.pair.car->this.symbol);
							if(p->this.pair.cdr->type==SFS_NUMBER){
								operande2->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
							}
							else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						}
						else if(input->this.pair.car->type==SFS_NUMBER){
							operande2->this.number.this.integer=input->this.pair.car->this.number.this.integer;
						}
						else ERROR_MSG("Pas de nombre à comparer");
					}
					resultat->this.boolean= (operande1->this.number.this.integer < operande2->this.number.this.integer) ? TRUE:FALSE;
					operande1->this.number.this.integer = operande2->this.number.this.integer;
				}
				return resultat;
}

object sup(object input)

{
				object p=creer_env();
				object resultat=make_object(SFS_BOOLEAN);
				resultat->this.boolean=TRUE;
				object operande1=make_object(SFS_NUMBER);
				object operande2=make_object(SFS_NUMBER);
				
				
				if(input->this.pair.cdr->type!=SFS_NIL){
					input=input->this.pair.cdr;
					if(input->this.pair.car->type==SFS_PAIR){
						input->this.pair.car=sfs_eval(input->this.pair.car);
					}
					else if(input->this.pair.car->type==SFS_SYMBOL){
						p=recherche(toplevel,input->this.pair.car->this.symbol);
						if(p->this.pair.cdr->type==SFS_NUMBER){
							operande1->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
						}
						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
					}
					else if(input->this.pair.car->type==SFS_NUMBER){
						operande1->this.number.this.integer=input->this.pair.car->this.number.this.integer;
					}
					else ERROR_MSG("Pas de nombre à comparer");
				}
				
				while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){

					if(input->this.pair.cdr->type!=SFS_NIL){
						input=input->this.pair.cdr;
						if(input->this.pair.car->type==SFS_PAIR){
							input->this.pair.car=sfs_eval(input->this.pair.car);
						}
						else if(input->this.pair.car->type==SFS_SYMBOL){
							p=recherche(toplevel,input->this.pair.car->this.symbol);
							if(p->this.pair.cdr->type==SFS_NUMBER){
								operande2->this.number.this.integer=p->this.pair.cdr->this.number.this.integer;
							}
							else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
						}
						else if(input->this.pair.car->type==SFS_NUMBER){
							operande2->this.number.this.integer=input->this.pair.car->this.number.this.integer;
						}
						else ERROR_MSG("Pas de nombre à comparer");
					}
					resultat->this.boolean= (operande1->this.number.this.integer > operande2->this.number.this.integer) ? TRUE:FALSE;
					operande1->this.number.this.integer = operande2->this.number.this.integer;
				}
				return resultat;
}

object est_null(object input){
	object resultat=make_object(SFS_BOOLEAN);
	if(input->this.pair.cdr->type!=SFS_NIL){
		resultat->this.boolean= (input->cadr->type==SFS_NIL) ? TRUE:FALSE;
	}
	return resultat;
}

object est_boolean(object input){
	object resultat=make_object(SFS_BOOLEAN);
	if(input->this.pair.cdr->type!=SFS_NIL){
		resultat->this.boolean= (input->cadr->type==SFS_BOOLEAN) ? TRUE:FALSE;
	}
	return resultat;
}

object est_symbol(object input){
	object resultat=make_object(SFS_BOOLEAN);
	if(input->this.pair.cdr->type!=SFS_NIL){
		resultat->this.boolean= (input->cadr->type==SFS_SYMBOL) ? TRUE:FALSE;
	}
	return resultat;
}

object est_pair(object input)
{
	object resultat=make_object(SFS_BOOLEAN);
	resultat->this.boolean=TRUE;

	if (input->cadr->type==SFS_PAIR)
	{
		resultat->this.boolean=TRUE;
		return resultat;
	}

	else
	{
		resultat->this.boolean=FALSE;
		return resultat;
	}

}

object est_string(object input)
{
	object resultat=make_object(SFS_BOOLEAN);
	resultat->this.boolean=TRUE;

	if (input->cadr->type==SFS_STRING)
	{
		resultat->this.boolean=TRUE;
		return resultat;
	}

	else
	{
		resultat->this.boolean=FALSE;
		return resultat;
	}

}

object est_character(object input)
{
	object resultat=make_object(SFS_BOOLEAN);
	resultat->this.boolean=TRUE;

	if (input->cadr->type==SFS_CHARACTER)
	{
		resultat->this.boolean=TRUE;
		return resultat;
	}

	else
	{
		resultat->this.boolean=FALSE;
		return resultat;
	}

}

object est_integer(object input)
{
	object resultat=make_object(SFS_BOOLEAN);
	resultat->this.boolean=TRUE;

	if (input->cadr->type==SFS_NUMBER)
	{
		resultat->this.boolean=TRUE;
		return resultat;
	}

	else
	{
		resultat->this.boolean=FALSE;
		return resultat;
	}

}

object est_primitive(object input)
{
	object p=creer_env();
	object resultat=make_object(SFS_BOOLEAN);
	resultat->this.boolean=TRUE;
	
	p=recherche(toplevel,input->cadr->this.symbol);

		if (p->this.pair.cdr->type==SFS_PRIMITIVE)
		{
			resultat->this.boolean=TRUE;
			return resultat;
		}

		else
		{
			resultat->this.boolean=FALSE;
			return resultat;
		}
	
}

object conv_string_to_symbol(object input)
{	

	object resultat=make_object(SFS_SYMBOL);
	

	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}

	if(input->cadr->type==SFS_STRING)
	{
		strcpy(resultat->this.symbol,input->cadr->this.string);
		return resultat;
	} 

	else ERROR_MSG("Vous essayez de convertir type qui n'est pas une chaine de caractère");
	
}

object conv_symbol_to_string(object input)
{
	object resultat=make_object(SFS_STRING);

	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}

	if(input->cadr->type==SFS_SYMBOL)
	{
		strcpy(resultat->this.string,input->cadr->this.symbol);
		return resultat;
				
	} 

	else ERROR_MSG("Vous essayez de convertir type qui n'est pas un symbol");

	
}

object conv_string_to_number(object input)
{
	object resultat=make_object(SFS_NUMBER);
	int i=0;

	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}

	if(input->cadr->type==SFS_STRING)
	{
		while(i<strlen(input->cadr->this.string))
		{
			resultat->this.number.this.integer+=((int)(input->cadr->this.string[i]));
			i++;
		}return resultat;

	}
return input;

}

object set_car(object input)
{
	object env_courant=creer_env();
	env_courant=toplevel;

if(input->cadr->type==SFS_PAIR && input->cadr->this.pair.car->type==SFS_SYMBOL)
	{
		object p=creer_env();
		p=recherche_env(env_courant,input->cadr->this.pair.car->this.symbol);
		if(p!=NULL)
		{
			p->this.pair.cdr=sfs_eval(input->caddr);
			return env_courant;

		}

		else WARNING_MSG("Erreur de syntaxe");
	}

	else WARNING_MSG("Erreur de syntaxe");
	return input;
}


object set_cdr(object input)
{
	object env_courant=creer_env();
	env_courant=toplevel;

	if(input->cadr->type==SFS_PAIR && input->cadr->cadr->type==SFS_SYMBOL)
	{
		object p=creer_env();
		p=recherche_env(env_courant,input->cadr->cadr->this.symbol);
		if(p!=NULL)
		{
			p->this.pair.cdr=sfs_eval(input->caddr);
			return env_courant;

		}

		else WARNING_MSG("La variable n'est pas définie");
	}
	else WARNING_MSG("Erreur de syntaxe");

	return input;
}

object new_list(object input)
{
	object new_list=make_object(SFS_PAIR);
	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}
	else
	{
		new_list=input->this.pair.cdr;
		return new_list;
	}return input;
		
}

/* Test si deux object sont identiques*/
object eq_poly(object input)
{
	object resultat=make_object(SFS_BOOLEAN);

	if(input->cadr->type==SFS_PAIR)
	{
		input->cadr=sfs_eval(input->cadr);
	}

	while(input->cddr->type!=SFS_NIL)
	{
		if(input->cadr->type==input->caddr->type)
		{	
			switch(input->cadr->type)
			{
				
				case 0x00 : 
					if(input->cadr->this.number.this.integer==input->caddr->this.number.this.integer) 
					resultat->this.boolean=1;
						
					else 
					{
						resultat->this.boolean=FALSE;
						
						return resultat;
					}break;

				case 0x01 :
					if(input->cadr->this.character==input->caddr->this.character) 
						resultat->this.boolean=TRUE;
					else 
					{
						resultat->this.boolean=FALSE;
						return resultat;
					}break;

				case 0x02 : 
					if(strcpy(input->cadr->this.string,input->caddr->this.string)!=0) 
						resultat->this.boolean=TRUE;
					else 
					{
						resultat->this.boolean=FALSE;
						return resultat;
					}break;

				case 0x03 :

					input->cadr=sfs_eval(input->cadr);

				case 0x05 : 
					if(input->cadr->this.boolean==input->caddr->this.boolean) 
						resultat->this.boolean=TRUE;
					else 
					{
						resultat->this.boolean=FALSE;
						return resultat;
					}break;

				case 0x06 :
					if(strcpy(input->cadr->this.symbol,input->caddr->this.symbol)!=0) 
						resultat->this.boolean=TRUE;
					else 
					{
						resultat->this.boolean=FALSE;
						return resultat;
					}break;
					
			}
			input=input->this.pair.cdr;
			
		}
	
	}return resultat;

}





