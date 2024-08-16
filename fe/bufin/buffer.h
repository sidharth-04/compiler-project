#ifndef clox_buffer_h
#define clox_buffer_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_LEN 1

typedef struct {
    char buffer1[MAX_BUFFER_LEN];
    char buffer2[MAX_BUFFER_LEN];
    char *nextPos;
    char *currBuffer;
    FILE *fp;
    int finishedReading;
    int inPrevBuffer;
} Buffer;

Buffer *buildBuffer(char filename[]);
void destroyBuffer(Buffer *buf);
char readChar(Buffer *buf);
char peek(Buffer *buf);
void unReadChar(Buffer *buf);

#endif
