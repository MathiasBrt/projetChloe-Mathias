#include "environnement.h"
#include "print.h"
#include "primitive.h"

object creer_env(void){
	object env=make_object(SFS_ENVIRONNEMENT);
	env->env_suiv=NULL;
	env->var_suiv=NULL;
	return env;
}

BOOL est_vide_env(object env){
	return !env;
}

void affiche_env(object env){
	object p=creer_env();
	p=env->var_suiv;
	while(!est_vide_var(p)){
		affiche_var(p);
		p=p->var_suiv;
	}
}

/* Associe une variable à sa valeur (si elle existe). Le résultat est un nouvel objet indépendant pour éviter les risques de modifications involontaires */
object association(object env, object variable){
	object p=creer_env();
	p=recherche(env, variable->this.symbol);
	if (p==NULL) return variable;
	object resultat=make_object(p->this.pair.cdr->type);
	switch(p->this.pair.cdr->type){
		case 0x00: resultat->this.number=p->this.pair.cdr->this.number; break;
		case 0x01: resultat->this.character=p->this.pair.cdr->this.character; break;
		case 0x02: strcpy(resultat->this.string,p->this.pair.cdr->this.string); break;
		case 0x03: resultat=p->this.pair.cdr; break;
		case 0x05: resultat->this.boolean=p->this.pair.cdr->this.boolean; break;
		case 0x06: strcpy(resultat->this.symbol,p->this.pair.cdr->this.symbol); break;
		case 0x08: resultat->this.primitive=p->this.pair.cdr->this.primitive; break;
		case 0x04: resultat=NULL;
	}
	return resultat;
}


/* Ajoute un nouvel environnement en queue de la liste des environnements existants */
object ajout_queue_env(object env){
	object nv_env=creer_env();
	object p=creer_env();
	p=env;
	while(!est_vide_env(p->env_suiv)) p=p->env_suiv;
	p->env_suiv=nv_env;
	return env;
}

object recherche_etiquette(object env, string etiquette){
	object p=env;
	while(!est_vide_env(p)){
		if(!strcmp(p->this.pair.car->this.symbol,etiquette)) return p;
		p=p->env_suiv;
	}
	ERROR_MSG("Etiquette %s non existante",etiquette);
}

BOOL est_vide_var(object variable){
	return !variable;
}


/* Recherche si une variable existe dans un environnement donné et renvoie le maillon correspondant, ie un objet SFS_ENVIRONNEMENT dont le car est la variable et le cdr est la valeur. Dans le cas contraire, NULL est retourné */
object recherche_env(object env, string variable){
	object p=creer_env();
	p=env->var_suiv;
	while(!est_vide_env(p)){
		if(!strcmp(variable,p->this.pair.car->this.symbol)) return p;
		p=p->var_suiv;
	}
	return p;
}


/* Itération de la fonction précédente sur tous les environnements. La valeur de retour est identique. */
object recherche(object env, string variable){
	object p=env;
	object result;
	while(!est_vide_env(p)){
		result=recherche_env(p,variable);
		if(result!=NULL) return result;
		p=p->env_suiv;
	}
	return p;
}


/* Fonction d'ajout d'une variable à un environnement. Elle est ajoutée à la fin de celui-ci. */
object ajout_queue_var(object env, object variable, object valeur){
	object nv_var=creer_env();
	nv_var->this.pair.car=make_object(SFS_SYMBOL);
	strcpy(nv_var->this.pair.car->this.symbol,variable->this.symbol);
	nv_var->this.pair.cdr=make_object(valeur->type);
	switch(nv_var->this.pair.cdr->type){
		case 0x00: nv_var->this.pair.cdr->this.number=valeur->this.number; break;
		case 0x01: nv_var->this.pair.cdr->this.character=valeur->this.character; break;
		case 0x02: strcpy(nv_var->this.pair.cdr->this.string,valeur->this.string); break;
		case 0x03: nv_var->this.pair.cdr=valeur; break;
		case 0x05: nv_var->this.pair.cdr->this.boolean=valeur->this.boolean; break;
		case 0x06: strcpy(nv_var->this.pair.cdr->this.symbol,valeur->this.symbol); break;
		case 0x08: nv_var->this.pair.cdr->this.primitive=valeur->this.primitive; break;
		case 0x04: nv_var->this.pair.cdr=NULL;
	}
	object p=creer_env();
	p=env;
	while(!est_vide_env(p->var_suiv)) p=p->var_suiv;
	p->var_suiv=nv_var;
	return env;
}


/* Fonction d'affichage d'une variable */
void affiche_var(object variable){
	sfs_print(variable->this.pair.car);
	printf(" a la valeur ");
	sfs_print(variable->this.pair.cdr);
	printf("\n");
}


/* Fonction d'initialisation du toplevel. Y stocke les formes courantes comme des entiers (arbitraire) et les primitives comme des pointeurs de fonction. Pour implémenter une nouvelle primitive, il faut l'ajouter ici. */
object init_top_level(void){
	object env=creer_env();
	object forme=make_object(SFS_PRIMITIVE);
	object valeur=make_object(SFS_PRIMITIVE);
	object variable=make_object(SFS_SYMBOL);
	object donnee=make_object(SFS_NUMBER);
	donnee->this.number.this.integer=1;

	/* Implantation Formes de base*/
	strcpy(variable->this.symbol,"if");
	env=ajout_queue_var(env,variable,donnee);
	
	strcpy(variable->this.symbol,"and"); donnee->this.number.this.integer=2;
	env=ajout_queue_var(env,variable,donnee);
	
	strcpy(variable->this.symbol,"or"); donnee->this.number.this.integer=3;
	env=ajout_queue_var(env,variable,donnee);
	
	strcpy(variable->this.symbol,"quote"); donnee->this.number.this.integer=4;
	env=ajout_queue_var(env,variable,donnee);
	
	strcpy(variable->this.symbol,"define"); donnee->this.number.this.integer=5;
	env=ajout_queue_var(env,variable,donnee);
	
	strcpy(variable->this.symbol,"set!"); donnee->this.number.this.integer=6;
	env=ajout_queue_var(env,variable,donnee);
	/* Implantation Primitives */
	strcpy(forme->this.symbol,"+"); valeur->this.primitive=add;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"-"); valeur->this.primitive=sous;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"*"); valeur->this.primitive=mult;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"/"); valeur->this.primitive=divi;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"="); valeur->this.primitive=egal;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"<"); valeur->this.primitive=inf;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,">"); valeur->this.primitive=sup;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"null?"); valeur->this.primitive=est_null;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"boolean?"); valeur->this.primitive=est_boolean;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"symbol?"); valeur->this.primitive=est_symbol;
	env=ajout_queue_var(env,forme,valeur);

	strcpy(forme->this.symbol,"pair?"); valeur->this.primitive=est_pair;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"string?"); valeur->this.primitive=est_string;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"character?"); valeur->this.primitive=est_character;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"integer?"); valeur->this.primitive=est_integer;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"primitive?"); valeur->this.primitive=est_primitive;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"chartointeger"); valeur->this.primitive=conv_char_to_integer;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"integertochar"); valeur->this.primitive=conv_integer_to_char;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"numbertostring"); valeur->this.primitive=conv_number_to_string;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"stringtosymbol"); valeur->this.primitive=conv_string_to_symbol;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"symboltostring"); valeur->this.primitive=conv_symbol_to_string;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"stringtonumber"); valeur->this.primitive=conv_string_to_number;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"car"); valeur->this.primitive=car;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"cdr"); valeur->this.primitive=cdr;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"set-car!"); valeur->this.primitive=set_car;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"set-cdr!"); valeur->this.primitive=set_cdr;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"list!"); valeur->this.primitive=new_list;
	env=ajout_queue_var(env,forme,valeur);
	
	strcpy(forme->this.symbol,"eq?"); valeur->this.primitive=eq_poly;
	env=ajout_queue_var(env,forme,valeur);
	
	return env;
}
