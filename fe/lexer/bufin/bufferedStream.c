#include "buffer.c"

typedef struct {
    Buffer *buffer;
    int linecount;
} BufferedStream;

void buildBufferedStream(BufferedStream *stream, char filename[]) {
    stream->buffer = (Buffer *)malloc(sizeof(Buffer));
    buildBuffer(stream->buffer, filename);
    stream->linecount = 1;
}
void destroyBufferedStream(BufferedStream *stream) {
    destroyBuffer(stream->buffer);
    free(stream->buffer);
}

char streamPeek(BufferedStream *stream) {
    return peek(stream->buffer);
}
char streamRead(BufferedStream *stream) {
    char result = readChar(stream->buffer);
    if (result == '\n') {
        stream->linecount++;
    }
    return result;
}
void streamUnread(BufferedStream *stream) {
    unReadChar(stream->buffer);
    if (streamPeek(stream) == '\n') {
        stream->linecount --;
    }
}
int streamLineCount(BufferedStream *stream) {
    return stream->linecount;
}

int testBufferedStream() {
    BufferedStream *stream;
    buildBufferedStream(stream, "hello.cd");
    char c;
    int i = 0;
    while ((c = streamRead(stream)) != EOF) {
        putchar(c);
        i ++;
        if (i == 4) {
            streamUnread(stream);
        }
    }
    return 0;
}