
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


/*int is_forme(object o){
	if (strcmp(o->this.symbol == ("quote" || "define" || "set!" || "if" || "and" || "or" ))==0) return 1;
	else return 0;
	}
*/

object sfs_eval_predicat(object input){
	input = sfs_eval(input);
	if (input->type==SFS_BOOLEAN && input->this.boolean==FALSE) return false;
	else return true;
	}

object sfs_eval(object input ) {


restart:

DEBUG_MSG("type de input à évaluer : %d",input->type);

/* Gestion de la forme QUOTE */

if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "quote")){
	return input->cadr;
	}


/*Gestion de DEFINE */
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "define")){

	
	}

/*Gestion de SET! 
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "set!")){
	}*/


/*Gestion de IF */
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "if")){

	
	if (input->this.pair.cdr->type == SFS_NIL){
		WARNING_MSG("Pas de prédicat");
		return false;
		}
	
	else if (sfs_eval_predicat(input->cadr)== true && input->caddr->type != SFS_NIL){
		input = input->caddr;
		DEBUG_MSG("type de la conséquence: %d", input->type);
		goto restart;
		}
		
	else if (sfs_eval_predicat(input->cadr)== false && input->cadddr->type != SFS_NIL){
		input = input->cadddr;
		DEBUG_MSG("type de l'alternative: %d", input->type);
		goto restart; 
		}
	
	else return false;
	}
	


/*Gestion de AND*/
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "and")){

	if (input->this.pair.cdr->type == SFS_NIL || input->caddr->type == SFS_NIL){
		WARNING_MSG("Pas d'arguments à évaluer");
		return false;
		}
	
	else if(sfs_eval_predicat(input->cadr)== true && sfs_eval_predicat(input->caddr)== true) return true;

	else return false;
	}

/*Gestion de OR*/
if ((input->type==SFS_PAIR) && !strcmp(input->this.pair.car->this.symbol, "or")){

	if (input->this.pair.cdr->type == SFS_NIL || input->caddr->type == SFS_NIL){
		WARNING_MSG("Pas d'arguments à évaluer");
		return false;
		}
	
	else if(sfs_eval_predicat(input->cadr)== true || sfs_eval_predicat(input->caddr)== true) return true;

	else return false;
	}


else return input;

}



