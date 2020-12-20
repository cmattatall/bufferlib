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
    ringbuf_t ringbuf = ringbuf_ctor(2000);
    assert(ringbuf != NULL);

    char *input_buf  = (char *)malloc(TEST_BUF_SIZE);
    char *output_buf = (char *)malloc(TEST_BUF_SIZE);
    assert(input_buf != NULL);
    assert(output_buf != NULL);
    memset(input_buf, 0, TEST_BUF_SIZE);
    memset(output_buf, 0, TEST_BUF_SIZE);

    strcpy(input_buf, TEST_MSG);

    int i;
    for (i = 0; i < sizeof(TEST_MSG); i++)
    {
        ringbuf_write_next_byte(ringbuf, input_buf[i]);
    }

    for (i = 0; i < sizeof(TEST_MSG); i++)
    {
        char *next = ringbuf_read_next(ringbuf);
        assert(NULL != next);
        output_buf[i] = *next;
    }

    assert(0 == strcmp(input_buf, output_buf));


    ringbuf_dtor(ringbuf);
    free(input_buf);
    free(output_buf);
    return 0;
}