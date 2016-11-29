
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"

/* Création d'un objet en spécifiant son type */
object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

/* CREATION DES FONCTIONS POUR VARIABLES GLOBALES A INITIALISER */

/* Création d'une liste vide */
object make_nil( void ) {

    object t = make_object( SFS_NIL );

    t->this.special = t;

    return t;
}

/* Création du booléen (TRUE / FALSE) basé sur le C */
object make_boolean( unsigned int  val ){
  
	object t = make_object( SFS_BOOLEAN );
	
	if (val != 0) t->this.boolean =TRUE; 
	else t->this.boolean = FALSE;
	return t;
}

/* CREATION DES TYPES DE BASE */

/* Création des symboles */
object make_symbol( char* sym ){
	
	object t = make_object( SFS_SYMBOL );
	strcpy(t->this.symbol, sym );
	return t;
}

/* Création des entiers */
object make_integer( int val ){
	object t = make_object( SFS_NUMBER );
	t->this.number = val;
	return t;
}

/* Création des caractères */
object make_character( char c ){
	object t = make_object( SFS_CHARACTER );
	t->this.character = c ;
	return t;
}

/* Création des chaines de caractères */
object make_string( char* str ){
	object t = make_object( SFS_STRING );
	strcpy(t->this.string, str );
	return t;
}

/* Création des paires //on utilise les pointeurs car et cdr */
object make_pair(){
	object t = make_object( SFS_PAIR );
	return t;
}

/* création des opérateur mathematiques simples pour l'instant */ 
object make_arith_op( char c ){
	object t = make_object( SFS_ARITH_OP );
	t->this.character = c ;
	return t;
}

/* Création des atoms ayant une fonction spéciale dans le langage comme @,^,~,... */
object make_special_atom( char c ){
	object t = make_object( SFS_SPECIAL_ATOM );
	t->this.character = c ;
	return t;
}

/* Création des primitives*/
