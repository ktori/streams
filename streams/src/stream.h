/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <streams/stream_backend.h>

struct stream_s
{
	struct stream_backend_s backend;
};
