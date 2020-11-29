/*
 * Created by victoria on 11/29/20.
 */

#include <streams/stream_backend.h>

void
stream_backend_init(stream_backend_t backend,
					void *self,
					stream_backend_read_fn read,
					stream_backend_write_fn write,
					stream_backend_destroy_fn destroy)
{
	backend->def.read = read;
	backend->def.write = write;
	backend->def.destroy = destroy;
	backend->impl = self;
}

void
stream_backend_destroy(stream_backend_t backend)
{
	if (backend->def.destroy)
		backend->def.destroy(backend->impl);
}
