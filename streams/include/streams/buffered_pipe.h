/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <streams/streams.h>

typedef struct stream_buffered_pipe_s
{
	stream_t from;
	stream_t to;
	char *buffer;
	size_t buffer_size;
	size_t buffer_read_at;
	size_t buffer_write_at;
} * stream_buffered_pipe_t;

int
stream_buffered_pipe_init(stream_buffered_pipe_t pipe, stream_t from, stream_t to, size_t buffer_size);

int
stream_buffered_pipe_pass(stream_buffered_pipe_t pipe);

void
stream_buffered_pipe_destroy(stream_buffered_pipe_t pipe);
