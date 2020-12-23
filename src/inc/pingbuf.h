#ifndef __PING_BUF_H__
#define __PING_BUF_H__
#ifdef __cplusplus
/* clang-format off */
extern "C"
{
/* clang-format on */
#endif /* Start C linkage */

#include "bufferlib.h"

#define PINGBUF_BANK_COUNT 2

/**
 * @brief pingbuf constructor
 *
 * @param size size of ring buffer
 * @return buffer_instance_handle buffer handle
 */
buffer_instance_handle pingbuf_ctor(size_t size);


/**
 * @brief pingbuf destructor
 *
 * @param pingbuf pointer to buffer handle
 */
void pingbuf_dtor(buffer_instance_handle *this);


/**
 * @brief threadsafe read of byte from ring buffer
 *
 * @param pingbuf buffer handle
 * @return data in buffer : address of current byte in ring buffer
 *         no data in buffer : NULL
 *
 * @note reading from the ring buffer advances the outptr
 * @note thread safe
 */
int pingbuf_read_next(buffer_instance_handle this);


/**
 * @brief thread safe write to ring buffer
 *
 * @param pingbuf buffer handle
 * @param byte byte to write
 *
 * @note thread safe
 * @note Will overwrite data
 */
int pingbuf_write_next(buffer_instance_handle this, char byte);


/**
 * @brief get the buffer size
 *
 * @param this buffer handle
 * @return size_t size of buffer
 */
size_t pingbuf_size(buffer_instance_handle this);

#ifdef __cplusplus
/* clang-format off */
}
/* clang-format on */
#endif /* End C linkage */
#endif /* __PING_BUF_H__ */
