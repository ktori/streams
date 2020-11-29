/*
 * Created by victoria on 11/29/20.
 */

#include <errno.h>
#include <stdlib.h>
#include <streams/buffered_pipe.h>

int
stream_buffered_pipe_init(stream_buffered_pipe_t pipe, stream_t from, stream_t to, size_t buffer_size)
{
	pipe->from = from;
	pipe->to = to;
	pipe->buffer_write_at = 0;
	pipe->buffer_read_at = 0;
	pipe->buffer_size = buffer_size;
	pipe->buffer = calloc(buffer_size, sizeof(char));

	if (!pipe->buffer)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int
stream_buffered_pipe_pass(stream_buffered_pipe_t pipe)
{
	size_t count;
	struct stream_buffered_pipe_s pipe_copy = *pipe;

	for (;;)
	{
		if (pipe->buffer_write_at < pipe->buffer_read_at)
		{
			count = stream_write(
			  pipe_copy.to, pipe_copy.buffer + pipe->buffer_write_at, pipe->buffer_read_at - pipe->buffer_write_at);

			if (count == STREAM_IO_ERROR)
			{
				if (errno == EAGAIN)
					return EXIT_FAILURE;

				return PIPE_WRITE_ERROR;
			} else
			{
				pipe->buffer_write_at += count;
			}
		} else
		{
			count = stream_read(pipe_copy.from, pipe_copy.buffer, pipe_copy.buffer_size);

			if (count == STREAM_IO_ERROR)
			{
				if (errno == EAGAIN)
					return EXIT_FAILURE;

				return PIPE_READ_ERROR;
			} else if (count == 0) {
				return EXIT_SUCCESS;
			} else
			{
				pipe->buffer_read_at = count;
				pipe->buffer_write_at = 0;
			}
		}
	}
}

void
stream_buffered_pipe_destroy(stream_buffered_pipe_t pipe)
{
	free(pipe->buffer);
	pipe->buffer = NULL;
}
