#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include "object.h"

object add(object input);
object mult(object input);
object divi(object input);
object sous(object input);
object egal(object input);
object inf(object input);
object sup(object input);
object est_null(object input);
object est_boolean(object input);
object est_symbol(object input);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
