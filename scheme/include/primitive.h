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
object est_pair(object input);
object est_string(object input);
object est_character(object input);
object est_integer(object input);
object est_primitive(object input);
object conv_string_to_symbol(object input);
object conv_symbol_to_string(object input);
object conv_string_to_number(object input);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
