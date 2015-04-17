#include "shell.h"

extern char ** getln();

int main() {
	char ** args; //commands and arguments
	char cwd[1024];

	while( 1 ) { //infinte input loop
		getcwd( cwd, sizeof(cwd));
		printf("%s $/> ", cwd);
		args = getln();
		if ( argc_get( args ) > 0 )
			execute( args );		
	}
}

int argc_get( char ** args ) {
	int i;
	for ( i = 0; args[i] != NULL; i++);
	return i;
}

int execute( char ** args ) {
	pid_t pid;
	int background = 0;
	int argc = argc_get( args );

	if ( strcmp(args[0], "exit") == 0 ) { //exit command
		exit(0);
	}
	if ( localCmd( args ) == 1 ) {
		return 1;
	}
	if ( strcmp(args[argc_get(args)-1], "&") == 0 ) { //if the last arg is an ampersand
		args[argc_get(args)-1] = NULL; //getting rid of ampersand
		background = 1;
	}
	pid = fork();
	if ( pid == 0 ) { //child process 
		if ( argc > 2 && (strcmp(args[argc-2], ">") == 0 || strcmp(args[argc-2], "<") == 0 ) ) { //IO redirection
			switch ( args[argc-2][0] ) {
				case '>': //redirecting output to a file
					freopen( args[argc-1], "w+", stdout );
					args[argc - 1] = NULL;
					args[argc - 2] = NULL;
					break;
				case '<': //redirecting input from a file
					freopen( args[argc-1], "r", stdin );
					args[argc - 1] = NULL;
					args[argc - 2] = NULL;
					break;
				default: //NOOP 
					break;
			}
		}
		execvp(args[0], args);
		exit(127); //exiting if evec fails
	} else { //parent
		if ( background == 1 ) {
			printf("& PID: %d\n", pid );
		} else {
			waitpid(-1, NULL, 0);	
		}
	}

	return 1;
}

int localCmd( char ** args ) {
	if ( strcmp(args[0], "add") == 0 ){
		LCadd( args ); 
		return 1;
	}
	if ( strcmp(args[0], "arg") == 0 ){
		LCarg( args );
		return 1;
	}
	if ( strcmp(args[0], "cd") == 0 ){
		LCcd( args );
		return 1;
	}
	return 0;
} 

void LCadd( char ** args ) {
	int sum = 0;
	int argc = argc_get( args );
	int i;
	for ( i = 1; i < argc ; i++)
		sum += strtol(args[i], NULL, 0); //adding to total
	for ( i = 1; i < argc; i++) {
		printf("%s", args[i] );
		if ( i == argc - 1 ) {
			printf(" = ");
		} else {
			printf(" + ");
		}
	}
	printf("%d\n", sum );
}

void LCarg( char ** args ) {
	int i;
	printf("argc = %d, args = ", argc_get(args) );
	for ( i = 1; args[i] != NULL; i++)
		printf("%s ", args[i] );
	printf("\n");
}

void LCcd( char ** args ) {
	int err = chdir( args[1] );
	switch( err ) {
		case ENOENT: printf("Not a valid path.\n"); break;
		case ENOTDIR: printf("Item is not a directory.\n"); break;
		default:
			//NOOP
			break;
	}
}
