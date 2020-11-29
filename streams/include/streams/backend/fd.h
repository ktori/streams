/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <streams/stream_backend.h>

#define STREAMS_FD_BACKEND_CLOSE_READ 0x1u
#define STREAMS_FD_BACKEND_CLOSE_WRITE 0x2u
#define STREAMS_NO_FD -1

int
fd_backend(stream_backend_t backend, int read_fd, int write_fd, unsigned flags);
