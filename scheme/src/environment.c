#include "object.h"
#include "environment.h"
#include "mem.h"
#include "notify.h"
#include "print.h"
#include "primitives.h"

/* environnement = paire dont car indique l'environnement précédent
   et cdr indique la liste de variables associées à l'environnement */

object create_environment(){

  object env = make_pair();
  env->type = SFS_ENVIRONMENT;
  env->this.pair.car=nil;
  env->this.pair.cdr=nil;
  /*sfs_print(env->this.pair.car);
    sfs_print(env->this.pair.cdr);*/
  return env;
}

object create_top_level_environment(){
  object top = create_environment();
  object quote = make_symbol("quote");
  object if_scm = make_symbol("if");
  object and_scm = make_symbol("and");
  object or_scm = make_symbol("or");
  object define = make_symbol("define");
  object set_scm = make_symbol("set!");

  object prim = make_object(SFS_PRIMITIVE);

  add_variable(quote,nil,top);
  add_variable(if_scm,nil,top);
  add_variable(and_scm,nil,top);
  add_variable(or_scm,nil,top);
  add_variable(define,nil,top);
  add_variable(set_scm,nil,top);
  
  prim->this.primitive = add;
  add_variable(make_symbol("+"),prim,top);

  prim->this.primitive = sub;
  add_variable(make_symbol("-"),prim,top);

  prim->this.primitive = mult;
  add_variable(make_symbol("*"),prim,top);

  prim->this.primitive = divi;
  add_variable(make_symbol("/"),prim, top);

  
  
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
  /*DEBUG_MSG("----- %d -----",value->type);*/
  object variable = make_pair();
  variable->this.pair.car = make_pair();
  variable->caar = make_symbol(name->this.symbol);
  variable->cdar = add_variable_value(value,env);
  variable->this.pair.cdr = env->this.pair.cdr;
  env->this.pair.cdr=variable;
}

/*object copy_pair(object root, object env){
  object p = make_pair();

  object car;
  object cdr;

  switch(root->type){
  case SFS_NUMBER:
  return  make_integer(value->this.number);
  break;
  case SFS_CHARACTER:
  variable->cdar->this.pair.car = make_character(value->this.character);
  break;
  case SFS_STRING:
  variable->cdar = make_pair();
  variable->cdar->this.pair.car = make_string(value->this.string);
  variable->cdar->this.pair.cdr = make_nil();
  break;
  case SFS_PAIR:
  p = make_pair();
  p->this.pair.car = copy_pair(root->this.car,env);
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
  variable->cdar = make_pair();
  variable->cdar = make_symbol(value->this.symbol); /*nécessité de faire un lien avec la variable si elle existe */
/* variable->cdar->this.pair.cdr = make_nil();
   break;
   /*case SFS_ARITH_OP:
   printf("%c", o->this.character);
   break;
   case SFS_SPECIAL_ATOM:
   printf("%c", o->this.character);
   break;*/
/*default:
  variable->cdar = make_nil();
  break;*/
/* }
   p->this.pair.car = car;
   p->this.pair.cdr = cdr;
   return p;
   }*/
object add_variable_value(object value, object env/*, int start*/){
  object variable_value = make_variable_value();
  /*DEBUG_MSG("->-> value type = %d", value->type);
    DEBUG_MSG("value of value = %c",value->this.pair.car->this.character);
    DEBUG_MSG("9999999 variable value %d //99999999",variable_value->type);*/
  switch(value->type){
  case SFS_NUMBER:
    variable_value->this.pair.car = make_integer(value->this.number);
    break;
  case SFS_CHARACTER:
    variable_value->this.pair.car = make_character(value->this.character);
    break;
  case SFS_STRING:
    variable_value->this.pair.car = make_string(value->this.string);
    break;
  case SFS_PAIR:
    variable_value->this.pair.car = value;
    break;
  case SFS_NIL:
    break;
  case SFS_BOOLEAN:
    variable_value->this.pair.car = make_boolean(value->this.boolean);
    break;  
  case SFS_VARIABLE_VALUE:
    variable_value->this.pair.car = value;
    break;
  case SFS_ARITH_OP:
    variable_value->this.pair.car = make_arith_op(value->this.character);
    break;
  case SFS_PRIMITIVE:
    /*DEBUG_MSG(" *** primitives ***");
      DEBUG_MSG("variable_value type = %d", variable_value->this.pair.car->type);*/
    variable_value->this.pair.car = make_primitive(value);
    /* DEBUG_MSG("value type = %d", value->type);*/
       DEBUG_MSG("variable_value type = %d", variable_value->this.pair.car->type);
       break;
    /*case SFS_SPECIAL_ATOM:
      printf("%c", o->this.character);
      break;*/
  default:
    return make_nil();
    break;
  }
  /*DEBUG_MSG("******* value type = %d *********",variable_value->this.pair.car->type);*/
  return variable_value;
}

/* unused for now */
object delete_variable(object variable){
  if(variable->type == SFS_NIL) return nil;
  object variable1 = nil;
  sfs_free(variable->cadr);
  sfs_free(variable->cddr);
  sfs_free(variable->this.pair.car);
  variable1 = variable->this.pair.cdr;
  sfs_free(variable);
  return variable1;
}

void delete_variable_value(object variable){
  if(variable->this.pair.cdr->type == SFS_NIL){
    sfs_free(variable->caar);
    sfs_free(variable->cdar);
    sfs_free(variable->this.pair.cdr);
    variable->this.pair.cdr=nil;
  }
  else if(variable->this.pair.cdr->type == SFS_PAIR){
  }
  else{
  }
}

object research_variable(object variable_name, object env){
  DEBUG_MSG("debut fonction recherche");
  DEBUG_MSG("env = %p", env->this.pair.cdr);
  object var = env->this.pair.cdr;
  if(var->type == SFS_NIL){
    DEBUG_MSG("Empty environment");
    /*WARNING_MSG("Unbound variable");*/
    return nil;
  }
  DEBUG_MSG("debut recherche");
  do{
    /* DEBUG_MSG("variable name --> %s",variable_name->this.symbol); */
    /* DEBUG_MSG("compared to %s",var->caar/\*->this.pair.car*\/->this.symbol); */
    /* DEBUG_MSG("variable type %d", var->cdar/\*->this.pair.car*\/->type); */
    /* DEBUG_MSG("variable value %d", var->cdar->this.pair.car->this.number); */
    if(strcmp(var->caar->this.symbol, variable_name->this.symbol) == 0){
        DEBUG_MSG("fin recherche");
      return var->this.pair.car;
    }
    else{
      var = var->this.pair.cdr;
    }

  }while(var->type != SFS_NIL);

  /*WARNING_MSG("Unbound variable");*/
    DEBUG_MSG("fin recherche type = nil");
  return nil;
}

object research_variable_all_env(object variable_name, object env){
  DEBUG_MSG("debut fonction recherche_ALL");
  DEBUG_MSG("env = %p", env->this.pair.cdr);
  object var = env->this.pair.cdr;
  object env1 = env;
  if(var->type == SFS_NIL){
    DEBUG_MSG("Empty environment");
    /*WARNING_MSG("Unbound variable");*/
    return nil;
  }
  DEBUG_MSG("debut recherche");
  while(env1->type != SFS_NIL){
    
    do{
      DEBUG_MSG("valeur = %s",var->caar->this.symbol);
      if(strcmp(var->caar->this.symbol, variable_name->this.symbol) == 0){
	/*DEBUG_MSG("*** + **** = %s",var->caar->this.symbol);
	  DEBUG_MSG("var type = %d",var->cdar->type);*/
	  DEBUG_MSG("fin recherche");
	return var->this.pair.car;
      }
      else{
	var = var->this.pair.cdr;
      }

    }while(var->type != SFS_NIL);
    env1=env1->this.pair.car;
    var = env->this.pair.cdr;
  }

  /*WARNING_MSG("Unbound variable");*/
    DEBUG_MSG("fin recherche type nil");
  return nil;
}

  
/* fonctions pour debuggage */

void display_variable(object variable){
  /*object var = variable->this.pair.car;
    if(variable->cdar->type == SFS_PAIR){
    sfs_print_pair(variable->this.pair.car);
    }
    else{
    sfs_print_atom(variable);
    }*/
  sfs_print(variable->this.pair.car);
}

void display_environment(object env, int num_env2display){
  object env1 = env;
  object var = nil;
  int num_env = 0;

  DEBUG_MSG("debut env display");
  if(num_env != -1){
    while(num_env != num_env2display && env1->this.pair.car->type != SFS_NIL){
      env1=env1->this.pair.car;
      num_env ++;
    }
  }
  DEBUG_MSG("End env research"); 
  var=env1->this.pair.cdr;
  DEBUG_MSG("var type = %d\n",var->type);

  if(var->type == SFS_NIL){
    DEBUG_MSG("No variable declared in this environment");
  }
  else{
    DEBUG_MSG("Displaying environment n°%d :\n",num_env+1);
    uint i = 0;
    do{    
      DEBUG_MSG("Variable n°%d is --> ",i);
      display_variable(var);
      puts("");
      var=var->this.pair.cdr;
      i++;
    }while(var->type != SFS_NIL);
    DEBUG_MSG("End of display\n");
  }
}
