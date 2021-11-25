#ifndef __REQUEST_H__
#define ThreadsDefault 1
#define BuffersDefault 1

int threads;
int buffersmax;
int buffer;

void request_handle(int fd);

#endif // __REQUEST_H__
