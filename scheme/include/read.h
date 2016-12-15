
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "object.h"
#include "number.h"

  enum {S_OK, S_KO, S_END};

  uint sfs_get_sexpr( string input, FILE *fp );
  void get_atom(char* input, uint *here, char *str);
  void skip_blanks(char* input, uint * here);
  object sfs_read( char *input, uint *here );
  object sfs_read_atom( char *input, uint *here );
  object sfs_read_pair( char *stream, uint *i );
  uint is_arithemetic_op(char c);
  uint is_scm_space(char* str,uint indice);
  uint is_scm_newline(char* str, uint indice);

#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
