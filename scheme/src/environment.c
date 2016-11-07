#include "environment.h"
#include "mem.h"
#include "notify.h"
#include "print.h"

#define TOP_LEVEL 0x00

object create_environment(int num){

  object env = make_pair();
  env->type = SFS_ENVIRONMENT;
  env->this.number = num;
  env->this.pair.car=nil;
  env->this.pair.cdr=nil;
  return env;
}

object create_top_level_environment(){
  object top = create_environment(TOP_LEVEL);

  /* modification de make_pair pour initialiser car et cdr à nil ??? */
  
  top->this.pair.car=nil;

  /* ajout de la creation des formes ??? */

  return top;
}

object add_environment(object env, int num){
  int num_env = TOP_LEVEL+num;
  object new_env = create_environment(num_env);
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
  variable->caar = make_symbol(name->this.symbol);
  switch(value->type){
  case SFS_NUMBER:
    variable->cdar = make_integer(value->this.number);
    break;
  case SFS_CHARACTER:
    variable->cdar = make_character(value->this.character);
    break;
  case SFS_STRING:
    variable->cdar = make_string(value->this.string);
    break;
  case SFS_NIL:
    variable->cdar = make_nil();
    break;
  case SFS_BOOLEAN:
    variable->cdar = make_boolean(value->this.boolean);
    break;  
  case SFS_SYMBOL:
    variable->cdar = make_symbol(value->this.symbol);
    break;
    /*case SFS_ARITH_OP:
    printf("%c", o->this.character);
    break;
  case SFS_SPECIAL_ATOM:
    printf("%c", o->this.character);
    break;*/
  default:
    variable->cdar = make_nil();
    break;
  }
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

  }while(env1->type != SFS_NIL && var->this.pair.cdr->type != SFS_NIL);

  WARNING_MSG("Unbound variable");
  return nil;
}

void display_variable(object variable){
  sfs_print_pair(variable->this.pair.car);
}

void display_environment(object env, int num){
  object env1 = env;
  object var = nil;

  while(env1->this.number != num){
    env1=env1->this.pair.car;
  }
  var=env1->this.pair.cdr;

  if(var->type == SFS_NIL){
    DEBUG_MSG("No variable declared in this environment");
  }
  else{
    do{
      uint i = 0;
      printf("Displaying environment n°%d :\n",env1->this.number);
      printf("Variable n°%d is \n",i);
      display_variable(var);
      var=var->this.pair.cdr;
      i++;
    }while(var->this.pair.cdr->type != SFS_NIL);
    printf("End of display\n");
  }
}
    
    
  
  
  
  



