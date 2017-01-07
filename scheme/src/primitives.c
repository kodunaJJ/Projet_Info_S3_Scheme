
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
  object p=create_environment();
  /*object p=make_pair();*/
  object resultat=make_integer(0);
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
	if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number+=p->this.pair.cdr->this.number;
	}
	else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
      }
    }
  return resultat;
}

object sub(object input, object env)
{
  object p=create_environment();
  /*object p=make_pair();*/
  object resultat=make_integer(0);
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
	if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number-=p->this.pair.cdr->this.number;
	}
	else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
      }
    }
  return resultat;
}
			
			
object mult(object input, object env)
{				
  object p=create_environment();
  /*object p=make_pair();*/
  object resultat=make_integer(1);
  while(input->this.pair.cdr->type!=SFS_NIL)
    {
      input=input->this.pair.cdr;
      if(input->this.pair.car->type==SFS_PAIR){
	input->this.pair.car=sfs_eval(input->this.pair.car, env);
      }
      if(input->this.pair.car->type==SFS_NUMBER)
	{
	  resultat->this.number*=input->this.pair.car->this.number;
	}
      if(input->this.pair.car->type==SFS_SYMBOL){
	p=research_variable(input->this.pair.car, env);
	if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number*=p->this.pair.cdr->this.number;
	}
	else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
      }
    }return resultat;
			

}

object divi(object input, object env)
{
  object p=create_environment();
  /*object p=make_pair();*/
				
  object resultat=make_integer(1);	
  if(input->this.pair.cdr->type!=SFS_NIL)
    {
      if(input->cadr->type==SFS_PAIR){
	input->cadr=sfs_eval(input->cadr, env);
      }
      if(input->cadr->type==SFS_NUMBER && input->cadr->this.number !=0){
	resultat->this.number=input->cadr->this.number;
	input=input->this.pair.cdr;
      }
      if(input->cadr->type==SFS_NUMBER && input->cadr->this.number ==0)
	{
	  ERROR_MSG("Division par 0 impossible");

	}
      if(input->cadr->type==SFS_SYMBOL){
	p=research_variable(input->cadr, env);
	if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number=p->this.pair.cdr->this.number;
	}
	else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
	input=input->this.pair.cdr;
      }
    }
  while(input->this.pair.cdr->type!=SFS_NIL)
    {
      input=input->this.pair.cdr;
      if(input->this.pair.car->type==SFS_PAIR){
	input->this.pair.car=sfs_eval(input->this.pair.car, env);
      }
      if(input->this.pair.car->type==SFS_NUMBER)
	{
	  resultat->this.number/=input->this.pair.car->this.number;
	}
      if(input->this.pair.car->type==SFS_SYMBOL){
	p=research_variable(input->this.pair.car, env);
	if(p->this.pair.cdr->type==SFS_NUMBER){
	  resultat->this.number/=p->this.pair.cdr->this.number;
	}
	else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol);
      }
    }return resultat;
}



object egal(object input, object env)

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
}

