#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc , char** argv)
{

	if (argc != 3 ) 
	{

          perror("Something wrong in input file names ! Please do it right ! \n") ;
  	  return 1 ; 

	}	

        int fd1 = open ( argv[1] , O_RDONLY , 0666 )  ; 
	
 	if (fd1 < 0 ) 
 	{
	  perror("Wrong input source file name \n") ; 
	  return 1 ;
	}
	
	int fd2 = open (argv[2] , O_WRONLY | O_CREAT , 0666 )  ;
	char buffer[1024] ;
	int readbytes = read( fd1 , buffer , 1024 ) ; 	
	 	
	printf ( "%s" ,"Can I clear the target file or not ? y/n \n") ; 
	 
	char answer[1] = {0} ; 
	if (0 > read  ( 0 , answer , 1 ) ) 
	{
	perror ("Error when you reply in my question \n")  ; 
	return 1 ;
	}

        if (answer[0] == 'n') 

	{
	    
	              
	   lseek (fd2, 0, SEEK_END);
	   if (0 > write (fd2 ,  buffer , readbytes ) )
	   {
	   
		perror ("Error at the moment of copy !") ; 
		return 1;

	   } 
            
	   
	 return 0 ;

	}	

        if (answer[0] == 'y' )
	{
	 
	close (fd2) ; 

	fd2 = open(argv[2] , O_WRONLY | O_TRUNC , 0666 ) ; 
	
	if (0 > write (fd2 ,  buffer , readbytes ) )
           {

                perror ("Error at the moment of copy !") ;
                return 1;

           }
	
	return 0 ;
	}
         	

	perror ("Wrong answer ! " ) ; 
	return 1;   
}
