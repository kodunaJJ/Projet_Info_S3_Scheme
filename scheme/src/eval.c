
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
    DEBUG_MSG("syntax error --> too few arguments");    
    return 1;
  }
  else if(input->cddr->type != SFS_PAIR){
    DEBUG_MSG("syntax error --> too few arguments");
    return 1;
  }
  o = input->cddr;
  if(o->this.pair.cdr->type != SFS_NIL){
    if(o->cddr->type != SFS_NIL){
      DEBUG_MSG("syntax error --> too many arguments");
      return 1;
    }
  }
  return 0;
}

object sfs_eval_predicat(object input, object env){
	input = sfs_eval(input, env);
	if (input->type==SFS_BOOLEAN && input->this.boolean, env==FALSE) return false;
	else return true;
	}


object sfs_eval(object input, object env_courant) {

restart:

object p=create_environment();

 /*Renvoie directement la valeur de la variable si on l'entre*/
if(input->type==SFS_SYMBOL){
	p=research_variable(input->this.symbol, env_courant);
	if (p==NULL) return input;
	return p->this.pair.cdr;
}


/*Dans le cas d'une paire on gère les primitives et les formes*/
if(input->type==SFS_PAIR){

		/*Test si le car est un symbol*/
		if(input->this.pair.car->type==SFS_SYMBOL)
		{
			/*Recherche du symbole dans l'environnement courant*/
			p=research_variable(input->this.pair.car->this.symbol, env_courant);
			if(p==NULL) return input; /*Renvoie l'entrée si le symbole n'existe pas*/

			/* Test si le cdr est une primitive */
			if(p->this.pair.cdr->type==SFS_PRIMITIVE)
			{

				object (*prim)(object); /* Pointeur de fonction */
				prim = p->this.pair.cdr->this.primitive; /* Association de la fonction */
				return prim(input);
			}




DEBUG_MSG("type de input à évaluer : %d",input->type);

/* Gestion de la forme QUOTE */

if (!strcmp(input->this.pair.car->this.symbol, "quote")){
	return input->cadr;
	}



/*Gestion de DEFINE
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "define")){
	}*/

/*Gestion de SET! 

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
	

	else if (sfs_eval_predicat(input->cadr, env_courant)== true && input->caddr->type != SFS_NIL){
	else if (sfs_eval_predicat(input->cadr, env)== true && input->caddr->type != SFS_NIL){

		input = input->caddr;
		DEBUG_MSG("type de la conséquence: %d", input->type);
		goto restart;
		}

	else if (sfs_eval_predicat(input->cadr, env_courant)== false && input->cadddr->type != SFS_NIL){

	else if (sfs_eval_predicat(input->cadr,env)== false && input->cadddr->type != SFS_NIL){

		input = input->cadddr;
		DEBUG_MSG("type de l'alternative: %d", input->type);
		goto restart; 
		}
	
		else return false; */
  
}
	


/*Gestion de AND*/
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "and")){

  /*if (input->this.pair.cdr->type == SFS_NIL || input->caddr->type == SFS_NIL){
    WARNING_MSG("Pas d'arguments à évaluer");
    return false;
    }
	

	else if(sfs_eval_predicat(input->cadr, env_courant)== true && sfs_eval_predicat(input->caddr, env_courant)== true) return true;

	else return false;
	}

    else if(sfs_eval_predicat(input->cadr,env)== true && sfs_eval_predicat(input->caddr, env)== true) return true;

    else return false;*/

  if (input->this.pair.cdr->type == SFS_NIL){
    return true;
  }
  else if(sfs_eval_predicat(input->cadr,env)== true){
    input = input->cadr;
    goto restart;
  }
  else if(sfs_eval_predicat(input->cadr,env)== false){
    return input;
  }
      
 }


/*Gestion de OR*/
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "or")){

	if (input->this.pair.cdr->type == SFS_NIL || input->caddr->type == SFS_NIL){
		WARNING_MSG("Pas d'arguments à évaluer");
		return false;
		}
	

	else if(sfs_eval_predicat(input->cadr, env_courant)== true || sfs_eval_predicat(input->caddr, env_courant)== true) return true;

	else if(sfs_eval_predicat(input->cadr, env)== true || sfs_eval_predicat(input->caddr, env)== true) return true;


	else return false;
	}
} /*fin du test de SYMBOL*/

} /*fin du test de PAIR*/

else return input;

}
 


