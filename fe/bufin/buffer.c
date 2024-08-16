#include "buffer.h"

static int openFileSuccessfully(Buffer *buf, char filename[]);
static void closeFile(Buffer *buf);
static void closeBuffer(Buffer *buf);
static int bufferAtEnd(Buffer *buf);
static void switchBuffer(Buffer *buf);
static void reloadBuffer(Buffer *buf);

Buffer *buildBuffer(char filename[]) {
	Buffer *buf = (Buffer *)malloc(sizeof(Buffer));
    if (!openFileSuccessfully(buf, filename)) {
        perror("Couldn't open the specified file.");
    }
    buf->currBuffer = buf->buffer1;
    buf->nextPos = buf->currBuffer;
    buf->finishedReading = 0;
    buf->inPrevBuffer = 0;
    reloadBuffer(buf);
	return buf;
}
static int openFileSuccessfully(Buffer *buf, char filename[]) {
    buf->fp = fopen(filename, "r");
    if (buf->fp == NULL) {
        return 0;
    }
    return 1;
}

void destroyBuffer(Buffer *buf) {
    closeBuffer(buf);
	free(buf);
}
static void closeBuffer(Buffer *buf) {
    buf->finishedReading = 1;
    closeFile(buf);
}
static void closeFile(Buffer *buf) {
    if (!buf->finishedReading) {
		fclose(buf->fp);
	}
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

static int bufferAtEnd(Buffer *buf) {
    if (buf->nextPos == buf->currBuffer + MAX_BUFFER_LEN) {
        return 1;
    }
    return 0;
}
static void switchBuffer(Buffer *buf) {
    if (buf->currBuffer == buf->buffer1) {
        buf->currBuffer = buf->buffer2;
    } else {
        buf->currBuffer = buf->buffer1;
    }
    buf->nextPos = buf->currBuffer;
}
static void reloadBuffer(Buffer *buf) {
    int writeLength = fread(buf->currBuffer, 1, MAX_BUFFER_LEN, buf->fp);
    if (writeLength < MAX_BUFFER_LEN) {
        buf->currBuffer[writeLength] = EOF;
    }
}
