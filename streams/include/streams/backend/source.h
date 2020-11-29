/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <streams/stream_backend.h>

typedef size_t (*source_callback_fn)(void *self, char *out, size_t size);

int
source_backend(stream_backend_t backend, source_callback_fn callback, void *self);
