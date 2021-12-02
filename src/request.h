#ifndef __REQUEST_H__
#include <pthread.h> 
#define ThreadsDefault 1
#define BuffersDefault 1


int threads;
int buffersmax;
int buffer;

void request_handle(int fd);//Given by the teaches, performs most of the work for 
//handling requests in the basic web server.


//The function that we will use in order to really manage the threads (FIFO):
// Take the request from the queue of the buffer 
void* request_buffer_handler(void* arg);
void *Master_Thread(void *args);

struct inputINFO{
  int input_th;
  int input_buff;
  int input_ports;
  pthread_t *PointerToPool;
}InputINFO;

//struc table with the number of threads, buffer, ports, ppointer to the pool of t
//*threadmaster *args

#endif // __REQUEST_H__
