#ifndef bufferedstream_h
#define bufferedstream_h

#include "buffer.h"

typedef struct {
    Buffer *buffer;
    int linecount;
} BufferedStream;

BufferedStream *buildBufferedStream(char filename[]);
void destroyBufferedStream(BufferedStream *stream);
char streamPeek(BufferedStream *stream);
char streamRead(BufferedStream *stream);
void streamUnread(BufferedStream *stream);
int streamLineCount(BufferedStream *stream);

#endif
