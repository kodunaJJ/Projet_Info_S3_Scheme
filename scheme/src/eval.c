
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "object.h"
#include "environment.h"


int is_form(object o){
  if (strcmp(o->this.symbol,"quote") == 0 || strcmp(o->this.symbol,"define") == 0 || strcmp(o->this.symbol,"set!") == 0 || strcmp(o->this.symbol,"if") == 0 || strcmp(o->this.symbol,"and") == 0 || strcmp(o->this.symbol,"or") == 0 ) return 1;
  else return 0;
}


int auto_evaluating_object(object input){
  switch(input->type){
  case SFS_NUMBER:
    return 1;
  case SFS_CHARACTER:
    return 1;
  case SFS_STRING:
    return 1;
  case SFS_BOOLEAN:
    return 1;
  default:
    return 0;
  }
}

int error_syntax_IF_form(object input){

  object o;
  if(input->this.pair.cdr->type != SFS_PAIR){
    WARNING_MSG("syntax error --> too few arguments");    
    return 1;
  }
  else if(input->cddr->type != SFS_PAIR){
    WARNING_MSG("syntax error --> too few arguments");
    return 1;
  }  
  o = input->cddr;
  if(o->this.pair.cdr->type != SFS_NIL){
    if(o->cddr->type != SFS_NIL){
      WARNING_MSG("syntax error --> too many arguments");
      return 1;
    }
  }
  return 0;
}

int error_syntax_AND_form(object input){
  if(input->this.pair.car->type == SFS_PAIR){
    if(input->this.pair.car->type != SFS_SYMBOL){
      WARNING_MSG("syntax error AND_form");
      return 1;
    }
  }
  else{
    return 0;
  }
}

int error_syntax_OR_form(object input){
  if(input->this.pair.car->type == SFS_PAIR){
    if(input->this.pair.car->type != SFS_SYMBOL){
      WARNING_MSG("syntax error OR_form");
      return 1;
    }
  }
  else{
    return 0;
  }
}

int error_syntax_DEFINE_form(object input){

  if(input->cadr->type != SFS_SYMBOL){
    WARNING_MSG("Expected variable name after define");
    return 1;
  }
  else if(input->cddr->type == SFS_NIL){
    WARNING_MSG("Expected variable value");
    return 1;
  }
  else if(is_form(input->cadr)){
    WARNING_MSG("Imposible to change a form value");
  }
  else{
    return 0;
  }
}

int error_syntax_SET_form(object input){
  if(input->cadr->type != SFS_SYMBOL){
    WARNING_MSG("Expected variable name after set!");
    return 1;
  }
  else if(input->cddr->type == SFS_NIL){
    WARNING_MSG("Expected variable value");
    return 1;
  }
  else{
    return 0;
  }
}
int error_syntax_QUOTE_form(object input){
  if(input->this.pair.cdr->type == SFS_NIL){
    WARNING_MSG("Nothing to quote");
    return 1;
  }
  else{
    return 0;
  }
}



object sfs_eval_predicat(object input, object env){
  DEBUG_MSG("1) predicat type %d", input->type);
  input = sfs_eval(input, env);
  DEBUG_MSG("2) predicat type %d", input->type);
  if (input->type==SFS_BOOLEAN && input->this.boolean==FALSE) return false;
  else return true;
}

object sfs_eval(object input, object env ) {


 restart:

  DEBUG_MSG("type de input à évaluer : %d",input->type);


  /* gestion des paires */
/*Dans le cas d'une paire on gère les primitives et les formes*/
  if(input->type == SFS_PAIR){
    if(input->this.pair.car->type == SFS_PAIR){
      input = input->this.pair.car;
      goto restart;
    }
    else if(auto_evaluating_object(input->this.pair.car)){
      WARNING_MSG("pair is not a known function");
      return nil;
    }
    /*recherche du symbole dans l'environnement courant*/
    else if(input->this.pair.car->type == SFS_SYMBOL){ 
      object search_res = research_variable_all_env(input->this.pair.car,env);
      if(search_res->type == SFS_NIL){
	WARNING_MSG("pair is not a known function");
	return nil;
      }
      else{
      /* Test si le cdr est une primitive */
			if(search_res->this.pair.cdr->type==SFS_PRIMITIVE)
			{

				object (*prim)(object); /* Pointeur de fonction */
				prim = search_res->this.pair.cdr->this.primitive; /* Association de la fonction */
				return prim(input);
			}
		}
	}
	}
	/* Gestion de la forme QUOTE */

	if (!strcmp(input->this.pair.car->this.symbol, "quote")){
	  if(error_syntax_QUOTE_form(input)){
	    return nil;
	  }
	  else{
	    return input->cadr;
	  }
	}


	/*Gestion de DEFINE */
	if (!strcmp(input->this.pair.car->this.symbol, "define")){

	  if(error_syntax_DEFINE_form(input)){
	    return nil;
	  }
	  else{
	    DEBUG_MSG("je passe laaaaaaaaaaaaaaa");
	    object search_res = research_variable(input->cadr,env);
	    if(search_res->type == SFS_NIL){
	      DEBUG_MSG("research ok");
	      add_variable(input->cadr, sfs_eval(input->caddr,env), env);
	      return env->cadr->this.pair.car;
	    }
	    else {
	      delete_variable_value(search_res);
	      search_res->this.pair.cdr = add_variable_value(sfs_eval(input->caddr,env),env);
	      return search_res->this.pair.car;
	    }
	  }
	}


	/*Gestion de SET! */ 
	if (!strcmp(input->this.pair.car->this.symbol, "set!")){
	  object var = research_variable(input->cadr,env);
	  if(var->type == SFS_NIL){
	    WARNING_MSG("Unknown variable");
	    return nil;
	  }
	  else{
	    /* DEBUG_MSG("previous value name --> %s",var->this.pair.car->this.symbol);
	       DEBUG_MSG("previous value name --> %d",var->this.pair.cdr->this.number);*/
	    var->this.pair.cdr = sfs_eval(input->caddr,env);
	    return var->this.pair.cdr;
	  }
	}


	/*Gestion de IF */
	if (!strcmp(input->this.pair.car->this.symbol, "if")){
	  if(error_syntax_IF_form(input)){
	    WARNING_MSG("Syntax error");
	    return nil;
	  }
	  else{
	    if (sfs_eval_predicat(input->cadr, env)== true && input->caddr->type != SFS_NIL){
	      input = input->caddr;
	      DEBUG_MSG("type de la conséquence: %d", input->type);
	      goto restart;
	    }
		
	    else if (sfs_eval_predicat(input->cadr,env)== false && input->cadddr->type != SFS_NIL){
	      input = input->cadddr;
	      DEBUG_MSG("type de l'alternative: %d", input->type);
	      goto restart; 
	    }
	  }
	  return nil;
       
	}
	
	/*Gestion de AND*/
	if (!strcmp(input->this.pair.car->this.symbol, "and")){

	  if(input->this.pair.cdr->type == SFS_NIL){
	    return true;
	  }
	  input = input->this.pair.cdr;

	  while(sfs_eval_predicat(input->this.pair.car,env)== true){
	    if(/*error_syntax_AND_form(input)*/0){
	      return nil;
	    }
	    else{
       
	      DEBUG_MSG("car type = %d",input->this.pair.car->type);
	      DEBUG_MSG("cdr type = %d",input->this.pair.cdr->type);
	      DEBUG_MSG("next pair");
	      if(input->this.pair.cdr->type == SFS_NIL){
		if(input->this.pair.cdr->type != SFS_PAIR){
		  input = input->this.pair.car;
		  goto restart;
		}
	      }
	      input = input->this.pair.cdr;
	      DEBUG_MSG("inc");
	    }
	  }
	  return false;
	}

	/*Gestion de OR*/
	if (!strcmp(input->this.pair.car->this.symbol, "or")){

	  if(input->this.pair.cdr->type == SFS_NIL){
	    return false;
	  }
	  input = input->this.pair.cdr;

	  while(sfs_eval_predicat(input->this.pair.car,env)== false){
	    if(error_syntax_OR_form(input)){
	      return nil;
	    }
	    else{
       
	      DEBUG_MSG("car type = %d",input->this.pair.car->type);
	      DEBUG_MSG("cdr type = %d",input->this.pair.cdr->type);
	      DEBUG_MSG("next pair");
	      if(input->this.pair.cdr->type == SFS_NIL){
		if(input->this.pair.cdr->type != SFS_PAIR){
		  input = input->this.pair.car;
		  goto restart;
		}
	      }
	      input = input->this.pair.cdr;
	      DEBUG_MSG("inc");
	    }
	  }
	  input = input->this.pair.car;
	  goto restart;
	}
      
    
  


/*Renvoie directement la valeur de la variable si on l'entre*/
  else if(input->type == SFS_SYMBOL){
    /*if(symbol_exist(symbol_name, env)){*/
    /*DEBUG_MSG("%s",input->this.symbol);
      DEBUG_MSG("/////// %d ////////////",research_variable(input,env)->this.pair.cdr->type);*/
    /*return research_variable(input,env)->this.pair.cdr;*/
    object search_res = research_variable(input,env);
    if(search_res->type == SFS_NIL){
      WARNING_MSG("Unbound variable !");
      return search_res;
    }
    else{
      return search_res->this.pair.cdr;
    }
  }
  /*else{
    WARNING_MSG("Unbound variable");
    return nil;
    }
    }*/
  else return input;

}
