/*
 * Created by victoria on 11/29/20.
 */

#include <errno.h>
#include <stdlib.h>
#include <streams/pipe.h>

int
stream_pipe_init(stream_pipe_t pipe, stream_t from, stream_t to)
{
	pipe->from = from;
	pipe->to = to;

	return EXIT_SUCCESS;
}

int
stream_pipe_pass(stream_pipe_t pipe)
{
	char c;
	stream_t from = pipe->from;
	stream_t to = pipe->to;

	for (;;)
	{
		switch (stream_read(from, &c, 1))
		{
			case 1:
				if (stream_write(to, &c, 1) == STREAM_IO_ERROR)
					return PIPE_WRITE_ERROR;
				break;
			case 0:
				goto done;
			case STREAM_IO_ERROR:
				if (errno == EAGAIN)
					goto done;
				else
					return PIPE_READ_ERROR;
			default:
				break;
		}
	}

done:
	return EXIT_SUCCESS;
}
