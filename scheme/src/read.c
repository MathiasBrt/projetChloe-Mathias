
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

#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"
#include "print.h"



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
        chunk = NULL;

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
            chunk = readline( sfs_prompt );
        }
        /*si en mode fichier*/
        else {
            chunk=k;
            memset( chunk, '\0', BIGSTRING );
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

    if(stdin == fp) {
        add_history( input );
    }
    return S_OK;
}


/*
 * Effectue la décomposition analytique de l'entrée input.
 * Cette fonction ne conserve aucune information autre que les atomes et les paires : pas de mémorisation de
 * parenthèses ni d'espaces et tabulations.
 * Cette fonction et sfs_read_pair s'appellent mutuellement.
 * Si on lit un couple de parentheses, l'objet nil est retourné.
 * Si on lit une parenthese ouvrante, sfs_read_pair est appelée.
 * Sinon, c'est sfs_read_atom.
 */
object sfs_read( char *input, uint *here ) {
    while ( input[*here] == ' ' || (int)input[*here]==9) (*here)++;
    if ( input[*here] == '(' ) {
    	(*here)++;
    	while ( input[*here] == ' ' || (int)input[*here]==9 ) (*here)++;
        if ( input[(*here)] == ')' ) {
            *here += 1;
            return nil;
        }
        else {
            return sfs_read_pair( input, here );
        }
    }
    if  ( input[*here] == ')' ) {
        return nil;
    }
    else {
        return sfs_read_atom( input, here );
    }
}


/*
 * Cette fonction parcourt l'entrée input jusqu'à la lecture d'un atome complet. Elle est appelée par sfs_read.
 * Le premier caractere lu donne une indication sur le type à chercher. Le code ASCII est utilisé pour l'analogie
 * entre les entiers et les caracteres.
 * À la fin d'une lecture, here pointe sur le caractere de input qui suit l'atome lu.
 */

object sfs_read_atom( char *input, uint *here ) {

    object atom = NULL;
    int ascii = (int) input[*here];
    string buffer;
    int buffer_counter=0;
    int echappement=0; /* concerne l'echappement de \ */

    /* lecture d'un # */
    if (ascii==35){
        if (input[((*here)+1)]=='t' || input[((*here)+1)]=='f'){
            (*here)+=2;
            if(input[(*here)]=='\0' || input[(*here)]==' ' || (int)input[(*here)]==9 || input[*(here)]==')'){
                atom = make_object(SFS_BOOLEAN);
                atom->this.boolean= (input[(*here)-1]=='t') ? TRUE:FALSE;
            }
            else WARNING_MSG( "Could not read valid atom expression" );
            return atom;
        }
        if (input[((*here)+1)=='\\']){
            
            atom = make_object(SFS_CHARACTER);
            (*here)+=2;
            while(*here<strlen(input) && input[*here]!=' ' && (int)input[(*here)]!=9 && input[*here]!=')'){
                 
                 buffer[buffer_counter]=input[*here];
                 buffer_counter++;
                 (*here)++;
            }
            if (buffer_counter==0){
                 WARNING_MSG( "Could not read valid atom expression" );
                 return NULL;
            }
            if (buffer_counter==1){
                 atom->this.character=buffer[0]; /* un seul caractere lu */
                 return atom;
            }
            if (buffer_counter>1){
                 if (!strncmp(buffer,"space",buffer_counter)) atom->this.character=32; /* ascii de space */
                 else if (!strncmp(buffer,"newline",buffer_counter)) atom->this.character=10; /* ascii de newline */
                 else {
                     WARNING_MSG( "Could not read valid atom expression" );
                     return NULL;
                 }
                 return atom;
            }
        }
        else WARNING_MSG( "Could not read valid atom expression" );
        return NULL;
    }

    /* lecture de " */
    if (ascii==34){
        (*here)++;
        while(*here<strlen(input)){
            buffer[buffer_counter]=input[*here];
            if (input[*here]=='\\') echappement++;
            if (input[*here]!='\\' && echappement) echappement--; 
            if (buffer[buffer_counter]=='"' && buffer[buffer_counter-1]!='\\'){ /* si guillemets non echappees */
                atom=make_object(SFS_STRING);
                buffer[buffer_counter]='\0';
                strncpy(atom->this.string,buffer,strlen(buffer));
                (*here)++;
                return atom;
            }
            else if (buffer[buffer_counter]=='"' && buffer[buffer_counter-1]=='\\'){ /* si guillemets echappees */
                if (!echappement){
                    buffer_counter--;
                    buffer[buffer_counter]='"';
                }
                else {
                    atom=make_object(SFS_STRING);
                    buffer[buffer_counter]='\0';
                    strncpy(atom->this.string,buffer,strlen(buffer));
                    return atom;
                }
            }
            buffer_counter++;
            (*here)++;
        }
        return NULL;
    }

    /* lecture d'un +, d'un - ou d'un chiffre */
    if (ascii==43 || ascii==45 || (ascii>= 48 && ascii<=57))
    {
    	buffer[buffer_counter]=input[*here];
    	buffer_counter++;
        (*here)++;
        while((*here)<strlen(input) && (int)input[(*here)]!=32 && (int)input[(*here)]!=9 && (int)input[(*here)]!=41)
        {
            if((int)input[(*here)]< 48 || (int)input[(*here)]>57)
            {
             printf("\n>>>>>%d\n",input[(*here)]);
                WARNING_MSG( "Ce n'est pas un nombre" ); 
                return NULL;
            } 
        buffer[buffer_counter]=input[*here];
        buffer_counter++;
        (*here)++;    
        }
            num nombre;
            nombre.this.integer=atoi(buffer);
            atom = make_object( SFS_NUMBER ) ; 
            atom->this.number=nombre;
            return atom;
    }

    /* autre cas : lecture d'un caractère isolé i.e. un symbole */
    else {
        atom=make_object(SFS_SYMBOL);

        if((int)input[*here]==39)
            {
                char citation[256];
                strcpy(citation,"(quote ");

                while ((*here)<strlen(input))
                {

                    input[*here]=input[(*here)+1];
                    (*here)++;                    
                }
                strcat(citation,input);
                citation[strlen(citation)]=')';
                
                (*here)=0;
                return sfs_read(citation,here);

            }
        else 
        {   
            while((*here)<strlen(input) && input[*here]!=' ' && (int)input[(*here)]!=9 && input[*here]!=')'){
                buffer[buffer_counter]=input[*here];
                buffer_counter++;
                (*here)++;
            }
        buffer[buffer_counter]='\0';
        strcpy(atom->this.symbol,buffer);
        return atom;
        }
    }
    return NULL;
}


/*
 * Cette fonction est appelée par elle-même ou par sfs_read.
 * Elle crée une paire dont le car et le cdr sont nil. Le car est actualisé par sfs_read (et est donc un atome lu
 * par sfs_read_atom, ou une paire lue par sfs_read_pair). Le cdr est nécessairement une paire actualisée par 
 * sfs_read_pair.
 * Cette fonction ne garde mémoire d'aucun espace ou tabulation.
 * À la fin, here pointe sur le caractere qui suit une parenthese fermante (fin d'une paire).
 */

object sfs_read_pair( char *input, uint *here ) {

    object pair = NULL;
    pair = make_object(SFS_PAIR);
    pair->this.pair.cdr=nil;
    pair->this.pair.car=nil;
    pair->this.pair.car=sfs_read(input,here);
    while (input[*here]==' ' || (int)input[*here]==9) (*here)++;
    if (input[*here]!=')'){
    	
    	pair->this.pair.cdr=sfs_read_pair(input,here);
    	return pair;
   	}
   	(*here)++;
    return pair;
}

