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

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
