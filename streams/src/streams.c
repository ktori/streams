/*
 * Created by victoria on 11/29/20.
 */

#include "streams/streams.h"

#include "stream.h"

#include <errno.h>
#include <stdlib.h>

/** Allocate and init stream in heap */
stream_t
stream_new(struct stream_backend_s backend)
{
	stream_t result = calloc(1, sizeof(*result));
	stream_init(result, backend);

	return result;
}

/** Destroy and free stream */
void
stream_delete(stream_t stream)
{
	stream_destroy(stream);
	free(stream);
}

/** Init stream in-place */
void
stream_init(stream_t stream, struct stream_backend_s backend)
{
	stream->backend = backend;
}

/** Destroy stream (does not free()) */
int
stream_destroy(stream_t stream)
{
	return EXIT_SUCCESS;
}

size_t
stream_write(stream_t stream, const char *data, size_t size)
{
	if (!stream->backend.def.write)
	{
		/* Stream does not support writing */
		errno = EINVAL;

		return STREAM_IO_ERROR;
	}

	return stream->backend.def.write(stream->backend.impl, data, size);
}

size_t
stream_read(stream_t stream, char *data, size_t size)
{
	if (!stream->backend.def.read)
	{
		/* Stream does not support reading */
		errno = EINVAL;

		return STREAM_IO_ERROR;
	}

	return stream->backend.def.read(stream->backend.impl, data, size);
}
