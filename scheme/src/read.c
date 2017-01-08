
/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include "read.h"




void flip( uint *i ) {

  if ( *i == FALSE ) {
    *i = TRUE;
  }
  else {
    *i = FALSE;
  }
}

/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line) {

  int i=0;
  if (line == NULL) {
    return NULL;
  }
  i = 0;
  /* on saute les espaces */
  while(line[i] != '\0' && isspace(line[i])) {
    i++;
  }
  /* si fin de ligne => ligne inutile */
  if(line[i] == '\0') {
    return NULL;
  }
  /* si premier caractere non espace est ';' => ligne inutile */
  if(line[i] == ';') {
    return NULL;
  }
  return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que 
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
  NOTHING,        /* rien n'a ete trouve encore.. */
  STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
  BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
  S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
  FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
  int       parlevel = 0;
  uint      in_string = FALSE;
  uint      s = 0;
  char      k[BIGSTRING];
  char      *ret = NULL;
  char      *chunk = NULL;
  uint      i = 0;
  string    sfs_prompt;

  EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

  parlevel = 0;
  memset( input, '\0', BIGSTRING );

  do {
    ret = NULL;
    chunk=k;
    memset( chunk, '\0', BIGSTRING );

    /* si en mode interactif*/
    if ( stdin == fp ) {
      uint nspaces = 2*parlevel;

      init_string( sfs_prompt );

      /* le prompt indique le niveau de parenthese
	 et decale la prochaine entrée en fonction
	 de ce niveau (un peu à la python)*/
      sprintf( sfs_prompt, "SFS:%u > ", parlevel );

      for ( i= 0; i< nspaces; i++ ) {
	sfs_prompt[strlen(sfs_prompt)] = ' ';
      }

      /* si sur plusieurs lignes, le \n équivaut à un espace*/
      if (nspaces>0) {
	input[strlen(input)+1] = '\0';
	input[strlen(input)] = ' ';
      }

      /*saisie de la prochaine ligne à ajouter dans l'input*/
      printf("%s",sfs_prompt);
      ret = fgets( chunk, BIGSTRING, fp );
      if (ret && chunk[strlen(chunk)-1] == '\n') chunk[strlen(chunk)-1] = '\0';

    }
    /*si en mode fichier*/
    else {
      ret = fgets( chunk, BIGSTRING, fp );

      if ( NULL == ret ) {
	/* fin de fichier...*/
	if ( parlevel != 0 ) {
	  WARNING_MSG( "Parse error: missing ')'" );
	  return S_KO;
	}
	return S_END;
      }

      if (strlen(chunk) == BIGSTRING-1
	  && chunk[BIGSTRING-1] != '\n'
	  && !feof(fp)) {
	WARNING_MSG( "Too long line for this interpreter!" );
	return S_KO;
      }
    }

    /* si la ligne est inutile 
       => on va directement à la prochaine iteration */
    if (first_usefull_char(chunk) == NULL) {
      continue;
    }


    s = strlen( chunk );

    if ( s > 0 ) {
      if (strlen(input) + s > BIGSTRING-1 ) {
	WARNING_MSG( "Too long a S-expression for this interpreter!" );
	return S_KO;
      }

      for ( i = 0; i< strlen(chunk); i++ ) {
	/* si la fin de la ligne chunk est inutile,
	   on ajoute un espace dans input et on sort de la boucle*/
	if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
	  chunk[i]='\0';
	  input[strlen(input)] = ' ';
	  break;
	}


	switch(chunk[i]) {
	case '(':
	  if (in_string == FALSE
	      && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
	    parlevel++;
	    typeOfExpressionFound = S_EXPR_PARENTHESIS;
	  }
	  break;
	case ')':
	  if ( in_string == FALSE
	       && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
	    parlevel--;
	    if (parlevel == 0 ) {
	      typeOfExpressionFound = FINISHED;
	    }
	    if ( parlevel < 0 ) {
	      WARNING_MSG( "Parse error : cannot start with ')'" );
	      return S_KO;
	    }
	  }
	  break;
	case '"':
	  if ( i<2 || chunk[i-1] != '\\' ) {
	    if ( in_string == FALSE ) {
	      if(typeOfExpressionFound == BASIC_ATOME) {
		WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
		return S_KO;
	      }
	      in_string = TRUE;
	      if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
		typeOfExpressionFound = STRING_ATOME;
	      }
	    }
	    else {
	      in_string = FALSE;
	      if(typeOfExpressionFound == STRING_ATOME) {
		typeOfExpressionFound = FINISHED;
	      }
	    }
	  }
	  break;
	default:
	  if(in_string == FALSE) {
	    if(isspace(chunk[i])) {
	      if(typeOfExpressionFound == BASIC_ATOME) {
		typeOfExpressionFound = FINISHED;
	      }
	    } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
	      typeOfExpressionFound = BASIC_ATOME;
	    }
	  }
	  break;
	}


	if(typeOfExpressionFound == FINISHED) {
	  char *first_useful = first_usefull_char(chunk + i + 1);
	  if( first_useful != NULL) {
	    if(*first_useful == ')' ) {
	      WARNING_MSG( "Parse error: too many closing parenthesis')'" );
	    }
	    else {
	      WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
	    }
	    return S_KO;
	  }
	}

	/* recopie char par char*/
	input[strlen(input)] = chunk[i];
      }
      if(in_string == TRUE) {
	WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
	return S_KO;
      }
    }


    if ( parlevel > 0 && fp != stdin ) {
      if ( feof( fp ) ) {
	WARNING_MSG( "Parse error: missing ')'" );
	return S_KO;
      }

      if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
    }
  } while ( parlevel > 0 );

  /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
  while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';

  return S_OK;
}

void skip_blanks(char* input, uint * here){
  while(isspace(input[*here])){(*here)++; }
}

object sfs_read( char *input, uint *here ) {
  skip_blanks(input,here);
  if ( input[*here] == '(' ) {
    if ( input[(*here)+1] == ')' ) {
      *here += 2;
      return nil;
    }
    else {
      (*here)++;
      return sfs_read_pair( input, here );
    }
  }
  else {
      
    return sfs_read_atom( input, here );
  }
}




void get_atom(char* input, uint *here, char* str){ /* On récupère la chaine de caractères entre 2 espaces */
  uint indice =0;
  while (isspace(input[*here]) && input[*here] != '\0') (*here)++;
  
  if(input[*here]=='\'') {
  	strcpy(str,input);
  	DEBUG_MSG("valeur de string : %s",str);
  	DEBUG_MSG("BYPASS");
  	}
  
  if(input[*here]=='"'){
    do{
      str[indice] = input[*here];
      if(input[*here]=='\\'){
	if(input[(*here)+1]=='"' && (*here)>0){ 
	  str[indice]='"';
	  (*here)++;
	}
      }
      (*here)++;
      indice ++;
    }while (input[*here] != '"' && input[*here]!='\0');
    str[indice]=input[(*here)];
    (*here)++; /* incrementation pour etre sur l'espace ou la parenthese fermante */
    	
    if(indice<BIGSTRING) str[indice +1] == '\0';
    else{
      str[BIGSTRING-1]='\0';
      WARNING_MSG("Chaine de caractere trop longue");
    }
  }
  else{
    while (isspace(input[*here]) == 0 && input[*here]!='\0' && input[*here]!='"') {
      if(input[*here]=='('|| input[*here]==')'){
	if(*here > 0){
	  if(input[(*here)-1]!='\\') break;
	}
      }
      str[indice] = input[*here];
      if(input[*here]=='\\'){
		if(input[(*here)-1]=='#' && input[(*here)+1]=='"' && (*here)>0){
		str[indice]='\\';
		str[indice+1]='"';
		indice++;
		(*here)++;
		}
		}
		(*here)++;
      indice ++;
    }
    if(indice<BIGSTRING) str[indice] == '\0';
    else{
      str[BIGSTRING-1]='\0';
      WARNING_MSG("Chaine de caractere trop longue");
    }
  }
}

/* Detecte les operateurs arithmetiques simples */
uint is_arithemetic_op(char c){

  if(c=='+' || c=='-' || c=='*' || c== '/') return 1;
  else return 0;

}

/* Detecte le caractere espace en scheme */
uint is_scm_space(char* str, uint indice){
  if(str[indice+2] =='s'){ /*Lecture des espaces */
    char *str_bis = str + 2;
    if(strcmp(str_bis,"space")==0){
      return 1; 
    }
  }
  return 0;
}

/* Detecte le caractere retour a la ligne en scheme */
uint is_scm_newline(char* str, uint indice){
  if(str[indice+2]=='n'){ /*lecture du retour de ligne */
    char *str_bis = str + 2;
    if(strcmp(str_bis, "newline")==0){
      return 1;
    }
  }
  return 0;
}

object sfs_read_atom( char *input, uint *here ) { /* *here est le compteur pour savoir quel caractère on est en train de lire, initialisé à 0 pour le 1er caractère de l'atome S-expression */
 
  /*object atom = NULL;*/
  char str[BIGSTRING]="";
  uint indice = 0;
  /*int val= 0;*/
DEBUG_MSG("valeur de input1 : %s",input);
  get_atom(input, here, str);
  
  DEBUG_MSG("valeur de str1 : %s",str);
  
  if(input[indice] == '\''){ /*Gestion de la tranformation de 'abc en (quote abc)*/
  		char quote[256] = "";
  		strcpy(quote, "(quote ");
  		DEBUG_MSG("valeur de str : %s",str);
  		while(indice < strlen(input)+1){ 
  			quote[indice+7]=input[indice+1]; 
  			indice++;
  			}
  		
  		quote[strlen(input)+6]=')';
  		/*quote[strlen(str)+7]='\0';*/
  		DEBUG_MSG("valeur de quote : %s",quote);
  		(*here)=0;
  		
  		return sfs_read(quote, here);
  		}
  
  else if(str[indice] == '"'){ /*lecture des string */
    return make_string(str);
  }
	
	
  else if(str[indice] == '#'){ /*lecture des caractères */;
    switch(str[indice+1]){
    case 't':
      if(str[indice+2]!='\0'){
	WARNING_MSG("Parser error incorrect boolean");
	break;
      }
      else{
	return make_boolean(TRUE);
      }
    case 'f':
      if(str[indice+2]!='\0'){
	WARNING_MSG("Parser error incorrect boolean");
	break;
      }
      else{
	return make_boolean(FALSE);
      }
    case '\\': /* code ASCII de backslash */
      if(is_scm_space(str,indice)){ /*Lecture des espaces */
	return make_string(str); 
      }       
      if(is_scm_newline(str,indice)){ /*lecture du retour de ligne */
	return make_string(str);
      }
      if(str[indice+3]!='\0'){
	WARNING_MSG("Parser error incorrect character");
	break;
      }
      else if(isdigit(str[indice+2])){
	return make_character(str[indice+2]); 
      }	    
      else { /* lecture des autres caractères */
	return make_character(str[indice+2]);
      }
    default : break;
    }
  }
  else if(is_arithemetic_op(str[indice]) && str[indice+1] =='\0'){
    char s[2];
    s[0] = str[indice];
    s[1] = '\0';
    DEBUG_MSG("s = %s",s);
    return /*make_arith_op(str[indice]);*/ make_symbol(s);
  }
  else if(str[indice] == '+' || str[indice]=='-'){ /*lecture des nombres */ /* pas de prise en compte d'un depassement de capacite */
    int i;
    for(i = indice + 1 ; i<strlen(str)-1; i++) {
      if (isdigit(str[i])){
	i++;
      }
      else{
	WARNING_MSG("parser error: incorrect number");
	return NULL;
      }
    }
    
    int value = strtol(str, NULL, 10);
    int err_val = errno;
    if(err_val==ERANGE && str[indice]=='+'){
      errno=0;
      WARNING_MSG("OVERFLOW");
      return make_string("+inf");
    }
    else if(err_val==ERANGE && str[indice]=='-'){
      errno=0;
      WARNING_MSG("OVERFLOW");
      return make_string("-inf");
    }
    else{
      return make_integer(value);
    }
  }
  else if(isdigit(str[indice])){
    int i;
    for(i = indice ; i<strlen(str); i++) {
      if (isdigit(str[i])){
	i++;
      }
      else{
	WARNING_MSG("parser error: incorrect number");
	return NULL;
      }
    }
    
    int value = strtol(str, NULL, 10);
    int err_val = errno;
    if(err_val==ERANGE){
      WARNING_MSG("OVERFLOW");
      errno=0;
      return make_string("+inf");
    }
    else{
      return make_integer(value);
    }
     }
     
  /*else if(ispunct(str[indice]) && str[indice]=='\0'){
    return make_special_atom(str[indice]); en attendant de savoir ce qu'on en fait ^^ 
  }*/
  
 
  	
  	
  		
    else return make_symbol(str);
	
  /*else {
    return make_string(str);  cas fourre tout a ameliorer au plus vite 
  }*/
  return NULL;     
}

/* La fonction est capable de retourner et de stocker le type correct de l'objet, sans erreur de syntaxe cependant */

object sfs_read_pair( char *stream, uint *i ) {

  object p=make_pair();
 
  object car;
  object cdr;
	
  skip_blanks(stream, i);
  if(stream[(*i) ]== ')') return nil;
  
  car=sfs_read(stream, i);
  skip_blanks(stream, i);
	
  if(stream[(*i)] == ')') {cdr=make_nil();
    (*i)++;
  }
		
  else{
	
    cdr=sfs_read_pair(stream,i);
  }
			
  p->this.pair.car=car;
  p->this.pair.cdr=cdr;
  return p;	
}
