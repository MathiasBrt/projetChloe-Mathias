
/**
 * @file basic.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Sat Jun 23 01:09:22 2012
 * @brief Basic types.
 *
 * Basic types.
 */

#ifndef _BASIC_H_
#define _BASIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "notify.h"


#define STRLEN       256
#define BIGSTRING 65536


#define TRUE    1
#define FALSE   0

typedef unsigned int uint;

typedef char string[STRLEN];

#define init_string( s ) memset( s, '\0', STRLEN )

#ifdef __cplusplus
}
#endif

#endif /* _BASIC_H_ */
