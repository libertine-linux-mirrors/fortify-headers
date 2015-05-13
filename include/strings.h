/*
 * Copyright (C) 2015 Dimitris Papastamos <sin@2f30.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _FORTIFY_STRINGS_H
#define _FORTIFY_STRINGS_H

#include_next <strings.h>

#if defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE > 0 && defined(__OPTIMIZE__) && __OPTIMIZE__ > 0
#include "fortify-headers.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE) || defined(_POSIX_SOURCE) \
 || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 < 200809L) \
 || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE+0 < 700)
#undef bcopy
#undef bzero
fortify_fn(bcopy) void bcopy(const void *src, void *dst, size_t n)
{
	size_t bos_dst = __builtin_object_size(dst, 0);
	size_t bos_src = __builtin_object_size(src, 0);

	if (n > bos_dst || n > bos_src)
		__builtin_trap();
	return __orig_bcopy(src, dst, n);
}

fortify_fn(bzero) void bzero(void *src, size_t n)
{
	size_t bos = __builtin_object_size(src, 0);

	if (n > bos)
		__builtin_trap();
	return __orig_bzero(src, n);
}
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif
