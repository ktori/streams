/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stream_backend.h>

#include <stddef.h>

typedef struct stream_s *stream_t;

/*
 * BaseStream: no callbacks
 * PullStream: read() calls producer
 * PushStream: write() calls consumer
 */

#define STREAM_IO_ERROR ((size_t)-1)

/** Allocate and init stream in heap */
stream_t
stream_new(struct stream_backend_s backend);

/** Destroy and free stream */
void
stream_delete(stream_t stream);

/** Init stream in-place */
void
stream_init(stream_t stream, struct stream_backend_s backend);

/** Destroy stream (does not free()) */
int
stream_destroy(stream_t stream);

size_t
stream_write(stream_t stream, const char *data, size_t size);

size_t
stream_read(stream_t stream, char *data, size_t size);
