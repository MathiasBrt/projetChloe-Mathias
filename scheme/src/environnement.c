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

object recherche_env(object env, string variable){
	object p=creer_env();
	p=env->var_suiv;
	while(!est_vide_env(p)){
		if(!strcmp(variable,p->this.pair.car->this.symbol)) return p;
		p=p->var_suiv;
	}
	return p;
}

object recherche(object env, string variable){
	object p=env;
	object result;
	while(!est_vide_env(p)){
		result=recherche_env(p,variable);
		if(result!=NULL) return result;
		p=p->env_suiv;
	}
	ERROR_MSG("Unbound variable '%s'",variable);
}

object ajout_queue_var(object env, object variable, object valeur){
	object nv_var=creer_env();
	nv_var->this.pair.car=make_object(SFS_SYMBOL);
	strcpy(nv_var->this.pair.car->this.symbol,variable->this.symbol);
	nv_var->this.pair.cdr=make_object(valeur->type);
	switch(nv_var->this.pair.cdr->type){
		case 0x00: nv_var->this.pair.cdr->this.number=valeur->this.number; break;
		case 0x01: nv_var->this.pair.cdr->this.character=valeur->this.character; break;
		case 0x02: strcpy(nv_var->this.pair.cdr->this.string,valeur->this.string); break;
		case 0x05: nv_var->this.pair.cdr->this.boolean=valeur->this.boolean; break;
		case 0x06: strcpy(nv_var->this.pair.cdr->this.symbol,valeur->this.symbol); break;
		case 0x08: nv_var->this.pair.cdr->this.primitive=valeur->this.primitive; break;
	}
	object p=creer_env();
	p=env;
	while(!est_vide_env(p->var_suiv)) p=p->var_suiv;
	p->var_suiv=nv_var;
	return env;
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
	object valeur=make_object(SFS_PRIMITIVE);
	/*valeur->this.number.this.integer=1;
	strcpy(forme->this.symbol,"if");
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"and"); valeur->this.number.this.integer=2;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"or"); valeur->this.number.this.integer=3;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"quote"); valeur->this.number.this.integer=4;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"define"); valeur->this.number.this.integer=5;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"set!"); valeur->this.number.this.integer=6;
	env=ajout_queue_var(env,forme,valeur);*/
	strcpy(forme->this.symbol,"+"); valeur->this.primitive=add;
	env=ajout_queue_var(env,forme,valeur);
	/*strcpy(forme->this.symbol,"-"); valeur->this.number.this.integer=8;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"*"); valeur->this.number.this.integer=9;
	env=ajout_queue_var(env,forme,valeur);
	strcpy(forme->this.symbol,"/"); valeur->this.number.this.integer=10;
	env=ajout_queue_var(env,forme,valeur);*/
	return env;
}
