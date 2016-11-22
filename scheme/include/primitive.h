#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include "object.h"

object add(object input, object env_courant);
object mult(object input, object env_courant);
object divi(object input, object env_courant);
object sous(object input, object env_courant);
object egal(object input, object env_courant);
object inf(object input, object env_courant);
object sup(object input, object env_courant);
object est_null(object input, object env_courant);
object est_boolean(object input, object env_courant);
object est_symbol(object input, object env_courant);
object est_pair(object input, object env_courant);
object est_string(object input, object env_courant);
object est_character(object input, object env_courant);
object est_integer(object input, object env_courant);
object est_primitive(object input, object env_courant);
object conv_char_to_integer(object input, object env_courant);
object conv_integer_to_char(object input, object env_courant);
object conv_number_to_string(object input, object env_courant);
object conv_string_to_symbol(object input, object env_courant);
object conv_symbol_to_string(object input, object env_courant);
object conv_string_to_number(object input, object env_courant);
object car(object input, object env_courant);
object cdr(object input, object env_courant);
object set_car(object input, object env_courant);
object set_cdr(object input, object env_courant);
object new_list(object input, object env_courant);
object eq_poly(object input, object env_courant);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
