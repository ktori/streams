/*
 * Created by victoria on 11/29/20.
 */

#include <stdlib.h>
#include <streams/backend/fd.h>
#include <unistd.h>

typedef struct fd_backend_data_s
{
	int read_fd;
	int write_fd;
	unsigned flags;
} * fd_backend_data_t;

size_t
fd_backend_read(fd_backend_data_t self, char *out, size_t size)
{
	return read(self->read_fd, out, size);
}

size_t
fd_backend_write(fd_backend_data_t self, const char *in, size_t size)
{
	return write(self->write_fd, in, size);
}

void
fd_backend_destroy(fd_backend_data_t self)
{
	if (self->read_fd >= 0 && (self->flags & STREAMS_FD_BACKEND_CLOSE_READ))
	{
		close(self->read_fd);
		self->read_fd = -1;
	}

	if (self->write_fd >= 0 && (self->flags & STREAMS_FD_BACKEND_CLOSE_WRITE))
	{
		close(self->write_fd);
		self->write_fd = -1;
	}
}

int
fd_backend(stream_backend_t backend, int read_fd, int write_fd, unsigned flags)
{
	fd_backend_data_t impl = calloc(1, sizeof(*impl));

	if (!impl)
		return EXIT_FAILURE;

	impl->read_fd = read_fd;
	impl->write_fd = write_fd;
	impl->flags = flags;

	backend->impl = impl;
	backend->def.read = (read_fd >= 0 ? (stream_backend_read_fn)fd_backend_read : NULL);
	backend->def.write = (write_fd >= 0 ? (stream_backend_write_fn)fd_backend_write : NULL);
	backend->def.destroy = (stream_backend_destroy_fn)fd_backend_destroy;

	return EXIT_SUCCESS;
}
