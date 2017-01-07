
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "object.h"
#include "primitives.h"
#include "eval.h"
#include "environment.h"
#include "basic.h"

/*extern object env;*/

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

/*object egal(object input, object env)

{
  object p=create_environment();
  object resultat=make_boolean(1);
  object operande1=make_integer(1);
  object operande2=make_integer(1);
				
				
  if(input->this.pair.cdr->type!=SFS_NIL){
    input=input->this.pair.cdr;
    if(input->this.pair.car->type==SFS_PAIR){
      input->this.pair.car=sfs_eval(input->this.pair.car, env);
    }
    if(input->this.pair.car->type==SFS_SYMBOL){
      p=research_variable(input->this.pair.car, env);
      if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){
	operande1->this.number=p->this.pair.cdr->this.number;
      }
      else {
	WARNING_MSG("Pas de nombre à comparer");
	return nil;
      }
    }
    else if(input->this.pair.car->type==SFS_NUMBER){
      operande1->this.number=input->this.pair.car->this.number;
    }
    else {
      WARNING_MSG("Pas de nombre à comparer");
      return nil;
    }
  }
				
  while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){

    if(input->this.pair.cdr->type!=SFS_NIL){
      input=input->this.pair.cdr;
      if(input->this.pair.car->type==SFS_PAIR){
	input->this.pair.car=sfs_eval(input->this.pair.car, env);
      }
      if(input->this.pair.car->type==SFS_SYMBOL){
	p=research_variable(input->this.pair.car, env);
	if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){
	  operande2->this.number=p->this.pair.cdr->this.number;
	}
	else {
	  WARNING_MSG("Pas de nombre à comparer");
	  return nil;
	}
      }
      else if(input->this.pair.car->type==SFS_NUMBER){
	operande2->this.number=input->this.pair.car->this.number;
      }
      else {
	WARNING_MSG("Pas de nombre à comparer");
	return nil;
      }
    }
    resultat->this.boolean= (operande1->this.number == operande2->this.number) ? TRUE:FALSE;
    operande1->this.number = operande2->this.number;
  }
  return resultat;
  }*/

object equal(object input, object env){
  object op1;
  object op2;
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
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
      if( op1->this.number == op2->this.number){
	op1->this.number = op2->this.number;
      }
      else{
	return false;
      }
    } 
    return resultat;
  }
}

object greater(object input, object env){
  object op1;
  object op2;
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
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
      if( op1->this.number > op2->this.number){
	op1->this.number = op2->this.number;
      }
      else{
	return false;
      }
    } 
    return resultat;
  }
}

object lower(object input, object env){
    object op1;
  object op2;
  object resultat=true;
  
  if(input->this.pair.cdr->type == SFS_NIL){
    return true;
  }
  if(input->cddr->type != SFS_PAIR){
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
      if( op1->this.number < op2->this.number){
	op1->this.number = op2->this.number;
      }
      else{
	return false;
      }
    } 
    return resultat;
  }
}
