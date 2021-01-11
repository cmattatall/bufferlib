/**
 * @file read_in_read_out
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-12-20
 *
 * @copyright Copyright (c) 2020 carl mattatall
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "bufferlib.h"

#define TEST_BUF_SIZE 50

#define TEST_MSG "HelloWorld"

int main(void)
{
    buffer_handle ringbuf    = bufferlib_ringbuf_new(TEST_BUF_SIZE);
    char *        input_buf  = (char *)malloc(TEST_BUF_SIZE);
    char *        output_buf = (char *)malloc(TEST_BUF_SIZE);
    assert(input_buf != NULL);
    assert(output_buf != NULL);
    memset(input_buf, 0, TEST_BUF_SIZE);
    memset(output_buf, 0, TEST_BUF_SIZE);

    strcpy(input_buf, TEST_MSG);

    unsigned int i;
    for (i = 0; i < sizeof(TEST_MSG); i++)
    {
        ringbuf.write_next(ringbuf.this, input_buf[i]);
    }

    for (i = 0; i < sizeof(TEST_MSG); i++)
    {
        int byte_written = ringbuf.read_next(ringbuf.this);
        if (byte_written != BUFFERLIB_WRITE_FAILURE)
        {
            output_buf[i] = (char)byte_written;
        }
        else
        {
            break;
        }
    }

    assert(0 == strcmp(input_buf, output_buf));

    ringbuf.delete(ringbuf.this);
    free(input_buf);
    free(output_buf);
    return 0;
}