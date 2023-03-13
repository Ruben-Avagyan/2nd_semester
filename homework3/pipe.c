#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc , char** argv )
{
	int count = argc - 2 ; 

	if (count < 2 )
	{
		printf("%s" , "too few arguments \n" ) ;
		return 1;
	}

	int** pipefd = (int**)malloc(count * sizeof(int*));
    	
	for (int i = 0; i < 2; i++)
    	{
	    pipefd[i] = (int*)malloc(2 * sizeof(int));
	}
    
	
    	for (int i = 0 ; i < count ; ++i)
	{

		if (pipe(pipefd[i]) < 0 )
		{
			perror("pipe error!!!") ; 
			exit(1);
		}

		close(pipefd[i][0]) ; 
		close(pipefd[i][1]) ;
	}
	
   

	pid_t pid = fork() ; 

	if (pid < 0 )
	{
		perror ("Unable to fork!") ; 
		exit(1) ;
	}

 	if (pid == 0 ) 
	{
	      
		for (int k = 1 ; k < count ; ++k ) 
		{
			close ( pipefd[k][0] ) ; 
			close ( pipefd[k][1] ) ;
		}

		close ( pipefd[0][0] ) ; 
		dup2(pipefd[0][1] , STDOUT_FILENO) ;
		close (pipefd[0][1]) ; 
		execlp(argv[1] , argv[1] , NULL) ;
		return 0 ;
	}


	for (int p = 0 ; p < argc - 3 ; ++p) 
       	{
	        pid = fork() ; 
		if (pid < 0 )
		{
		perror("Unable to fork") ; 
		exit(1) ; 
		}

		if (pid == 0 ) {
	
		dup2(pipefd[p][0] , STDIN_FILENO) ;
		dup2(pipefd[p + 1][1] , STDOUT_FILENO) ;
			
		

		for (int k = 0 ; k < count; ++k)
		{
						
			close(pipefd[k][0]) ; 
			close(pipefd[k][1]) ;
			
		}

			
			execlp(argv[ p + 2 ] , argv[ p + 2 ] , NULL) ;
			return 0 ;
			
		}}
	
	
	
	


	pid_t pid0 = fork() ; 

	if (pid0 < 0 )
	{
		perror ("Unable to do in last fork !") ; 
		exit(1) ;
	}

        if (pid0 == 0 ) 
	{
	    for (int k = 0 ; k < count - 1 ; ++k ) 
	    {
	      close (pipefd[k][0] ) ; 
	      close (pipefd[k][1] ) ;
	    
	    }
	
	    close (pipefd[count - 1 ][1]) ; 
	    dup2(STDIN_FILENO , pipefd[count - 1][0]) ;
	    close ( pipefd[count - 1][0] ) ;
	    execlp(argv[argc - 1] , argv[argc - 1 ] , NULL) ;
	    return 0 ;
	}

	for (int i = 0 ; i < argc - 1  ; ++i)
	{
		wait(NULL) ; 
	}
 
	for (int i = 0; i < count; i++)
        free(pipefd[i]);
 
    free(pipefd);

	return 0;
}

