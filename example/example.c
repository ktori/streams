/*
 * Created by victoria on 11/29/20.
 */

#include <backend/linear_fixed_buffer.h>
#include <backend/sink.h>
#include <backend/source.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <streams.h>
#include <unistd.h>

const char SOME_DATA[] = "Some data";

#define MAX_READ 65536

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

size_t
fd_sink(const int *fd, const char *data, size_t size)
{
	return write(*fd, data, size);
}

size_t
fd_source(const int *fd, char *data, size_t size)
{
	return read(*fd, data, size);
}

void
basic_pipe_example()
{
	struct stream_backend_s source_bk;
	struct stream_backend_s sink_bk;
	char c = 0;
	stream_t source;
	stream_t sink;
	int source_fd = 1;
	int sink_fd = 0;
	size_t ret;

	source_backend(&source_bk, (source_callback_fn)fd_source, &source_fd);
	sink_backend(&sink_bk, (sink_callback_fn)fd_sink, &sink_fd);

	source = stream_new(source_bk);
	sink = stream_new(sink_bk);

	while (c != EOF)
	{
		ret = stream_read(source, &c, 1);
		if (ret == STREAM_IO_ERROR)
		{
			perror("Source read error");
			break;
		}

		c = toupper(c);

		ret = stream_write(sink, &c, 1);
		if (ret == STREAM_IO_ERROR)
		{
			perror("Sink write error");
			break;
		}
	}

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
