/**
 * @file bufferlib.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-12-23
 *
 * @copyright Copyright (c) 2020 Carl Mattatall
 *
 * @note
 */

#include <string.h>

#include "bufferlib.h"
#include "ringbuf.h"


buffer_handle bufferlib_ringbuf(unsigned int size)
{
    buffer_handle handle;
    handle.this       = ringbuf_ctor(size);
    handle.size       = &ringbuf_size;
    handle.read_next  = &ringbuf_read_next;
    handle.write_next = &ringbuf_write_next;
    handle.delete     = &ringbuf_dtor;
    return handle;
}
