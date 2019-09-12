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
	
	
    for (i=1; i<argc; i++){ 
        if ((pid[i] = fork()) == 0){
			int cpid = getpid();
			int total = 0;
			int statusArr;
			long seconds;
			long ns;
			struct timespec start, finish;
			clock_gettime(CLOCK_REALTIME, &start);
			char *foo = argv[i];
			char *bar = " >/dev/null 2>&1";
			char str[80];
			strcpy(str, "");
			strcat(str, foo);
			strcat(str, bar);
            statusArr = system(str);
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
			}
			
			//finally return seconds through the exit code
            exit(seconds & 0xff); 
        } 
    } 
  
    // Using waitpid() and printing exit status 
    // of children. 
	int total = 0;
	int max = 0;
	int mcpid = 0;
    for (i=1; i<argc; i++){
        pid_t cpid = waitpid(pid[i], &stat, 0);
		
        if (WIFEXITED(stat)){
			int exit = WEXITSTATUS(stat);
			if(cpid > 0){
				//Itterate through all exit status seconds run time for each child
				//If greater thatn current Total that child become the newet winner 
				//In the Longest Runtime child process race.
				if(max <= exit){
					max = exit;
					mcpid = cpid;
				}
				//tally up all totals
				total += exit;
				printf("\nChild %d terminated with time: %d (sec)\n",
                   cpid, exit);
			}
		}
    }
	printf("\nThe child process with the Longest Run-Time: %d (pid) At: %d (seconds)\n", mcpid, max);
	printf("\nThe Total Runtime of All Program(s): %d (seconds)\n", total); 
}