
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "object.h"
#include "primitives.h"
#include "eval.h"
#include "environment.h"
#include "basic.h"
#include "read.h"

/*extern object env;*/


/* fonctions de calcul arithmetique de base */

object add(object input, object env)
{
  object p;
  /*object p=make_pair();*/
  object resultat=make_integer(0);
  if(input->this.pair.cdr->type == SFS_NIL){
    WARNING_MSG("No operand");
  }
  else{
    
    while(input->this.pair.cdr->type!=SFS_NIL)
      {
	input=input->this.pair.cdr;
	if(input->this.pair.car->type==SFS_PAIR){
	  input->this.pair.car=sfs_eval(input->this.pair.car, env);
	}
	if(input->this.pair.car->type==SFS_NUMBER)
	  {
	    resultat->this.number+=input->this.pair.car->this.number;
	  }
	else if(input->this.pair.car->type==SFS_SYMBOL){
	  p=research_variable(input->this.pair.car, env);
	  if(p->type == SFS_NIL){
	    ERROR_MSG("Unbound variable");
	  }
	  else if(p->cadr->type==SFS_NUMBER){
	    resultat->this.number+=p->cadr->this.number;
	  }
	  else ERROR_MSG("wrong operand type");
	}
	else ERROR_MSG("Wrong operand type !");
      }
  }
  return resultat;
}

object sub(object input, object env)
{
  object p;
  /*object p=make_pair();*/
  object resultat=make_integer(0);
  object res_init;
  if(input->this.pair.cdr->type != SFS_NIL){
    if(input->cddr->type != SFS_NIL){
      res_init = sfs_eval(input->cadr, env);
      DEBUG_MSG("res_init value = %d", res_init->this.number);
      DEBUG_MSG("res_init type = %d", res_init->type);
      if(res_init->type == SFS_VARIABLE_VALUE){
	res_init = res_init->this.pair.car;
      }
    }
    else{
      resultat->this.number -= input->cadr->this.number;
      return resultat;
    }
    if(res_init->type == SFS_NUMBER){
      resultat->this.number = res_init->this.number;
    }
    else{
      ERROR_MSG("Wrong operand type !");
    }
  }
  else{
    WARNING_MSG("No operand !");
    return resultat;
  }
  input=input->this.pair.cdr;
  while(input->this.pair.cdr->type!=SFS_NIL)
    {
      input=input->this.pair.cdr;
      if(input->this.pair.car->type==SFS_PAIR){
	input->this.pair.car=sfs_eval(input->this.pair.car, env);
      }
      if(input->this.pair.car->type==SFS_NUMBER)
	{
	  resultat->this.number-=input->this.pair.car->this.number;
	}
      else if(input->this.pair.car->type==SFS_SYMBOL){
	p=research_variable(input->this.pair.car, env);
	if(p->type == SFS_NIL){
	  ERROR_MSG("Unbound variable");
	}
	else if(p->cadr->type==SFS_NUMBER){
	  resultat->this.number-=p->cadr->this.number;
	}
	else ERROR_MSG("wrong operand type");
      }
      else ERROR_MSG("Wrong operand type !");
      
    }
  return resultat;
}
			
			
object mult(object input, object env)
{				
  object p;
  /*object p=make_pair();*/
  object resultat=make_integer(1);
  if(input->this.pair.cdr->type == SFS_NIL){
    WARNING_MSG("No operand");
    return resultat;
  }
  while(input->this.pair.cdr->type!=SFS_NIL)
    {
      input=input->this.pair.cdr;
      if(input->this.pair.car->type==SFS_PAIR){
	input->this.pair.car=sfs_eval(input->this.pair.car, env);
      }
      if(input->this.pair.car->type==SFS_NUMBER)
	{
	  if(input->this.pair.car->this.number == 0) return make_integer(0);
	  resultat->this.number*=input->this.pair.car->this.number;
	}
      else if(input->this.pair.car->type==SFS_SYMBOL){
	p=research_variable(input->this.pair.car, env);
	DEBUG_MSG("p type = %d",p->type);
	if(p->type == SFS_NIL){
	  ERROR_MSG("Unbound variable");
	}
	else if(p->cadr->type==SFS_NUMBER){
	  resultat->this.number*=p->cadr->this.number;
	}
	else ERROR_MSG("wrong operand type");
      }
      else ERROR_MSG("wrong operand type !");
    }
  return resultat;
}
			

object divi(object input, object env)
{
  object p;
  /*object p=make_pair();*/
  object op1;
  object op2;
  object resultat=make_integer(1);	
  if(input->this.pair.cdr->type!=SFS_NIL)
    {

      if(input->cddr->type == SFS_NIL){
	ERROR_MSG("Too few arguments");
      }
      if(input->this.pair.cdr->type==SFS_PAIR){
	op1=sfs_eval(input->cadr, env);
	DEBUG_MSG("op1 type = %d",op1->type);
	if(op1->type != SFS_NUMBER){
	  if(op1->type == SFS_VARIABLE_VALUE){
	    op1=op1->this.pair.car;
	    DEBUG_MSG("op1 type = %d",op1->type);
	    if(op1->type != SFS_NUMBER){
	      ERROR_MSG("Wrong type of operand");
	    }
	  }
	  else{
	    ERROR_MSG("Wrong type of operand");
	  }
	}
        if(input->cdddr->type != SFS_NIL){
	  ERROR_MSG("too many arguments");
	}  
	op2=sfs_eval(input->cddr->this.pair.car, env);
	DEBUG_MSG("op2 type = %d",op2->type);
	if(op2->type != SFS_NUMBER){
	  if(op2->type == SFS_VARIABLE_VALUE){
	    op2=op2->this.pair.car;
	    if(op2->type != SFS_NUMBER){
	      ERROR_MSG("Wrong type of operand");
	    }
	  }
	  else{
	    ERROR_MSG("Wrong type of operand");
	  }
	}
      }
      if(op2->this.number !=0){
	resultat->this.number=op1->this.number/op2->this.number;
	return resultat;
      }
      else if(op2->this.number ==0)
	{
	  ERROR_MSG("Div 0 !");

	}
      else
	/*if(input->cadr->type==SFS_SYMBOL){
	  p=research_variable(input->cadr, env);
	  if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number=p->this.pair.cdr->this.number;
	  }
	  else ERROR_MSG("No operand");
	  input=input->this.pair.cdr;
	  }
	  }*/
	/*while(input->this.pair.cdr->type!=SFS_NIL)
	  {
	  input=input->this.pair.cdr;
	  if(input->this.pair.car->type==SFS_PAIR){
	  input->this.pair.car=sfs_eval(input->this.pair.car, env);
	  }
	  if(input->this.pair.car->type==SFS_NUMBER)
	  {
	  resultat->this.number/=input->this.pair.car->this.number;
	  }
	  else if(input->this.pair.car->type==SFS_SYMBOL){
	  p=research_variable(input->this.pair.car, env);
	  if(p->type == SFS_NIL){
	  ERROR_MSG("Unbound variable");
	  }
	  else if(p->cadr->type==SFS_NUMBER){
	  resultat->this.number/=p->cadr->this.number;
	  }
	  else ERROR_MSG("Wrong operand type !");
	  }
	  else ERROR_MSG("wrong operand type !");
	  }*/
	ERROR_MSG("Wrong type of operand");
    }
  else ERROR_MSG("No operand");
}

object remainder(object input, object env)
{
  object p;
  /*object p=make_pair();*/
  object op1;
  object op2;
  object resultat=make_integer(1);	
  if(input->this.pair.cdr->type!=SFS_NIL)
    {

      if(input->cddr->type == SFS_NIL){
	ERROR_MSG("Too few arguments");
      }
      if(input->this.pair.cdr->type==SFS_PAIR){
	op1=sfs_eval(input->cadr, env);
	DEBUG_MSG("op1 type = %d",op1->type);
	if(op1->type != SFS_NUMBER){
	  if(op1->type == SFS_VARIABLE_VALUE){
	    op1=op1->this.pair.car;
	    DEBUG_MSG("op1 type = %d",op1->type);
	    if(op1->type != SFS_NUMBER){
	      ERROR_MSG("Wrong type of operand");
	    }
	  }
	  else{
	    ERROR_MSG("Wrong type of operand");
	  }
	}
        if(input->cdddr->type != SFS_NIL){
	  ERROR_MSG("too many arguments");
	}  
	op2=sfs_eval(input->cddr->this.pair.car, env);
	DEBUG_MSG("op2 type = %d",op2->type);
	if(op2->type != SFS_NUMBER){
	  if(op2->type == SFS_VARIABLE_VALUE){
	    op2=op2->this.pair.car;
	    if(op2->type != SFS_NUMBER){
	      ERROR_MSG("Wrong type of operand");
	    }
	  }
	  else{
	    ERROR_MSG("Wrong type of operand");
	  }
	}
      }
      if(op2->this.number !=0){
	resultat->this.number=op1->this.number%op2->this.number;
	return resultat;
      }
      else if(op2->this.number ==0)
	{
	  ERROR_MSG("Div 0 !");

	}
      else
	/*if(input->cadr->type==SFS_SYMBOL){
	  p=research_variable(input->cadr, env);
	  if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number=p->this.pair.cdr->this.number;
	  }
	  else ERROR_MSG("No operand");
	  input=input->this.pair.cdr;
	  }
	  }*/
	/*while(input->this.pair.cdr->type!=SFS_NIL)
	  {
	  input=input->this.pair.cdr;
	  if(input->this.pair.car->type==SFS_PAIR){
	  input->this.pair.car=sfs_eval(input->this.pair.car, env);
	  }
	  if(input->this.pair.car->type==SFS_NUMBER)
	  {
	  resultat->this.number/=input->this.pair.car->this.number;
	  }
	  else if(input->this.pair.car->type==SFS_SYMBOL){
	  p=research_variable(input->this.pair.car, env);
	  if(p->type == SFS_NIL){
	  ERROR_MSG("Unbound variable");
	  }
	  else if(p->cadr->type==SFS_NUMBER){
	  resultat->this.number/=p->cadr->this.number;
	  }
	  else ERROR_MSG("Wrong operand type !");
	  }
	  else ERROR_MSG("wrong operand type !");
	  }*/
	ERROR_MSG("Wrong type of operand");
    }
  else ERROR_MSG("No operand");
}

/* fonctions de comparaison arithmetique */

object equal(object input, object env){
  object op1;
  object op2;
  object c_op1 = make_object(SFS_NUMBER);
  object c_op2 = make_object(SFS_NUMBER);
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  else{
    input = input->this.pair.cdr;
    op1 = sfs_eval(input->this.pair.car,env);
    if(op1->type != SFS_NUMBER){
      if(op1->type == SFS_VARIABLE_VALUE){
	op1=op1->this.pair.car;

	DEBUG_MSG("op1 type = %d",op1->type);
	if(op1->type != SFS_NUMBER){
	  ERROR_MSG("Wrong type of operand");
	}
      }
      else{
	ERROR_MSG("Wrong type of operand");
      }
    }
    	c_op1->this.number = op1->this.number;
    while(input->this.pair.cdr->type != SFS_NIL){
      input = input->this.pair.cdr;

      /*if(input->this.pair.cdr->type != SFS_NIL){*/
      op2 = sfs_eval(input->this.pair.car,env);
      if(op2->type != SFS_NUMBER){
	if(op2->type == SFS_VARIABLE_VALUE){
	  op2=op2->this.pair.car;
	  DEBUG_MSG("op2 type = %d",op2->type);
	  if(op2->type != SFS_NUMBER){
	    ERROR_MSG("Wrong type of operand");
	  }
	}
	else{
	  ERROR_MSG("Wrong type of operand");
	}
      }
      /* }*/
      c_op2->this.number = op2->this.number;
      if( c_op1->this.number == c_op2->this.number){
	c_op1->this.number = c_op2->this.number;
      }
      else{
	sfs_free(c_op1);
	sfs_free(c_op2);
	return false;
      }
    }
    sfs_free(c_op1);
    sfs_free(c_op2);
    return resultat;
  }
}

object greater(object input, object env){
  object op1;
  object op2;
  object c_op1 = make_object(SFS_NUMBER);
  object c_op2 = make_object(SFS_NUMBER);
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  else{
    input = input->this.pair.cdr;
    op1 = sfs_eval(input->this.pair.car,env);
    if(op1->type != SFS_NUMBER){
      if(op1->type == SFS_VARIABLE_VALUE){
	op1=op1->this.pair.car;
	
	DEBUG_MSG("op1 type = %d",op1->type);
	if(op1->type != SFS_NUMBER){
	  ERROR_MSG("Wrong type of operand");
	}
      }
      else{
	ERROR_MSG("Wrong type of operand");
      }
    }
    c_op1->this.number = op1->this.number;
    while(input->this.pair.cdr->type != SFS_NIL){
      input = input->this.pair.cdr;

      /*if(input->this.pair.cdr->type != SFS_NIL){*/
      op2 = sfs_eval(input->this.pair.car,env);
      if(op2->type != SFS_NUMBER){
	if(op2->type == SFS_VARIABLE_VALUE){
	  op2=op2->this.pair.car;
	  DEBUG_MSG("op2 type = %d",op2->type);
	  if(op2->type != SFS_NUMBER){
	    ERROR_MSG("Wrong type of operand");
	  }
	}
	else{
	  ERROR_MSG("Wrong type of operand");
	}
      }
      /* }*/
      c_op2->this.number = op2->this.number;
      if( c_op1->this.number > c_op2->this.number){
	c_op1->this.number = c_op2->this.number;
      }
      else{
	sfs_free(c_op1);
	sfs_free(c_op2);
	return false;
      }
    }
    sfs_free(c_op1);
    sfs_free(c_op2);
    return resultat;
  }
}

object lower(object input, object env){
  object op1;
  object op2;
  object c_op1 = make_object(SFS_NUMBER);
  object c_op2 = make_object(SFS_NUMBER);
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
    sfs_free(c_op1);
    sfs_free(c_op2);
    return true;
  }
  else{
    input = input->this.pair.cdr;
    op1 = sfs_eval(input->this.pair.car,env);
    if(op1->type != SFS_NUMBER){
      if(op1->type == SFS_VARIABLE_VALUE){
	op1=op1->this.pair.car;
 
	DEBUG_MSG("op1 type = %d",op1->type);
	if(op1->type != SFS_NUMBER){
	  ERROR_MSG("Wrong type of operand");
	}
      }
      else{
	ERROR_MSG("Wrong type of operand");
      }
    }
    	c_op1->this.number = op1->this.number;
    while(input->this.pair.cdr->type != SFS_NIL){
      input = input->this.pair.cdr;

      /*if(input->this.pair.cdr->type != SFS_NIL){*/
      op2 = sfs_eval(input->this.pair.car,env);
      if(op2->type != SFS_NUMBER){
	if(op2->type == SFS_VARIABLE_VALUE){
	  op2=op2->this.pair.car;
	  DEBUG_MSG("op2 type = %d",op2->type);
	  if(op2->type != SFS_NUMBER){
	    ERROR_MSG("Wrong type of operand");
	  }
	}
	else{
	  ERROR_MSG("Wrong type of operand");
	}
      }
      /* }*/
      c_op2->this.number = op2->this.number;
      if(c_op1->this.number < c_op2->this.number){
	c_op1->this.number = c_op2->this.number;
      }
      else{
	sfs_free(c_op1);
	sfs_free(c_op2);
	return false;
      }
    }
    sfs_free(c_op1);
    sfs_free(c_op2);
    return resultat;
  }
}



/* fonctions de conversion de type */

object char_to_integer(object input, object env){
  object op;
  object res;
  if(input->this.pair.cdr->type == SFS_NIL){
    ERROR_MSG("No operand");
  }
  else{
    input = input->this.pair.cdr;
    if(input->this.pair.cdr->type != SFS_NIL){
      ERROR_MSG("Too many arguments");
    }
    op = sfs_eval(input->this.pair.car,env);
    if(op->type != SFS_CHARACTER){
      if(op->type == SFS_VARIABLE_VALUE){
	op = op->this.pair.car;
	if(op->type == SFS_CHARACTER){
	  res=make_integer((int)op->this.character);
	  return res;
	}
	else if(op->type == SFS_STRING){
	  if(is_scm_newline(op->this.string,0)){
	    res=make_integer((int)'\n');
	    return res;
	  }
	  else if(is_scm_space(op->this.string,0)){
	    res=make_integer((int)' ');
	    return res;
	  }
	  else{
	    ERROR_MSG("Wrong type of operand !");
	  }
	}
	else{
	  ERROR_MSG("Wrong type of operand !");
	}	  
      }
      if(op->type == SFS_STRING){
	if(is_scm_newline(op->this.string,0)){
	  res=make_integer((int)'\n');
	  return res;
	}
	else if(is_scm_space(op->this.string,0)){
	  res=make_integer((int)' ');
	  return res;
	}
	else{
	  ERROR_MSG("Wrong type of operand !");
	}
      }
    }
    else{
      res=make_integer((int)op->this.character);
      return res;
    }
  }
}

object integer_to_char(object input, object env){
  object op;
  object res;
  if(input->this.pair.cdr->type == SFS_NIL){
    ERROR_MSG("No operand");
  }
  else{
    input = input->this.pair.cdr;
    if(input->this.pair.cdr->type != SFS_NIL){
      ERROR_MSG("Too many arguments");
    }
    op = sfs_eval(input->this.pair.car,env);
    if(op->type != SFS_NUMBER){
      if(op->type == SFS_VARIABLE_VALUE){
	op = op->this.pair.car;
	if(op->type == SFS_NUMBER){
	  if(op->this.number == (int)' '){
	    res = make_string("#\\space");
	    return res;
	  }
	  else if(op->this.number == (int)'\n'){
	    res=make_string("#\\newline");
	    return res;
	  }
	  else{
	    if(-1 < op->this.number && op->this.number < 128){
	      res=make_character((char)op->this.number);
	      return res;
	    }
	    else{
	      ERROR_MSG("Conversion impossible integer value does not correspond to a character");
	    }
	  }
	}
	else{
	  ERROR_MSG("Wrong type of operand !");
	}
      }
      else{
	ERROR_MSG("Wrong type of operand !");
      }
    }
    else{
      if(op->this.number == (int)' '){
	res = make_string("#\\space");
	return res;
      }
      else if(op->this.number == (int)'\n'){
	res=make_string("#\\newline");
	return res;
      }
      else{
	if(op->this.number > -1 && op->this.number < 128){
	  res=make_character((char)op->this.number);
	  return res;
	}
	else{
	  ERROR_MSG("Conversion impossible integer value does not correspond to a character");
	}
      }
    } 
  }
}

object number_to_string(object input, object env){
  return input;
}

object string_to_number(object input, object env){
  return input;
}

object symbol_to_string(object input, object env){
  return input;
}

object string_to_symbol(object input, object env){
  return input;
}
