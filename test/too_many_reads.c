/**
 * @file too_many_reads.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief Test for too many reads
 * @version 0.1
 * @date 2020-12-20
 *
 * @copyright Copyright (c) 2020 carl mattatall
 *
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "bufferlib.h"

#define TEST_BUF_SIZE 50


int main(void)
{
    int          status = 0;
    unsigned int size;
    for (size = 1; (status == 0) && (size < 2000); size++)
    {
        buffer_handle ringbuf = bufferlib_ringbuf(size);
        unsigned int           i;
        int           byte = '!';
        for (i = 0; (status == 0) && (i < size); i++)
        {
            int byte_written = ringbuf.write_next(ringbuf.this, (char)byte);
            if (byte_written != byte)
            {
                status = 1;
            }
        }

        for (i = 0; (status == 0) && (i < size); i++)
        {
            int byte_read = ringbuf.read_next(ringbuf.this);
            if (byte_read != byte)
            {
                status = 1;
            }
        }

        /* After we've read out as many bytes as we have written,
         * next read should fail
         */
        if (status == 0)
        {
            int byte_read = ringbuf.read_next(ringbuf.this);
            if (byte_read != BUFFERLIB_READ_FAILURE)
            {
                status = 1;
            }
        }

        ringbuf.delete(ringbuf.this);
    }
    return status;
}