#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "./forker_lib.h"
/*
#############################################################################
#Final Assignmant C Program "Forker_Lib"
#
#Author: Jason M Rupright
#School GVSU
#Class 241
#
#############################################################################
*/

void wait_forker(int argc, char **argv) 
{ 
	//long seconds[argc];
	//long ns[argc];
	//float total[argc];
    int i, stat;
    pid_t pid[argc];
	int mypipefd[2];
	int ret;
	int buf[50];
	//char *(buff)[50] = malloc(sizeof *buff);
	// Instantiate the pipe file descriptor
	ret = pipe(mypipefd);
	int total = 0;
	int max = 0;
	int mcpid = 0;
	
	// Check if pipe error condition
	if(ret == -1){
		perror("ERROR in pipe");
		exit(1);
	}
	// Loop to create arc No. of Child processes via the use of fork()
    for (i=1; i<argc; i++){
		// Child Process Conditional to Do stuff here if its pid is a Child process pid = 0
        if ((pid[i] = fork()) == 0){
			// Secure Leaks 0 is for parent process (read); 1 is for child process(write)
			close(mypipefd[0]);
			// Get the child process PID
			int cpid = getpid();
			// All other child process variables for time keeping
			int total = 0;
			int statusArr;
			long seconds;
			long ns;
			struct timespec start, finish;
			// Start clock
			clock_gettime(CLOCK_REALTIME, &start);
			
			// All these char type variables are for concatenating my command line string with  >/dev/null 2>&1
			char *foo = argv[i];
			char *bar = " >/dev/null 2>&1";
			char str[80];
			strcpy(str, "");
			strcat(str, foo);
			strcat(str, bar);
			
			// Run command itself using system() a wrapper for execv()
            statusArr = system(str);
			
			// If there is an error in the command returned from linux tell the user.
			if( statusArr != 0){
				printf("\nERROR:{%s} is Not a valid Unix/Linux Command!!\nPlease enter valid Unix/Linux command argument in double-quotes.\nUsage: %s \"Unix/Linux Command\"\nExample: %s \"ls -l\" \"sleep 1\" \n", argv[i], argv[0], argv[0]);
				exit(-1);
			}
			// Stop clock on completion and get clock time
			clock_gettime(CLOCK_REALTIME, &finish);
			
			// Calculate run time in (seconds) and ns (nano-seconds)
            //run_time[i] = time(NULL) - time(&start[i]);
			seconds = finish.tv_sec - start.tv_sec;
			ns = finish.tv_nsec - start.tv_nsec;
			
			// Adjust for underrun times
			if (start.tv_nsec > finish.tv_nsec){ // clock underflow
				--seconds;
				ns += 1000000000;
			}
			
			// Collect the child process with max-runtime s.%09
			if( i < argc ){
				total = 1.0e3*(seconds + 1.0e-9*ns );
				printf("\nOUTPUT>>>\nRunning time: %ld (sec) + %ld (ns) = %d.%.3d (seconds) Total; from child: %d (pid); %s (command)\n",seconds, ns, (int) (total/1000), (int) (total%1000), cpid, argv[i]);
				
				printf("\nFROM CHILD PROCESS No. %d TOTAL PTIME: %d\n", i, total);
				write(mypipefd[1], total, 4);
			}
			
			// Finally return seconds through the exit code
            exit(i +1); 
        }
		else{
			// Parent Process
			close(mypipefd[1]);
			
			
			printf("\n");
			pid_t cpid = waitpid(pid[i], &stat, 0);
		
			if (WIFEXITED(stat)){
				int exit = WEXITSTATUS(stat);
				if(cpid > 0){
				read(mypipefd[0], total, 4);
				printf("\nFROM PARENT PROCESS No. %d TOTAL PTIME: %d\n", i, total);
				}
			}

		}
    }
	
    // Using waitpid() and printing exit status 
    // of children. 
	
	
	
	
	
    for (i=1; i<argc; i++){
        
				//printf("No. %d Process Total time: %d\n", i, buf[i]);

    }
	printf("\nThe child process with the Longest Run-Time: %d (pid) At: %d (seconds)\n", mcpid, max);
	printf("\nThe Total Runtime of All Program(s): %d (seconds)\n", total); 
}