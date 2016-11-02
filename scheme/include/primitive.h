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
object conv_char_to_integer(object input);
object conv_integer_to_char(object input);
object conv_number_to_string(object input);
object conv_string_to_symbol(object input);
object conv_symbol_to_string(object input);
object conv_string_to_number(object input);
object car(object input);
object cdr(object input);
object set_car(object input);
object set_cdr(object input);
object new_list(object input);
object eq_poly(object input);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
