/* <<<<<<< Updated upstream */

/* ======= */
/* >>>>>>> Stashed changes */
/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <string.h> */


/* #include "primitives.h" */
/* #include "eval.h" */
/* #include "environment.h" */
/* #include "basic.h" */

/* /\*extern object env;*\/ */

/* object add(object input, object env) */
/* 			{ */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
/* 				object resultat=make_integer(0); */
/* 				while(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_NUMBER) */
/* 					{ */
/* 						resultat->this.number+=input->this.pair.car->this.number; */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 					p=research_variable(input->this.pair.car, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number+=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 					} */
/* 				} */
/* return resultat; */
/* } */

/* object sous(object input, object env) */
/* { */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
/* 				object resultat=make_integer(0); */
/* 				while(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_NUMBER) */
/* 					{ */
/* 						resultat->this.number-=input->this.pair.car->this.number; */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->this.pair.car, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number-=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 					} */
/* 				} */
/* return resultat; */
/* } */
/* <<<<<<< Updated upstream */
			
			
/* object mult(object input, object env) */
/* {				 */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
/* 				object resultat=make_integer(1); */
/* 				while(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_NUMBER) */
/* 					{ */
/* 						resultat->this.number*=input->this.pair.car->this.number; */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->this.pair.car, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number*=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 					} */
/* 				}return resultat; */
			

/* } */

/* object divi(object input, object env) */
/* { */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
				
/* 				object resultat=make_integer(1);	 */
/* 				if(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					if(input->cadr->type==SFS_PAIR){ */
/* 						input->cadr=sfs_eval(input->cadr); */
/* 					} */
/* 					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number !=0){ */
/* 						resultat->this.number=input->cadr->this.number; */
/* 						input=input->this.pair.cdr; */
/* 					} */
/* 					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number ==0) */
/* 					{ */
/* 					ERROR_MSG("Division par 0 impossible"); */

/* 					} */
/* 					if(input->cadr->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->cadr, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 						input=input->this.pair.cdr; */
/* 					} */
/* 				} */
/* ======= */
			
			
/* object mult(object input, object env) */
/* {				 */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
/* 				object resultat=make_integer(1); */
/* >>>>>>> Stashed changes */
/* 				while(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_NUMBER) */
/* 					{ */
/* <<<<<<< Updated upstream */
/* 						resultat->this.number/=input->this.pair.car->this.number; */
/* ======= */
/* 						resultat->this.number*=input->this.pair.car->this.number; */
/* >>>>>>> Stashed changes */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->this.pair.car, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* <<<<<<< Updated upstream */
/* 							resultat->this.number/=p->this.pair.cdr->this.number; */
/* ======= */
/* 							resultat->this.number*=p->this.pair.cdr->this.number; */
/* >>>>>>> Stashed changes */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 					} */
/* 				}return resultat; */
/* <<<<<<< Updated upstream */
/* } */


/* 		/\*ON VERRA LA SUITE PLUS TARD*\/	 */

/* object egal(object input, object env) */

/* { */
/* 				object p=create_environment(); */
/* 				object resultat=make_boolean(1); */
/* 				object operande1=make_integer(1); */
/* 				object operande2=make_integer(1); */
				
				
/* 				if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_environment(input->this.pair.car->this.symbol, env); */
/* 						if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							operande1->this.number=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 						operande1->this.number=input->this.pair.car->this.number; */
/* 					} */
/* 					else { */
/* 					    WARNING_MSG("Pas de nombre à comparer"); */
/* 					    return nil; */
/* 					} */
/* 				} */
				
/* 				while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){ */

/* 					if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 						input=input->this.pair.cdr; */
/* 						if(input->this.pair.car->type==SFS_PAIR){ */
/* 							input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 						} */
/* 						if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 							p=recherche(env,input->this.pair.car->this.symbol); */
/* 							if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 								operande2->this.number=p->this.pair.cdr->this.number; */
/* 							} */
/* 							else { */
/* 							    WARNING_MSG("Pas de nombre à comparer"); */
/* 							    return nil; */
/* 							} */
/* 						} */
/* 						else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 							operande2->this.number=input->this.pair.car->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					resultat->this.boolean= (operande1->this.number == operande2->this.number) ? TRUE:FALSE; */
/* 					operande1->this.number. = operande2->this.number; */
/* 				} */
/* 				return resultat; */
/* } */
/* /\* */
/* object inf(object input, object env) */

/* { */
/* 				object p=creer_env(); */
/* 				object resultat=make_object(SFS_BOOLEAN); */
/* 				resultat->this.boolean=TRUE; */
/* 				object operande1=make_object(SFS_NUMBER); */
/* 				object operande2=make_object(SFS_NUMBER); */
				
				
/* 				if(input->this.pair.cdr->type!=SFS_NIL){ */
/* ======= */
			

/* } */

/* object divi(object input, object env) */
/* { */
/* 				object p=create_environment(); */
/* 				/\*object p=make_pair();*\/ */
				
/* 				object resultat=make_integer(1);	 */
/* 				if(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* 					if(input->cadr->type==SFS_PAIR){ */
/* 						input->cadr=sfs_eval(input->cadr); */
/* 					} */
/* 					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number !=0){ */
/* 						resultat->this.number=input->cadr->this.number; */
/* 						input=input->this.pair.cdr; */
/* 					} */
/* 					if(input->cadr->type==SFS_NUMBER && input->cadr->this.number ==0) */
/* 					{ */
/* 					ERROR_MSG("Division par 0 impossible"); */

/* 					} */
/* 					if(input->cadr->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->cadr, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 						input=input->this.pair.cdr; */
/* 					} */
/* 				} */
/* 				while(input->this.pair.cdr->type!=SFS_NIL) */
/* 				{ */
/* >>>>>>> Stashed changes */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* <<<<<<< Updated upstream */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=recherche(env,input->this.pair.car->this.symbol); */
/* 						if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							operande1->this.number.=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 						operande1->this.number=input->this.pair.car->this.number; */
/* 					} */
/* 					else { */
/* 					    WARNING_MSG("Pas de nombre à comparer"); */
/* 					    return nil; */
/* 					} */
/* 				} */
				
/* 				while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){ */

/* 					if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 						input=input->this.pair.cdr; */
/* 						if(input->this.pair.car->type==SFS_PAIR){ */
/* 							input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 						} */
/* 						if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 							p=recherche(env,input->this.pair.car->this.symbol); */
/* 							if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 								operande2->this.number=p->this.pair.cdr->this.number.; */
/* 							} */
/* 							else { */
/* 							    WARNING_MSG("Pas de nombre à comparer"); */
/* 							    return nil; */
/* 							} */
/* 						} */
/* 						else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 							operande2->this.number.=input->this.pair.car->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					resultat->this.boolean= (operande1->this.number < operande2->this.number) ? TRUE:FALSE; */
/* 					operande1->this.number. = operande2->this.number; */
/* 				} */
/* 				return resultat; */
/* } */

/* object sup(object input, object env) */

/* { */
/* 				object p=creer_env(); */
/* 				object resultat=make_object(SFS_BOOLEAN); */
/* 				resultat->this.boolean=TRUE; */
/* 				object operande1=make_object(SFS_NUMBER); */
/* 				object operande2=make_object(SFS_NUMBER); */
/* ======= */
/* 					if(input->this.pair.car->type==SFS_NUMBER) */
/* 					{ */
/* 						resultat->this.number/=input->this.pair.car->this.number; */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_variable(input->this.pair.car, env); */
/* 						if(p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							resultat->this.number/=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else ERROR_MSG("%s ne peut être un opérande !",p->this.pair.car->this.symbol); */
/* 					} */
/* 				}return resultat; */
/* } */

/* /\* */

/* object egal(object input, object env) */

/* { */
/* 				object p=create_environment(); */
/* 				object resultat=make_boolean(1); */
/* 				object operande1=make_integer(1); */
/* 				object operande2=make_integer(1); */
				
/* >>>>>>> Stashed changes */
				
/* 				if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=research_environment(input->this.pair.car->this.symbol, env); */
/* 						if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							operande1->this.number=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 						operande1->this.number=input->this.pair.car->this.number; */
/* 					} */
/* 					else { */
/* 					    WARNING_MSG("Pas de nombre à comparer"); */
/* 					    return nil; */
/* 					} */
/* 				} */
				
/* <<<<<<< Updated upstream */
/* 				if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 					input=input->this.pair.cdr; */
/* 					if(input->this.pair.car->type==SFS_PAIR){ */
/* 						input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 					} */
/* 					if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 						p=recherche(env,input->this.pair.car->this.symbol); */
/* 						if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 							operande1->this.number=p->this.pair.cdr->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* 					else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 						operande1->this.number=input->this.pair.car->this.number; */
/* 					} */
/* 					else { */
/* 					    WARNING_MSG("Pas de nombre à comparer"); */
/* 					    return nil; */
/* 					} */
					
/* 				} */
				
/* ======= */
/* >>>>>>> Stashed changes */
/* 				while(input->this.pair.cdr->type!=SFS_NIL && resultat->this.boolean==TRUE){ */

/* 					if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 						input=input->this.pair.cdr; */
/* 						if(input->this.pair.car->type==SFS_PAIR){ */
/* 							input->this.pair.car=sfs_eval(input->this.pair.car); */
/* 						} */
/* 						if(input->this.pair.car->type==SFS_SYMBOL){ */
/* 							p=recherche(env,input->this.pair.car->this.symbol); */
/* 							if(p!=NULL && p->this.pair.cdr->type==SFS_NUMBER){ */
/* 								operande2->this.number=p->this.pair.cdr->this.number; */
/* 							} */
/* 							else { */
/* 							    WARNING_MSG("Pas de nombre à comparer"); */
/* 							    return nil; */
/* 							} */
/* 						} */
/* 						else if(input->this.pair.car->type==SFS_NUMBER){ */
/* 							operande2->this.number=input->this.pair.car->this.number; */
/* 						} */
/* 						else { */
/* 						    WARNING_MSG("Pas de nombre à comparer"); */
/* 						    return nil; */
/* 						} */
/* 					} */
/* <<<<<<< Updated upstream */
/* 					resultat->this.boolean= (operande1->this.number > operande2->this.number) ? TRUE:FALSE; */
/* 					operande1->this.number = operande2->this.number; */
/* 				} */
/* 				return resultat; */
/* } */

/* object est_null(object input){ */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(resultat->this.boolean && input->this.pair.cdr->type!=SFS_NIL){ */
/* 		if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 		    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		    resultat->this.boolean= (input->cadr->type==SFS_NIL) ? TRUE:FALSE; */
/* 		} */
/* 		input=input->this.pair.cdr; */
/* 	} */
/* 	return resultat; */
/* } */

/* object est_boolean(object input){ */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(resultat->this.boolean && input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 		if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 		    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		    resultat->this.boolean= (input->cadr->type==SFS_BOOLEAN) ? TRUE:FALSE; */
/* 		} */
/* 		input=input->this.pair.cdr; */
/* 	} */
/* 	return resultat; */
/* } */

/* object est_symbol(object input){ */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(resultat->this.boolean && input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 		if(input->this.pair.cdr->type!=SFS_NIL){ */
/* 		    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		    resultat->this.boolean= (input->cadr->type==SFS_SYMBOL) ? TRUE:FALSE; */
/* 		}input=input->this.pair.cdr; */
/* 	} */
/* 	return resultat; */
/* } */

/* object est_pair(object input) */
/* { */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 	    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		if (input->cadr->type==SFS_PAIR) */
/* 		{ */
/* 			resultat->this.boolean=TRUE; */
			
/* 		} */

/* 		else */
/* 		{ */
/* 			resultat->this.boolean=FALSE; */
/* 			return resultat; */
/* 		}input=input->this.pair.cdr; */
/* 	}return resultat; */

/* } */

/* object est_string(object input) */
/* { */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 	    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		if (input->cadr->type==SFS_STRING) */
/* 		{ */
/* 			resultat->this.boolean=TRUE; */
		
/* 		} */

/* 		else */
/* 		{ */
/* 			resultat->this.boolean=FALSE; */
/* 			return resultat; */
/* 		} */

/* 		input=input->this.pair.cdr;	 */
/* 	}return resultat; */

/* } */

/* object est_character(object input) */
/* { */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 	    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		if (input->cadr->type==SFS_CHARACTER) */
/* 		{ */
/* 			resultat->this.boolean=TRUE; */
			
/* 		} */

/* 		else */
/* 		{ */
/* 			resultat->this.boolean=FALSE; */
/* 			return resultat; */
/* 		}input=input->this.pair.cdr; */
/* 	}return resultat; */
/* } */

/* object est_integer(object input) */
/* { */
/* 	object resultat=make_integer(1); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 	    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		if (input->cadr->type==SFS_NUMBER) */
/* 		{ */
/* 			resultat->this.boolean=TRUE; */
		
/* 		} */

/* 		else */
/* 		{ */
/* 			resultat->this.boolean=FALSE; */
/* 			return resultat; */
/* 		}input=input->this.pair.cdr; */
/* 	}return resultat; */

/* } */

/* object est_primitive(object input) */
/* { */
/* 	object p=creer_env(); */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	resultat->this.boolean=TRUE; */
/* 	while(input->this.pair.cdr->type!=SFS_NIL) */
/* 	{ */
/* 	    if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		p=recherche(env,input->cadr->this.symbol); */

/* 		if (p->this.pair.cdr->type==SFS_PRIMITIVE) */
/* 		{ */
/* 			resultat->this.boolean=TRUE; */
		
/* 		} */

/* 		else */
/* 		{ */
/* 			resultat->this.boolean=FALSE; */
/* 			return resultat; */
/* 		}input=input->this.pair.cdr; */
/* 	}return resultat; */
	
/* } */

/* object conv_char_to_integer(object input){ */
/* 	object resultat=make_object(SFS_NUMBER); */
/* 	if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 	if(input->cadr->type==SFS_CHARACTER){ */
/* 		resultat->this.number=(int)input->cadr->this.character; */
/* 		return resultat; */
/* 	} */
/* 	WARNING_MSG("Vous essayez de convertir un type qui n'est pas un caractère"); */
/* 	return input; */
/* } */

/* object conv_integer_to_char(object input){ */
/* 	object resultat=make_object(SFS_CHARACTER); */
/* 	if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 	if(input->cadr->type==SFS_NUMBER){ */
/* 		resultat->this.character=input->cadr->this.number; */
/* 		return resultat; */
/* 	} */
/* 	WARNING_MSG("Vous essayez de convertir un type qui n'est pas un nombre"); */
/* 	return input; */
/* } */

/* object conv_number_to_string(object input){ */
/* 	object result=make_object(SFS_STRING); */
/* 	if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 	if(input->cadr->type==SFS_NUMBER){ */
/* 		sprintf(result->this.string,"%d",input->cadr->this.number); */
/* 		return result; */
/* 	} */
/* 	WARNING_MSG("Vous essayez de convertir un type qui n'est pas un nombre"); */
/* 	return input; */
/* } */

/* object conv_string_to_symbol(object input) */
/* {	 */

/* 	object resultat=make_object(SFS_SYMBOL); */
	

/* 	if(input->cadr->type==SFS_PAIR) */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 	} */

/* 	if(input->cadr->type==SFS_STRING) */
/* 	{ */
/* 		strcpy(resultat->this.symbol,input->cadr->this.string); */
/* 		return resultat; */
/* 	}  */

/* 	else ERROR_MSG("Vous essayez de convertir type qui n'est pas une chaine de caractère"); */
	
/* } */

/* object conv_symbol_to_string(object input) */
/* { */
/* 	object resultat=make_object(SFS_STRING); */

/* 	if(input->cadr->type==SFS_PAIR) */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 	} */

/* 	if(input->cadr->type==SFS_SYMBOL) */
/* 	{ */
/* 		strcpy(resultat->this.string,input->cadr->this.symbol); */
/* 		return resultat; */
				
/* 	}  */

/* 	else ERROR_MSG("Vous essayez de convertir type qui n'est pas un symbol"); */

	
/* } */

/* object conv_string_to_number(object input) */
/* { */
/* 	object resultat=make_object(SFS_NUMBER); */
/* 	int i=0; */

/* 	if(input->cadr->type==SFS_PAIR) */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 	} */

/* 	if(input->cadr->type==SFS_STRING) */
/* 	{ */
/* 		while(i<strlen(input->cadr->this.string)) */
/* 		{ */
/* 			resultat->this.number.+=((int)(input->cadr->this.string[i])); */
/* 			i++; */
/* 		}return resultat; */

/* 	} */
/* return input; */

/* } */

/* object car(object input){ */
/* 	if (input->cadr->type==SFS_PAIR)  */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 		if(input->cadr->type==SFS_PAIR)return input->cadr->this.pair.car; */
/* 	} */
	
/* 	WARNING_MSG("Ce n'est pas une paire"); */
/* 	return input; */
/* } */

/* object cdr(object input){ */
/* 	if (input->cadr->type==SFS_PAIR) */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 		if(input->cadr->type==SFS_PAIR) return input->cadr->this.pair.cdr; */
/* 	} */
	
/* 	WARNING_MSG("Ce n'est pas une paire"); */
/* 	return input; */
/* } */

/* object set_car(object input) */
/* { */
/* 	object env_courant=creer_env(); */
/* 	env_courant=env; */

/* 	if(input->cadr->type==SFS_PAIR && input->cadr->this.pair.car->type==SFS_SYMBOL) */
/* 	{ */
/* 		object p=creer_env(); */
/* 		p=recherche_env(env_courant,input->cadr->this.pair.car->this.symbol); */
/* 		if(p!=NULL) */
/* 		{ */
/* 			p->this.pair.cdr=sfs_eval(input->caddr); */
/* 			return env_courant; */

/* 		} */

/* 		else WARNING_MSG("Erreur de syntaxe"); */
/* 	} */

/* 	else WARNING_MSG("Erreur de syntaxe"); */
/* 	return input; */
/* } */


/* object set_cdr(object input) */
/* { */
/* 	object env_courant=creer_env(); */
/* 	env_courant=env; */

/* 	if(input->cadr->type==SFS_PAIR && input->cadr->cadr->type==SFS_SYMBOL) */
/* 	{ */
/* 		object p=creer_env(); */
/* 		p=recherche_env(env_courant,input->cadr->cadr->this.symbol); */
/* 		if(p!=NULL) */
/* 		{ */
/* 			p->this.pair.cdr=sfs_eval(input->caddr); */
/* 			return env_courant; */

/* 		} */

/* 		else WARNING_MSG("La variable n'est pas définie"); */
/* 	} */
/* 	else WARNING_MSG("Erreur de syntaxe"); */

/* 	return input; */
/* } */

/* object new_list(object input) */
/* { */
/* 	object new_list=make_object(SFS_PAIR); */
/* 	if(input->cadr->type==SFS_PAIR) */
/* 	{ */
/* 		input->cadr=sfs_eval(input->cadr); */
/* 	} */
/* 	else */
/* 	{ */
/* 		new_list=input->this.pair.cdr; */
/* 		return new_list; */
/* 	}return input; */
		
/* } */
/* *\/ */
/* /\* Test si deux object sont identiques*\/ */
/* /\* */
/* object eq_poly(object input) */
/* { */
/* 	object resultat=make_object(SFS_BOOLEAN); */
/* 	object env_courant=creer_env(); */
/* 	env_courant=env; */

/* 	while(input->cddr->type!=SFS_NIL) */
/* 	{	 */
/* 		/\* on remplace les éléments non auto évaluants (les pairs et les symbols) par leur valeur *\/ */
/* 		if(input->cadr->type==SFS_PAIR) input->cadr=sfs_eval(input->cadr); */
/* 		if(input->caddr->type==SFS_PAIR) input->caddr=sfs_eval(input->caddr); */
/* 		if(input->cadr->type==SFS_SYMBOL) input->cadr=association(env_courant,input->cadr); */
/* 		if(input->caddr->type==SFS_SYMBOL) input->caddr=association(env_courant,input->caddr); */
		
/* 		/\* on regarde si les types sont égaux *\/ */
/* 		if(input->cadr->type==input->caddr->type) */
/* 		{	 */
/* 			switch(input->cadr->type) */
/* 			{		 */
/* 				case 0x00 :  */
/* 					if(input->cadr->this.number==input->caddr->this.number)  */
/* 					resultat->this.boolean=1; */
						
/* 					else  */
/* 					{ */
/* 						resultat->this.boolean=FALSE; */
						
/* 						return resultat; */
/* 					}break; */

/* 				case 0x01 : */
/* 					if(input->cadr->this.character==input->caddr->this.character)  */
/* 						resultat->this.boolean=TRUE; */
/* 					else  */
/* 					{ */
/* 						resultat->this.boolean=FALSE; */
/* 						return resultat; */
/* 					}break; */

/* 				case 0x02 :  */
/* 					if(!strcmp(input->cadr->this.string,input->caddr->this.string))  */
/* 						resultat->this.boolean=TRUE; */
/* 					else  */
/* 					{ */
/* 						resultat->this.boolean=FALSE; */
/* 						return resultat; */
/* 					}break; */
				
/* 				case 0x04 : */
/* 					resultat->this.boolean=TRUE; */
/* 					break; */

/* 				case 0x05 :  */
/* 					if(input->cadr->this.boolean==input->caddr->this.boolean)  */
/* 						resultat->this.boolean=TRUE; */
/* 					else  */
/* 					{ */
/* 						resultat->this.boolean=FALSE; */
/* 						return resultat; */
/* 					}break; */
								
/* 				case 0x06 : */
/* 					if(!strcmp(input->cadr->this.symbol,input->caddr->this.symbol))  */
/* 						resultat->this.boolean=TRUE; */
/* 					else  */
/* 					{ */
/* 						resultat->this.boolean=FALSE; */
/* 						return resultat; */
/* 					}break; */
									
/* 			} */
/* 			input=input->this.pair.cdr; */
			
/* 		} */
/* 		else{ */
/* 			resultat->this.boolean=FALSE; */
/* 			input=input->this.pair.cdr; */
/* 		} */
	
/* 	}return resultat; */

/* }*\/ */
/* ======= */
/* 					resultat->this.boolean= (operande1->this.number == operande2->this.number) ? TRUE:FALSE; */
/* 					operande1->this.number. = operande2->this.number; */
/* 				} */
/* 				return resultat; */
/* } */
/* *\/ */
/* >>>>>>> Stashed changes */
