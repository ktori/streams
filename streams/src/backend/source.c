/*
 * Created by victoria on 11/29/20.
 */

#include <backend/source.h>

#include <stdlib.h>

typedef struct source_backend_s {
	void *self;
	source_callback_fn callback;
} *source_backend_t;

size_t
source_backend_read(source_backend_t backend, char *data, size_t size)
{
	return backend->callback(backend->self, data, size);
}

void
source_backend_destroy(source_backend_t backend)
{
	free(backend);
}

int
source_backend(stream_backend_t backend, source_callback_fn callback, void *self)
{
	source_backend_t impl = calloc(1, sizeof(*impl));

	if (!impl)
		return EXIT_FAILURE;

	impl->self = self;
	impl->callback = callback;

	backend->impl = impl;
	backend->def.read = (stream_backend_read_fn)source_backend_read;
	backend->def.write = NULL;
	backend->def.destroy = (stream_backend_destroy_fn)source_backend_destroy;

	return EXIT_SUCCESS;
}
