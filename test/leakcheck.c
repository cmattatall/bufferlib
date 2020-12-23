/**
 * @file leakcheck.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief test to check for memory leaks in ringbuf api
 * @version 0.1
 * @date 2020-12-20
 *
 * @copyright Copyright (c) 2020
 *
 * @note THIS SHOULD BE RUN THROUGH VALGRIND
 */
#include "bufferlib.h"

int main(void)
{
    buffer_handle ringbuf = bufferlib_ringbuf(2000);
    ringbuf.deinit(ringbuf.this);
    return 0;
}