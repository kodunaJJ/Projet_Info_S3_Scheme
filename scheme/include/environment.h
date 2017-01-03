/* Scheme environment definition */

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#define TOP_LEVEL 0x00
  
  
  object create_environment();
  object create_top_level_environment();
  object add_environment(object env);
  object delete_environment(object env);
  object goto_environment_X(int num); /* utile ??? */
  void add_variable(object name, object value, object env);
  object add_variable_value(object value, object env);
  object delete_variable(object variable);
  void delete_variable_value(object variable);
  /* recherche variable dans l'environnement courant */
  /*renvoie une paire contenant le nom et la valeur de la variable */
  object research_variable(object variable_name, object env);
  /* recherche variable dans tous les environnements */
  object research_variable_all_env(object variable_name, object env);

  /* fonction pour le deboggage */
  void display_variable(object variable);
  void display_environment(object env, int num_env2display);
  
#ifdef __cplusplus
}
#endif

#endif /* _ENVIRONMENT_H_ */  




