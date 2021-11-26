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

//We select the default values that where given in the ReadMe file. Those values are defined on the
//Request.h file

	threads=ThreadsDefault;   //amount of threads
	buffermax=BuffersDefault; //Maximum size of the buffer
    
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
	    buffermax = atoi(optarg);
	    break;
	default:
	// We made a little change by adding the threads and the buffers
	    fprintf(stderr, "usage: wserver [-d basedir] [-p port] [-t threads] [-b buffers]\n");
	    exit(1);
	}

    // run out of this directory
    chdir_or_die(root_dir);

	//The Threads part:
	// 1st we have to create a thread pool depending on the number of threads that we want
	pthread_t thread_pool[threads]; //pthread_t is used to identify a thread
	for(int i=0; i<threads; i++)
	//create a new thread, as we want the default attributes for simplicity, we can left 
	// it as NULL
    	pthread_create(&thread_pool[i], NULL, request_buffer_handler, NULL); //
	// we can initialize the buffer size in 0
	buffer = 0;	

    // now, get to work
    int listen_fd = open_listen_fd_or_die(port);
    while (1) {
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int conn_fd = accept_or_die(listen_fd, (sockaddr_t *) &client_addr, (socklen_t *) &client_len);
	request_handle(conn_fd);
	close_or_die(conn_fd);
    }
    return 0;
}


    


 
