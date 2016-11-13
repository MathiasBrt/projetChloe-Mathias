#ifndef _ENVIRONNEMENT_H_
#define _ENVIRONNEMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include "object.h"

/* fonctions sur les environnements */
object creer_env(void);
BOOL est_vide_env(object env);
void affiche_env(object env);
object ajout_queue_env(object env);
object recherche_etiquette(object env, string etiquette);

/* fonctions sur les variables */
BOOL est_vide_var(object env);
object recherche_env(object env, string variable);
object recherche(object env, string variable);
object ajout_queue_var(object env, object variable, object valeur);
object association(object env, object variable);
void affiche_var(object variable);
object parcours_env( object env);

/* fonction d'initialisation de l'environnement top level */
object init_top_level(void);


#ifdef __cplusplus
}
#endif

#endif /* _ENVIRONEMENT_H_ */
