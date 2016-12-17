
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


/*int is_forme(object o){
	if (strcmp(o->this.symbol == ("quote" || "define" || "set!" || "if" || "and" || "or" ))==0) return 1;
	else return 0;
	}
*/

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

object sfs_eval_predicat(object input, object env){
  input = sfs_eval(input, env);
	if (input->type==SFS_BOOLEAN && input->this.boolean==FALSE) return false;
	else return true;
	}

object sfs_eval(object input, object env ) {


restart:

DEBUG_MSG("type de input à évaluer : %d",input->type);

/* Gestion de la forme QUOTE */

if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "quote")){
	return input->cadr;
	}


/*Gestion de DEFINE */
 if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "define")){

   if(input->cadr->type != SFS_SYMBOL /*|| input->cadr->type != SFS_PAIR*/){
     WARNING_MSG("Expected symbol name or pair after define");
   }
   else{
    
     if(research_variable(input->cadr,env)->type == SFS_NIL){
       DEBUG_MSG("research ok");
       add_variable(input->cadr, input->cddr, env);
       return env->cadr->this.pair.car;
     }
     else {
       WARNING_MSG("Variable already declared");
       return nil;
     }
   }
 }


/*Gestion de SET! */ 
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "set!")){
  object var = research_variable(input->cadr,env);
  if(var->type == SFS_NIL){
    WARNING_MSG("Unknown variable");
    return nil;
  }
  else{
    var->this.pair.cdr = input->cddr;
    return var->this.pair.car;
  }
 }


/*Gestion de IF */
 if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "if")){
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
     

	
  /*if (input->this.pair.cdr->type == SFS_NIL){
		WARNING_MSG("Syntax error --> Nothing to evaluate");
		return nil;
		 return false 
		
		}
	
	else if (sfs_eval_predicat(input->cadr, env)== true && input->caddr->type != SFS_NIL){
		input = input->caddr;
		DEBUG_MSG("type de la conséquence: %d", input->type);
		goto restart;
		}
		
	else if (sfs_eval_predicat(input->cadr,env)== false && input->cadddr->type != SFS_NIL){
		input = input->cadddr;
		DEBUG_MSG("type de l'alternative: %d", input->type);
		goto restart; 
		}
	
		else return false; */
  
}
	


/*Gestion de AND*/
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "and")){

    if(input->this.pair.cdr->type == SFS_NIL){
      return true;
    }
    input = input->this.pair.cdr;

    while(sfs_eval_predicat(input->this.pair.car,env)== true){
      if(error_syntax_AND_form(input)){
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
  if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "or")){

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


else return input;

}



