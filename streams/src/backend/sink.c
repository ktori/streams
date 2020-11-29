/*
 * Created by victoria on 11/29/20.
 */

#include <backend/sink.h>

#include <stdlib.h>

typedef struct sink_backend_s {
	void *self;
	sink_callback_fn callback;
} *sink_backend_t;

size_t
sink_backend_write(sink_backend_t backend, const char *data, size_t size)
{
	return backend->callback(backend->self, data, size);
}

void
sink_backend_destroy(sink_backend_t backend)
{
	free(backend);
}

int
sink_backend(stream_backend_t backend, sink_callback_fn callback, void *self)
{
	sink_backend_t impl = calloc(1, sizeof(*impl));

	if (!impl)
		return EXIT_FAILURE;

	impl->self = self;
	impl->callback = callback;

	backend->impl = impl;
	backend->def.read = NULL;
	backend->def.write = (stream_backend_write_fn)sink_backend_write;
	backend->def.destroy = (stream_backend_destroy_fn)sink_backend_destroy;

	return EXIT_SUCCESS;
}
