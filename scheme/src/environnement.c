#include "environnement.h"
#include "print.h"

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
	p=env;
	while(!est_vide_var(p->var_suiv)){
		affiche_var(p);
		p=p->var_suiv;
	}
}

object ajout_tete_env(object env){
	object nv_env=make_object(SFS_ENVIRONNEMENT);
	nv_env->env_suiv=env;
	nv_env->var_suiv=NULL;
	return nv_env;
}

BOOL est_vide_var(object variable){
	return !variable;
}

object recherche(object env, string variable){
	object p=creer_env();
	p=env;
	while(!est_vide_env(p)){
		if(!strcmp(variable,p->this.pair.car->this.symbol)) return p;
		p=p->var_suiv;
	}
	return p;
}

object ajout_tete_var(object env, object variable, object valeur){
	object nv_var=make_object(SFS_ENVIRONNEMENT);
	nv_var->this.pair.car=make_object(SFS_SYMBOL);
	strcpy(nv_var->this.pair.car->this.symbol,variable->this.symbol);
	nv_var->this.pair.cdr=make_object(valeur->type);
	switch(nv_var->this.pair.cdr->type){
		case 0x00: nv_var->this.pair.cdr->this.number=valeur->this.number; break;
		case 0x01: nv_var->this.pair.cdr->this.character=valeur->this.character; break;
		case 0x02: strcpy(nv_var->this.pair.cdr->this.string,valeur->this.string); break;
		case 0x05: nv_var->this.pair.cdr->this.boolean=valeur->this.boolean; break;
		case 0x06: strcpy(nv_var->this.pair.cdr->this.symbol,valeur->this.symbol); break;
	}
	nv_var->var_suiv=env;
	nv_var->env_suiv=env->env_suiv;
	return nv_var;
}

void affiche_var(object variable){
	sfs_print_atom(variable->this.pair.car);
	printf(" a la valeur ");
	sfs_print_atom(variable->this.pair.cdr);
	printf("\n");
}

object init_top_level(void){
	object env=creer_env();
	object forme=make_object(SFS_SYMBOL);
	object valeur=make_object(SFS_NUMBER);
	valeur->this.number.this.integer=1;
	strcpy(forme->this.symbol,"if");
	env=ajout_tete_var(env,forme,valeur);
	strcpy(forme->this.symbol,"and"); valeur->this.number.this.integer=2;
	env=ajout_tete_var(env,forme,valeur);
	strcpy(forme->this.symbol,"or"); valeur->this.number.this.integer=3;
	env=ajout_tete_var(env,forme,valeur);
	strcpy(forme->this.symbol,"quote"); valeur->this.number.this.integer=4;
	env=ajout_tete_var(env,forme,valeur);
	strcpy(forme->this.symbol,"define"); valeur->this.number.this.integer=5;
	env=ajout_tete_var(env,forme,valeur);
	strcpy(forme->this.symbol,"set!"); valeur->this.number.this.integer=6;
	env=ajout_tete_var(env,forme,valeur);
	return env;
}
