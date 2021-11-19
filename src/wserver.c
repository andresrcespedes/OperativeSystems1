#include <stdio.h>
#include "request.h"
#include "io_helper.h"

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
    
    while ((c = getopt(argc, argv, "d:p:")) != -1)
	switch (c) {
	case 'd':
	    root_dir = optarg;
	    break;
	case 'p':
	    port = atoi(optarg);
	    break;
	default:
	    fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
	    exit(1);
	}

    // run out of this directory
    chdir_or_die(root_dir);

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


    


 
