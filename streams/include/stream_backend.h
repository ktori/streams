/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stddef.h>

#define STREAM_BACKEND_IO_ERROR ((size_t)-1)

typedef size_t (*stream_backend_read_fn)(void *self, char *data, size_t size);
typedef size_t (*stream_backend_write_fn)(void *self, const char *data, size_t size);
typedef void (*stream_backend_destroy_fn)(void *self);

struct stream_backend_def_s
{
	stream_backend_read_fn read;
	stream_backend_write_fn write;
	stream_backend_destroy_fn destroy;
};

typedef struct stream_backend_s
{
	void *impl;
	struct stream_backend_def_s def;
} *stream_backend_t;

void
stream_backend_destroy(stream_backend_t backend);
