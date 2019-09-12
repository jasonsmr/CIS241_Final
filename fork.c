#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>

float child_array(char * string){
    pid_t children;
	pid_t pid;
	long seconds;
	long ns;
	float total = 0.0000;
    int i;
	
	//initialize struct timespec and start and finish arrays
	struct timespec start, finish;
	int status;
	
	children = fork();
	if( children == 0 )  {
		//start running timing struct mechanics (using start for each children itterator)
		clock_gettime(CLOCK_REALTIME, &start);
		// Chunk of code for the child to run permanently...
		
		// Actualy run the child process for each children itterator
		pid = getpid();
			
		// Caculate timing information and display, or return it for children

        //start = time(NULL);
			
		// 
        // chew up some CPU time
		//int i,j; for (i=0,j=0; i<100000000; i++) { j+=i*i; }
		//sleep(3);
		status = system(string);
		if( status != 0){
			printf("ERROR:{%s} is Not a valid Unix/Linux Command!!\nPlease enter valid Unix/Linux command argument in parenthisis.\nUsage: ./project.bin \"Unix/Linux Command\"\nExample: ./project.bin \"ls -l\" \"sleep 1\" \n", string);
			exit(-1);
		}
		// Stop clock on completion and get clock time
		clock_gettime(CLOCK_REALTIME, &finish);
			
		// Calculate run time in (seconds) and ns (nano-seconds)
        //run_time = time(NULL) - time(&start);
		seconds = finish.tv_sec - start.tv_sec;
		ns = finish.tv_nsec - start.tv_nsec;
			
		// Stores run_time as seconds
		//time(&run_time);
		// prints run_time out to user
			
		// Adjust for underrun times
		if (start.tv_nsec > finish.tv_nsec) { // clock underflow
			--seconds;
			ns += 1000000000;
		}
			
		// Add up the total time in sec and ns to seconds
		total = ((double)seconds + (double)ns/(double)1000000000);
			
		//print the time for each forked process run.
		//printf("\nOUTPUT>>>\nRunning time: %ld (sec) + %ld (ns) = %f (seconds) from child: %d (pid); %s (command)\n",seconds, ns, total, pid, string);

		// Adds additional itterations to the total runtime for the program
		// Can be checked against a start and stop time clock experimentaly
		//printf("\nThis time: %f", total);
		
		// Final Print and check that we are printing only if current parallel fork is at least equal to first seconds itteration
		//printf("\nThe %d-process time = %f\n",i, total);
			
			
		// Return the runtime as an 8-bit integer
        exit(seconds & 0xff);
	}
	if( ( children=waitpid(-1,&status,0))!=-1 ){
		if(total != 0.0000)
			return total;
		else{printf("SWEET COMPLETED WITH FAITAL ERROR NO. 1!");exit(-1);}
	}else{printf("SWEET COMPLETED WITH FAITAL ERROR NO. 2!");exit(-1);}
}