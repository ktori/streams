/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <streams/stream_backend.h>

typedef size_t (*sink_callback_fn)(void *self, const char *out, size_t size);

int
sink_backend(stream_backend_t backend, sink_callback_fn callback, void *self);