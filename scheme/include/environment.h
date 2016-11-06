/* Scheme environment definition */

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

  /* creation d'une structure specifique pour les environements ??? */
  
  object create_environment();
  object create_top_level_environment();
  object add_environment(object env, int num);
  object delete_environment(object env);
  object goto_environment_X(int num); /* utile ??? */
  void add_variable(object name, object value, object env);
  object delete_variable(object variable);
  object research_variable(object variable, object env);
  
#ifdef __cplusplus
}
#endif

#endif /* _ENVIRONMENT_H_ */  




