
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"

typedef enum bool{ /* une définition pour la gestion des booléens */
    t=1,
    f=0
} BOOL;

typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           string;
        string           symbol;
        BOOL             boolean;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;
        struct object_t *special;
    } this;
    struct object_t *env_suiv;
    struct object_t *var_suiv;

} *object;


object make_object( uint type );
object make_nil( void );

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_ENVIRONNEMENT 0x07

#define cadr this.pair.cdr->this.pair.car
#define caar this.pair.car->this.pair.car
#define cdar this.pair.car->this.pair.cdr
#define cddr this.pair.cdr->this.pair.cdr
#define caddr cddr->this.pair.car
#define cdddr cddr->this.pair.cdr
#define cadddr cdddr->this.pair.car
#define cddddr cdddr->this.pair.cdr


extern object nil;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
