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
<<<<<<< HEAD
object est_pair(object input);
object est_string(object input);
object est_character(object input);
object est_integer(object input);
object est_primitive(object input);
=======
object est_null(object input);
object est_boolean(object input);
object est_symbol(object input);
>>>>>>> 32e1d30bcdbcef315310de9da15b8182a1df2d16

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
