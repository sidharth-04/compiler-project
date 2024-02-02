#include <stdio.h>

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

int openFileSuccessfully(Buffer *buf, char filename[]);
int bufferAtEnd(Buffer *buf);
void switchBuffer(Buffer *buf);
void reloadBuffer(Buffer *buf);
void closeFile(Buffer *buf);

void buildBuffer(Buffer *buf, char filename[]) {
    if (!openFileSuccessfully(buf, filename)) {
        perror("Couldn't open the specified file.");
    }
    buf->currBuffer = buf->buffer1;
    buf->nextPos = buf->currBuffer;
    buf->finishedReading = 0;
    buf->inPrevBuffer = 0;
    reloadBuffer(buf);
}
void destroyBuffer(Buffer *buf) {
    if (!buf->finishedReading) {
        closeFile(buf);
    }
}

int openFileSuccessfully(Buffer *buf, char filename[]) {
    buf->fp = fopen(filename, "r");
    if (buf->fp == NULL) {
        return 0;
    }
    return 1;
}
void closeFile(Buffer *buf) {
    fclose(buf->fp);
}
void closeBuffer(Buffer *buf) {
    buf->finishedReading = 1;
    closeFile(buf);
}

char readChar(Buffer *buf) {
    if (buf->finishedReading) return EOF;
    char c = *buf->nextPos;
    if (c == EOF) {
        closeBuffer(buf);
        return EOF;
    }
    buf->nextPos ++;
    if (bufferAtEnd(buf)) {
        switchBuffer(buf);
        if (buf->inPrevBuffer) {
            buf->inPrevBuffer = 0;
        } else {
            reloadBuffer(buf);
        }
    }
    return c;
}
char peek(Buffer *buf) {
    if (buf->finishedReading) return EOF;
    return *buf->nextPos;
}
void unReadChar(Buffer *buf) {
    if (buf->nextPos == buf->currBuffer) {
        switchBuffer(buf);
        buf->nextPos += MAX_BUFFER_LEN - 1;
        buf->inPrevBuffer = 1;
    } else {
        buf->nextPos --;
    }
    
}

int bufferAtEnd(Buffer *buf) {
    if (buf->nextPos == buf->currBuffer + MAX_BUFFER_LEN) {
        return 1;
    }
    return 0;
}
void switchBuffer(Buffer *buf) {
    if (buf->currBuffer == buf->buffer1) {
        buf->currBuffer = buf->buffer2;
    } else {
        buf->currBuffer = buf->buffer1;
    }
    buf->nextPos = buf->currBuffer;
}

void reloadBuffer(Buffer *buf) {
    int writeLength = fread(buf->currBuffer, 1, MAX_BUFFER_LEN, buf->fp);
    if (writeLength < MAX_BUFFER_LEN) {
        buf->currBuffer[writeLength] = EOF;
    }
}