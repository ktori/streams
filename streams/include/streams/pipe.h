/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <streams/streams.h>

typedef struct stream_pipe_s
{
	stream_t from;
	stream_t to;
} * stream_pipe_t;

int
stream_pipe_init(stream_pipe_t pipe, stream_t from, stream_t to);

int
stream_pipe_pass(stream_pipe_t pipe);
