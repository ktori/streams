/*
 * Created by victoria on 11/29/20.
 */

#include <errno.h>
#include <stdio.h>
#include <streams/backend/linear_fixed_buffer.h>
#include <streams/backend/fd.h>
#include <streams/buffered_pipe.h>
#include <streams/streams.h>
#include <unistd.h>

struct az_sequence_source_s
{
	char current;
};

size_t
az_sequence_source(struct az_sequence_source_s *source, char *out, size_t size)
{
	size_t emitted = 0;

	if (source->current == 'z' + 1)
	{
		errno = ERANGE;

		return STREAM_BACKEND_IO_ERROR;
	}

	while (emitted++ < size)
	{
		*out++ = source->current++;
		if (source->current == 'z' + 1)
			break;
	}

	return emitted;
}

void
basic_pipe_example()
{
	struct stream_buffered_pipe_s p;
	struct stream_backend_s source_bk;
	struct stream_backend_s sink_bk;
	stream_t source;
	stream_t sink;

	fd_backend(&source_bk, STDIN_FILENO, STREAMS_NO_FD, 0);
	fd_backend(&sink_bk, STREAMS_NO_FD, STDOUT_FILENO, 0);

	source = stream_new(source_bk);
	sink = stream_new(sink_bk);

	stream_buffered_pipe_init(&p, source, sink, 16);

	switch (stream_buffered_pipe_pass(&p))
	{
		case 0:
			break;
		case PIPE_READ_ERROR:
			perror("Read error");
			break;
		case PIPE_WRITE_ERROR:
			perror("Write error");
			break;
		default:
			perror("Unknown error");
			break;
	}

	stream_buffered_pipe_destroy(&p);

	stream_delete(sink);
	stream_delete(source);
	stream_backend_destroy(&sink_bk);
	stream_backend_destroy(&source_bk);
}

int
main()
{
	basic_pipe_example();

	return 0;
}
