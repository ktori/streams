/*
 * Created by victoria on 11/29/20.
 */

#include <stream_backend.h>

void
stream_backend_destroy(stream_backend_t backend)
{
	backend->def.destroy(backend->impl);
}
