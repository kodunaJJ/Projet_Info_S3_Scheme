/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"

uint form_type(object o){
  puts("form_type");
  printf("%s\n", o->this.symbol);
  if(strcmp(o->this.symbol,"quote")==0){
    DEBUG_MSG("form quote detected");
    return QUOTE_FORM;
  }

  if(strcmp(o->this.symbol,"if")==0){
    DEBUG_MSG("form if detected");
    return IF_FORM;
  }
  if(strcmp(o->this.symbol,"set!")==0){
    DEBUG_MSG("form set detected");
    return SET_FORM;
  }
  if(strcmp(o->this.symbol,"define")==0){
    DEBUG_MSG("form define detected");
    return DEFINE_FORM;
  }
  if(strcmp(o->this.symbol,"and")==0){
    DEBUG_MSG("form and detected");
    return AND_FORM;
  }
  DEBUG_MSG("Unknown form");
  return NOT_FORM;
}
    


object sfs_eval( object input ) {
  /* objets auto-evaluant */

 eval_start:
  switch(input->type){
  case SFS_NUMBER: return input;
  case SFS_CHARACTER: return input;
  case SFS_STRING: return input;
  case SFS_BOOLEAN: return input;
  default:
    DEBUG_MSG("Not an auto-evaluating object");
    break;
  }
  puts("form detection");
  if(input->type == SFS_PAIR){
    if(input->this.pair.car->type == SFS_SYMBOL){
      object o = input->this.pair.car;
      puts("form detection");
      switch(form_type(o)){
      case QUOTE_FORM: return input->this.pair.cdr->this.pair.car;
      case IF_FORM:
	DEBUG_MSG("form if detected");
	break;
      case SET_FORM:
	DEBUG_MSG("form set! detected");
	break;
      case DEFINE_FORM:
	DEBUG_MSG("form define detected");
	break;
      case AND_FORM:
	DEBUG_MSG("form and detected");
	break;
      case NOT_FORM:
	DEBUG_MSG("Not form detected");
	break;
      default:
	DEBUG_MSG("Program error");
	break;
      }
    }
  }
  return input;
}
