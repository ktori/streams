/*
 * Created by victoria on 11/29/20.
 */

#pragma once

#include <stream_backend.h>

#include <stdint.h>
#include <stddef.h>

struct stream_s
{
	struct stream_backend_s backend;
};
