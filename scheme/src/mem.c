
/**
 * @file mem.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:06:23 2012
 * @brief Memory wrappers for malloc/free.
 *
 * Memory wrappers for malloc/free.
 */

#include "mem.h"


void *sfs_malloc( size_t size ) {

    return malloc( size );
}

void  sfs_free( void *ptr ) {

    free( ptr );
}

