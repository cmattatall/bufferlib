/**
 * @file pingbuf.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief bufferlib implementation of pingpong buffer
 * @version 0.1
 * @date 2020-12-23
 *
 * @copyright Copyright (c) 2020 Carl Mattatall
 *
 * @note
 */

#include <string.h>
#include <assert.h>
#include "fat_pointer.h"

#include "pingbuf.h"

#include "ringbuf.h"

struct pingbuf
{
    unsigned int       bank_idx;
    unsigned int       bank_cnt;
    char *             in_ptr;
    char *             out_ptr;
    unsigned int       bcnt;
    unsigned int       total_size;
    struct fat_pointer buf[2];
};


buffer_instance_handle pingbuf_ctor(unsigned int size)
{
    /**
     * Honestly, an N-bank pingpong buffer is really just a ring buffer
     * with extra computational overhead and problems to solve regarding
     * concurrency race conditions. Until I actually ever need an explicit
     * pingpong buffer, I'm just going to use the ring buffer implementation...
     */
    return ringbuf_ctor_new(size);
}


buffer_instance_handle pingbuf_ctor_internal(unsigned int size)
{
    buffer_instance_handle handle;
    if (size < PINGBUF_BANK_COUNT)
    {
        handle = NULL;
    }
    else
    {
        struct pingbuf *pingbuf = malloc(sizeof(*pingbuf));
        assert(pingbuf != NULL);
        pingbuf->bank_idx = 0;
        pingbuf->bcnt     = 0;
        pingbuf->bank_cnt = PINGBUF_BANK_COUNT; /* for now, we use PP def */

        unsigned int remainder  = size % pingbuf->bank_cnt;
        unsigned int bank_size  = (size - remainder) / pingbuf->bank_cnt;
        unsigned int bank0_size = bank_size + remainder;
        pingbuf->buf[0].start   = malloc(bank0_size);
        assert(pingbuf->buf[0].start != NULL);
        memset(pingbuf->buf[0].start, 0, bank0_size);

        /* start at first bank */
        pingbuf->in_ptr  = pingbuf->buf[0].start;
        pingbuf->out_ptr = pingbuf->buf[0].start;

        /* Alloc other banks */
        unsigned int i;
        for (i = 1; i < pingbuf->bank_cnt; i++)
        {
            pingbuf->buf[i].start = malloc(bank_size);
            assert(pingbuf->buf[i].start != NULL);
            memset(pingbuf->buf[i].start, 0, bank_size);
            pingbuf->buf[i].size = bank_size;
        }
        pingbuf->total_size = size;
    }
    return handle;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static void            pingbuf_dtor_internal(buffer_instance_handle *this)
{
    if (*this != NULL)
    {
        struct pingbuf *pingbuf = *this;
        assert(pingbuf != NULL);
        unsigned int i;
        for (i = 0; i < pingbuf->bank_cnt; i++)
        {
            free(pingbuf->buf[i].start);
        }
        free(pingbuf);
        *this = NULL;
    }
}
#pragma GCC diagnostic pop


#if 0
int pingbuf_read_next(buffer_instance_handle this)
{   
    (void)this;
    return BUFFERLIB_READ_FAILURE;
}


int pingbuf_write_next(buffer_instance_handle this, char byte)
{
    (void)this;
    (void)byte;
    return BUFFERLIB_WRITE_FAILURE;
}


unsigned int pingbuf_size(buffer_instance_handle this)
{
    struct pingbuf *pingbuf = this;
    return pingbuf->total_size;
}
#endif