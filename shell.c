#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

//Shell program which executes unix commands. 
int main()
{
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		char input[100];
		printf("$$$");

		//get input
		fgets( input, 100, stdin );
		if ( strcmp( input, "exit\n" ) == 0 )
		{
			exit(1);
		}

		//overwrites newline & parses the string
		input[strlen(input) - 1] = '\0';
		char* args[100];
		int i = 0;
		args[i] = strtok( input, " " );
		while ( ( args[++i] = strtok(NULL, " " )));
		if (strcmp( args[0], "cd" ) == 0)
		{
			mkdir( args[1], 0744 );
			chdir( args[1] );
		}
		//forks a child process
		int forkrv;
		forkrv = fork();

		if (forkrv < 0)
		{
			perror("problem with forking");
		}
		else if (forkrv > 0)
		{
			int waitrv;
			int a;
			waitrv = wait(&a);
		}
		else
		{
			execvp(args[0], args);
		}
	}
}