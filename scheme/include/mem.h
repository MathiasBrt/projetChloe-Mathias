
/**
 * @file mem.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:04:52 2012
 * @brief Memory wrappers for malloc/free.
 *
 * Memory wrappers for malloc/free.
 */

#ifndef _MEM_H_
#define _MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

void *sfs_malloc( size_t size );
void  sfs_free( void *ptr );


#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
