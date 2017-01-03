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
object sous(object input, object env);
object egal(object input, object env);

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
