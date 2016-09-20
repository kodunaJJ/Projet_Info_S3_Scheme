
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

//Création d'un objet en spécifiant son type
object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

//CREATION DES FONCTIONS POUR VARIABLES GLOBALES

// Création d'une liste vide
// make_nil et make_empty_list vraiment identique ????
object make_empty_list( void ) {

    object t = make_object( SFS_NIL );

    t->this.special = t;

    return t;
}

//Création du booléen (TRUE / FALSE) basé sur le C
object make_boolean( unsigned int  val ){
	
	object t = make_object( SFS_BOOLEAN );
	
	if (val != 0) t->this.boolean =1; 
	else t->this.boolean = 0;

	return t;
}

//CREATION DES TYPES DE BASE

//Création des symboles
object make_symbol( char* sym ){
	
	object t = make_object( SFS_SYMBOL );
	strcpy(t->this.symbol, sym );
	return t;
}

//Création des entiers
object make_integer( num val ){
	object t = make_object( SFS_NUMBER );
	t->this.number = val;
	return t;
}

//Création des caractères
object make_character( char c ){
	object t = make_object( SFS_CHARACTER );
	t->this.character = c ;
	return t;
}

//Création des chaines de caractères
object make_string( char* str ){
	object t = make_object( SFS_STRING );
	strcpy(t->this.symbol, str );
	return t;
}

//Création des paires //comment définir la paire hors de l'objet ?
object make_pair( object *car, object *cdr ){
	object t = make_object( SFS_PAIR );
	t->this.pair.car = car ;
	t->this.pair.cdr = cdr ;

	return t;
}

// création de la fonction de lecture et de création d'arbre syntaxique

object read(char *c){

}
