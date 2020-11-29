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
	char buffer[sizeof(SOME_DATA)];

	linear_fixed_buffer_backend(&backend, 256);
	stream = stream_new(backend);

	stream_write(stream, SOME_DATA, sizeof(SOME_DATA));
	stream_read(stream, buffer, sizeof(buffer));

	printf("Read from stream: %s", buffer);

	stream_delete(stream);

	return 0;
}
