/**
 * @file leakcheck.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief test to check for memory leaks in ringbuf api
 * @version 0.1
 * @date 2020-12-20
 *
 * @copyright Copyright (c) 2020
 *
 * @note THIS SHOULD BE RUN THROUGH VALGRIND or another memory checker
 */
#include <limits.h>

#include "bufferlib.h"

int main(void)
{
    unsigned int size;
    /* I want to run it up to UINT_MAX but that takes EONS.
     * could be part of a CI script eventually
     */
    for (size = 0; size < 2000; size++)
    {
        buffer_handle ringbuf = bufferlib_ringbuf_new(size);
        ringbuf.delete(ringbuf.this);
    }
    return 0;
}