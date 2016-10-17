
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
int predicat(object o){
	if (o->type == SFS_BOOLEAN && o->this.pair.car->this.boolean==0) return 0;
	else return 1;
	}


object sfs_eval( object input ) {

object output=input ;

eval:



DEBUG_MSG("type de input à évaluer : %d",input->type);

/* Gestion de la forme QUOTE */

if ((output->type==SFS_PAIR) && !strcmp(output->this.pair.car->this.symbol, "quote")){
	return output->cadr;
	}


/*Gestion de DEFINE 
if ((output->type==SFS_PAIR) && !strcmp(output->this.pair.car->this.symbol, "define")){
	}*/

/*Gestion de SET! 
if ((output->type==SFS_PAIR) && !strcmp(output->this.pair.car->this.symbol, "set!")){
	}*/


/*Gestion de IF 
if ((output->type==SFS_PAIR) && !strcmp(output->this.pair.car->this.symbol, "if")){

	if (predicat(output->cadr)==TRUE){
		output = output->caddr;
		goto eval;
		}
	
	else if (predicat(output->cadr)==FALSE && output->cadddr = nil) {
		return FALSE;
	}
	
	else {
		output = output->cadddr;
		goto eval; 
		}
	}*/
	

else return output;

}



