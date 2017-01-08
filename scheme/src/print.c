
/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

void sfs_print_atom( object o ) {
DEBUG_MSG(" entrée dans la fonction print atom type de l' atome : %d  ",o->type);
  switch(o->type){
  case SFS_NUMBER:
    printf("%d",o->this.number);
    break;
  case SFS_CHARACTER:
    printf("#\\%c",o->this.character);
    break;
  case SFS_STRING:
    printf("%s",o->this.string);
    break;
  case SFS_NIL:
    printf("()");
    break;
  case SFS_BOOLEAN:
    if(o->this.boolean){
      printf("#t");
    }
    else {
      printf("#f");
    }
    break;  
  case SFS_SYMBOL:
    printf("%s",o->this.symbol);
    break;
  case SFS_ARITH_OP:
    printf("%c", o->this.character);
    break;
  case SFS_SPECIAL_ATOM:
    printf("%c", o->this.character);
    break;
  case SFS_VARIABLE_VALUE:
    DEBUG_MSG(" o type %d", o->this.pair.car->type);
    if( o->this.pair.car->type == SFS_PAIR){
      printf("(");
    }
      sfs_print(o->this.pair.car);
      break;
  default:
    printf("Erreur atome inconnu");
    break;
  }
}


void sfs_print_pair( object o ) {
  /*DEBUG_MSG(" entrée print pair type %d",o->type);*/
    
	if(o->this.pair.car->type == SFS_PAIR) printf("(");
	
    sfs_print(o->this.pair.car);
    
    if(o->this.pair.cdr->type == SFS_NIL) printf(")");
    
    if(o->this.pair.cdr->type != SFS_NIL)  {
    	printf(" ");
    	sfs_print(o->this.pair.cdr);
    	}

    	
	 }

	
	 
void sfs_print( object o ) {
  /*DEBUG_MSG(" entrée print ");*/
	if ( SFS_PAIR == o->type ) {

		sfs_print_pair( o );
    
  }	
	else {
    	sfs_print_atom( o );
  }

}

void sfs_print_expr( object o ){
  printf( "==> " );
  if(o->type==SFS_PAIR) printf("(");
  sfs_print( o );
  printf( "\n" );
}
