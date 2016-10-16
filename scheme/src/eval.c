
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

object sfs_eval( object input ) {

object output=input ;

/* Gestion de QUOTE */
if (output->type==SFS_SYMBOL && output->this.symbol[0]=='\''){ 
	output=make_pair();
	output->this.pair.car = make_symbol("quote") ;
	int i =1;
	while (input->this.symbol[i] != '\0'){ 
		output->this.pair.cdr->this.symbol[i-1] = input->this.symbol[i];
		i++;
		}
	return output ;
	}

if (output->type==SFS_PAIR && strcmp(output->this.pair.car->this.symbol , "quote")){
	return output->this.pair.cdr;
	}


/*Gestion de DEFINE */
if (output->type==SFS_PAIR && strcmp(output->this.pair.car->this.symbol , "define")){
	}

/*Gestion de set! */
	
	
	

else return output;


    return input;
}
