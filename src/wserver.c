#include <stdio.h>
#include "request.h"
#include "io_helper.h"
#include <pthread.h> //We include this library in order to implement varius threads.


char default_root[] = ".";

// in this part we just write how we want the C program to be invoked. For now it is like:
// ./wserver [-d <basedir>] [-p <portnum>] 
// where d is the base directory from which the web server should operate. 
// p is the port number that the web server should listen on
// We have to add to this part the t and b part in order to get something like: 
// ./wserver [-d basedir] [-p port] [-t threads] [-b buffers]
// where t is the number of worker threads that should be created within the webserver. Must be a positive integer.
// b is the number of request connections that can be accepted at one time. Must be a positive integer. 
int main(int argc, char *argv[]) {
    int c;
    char *root_dir = default_root;
    int port = 10000;
	pthread_t M_Thread;

//We select the default values that where given in the ReadMe file. Those values are defined on the
//Request.h file

	threads=ThreadsDefault;   //amount of threads
	buffersmax=BuffersDefault; //Maximum size of the buffer
    
    while ((c = getopt(argc, argv, "d:p:t:b:")) != -1)
		switch (c) {
		case 'd':
			root_dir = optarg;
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 't':
			threads = atoi(optarg);
			break;
		case 'b':
			buffersmax = atoi(optarg);
			break;
		default:
		// We made a little change by adding the threads and the buffers
			fprintf(stderr, "usage: wserver [-d basedir] [-p port] [-t threads] [-b buffers]\n");
			exit(1);
	}

	pthread_t thread_pool[threads]; //pthread_t is used to identify a thread
	// We put the the input info in a struct for more the manipulation.
	struct inputINFO INPUT;
		INPUT.input_ports=port;
		INPUT.PointerToPool=thread_pool;
	// run out of this directory
    chdir_or_die(root_dir);
	pthread_create(&M_Thread,NULL,Master_Thread,&INPUT); //we create a new thread
	pthread_join(M_Thread,NULL); //Wait for a specific thread to exit

    return 0;
}


    


 
