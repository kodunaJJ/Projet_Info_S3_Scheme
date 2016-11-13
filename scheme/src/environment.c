#include "environment.h"
#include "mem.h"
#include "notify.h"
#include "print.h"

/* environnement = paire dont car indique l'environnement précédent
   et cdr indique la liste de variables associées à l'environnement */

object create_environment(){

  object env = make_pair();
  env->type = SFS_ENVIRONMENT;
  env->this.pair.car=nil;
  env->this.pair.cdr=nil;
  /*printf("env type = %d\n", env->type);
printf("env num = %d\n",env->this.pair.car->this.number);
sfs_print(env->this.pair.car);
sfs_print(env->this.pair.cdr);*/
  return env;
}

object create_top_level_environment(){
  object top = create_environment(TOP_LEVEL);

  /* modification de make_pair pour initialiser car et cdr à nil ??? */
  
  /* top->this.pair.car=nil; */

  /* ajout de la creation des formes ??? */

  return top;
}

object add_environment(object env){
  object new_env = create_environment();
  new_env->this.pair.car=env;
  return new_env;
}

object delete_environment(object env){
  if(env->this.pair.car->type == SFS_NIL){
    WARNING_MSG("Deletion of top level environment IMPOSSIBLE");
    return env;
  }
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

  puts("debut add var");
  object variable = make_pair();
  variable->this.pair.car = make_pair();
  variable->caar = make_pair();
  variable->caar->this.pair.car = make_symbol(name->this.symbol);
  variable->caar->this.pair.cdr = make_nil();

  /* pas de prise en charge des listes pour l'instant */
  switch(value->type){
  case SFS_NUMBER:
    variable->cdar = make_pair();
    variable->cdar->this.pair.car = make_integer(value->this.number);
    variable->cdar->this.pair.cdr = make_nil();
    break;
  case SFS_CHARACTER:
    variable->cdar = make_character(value->this.character);
    break;
  case SFS_STRING:
    variable->cdar = make_string(value->this.string);
    break;
  case SFS_NIL:
    variable->cdar = make_pair();
    variable->cdar->this.pair.car = make_nil();
    variable->cdar->this.pair.cdr = make_nil();
    break;
  case SFS_BOOLEAN:
    variable->cdar = make_pair();
    variable->cdar->this.pair.car = make_boolean(value->this.boolean);
    variable->cdar->this.pair.cdr = make_nil();
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

/* fonctions pour debuggage */

void display_variable(object variable){
  object var = variable->this.pair.car;
  if(variable->cdar->type == SFS_PAIR){
    sfs_print_pair(variable->this.pair.car);
  }
  else{
    sfs_print_atom(variable);
  }
}

void display_environment(object env, int num_env2display){
  object env1 = env;
  object var = nil;
  int num_env = 0;

  /* printf("env num = %d\n",env1->thi); */
  puts(" debut display");
  if(num_env != -1){
    while(num_env != num_env2display && env1->this.pair.car->type != SFS_NIL){
      env1=env1->this.pair.car;
      num_env ++;
    }
  }
  puts("End env research"); 
  var=env1->this.pair.cdr;
  printf("var type = %d\n",var->type);

  if(var->type == SFS_NIL){
    DEBUG_MSG("No variable declared in this environment");
  }
  else{
    printf("Displaying environment n°%d :\n",num_env+1);
    uint i = 0;
    do{    
      printf("Variable n°%d is --> ",i);
      display_variable(var);
      puts("");
      var=var->this.pair.cdr;
      i++;
    }while(var->type != SFS_NIL);
    printf("End of display\n");
  }
}
    
    
  
  
  
  



