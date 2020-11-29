/*
 * Created by victoria on 11/29/20.
 */

#include <streams.h>
#include <backend/linear_fixed_buffer.h>

#include <stdio.h>

const char SOME_DATA[] = "Some data";

int main()
{
	struct stream_backend_s backend;
	stream_t stream;
	char c;
	size_t ret;

	linear_fixed_buffer_backend(&backend, 256);
	stream = stream_new(backend);

	stream_write(stream, SOME_DATA, sizeof(SOME_DATA));

	for (;;) {
		ret = stream_read(stream, &c, 1);

		if (ret == STREAM_IO_ERROR)
		{
			putchar('\n');
			fflush(stdout);
			perror("Stream IO error");
			break;
		}
		else
			putchar(c);
	}

	stream_delete(stream);
	stream_backend_destroy(&backend);

	return 0;
}
