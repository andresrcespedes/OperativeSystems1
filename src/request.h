#ifndef __REQUEST_H__
#include <pthread.h> 
#define ThreadsDefault 1
#define BuffersDefault 1


int threads;
int buffersmax;
int buffer;

void request_handle(int fd);//Given by the teacher, performs most of the work for 
//handling requests in the basic web server.


//We have been asked for a master thread and a worker threads that are in a producer-consumer
//relationship and require that their accesses to the shared buffer be synchronized.
// They are made in the functions:
void *Master_Thread(void *args);          //Master Thread
void* request_buffer_handler(void* arg);  //Worker Threads

struct inputINFO{
  int input_th;
  int input_buff;
  int input_ports;
  pthread_t *PointerToPool;
}InputINFO;


#endif // __REQUEST_H__
