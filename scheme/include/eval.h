
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

  object sfs_eval( object );
  uint form_type(object o);

#define QUOTE_FORM  0x00
#define IF_FORM     0x01
#define SET_FORM    0x02
#define DEFINE_FORM 0x03
#define AND_FORM    0x04
#define NOT_FORM    0xFF
  

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
