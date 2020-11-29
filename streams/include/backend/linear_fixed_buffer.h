/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stream_backend.h>

typedef struct linear_fixed_buffer_backend_s
{
	char *buffer;
	size_t size;
	size_t read_ptr;
	size_t write_ptr;
} * linear_fixed_buffer_backend_t;

struct stream_backend_def_s linear_fixed_buffer_backend_def;

int
linear_fixed_buffer_backend(struct stream_backend_s *backend, size_t size);

void
linear_fixed_buffer_backend_destroy(linear_fixed_buffer_backend_t backend);

size_t
linear_fixed_buffer_backend_read(linear_fixed_buffer_backend_t backend, void *data, size_t size);

size_t
linear_fixed_buffer_backend_write(linear_fixed_buffer_backend_t backend, const void *data, size_t size);
