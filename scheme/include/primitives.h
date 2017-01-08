#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"
#include "object.h"

object add(object input, object env);
object mult(object input, object env);
object divi(object input, object env);
object sub(object input, object env);
  object remainder(object input, object env);
object equal(object input, object env);
  object greater(object input, object env);
  object lower(object input, object env);

  object char_to_integer(object input, object env);
  object integer_to_char(object input, object env);
  object number_to_string(object input, object env);
  object string_to_number(object input, object env);
  object symbol_to_string(object input, object env);
  object string_to_symbol(object input, object env);

  object cons(object input, object env);
  object car(object input, object env);
  object cdr(object input, object env);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
