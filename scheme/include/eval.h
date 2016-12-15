
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"

<<<<<<< HEAD
object sfs_eval(object input, object env_courant );
object sfs_eval_predicat(object input, object env_courant);
=======
  object sfs_eval( object input, object environment);
  object sfs_eval_predicat(object input,object environement);
>>>>>>> c94c4d7f96dd2f8eb55f7248ce01043260ca2e6d
#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
