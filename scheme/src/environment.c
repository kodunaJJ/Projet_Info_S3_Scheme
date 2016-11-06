#include "environment.h"
#include "mem.h"
#include "notify.h"

object create_environment(int num){

  object env = make_pair();
  env->type = SFS_ENVIRONMENT;
  env->this.number = num;
  env->this.pair.car=nil;
  env->this.pair.cdr=nil;
  return env;
}

object create_top_level_environment(){
  object top = create_environment(0);

  /* modification de make_pair pour initialiser car et cdr à nil ??? */
  
  top->this.pair.car=nil;

  /* ajout de la creation des formes ??? */

  return top;
}

object add_environment(object env, int num){
  object new_env = create_environment(num);
  new_env->this.pair.car=env;
  return new_env;
}

object delete_environment(object env){
  if(env->this.number == 0) return env;
  if(env->this.pair.cdr->type == SFS_NIL){
    object env1 = env->this.pair.car; 
    sfs_free(env);
    return env1;
  }
  else{
    object variable = env->this.pair.cdr;
    do{
      /* utile de faire fonction de suppression d'une paire ??? */
      variable = delete_variable(variable);      
    }while(variable->this.pair.cdr->type != SFS_NIL);
    object env1 = env->this.pair.car;
    sfs_free(env);
    return env1;
  }
}

/*object goto_environment_X(int num){

  }*/

void add_variable(object name, object value, object env){
  object variable = make_pair();
  variable->this.pair.car = make_pair();
  variable->caar = name;
  variable->cdar = value;
  variable->this.pair.cdr = env->this.pair.cdr;
  env->this.pair.cdr=variable;
}

object delete_variable(object variable){
  if(variable->type == SFS_NIL) return nil;
  object variable1 = nil;
  sfs_free(variable->caar);
  sfs_free(variable->cdar);
  sfs_free(variable->this.pair.car);
  variable1 = variable->this.pair.cdr;
  sfs_free(variable);
  return variable1;
}

object research_variable(object variable, object env){
  object var = variable;
  object env1 = env;
  do{
    if(env1->this.pair.cdr->type == SFS_NIL){
      env1 = env1->this.pair.car;
    }
    else if(var->this.pair.car->type == SFS_NIL){
      env1 = env1->this.pair.car;
    }

    if(strcmp(var->caar->this.string, variable->caar->this.string) == 0 && var->cdar->type == variable->cdar->type){
      return var;
    }
    else{
      var = var->this.pair.cdr;
    }

  }while(env1->this.number != 0 && var->this.pair.cdr->type != SFS_NIL);

  WARNING_MSG("Unbound variable");
  return nil;
}
  
  
  
  



