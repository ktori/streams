/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stddef.h>
#include <streams/stream_backend.h>

typedef struct stream_s
{
	struct stream_backend_s backend;
} *stream_t;

#define STREAM_IO_ERROR ((size_t)-1)

#define PIPE_READ_ERROR  -1
#define PIPE_WRITE_ERROR -2

/** Allocate and init stream in heap */
stream_t
stream_new();

/** Destroy and free stream */
void
stream_delete(stream_t stream);

/** Init stream in-place */
void
stream_init(stream_t stream);

/** Destroy stream (does not free()) */
int
stream_destroy(stream_t stream);

size_t
stream_write(stream_t stream, const char *data, size_t size);

size_t
stream_read(stream_t stream, char *data, size_t size);
