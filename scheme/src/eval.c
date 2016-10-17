
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



object sfs_eval( object input ) {

object output=input ;

DEBUG_MSG("type de input à évaluer : %d",input->type);

/* Gestion de la forme QUOTE */
if (output->type==SFS_SYMBOL && output->this.symbol[0]=='\''){ 
	output=make_pair();
	output->this.pair.car = make_symbol("quote") ;
	int i =1;
	while (input->this.symbol[i] != '\0'){ 
		output->this.pair.cdr->this.symbol[i-1] = input->this.symbol[i];
		i++;
		}
	DEBUG_MSG("type du car : %d",output->this.pair.car->type);
	DEBUG_MSG("valeur : %s",output->this.pair.car->this.symbol);
	return nil ;
	} 

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
	

	}*/	
	

else return output;


}
