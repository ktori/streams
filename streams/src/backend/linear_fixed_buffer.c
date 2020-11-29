/*
 * Created by victoria on 11/29/20.
 */

#include <backend/linear_fixed_buffer.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>

#define LFB_ASSERTS

#ifdef LFB_ASSERTS
#include <assert.h>
#endif

struct stream_backend_def_s linear_fixed_buffer_backend_def = {
	(stream_backend_read_fn)linear_fixed_buffer_backend_read,
	(stream_backend_write_fn)linear_fixed_buffer_backend_write,
	(stream_backend_destroy_fn)linear_fixed_buffer_backend_destroy
};

int
linear_fixed_buffer_backend(struct stream_backend_s *backend, size_t size)
{
	linear_fixed_buffer_backend_t impl = calloc(1, sizeof(*impl));

	if (impl == NULL)
		return EXIT_FAILURE;

	impl->buffer = calloc(size, 1);

	if (impl->buffer == NULL)
	{
		free(impl);

		return EXIT_FAILURE;
	}

	impl->size = size;
	impl->read_ptr = 0;
	impl->write_ptr = 0;

	backend->def = linear_fixed_buffer_backend_def;
	backend->impl = impl;

	return EXIT_SUCCESS;
}

void
linear_fixed_buffer_backend_destroy(linear_fixed_buffer_backend_t backend)
{
	free(backend->buffer);
	backend->buffer = NULL;
	backend->size = 0;
}

size_t
linear_fixed_buffer_backend_read(linear_fixed_buffer_backend_t backend, void *data, size_t size)
{
#ifdef LFB_ASSERTS
	assert(backend->read_ptr <= backend->write_ptr);
	assert(backend->read_ptr <= backend->size);
#endif

	if (backend->read_ptr == backend->write_ptr)
	{
		if (backend->read_ptr == backend->size)
		{
			/* Reading reached end of buffer */
			errno = ERANGE;

			return STREAM_BACKEND_IO_ERROR;
		}

		/* There's no data to read */
		errno = EAGAIN;

		return STREAM_BACKEND_IO_ERROR;
	}

	if (size > backend->write_ptr - backend->read_ptr)
	{
		size = backend->write_ptr - backend->read_ptr;
	}

	memcpy(data, backend->buffer + backend->read_ptr, size);
	backend->read_ptr += size;

	return size;
}

size_t
linear_fixed_buffer_backend_write(linear_fixed_buffer_backend_t backend, const void *data, size_t size)
{
#ifdef LFB_ASSERTS
	assert(backend->write_ptr <= backend->size);
#endif

	if (backend->write_ptr == backend->size)
	{
		/* Writing reached end of buffer */
		errno = ERANGE;

		return STREAM_BACKEND_IO_ERROR;
	}

	if (size > backend->size - backend->write_ptr)
	{
		size = backend->size - backend->write_ptr;
	}

	memcpy(backend->buffer + backend->write_ptr, data, size);
	backend->write_ptr += size;

	return size;
}
